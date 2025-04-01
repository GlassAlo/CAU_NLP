/*
** File: InvertedIndex.cpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Tu Mar 2025                                                   *
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

#include "InvertedIndex.hpp"
#include <boost/range/algorithm/find.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "QueryHandler.hpp"
#include "boost/algorithm/string/case_conv.hpp"

Boolean::InvertedIndex::InvertedIndex(Shared::MatrixCreator &aMatrix)
{
    this->createInvertedIndex(aMatrix);
}

auto Boolean::InvertedIndex::createInvertedIndex(Shared::MatrixCreator &aMatrix) -> void
{
    const auto &matrix = aMatrix.getMatrix();

    for (const auto &[documentName, tokenOccurences] : matrix) {
        for (const auto &[token, occurences] : tokenOccurences) {
            this->_invertedMap[token].push_back(documentName);
        }
    }
}

auto Boolean::InvertedIndex::getInvertedMap() const -> const InvertedMap &
{
    return this->_invertedMap;
}

auto Boolean::InvertedIndex::getQueryResults(QueryHandler::Query &aQuery) -> DocumentWithOcc
{
    std::vector<DocumentWithOcc> tmp = {};
    DocumentWithOcc result;
    std::vector<std::tuple<int, std::string>> operatorsIndexes;

    for (auto &token : aQuery) {
        if (QueryHandler::isQueryOperator(token)) {
            auto itx = boost::range::find(aQuery, token);
            operatorsIndexes.emplace_back(static_cast<int>(itx - aQuery.begin()), token);
            token = " ";
            tmp.emplace_back();
            continue;
        }
        if (this->_invertedMap.find(token) != this->_invertedMap.end()) {
            tmp.push_back(this->_invertedMap[token]);
        }
    }

    if (tmp.empty()) {
        return {};
    }

    result = tmp[0];

    for (const auto &[index, ope] : operatorsIndexes) {
        if (index == static_cast<int>(tmp.size()) - 1) {
            std::cout << "Invalid query: " << ope << '\n';
            break;
        }
        if (ope == "AND") {
            auto tmpResult = getIntersection(tmp[index - 1], tmp[index + 1]);
            result = getIntersection(result, tmpResult);
        } else if (ope == "OR") {
            auto tmpResult = getUnion(tmp[index - 1], tmp[index + 1]);
            result = getUnion(result, tmpResult);
        } else if (ope == "NOT") {
            result = getDifference(result, tmp[index + 1]);
        }
    }

    return result;
}

auto Boolean::InvertedIndex::dumpInvertedMap() const -> void
{
    if (std::filesystem::exists("inverted_map_dump.json")) {
        std::filesystem::remove("inverted_map_dump.json");
    }

    std::ofstream outFile("inverted_map_dump.json", std::ios::out | std::ios::trunc);
    nlohmann::json jsonData;

    for (const auto &[token, documentList] : this->_invertedMap) {
        jsonData[token] = documentList;
    }

    outFile << jsonData.dump(4);
    outFile.close();
}

auto Boolean::InvertedIndex::loadInvertedMap(const std::string &aPath) -> bool
{
    std::ifstream inFile(aPath);
    if (!inFile.is_open()) {
        return false;
    }

    nlohmann::json jsonData;
    try {
        inFile >> jsonData;
    } catch (const nlohmann::json::parse_error &e) {
        inFile.close();
        return false;
    }

    for (const auto &[token, documentList] : jsonData.items()) {
        DocumentWithOcc documents;
        for (const auto &doc : documentList) {
            documents.push_back(doc);
        }
        this->_invertedMap[token] = documents;
    }

    inFile.close();
    return true;
}

auto Boolean::InvertedIndex::getIntersection(const DocumentWithOcc &aDoc1, const DocumentWithOcc &aDoc2)
    -> DocumentWithOcc
{
    DocumentWithOcc result;

    for (const auto &doc1 : aDoc1) {
        for (const auto &doc2 : aDoc2) {
            if (doc1 == doc2) {
                result.push_back(doc1);
            }
        }
    }

    return result;
}

auto Boolean::InvertedIndex::getUnion(const DocumentWithOcc &aDoc1, const DocumentWithOcc &aDoc2) -> DocumentWithOcc
{
    DocumentWithOcc result;

    for (const auto &doc1 : aDoc1) {
        result.push_back(doc1);
    }

    for (const auto &doc2 : aDoc2) {
        if (boost::range::find(result, doc2) == result.end()) {
            result.push_back(doc2);
        }
    }

    return result;
}

auto Boolean::InvertedIndex::getDifference(const DocumentWithOcc &aDoc1, const DocumentWithOcc &aDoc2)
    -> DocumentWithOcc
{
    DocumentWithOcc result;

    for (const auto &doc1 : aDoc1) {
        if (boost::range::find(aDoc2, doc1) == aDoc2.end()) {
            result.push_back(doc1);
        }
    }

    return result;
}

std::ostream &Boolean::operator<<(std::ostream &aOs, const InvertedIndex &aIndex)
{
    for (const auto &[token, documentList] : aIndex.getInvertedMap()) {
        aOs << token << " -> ";
        for (const auto &document : documentList) {
            aOs << document << ' ';
        }
        aOs << '\n';
    }

    return aOs;
}
