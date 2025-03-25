/*
** File: InvertedIndex.cpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Tu Mar 2025                                                   *
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

#include "InvertedIndex.hpp"

Boolean::InvertedIndex::InvertedIndex(Shared::MatrixCreator &aMatrix)
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

std::ostream &Boolean::operator<<(std::ostream &os, const InvertedIndex &index)
{
    for (const auto &[token, documentList] : index.getInvertedMap()) {
        os << token << " -> ";
        for (const auto &document : documentList) {
            os << document << ' ';
        }
        os << '\n';
    }

    return os;
}
