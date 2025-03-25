/*
** File: Main.cpp                                                              *
** Project: CAU_NLP                                                            *
** Created Date: Sa Mar 2025                                                   *
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

int main()
{
    auto *sanitizer = new Shared::Sanitizer("./UselessWords.txt");
    auto files = Shared::Utils::openFolder(folderName);
    Shared::MatrixCreator::DocumentList documentList;

    for (const auto &file : files) {
        documentList.emplace_back("games_data/" + file, file, sanitizer);
    }

    Shared::MatrixCreator matrixCreator;
    matrixCreator.createMatrix(documentList);

    Boolean::InvertedIndex invertedIndex(matrixCreator);

    delete sanitizer;
    return 0;
}
