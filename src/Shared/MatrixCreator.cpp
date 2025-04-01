/*
** File: MatrixCreator.cpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Su Mar 2025                                                   *
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

#include "MatrixCreator.hpp"
#include <cmath>
#include <fstream>
#include <nlohmann/json.hpp>
#include "DocumentHandler.hpp"

void Shared::MatrixCreator::createMatrix(const DocumentList &aDocumentHandlerList)
{
    for (const auto &doc : aDocumentHandlerList) {
        const auto &tokens = doc.getTokens();
        const auto &docName = doc.getDocumentId();

        for (const auto &token : tokens) {
            _matrix[docName][token]++;
        }
    }

    for (const auto &doc : aDocumentHandlerList) {
        const auto &tokens = doc.getTokens();
        const auto &docName = doc.getDocumentId();

        for (const auto &token : tokens) {
            _matrix[docName][token] /= static_cast<double>(tokens.size());
        }
    }
}

auto Shared::MatrixCreator::dumpMatrix() const -> void
{
    std::ofstream outFile("matrix_dump.json");
    nlohmann::json jsonData;

    for (const auto &[token, documentList] : this->_matrix) {
        jsonData[token] = documentList;
    }

    outFile << jsonData.dump(4);
    outFile.close();
}

auto Shared::MatrixCreator::loadMatrix(const std::string &aPath) -> bool
{
    std::ifstream inFile(aPath);
    if (!inFile.is_open()) {
        return false;
    }

    nlohmann::json jsonData;
    inFile >> jsonData;

    for (const auto &[docName, tokenMap] : jsonData.items()) {
        for (const auto &[token, value] : tokenMap.items()) {
            _matrix[docName][token] = value;
        }
    }

    inFile.close();
    return true;
}

auto Shared::MatrixCreator::getMatrix() const -> const Matrix &
{
    return _matrix;
}

auto Shared::MatrixCreator::getInvIndexFreq(const DocumentList &aDocumentHandlerList) -> InvIndexFreq
{
    auto nbrOfDocs = aDocumentHandlerList.size();
    InvertedMap invMap;
    InvIndexFreq invIndexFreq;

    for (const auto &[documentName, tokenOccurences] : _matrix) {
        for (const auto &[token, occurences] : tokenOccurences) {
            invMap[token].push_back(documentName);
        }
    }

    for (const auto &[token, documentList] : invMap) {
        invIndexFreq[token] = log(static_cast<double>(nbrOfDocs) / static_cast<double>(invMap[token].size()));
    }
    return invIndexFreq;
}

auto Shared::MatrixCreator::setTokensWeight(const DocumentList &aDocumentHandlerList) -> void
{
    auto invIndexFreq = getInvIndexFreq(aDocumentHandlerList);

    for (auto &[documentName, tokenOccurences] : _matrix) {
        for (auto &[token, occurences] : tokenOccurences) {
            occurences *= invIndexFreq[token];
        }
    }
}

std::ostream &Shared::operator<<(std::ostream &aOs, const MatrixCreator &aMatrixCreator)
{
    for (const auto &row : aMatrixCreator.getMatrix()) {
        aOs << row.first << ": ";
        for (const auto &col : row.second) {
            aOs << col.first << " -> " << col.second << ", ";
        }
        aOs << '\n';
    }
    return aOs;
}
