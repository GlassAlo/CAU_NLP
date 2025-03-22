/*
** File: MatrixCreator.cpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Su Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Sun Mar 23 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include "MatrixCreator.hpp"
#include "DocumentHandler.hpp"

void Matrix::MatrixCreator::createMatrix(DocumentList &aDocumentHandlerList)
{
    for (const auto &documentHandler : aDocumentHandlerList) {
        const auto &tokens = documentHandler.getTokens();

        for (const auto &token : tokens) {
            if (_uniqueTokensIndices.find(token) == _uniqueTokensIndices.end()) {
                _uniqueTokensIndices[token] = static_cast<int>(_uniqueTokensIndices.size());
            }
        }
    }

    _matrix = Matrix(aDocumentHandlerList.size(), std::vector<int>(_uniqueTokensIndices.size(), 0));

    for (size_t docID = 0; docID < aDocumentHandlerList.size(); ++docID) {
        const auto &tokens = aDocumentHandlerList[docID].getTokens();

        for (const auto &token : tokens) {
            _matrix[docID][_uniqueTokensIndices[token]] += 1;
        }
    }
}

auto Matrix::MatrixCreator::getMatrix() const -> const Matrix &
{
    return _matrix;
}

std::ostream &Matrix::operator<<(std::ostream &aOs, const MatrixCreator &aMatrixCreator)
{
    for (const auto &row : aMatrixCreator.getMatrix()) {
        for (const auto &value : row) {
            aOs << value << ' ';
        }
        aOs << '\n';
    }
    return aOs;
}
