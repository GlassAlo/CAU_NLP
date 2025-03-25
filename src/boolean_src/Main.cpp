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

#include "DocumentHandler.hpp"
#include "InvertedIndex.hpp"
#include "MatrixCreator.hpp"
#include "Sanitizer.hpp"
#include "Utils.hpp"

constexpr std::string folderName = "./games_data";

namespace {
    auto createInvertedIndex(Boolean::InvertedIndex &aInvertedIndex) -> void
    {
        auto *sanitizer = new Shared::Sanitizer("./UselessWords.txt");
        auto files = Shared::Utils::openFolder(folderName);
        Shared::MatrixCreator::DocumentList documentList;

        for (const auto &file : files) {
            documentList.emplace_back("games_data/" + file, file, sanitizer);
        }

        Shared::MatrixCreator matrixCreator;
        matrixCreator.createMatrix(documentList);

        aInvertedIndex.createInvertedIndex(matrixCreator);

        delete sanitizer;
    }
} // namespace

int main()
{
    Boolean::InvertedIndex invertedIndex;
    if (!invertedIndex.loadInvertedMap("inverted_map_dump.txt")) {
        createInvertedIndex(invertedIndex);
        invertedIndex.dumpInvertedMap();
    } else {
        auto query = Boolean::QueryHandler::getQuery("Would you like to refresh the inverted index? (y/n): ");
        if (query[0] == "y") {
            createInvertedIndex(invertedIndex);
            invertedIndex.dumpInvertedMap();
        }
    }

    auto query = Boolean::QueryHandler::getQuery();
    auto results = invertedIndex.getQueryResults(query);

    for (const auto &result : results) {
        std::cout << result << '\n';
    }

    return 0;
}
