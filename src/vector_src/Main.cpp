/*
** File: Main.cpp                                                              *
** Project: CAU_NLP                                                            *
** Created Date: Sa Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Wed Mar 26 2025                                              *
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
#include <string>
#include <vector>
#include "DocumentHandler.hpp"
#include "MatrixCreator.hpp"
#include "QueryHandler.hpp"
#include "Sanitizer.hpp"
#include "Utils.hpp"
#include <unordered_map>

constexpr std::string folderName = "./games_data";

namespace {
    auto getQueryWeight() -> std::unordered_map<std::string, double>
    {
        std::unordered_map<std::string, double> queryWeight;
        auto query = Boolean::QueryHandler::getQuery();

        for (const auto &token : query) {
            queryWeight[token]++;
        }

        for (auto &[token, weight] : queryWeight) {
            weight /= static_cast<double>(query.size());
        }

        return queryWeight;
    }

    auto createMatrix() -> void
    {
        auto *sanitizer = new Shared::Sanitizer("./UselessWords.txt");
        auto files = Shared::Utils::openFolder(folderName);
        Shared::MatrixCreator::DocumentList documentList;

        for (const auto &file : files) {
            documentList.emplace_back("games_data/" + file, file, sanitizer);
        }

        Shared::MatrixCreator matrixCreator;
        matrixCreator.createMatrix(documentList);

        matrixCreator.setTokensWeight(documentList);
        matrixCreator.dumpMatrix();
        delete sanitizer;
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
} // namespace

int main()
{
    Shared::MatrixCreator matrixCreator;
    if (!matrixCreator.loadMatrix("matrix_dump.txt")) {
        createMatrix();
    } else {
        auto query = Boolean::QueryHandler::getQuery("Would you like to refresh the matrix? (y/n): ");
        if (!query.empty() && query[0] == "y") {
            createMatrix();
        }
    }
    auto queryWeight = getQueryWeight();
    auto result = computeCosineSimilarity(queryWeight, matrixCreator.getMatrix());
    int index = 0;
    const int nbrMaxResults = 10;
    const int nbrResults = std::min(nbrMaxResults, static_cast<int>(result.size()));

    if (nbrResults == 0) {
        std::cout << "No results found.\n";
        return 0;
    }
    std::cout << "Top " << nbrResults << " results:\n";
    for (const auto &doc : result) {
        std::cout << doc << "\n";
        if (++index == nbrResults) {
            break;
        }
    }
    return 0;
}
