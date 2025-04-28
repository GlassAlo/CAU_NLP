/*
** File: Main.cpp                                                              *
** Project: CAU_NLP                                                            *
** Created Date: Sa Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Mon Apr 28 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments *
** ----------	---
*---------------------------------------------------------  *
*/

#include <boost/range/algorithm/sort.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "DocumentHandler.hpp"
#include "MatrixCreator.hpp"
#include "QueryHandler.hpp"
#include "Sanitizer.hpp"
#include "Utils.hpp"
#include "RedSVD/RedSVD-h"
#include <unordered_map>

constexpr std::string folderName = "./games_data";

namespace {
    auto getQueryWeight(Shared::Sanitizer *aSanitizer) -> std::unordered_map<std::string, double>
    {
        std::unordered_map<std::string, double> queryWeight;
        auto queryTuple = Boolean::QueryHandler::getQuery();
        auto query = std::get<0>(queryTuple);
        aSanitizer->sanitizeTokenList(query, true);

        for (const auto &token : query) {
            queryWeight[token]++;
        }

        for (auto &[token, weight] : queryWeight) {
            weight /= static_cast<double>(query.size());
        }

        return queryWeight;
    }

    auto createMatrix(Shared::Sanitizer *aSanitizer) -> void
    {
        auto files = Shared::Utils::openFolder(folderName);
        Shared::MatrixCreator::DocumentList documentList;

        for (const auto &file : files) {
            documentList.emplace_back("games_data/" + file, file, aSanitizer);
        }

        Shared::MatrixCreator matrixCreator;
        matrixCreator.createMatrix(documentList);

        matrixCreator.setTokensWeight(documentList);
        matrixCreator.dumpMatrix();
    }

    auto computeCosineSimilarity(const std::unordered_map<std::string, double> &aQueryWeight,
                                 const Shared::MatrixCreator::Matrix &aMatrix) -> std::vector<std::string>
    {
        std::unordered_map<std::string, double> documentScore = {};
        std::unordered_map<std::string, double> documentNorm = {};
        std::vector<std::string> result;

        for (const auto &[docName, tokens] : aMatrix) {
            for (const auto &[token, weight] : tokens) {
                if (aQueryWeight.find(token) == aQueryWeight.end()) {
                    continue;
                }
                documentScore[docName] += aQueryWeight.at(token) * weight;
                documentNorm[docName] += weight * weight;
            }
            documentNorm[docName] = std::sqrt(documentNorm[docName]);
        }

        for (const auto &[docName, score] : documentScore) {
            documentScore[docName] /= documentNorm[docName];
        }

        result.reserve(documentScore.size());
        for (const auto &[docName, score] : documentScore) {
            result.push_back(docName);
        }
        boost::range::sort(result, [&documentScore](const std::string &scoreA, const std::string &scoreB) {
            return documentScore[scoreA] > documentScore[scoreB];
        });

        return result;
    }

    auto LSI(Shared::MatrixCreator &aMatrix, const std::unordered_map<std::string, double> &aQueryWeight)
        -> std::vector<std::pair<std::string, double>>
    {
        auto &docNames = aMatrix.getMatrix();
        const auto &matrix = aMatrix.getEigenMatrix();
        auto term_to_index = aMatrix.getTermToIndex();
        int k = 1500;

        RedSVD::RedSVD svd(matrix, k);
        Eigen::MatrixXd U = svd.matrixU();
        Eigen::MatrixXd S = svd.singularValues();
        Eigen::MatrixXd V = svd.matrixV();
        Eigen::MatrixXd D = V * S.asDiagonal();

        for (int i = 0; i < D.rows(); ++i) {
            double norm = D.row(i).norm();
            if (norm > 0) {
                D.row(i) /= norm;
            }
        }

        Eigen::VectorXd queryVectorTermSpace = Eigen::VectorXd::Zero(static_cast<long>(term_to_index.size()));

        for (const auto &[term, weight] : aQueryWeight) {
            auto itx = term_to_index.find(term);
            if (itx != term_to_index.end()) {
                int index = itx->second;
                queryVectorTermSpace(index) = weight;
            }
            // If the term is not found, it's ignored
        }

        Eigen::VectorXd q_proj = U.transpose() * queryVectorTermSpace; // Resulting vector in latent space

        double q_norm = q_proj.norm();
        if (q_norm > 0) {
            q_proj /= q_norm;
        }
        std::vector<std::pair<std::string, double>> similarities;

        for (int i = 0; i < D.rows(); ++i) {
            double dot_product = D.row(i).dot(q_proj);
            int y = 0;

            for (const auto &[docName, _] : docNames) {
                if (i == y) {
                    similarities.emplace_back(docName, dot_product);
                    break;
                }
                y++;
            }
        }

        boost::range::sort(similarities,
                           [](const std::pair<std::string, double> &a, const std::pair<std::string, double> &b) {
                               return a.second > b.second;
                           });

        return similarities;
    }
} // namespace

int main()
{
    std::unique_ptr<Shared::Sanitizer> sanitizerPtr = std::make_unique<Shared::Sanitizer>("./UselessWords.txt");
    Shared::MatrixCreator matrixCreator;
    if (!matrixCreator.loadMatrix("matrix_dump.json")) {
        createMatrix(sanitizerPtr.get());
    } else {
        auto querTuple = Boolean::QueryHandler::getQuery("Would you like to refresh the matrix? (y/n): ");
        auto query = std::get<0>(querTuple);
        if (!query.empty() && query[0] == "y") {
            createMatrix(sanitizerPtr.get());
        }
    }
    auto queryWeight = getQueryWeight(sanitizerPtr.get());
    auto result = computeCosineSimilarity(queryWeight, matrixCreator.getMatrix());

    matrixCreator.createEigenMatrix();
    auto lsiResult = LSI(matrixCreator, queryWeight);

    int index = 0;
    const int nbrMaxResults = 10;
    const int nbrResults = std::min(nbrMaxResults, static_cast<int>(result.size()));

    if (nbrResults == 0) {
        std::cout << "No results found.\n";
        return 0;
    }
    std::cout << "Top " << nbrResults << " results in normal space:\n";
    for (const auto &doc : result) {
        std::cout << doc << "\n";
        if (++index == nbrResults) {
            break;
        }
    }
    index = 0;
    std::cout << "\nTop " << nbrResults << " results in latent space:\n";
    for (const auto &[docName, score] : lsiResult) {
        std::cout << docName << " - " << score << "\n";
        if (++index == nbrResults) {
            break;
        }
    }
    std::cout << "\n";
    return 0;
}
