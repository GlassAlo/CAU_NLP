/*
** File: MatrixCreator.cpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Su Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Tue Mar 25 2025                                              *
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

void Shared::MatrixCreator::createMatrix(DocumentList &aDocumentHandlerList)
{
    for (const auto &doc : aDocumentHandlerList) {
        const auto &tokens = doc.getTokens();
        const auto &docName = doc.getDocumentId();

        for (const auto &token : tokens) {
            _matrix[docName][token]++;
        }
    }
}

auto Shared::MatrixCreator::getMatrix() const -> const Matrix &
{
    return _matrix;
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
