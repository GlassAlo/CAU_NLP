/*
** File: Main.cpp                                                              *
** Project: CAU_NLP                                                            *
** Created Date: Sa Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Tue Apr 01 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments *
** ----------	---
*---------------------------------------------------------  *
*/

#include <boost/range/algorithm/find.hpp>
#include <memory>
#include "DocumentHandler.hpp"
#include "InvertedIndex.hpp"
#include "MatrixCreator.hpp"
#include "RelevanceHandler.hpp"
#include "Sanitizer.hpp"
#include "Utils.hpp"

constexpr std::string folderName = "./games_data";

namespace {
    auto createInvertedIndex(Boolean::InvertedIndex &aInvertedIndex, Shared::Sanitizer *aSanitizer) -> void
    {
        auto files = Shared::Utils::openFolder(folderName);
        Shared::MatrixCreator::DocumentList documentList;

        for (const auto &file : files) {
            documentList.emplace_back("games_data/" + file, file, aSanitizer);
        }

        Shared::MatrixCreator matrixCreator;
        matrixCreator.createMatrix(documentList);

        aInvertedIndex.createInvertedIndex(matrixCreator);
    }
} // namespace

int main()
{
    Boolean::InvertedIndex invertedIndex;
    std::unique_ptr<Shared::Sanitizer> sanitizerPtr = std::make_unique<Shared::Sanitizer>("./UselessWords.txt");
    if (!invertedIndex.loadInvertedMap("inverted_map_dump.json")) {
        createInvertedIndex(invertedIndex, sanitizerPtr.get());
        invertedIndex.dumpInvertedMap();
    } else {
        auto queryTuple = Boolean::QueryHandler::getQuery("Would you like to refresh the inverted index? (y/n): ");
        auto query = std::get<0>(queryTuple);
        if (!query.empty() && query[0] == "y") {
            invertedIndex.clearInvertedMap();
            createInvertedIndex(invertedIndex, sanitizerPtr.get());
            invertedIndex.dumpInvertedMap();
        }
    }

    auto queryTuple = Boolean::QueryHandler::getQuery();
    auto query = std::get<0>(queryTuple);
    auto queryString = std::get<1>(queryTuple);
    sanitizerPtr->sanitizeTokenList(query, true);
    auto results = invertedIndex.getQueryResults(query);

    std::cout << "Query results: ";
    for (const auto &doc : results) {
        std::cout << doc << ' ';
    }
    std::cout << '\n';

    try {
        Boolean::RelevanceHandler relevanceHandler;
        auto relevanceData = relevanceHandler.getRelevanceData(queryString);
        double precision = relevanceHandler.getPrecision(queryString, results);
        double recall = relevanceHandler.getRecall(queryString, results);
        double f1Score = relevanceHandler.getF1Score(queryString, results);

        std::cout << "Relevant documents: ";
        for (const auto &doc : relevanceData) {
            std::cout << doc << ' ';
        }
        std::cout << '\n';
        std::cout << "Precision: " << precision << '\n';
        std::cout << "Recall: " << recall << '\n';
        std::cout << "F1 Score: " << f1Score << '\n';

        std::cout << "Documents that are different between results and relevance data: ";
        for (const auto &doc : results) {
            if (boost::range::find(relevanceData, doc) == relevanceData.end()) {
                std::cout << doc << ' ';
            }
        }
        for (const auto &doc : relevanceData) {
            if (boost::range::find(results, doc) == results.end()) {
                std::cout << doc << ' ';
            }
        }
        std::cout << '\n';
    } catch (const std::out_of_range &e) {
        std::cout << "No relevance data found for the query, cannot establish an evaluation for: " << queryString
                  << '\n';
        return 1;
    }

    return 0;
}
