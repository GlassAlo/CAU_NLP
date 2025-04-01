/*
** File: RelevanceHandler.cpp                                                  *
** Project: CAU_NLP                                                            *
** Created Date: Tu Apr 2025                                                   *
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
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include "RelevanceHandler.hpp"
#include <fstream>
#include <iostream>

Boolean::RelevanceHandler::RelevanceHandler(const std::string &aFileName)
{
    loadRelevanceJudgment(aFileName);
}

void Boolean::RelevanceHandler::loadRelevanceJudgment(const std::string &aFileName)
{
    std::ifstream file(aFileName);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << aFileName << '\n';
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto &item : jsonData.items()) {
        const Query &query = item.key();
        QueryRelevantData relevantDocuments;

        for (const auto &doc : item.value()) {
            relevantDocuments.insert(doc.get<std::string>());
        }

        _relevanceData[query] = relevantDocuments;
    }
}

auto Boolean::RelevanceHandler::getPrecision(const Query &aQuery,
                                             const InvertedIndex::DocumentWithOcc &aRelevantDocuments) const -> double
{
    auto relevantDocuments = getRelevanceData(aQuery);
    int truePositives = 0;

    for (const auto &doc : aRelevantDocuments) {
        if (relevantDocuments.find(doc) != relevantDocuments.end()) {
            truePositives++;
        }
    }

    return aRelevantDocuments.size() > 0
               ? static_cast<double>(truePositives) / static_cast<double>(aRelevantDocuments.size())
               : 0.0;
}

auto Boolean::RelevanceHandler::getRecall(const Query &aQuery,
                                          const InvertedIndex::DocumentWithOcc &aRelevantDocuments) const -> double
{
    auto relevantDocuments = getRelevanceData(aQuery);
    int truePositives = 0;

    for (const auto &doc : aRelevantDocuments) {
        if (relevantDocuments.find(doc) != relevantDocuments.end()) {
            truePositives++;
        }
    }

    return relevantDocuments.size() > 0
               ? static_cast<double>(truePositives) / static_cast<double>(relevantDocuments.size())
               : 0.0;
}

auto Boolean::RelevanceHandler::getF1Score(const Query &aQuery,
                                           const InvertedIndex::DocumentWithOcc &aRelevantDocuments) const -> double
{
    double precision = getPrecision(aQuery, aRelevantDocuments);
    double recall = getRecall(aQuery, aRelevantDocuments);

    return (precision + recall > 0) ? (2 * precision * recall) / (precision + recall) : 0.0;
}

std::ostream &Boolean::operator<<(std::ostream &aOs, const RelevanceHandler &aRelevance)
{
    for (const auto &[query, relevantDocuments] : aRelevance.getRelevanceData()) {
        aOs << "Query: " << query << "\n";
        aOs << "Relevant Documents: ";
        for (const auto &doc : relevantDocuments) {
            aOs << doc << " ";
        }
        aOs << "\n";
    }
    return aOs;
}
