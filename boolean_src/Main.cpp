/*
** File: Main.cpp                                                              *
** Project: CAU_NLP                                                            *
** Created Date: Sa Mar 2025                                                   *
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
** Date      	By	Comments *
** ----------	---
*---------------------------------------------------------  *
*/

#include "DocumentHandler.hpp"
#include "MatrixCreator.hpp"
#include "Sanitizer.hpp"

int main()
{
    auto *sanitizer = new Document::Sanitizer("./UselessWords.txt");
    Matrix::MatrixCreator::DocumentList documentList = {
        Document::DocumentHandler("./games_data/Automobili Lamborghini.txt", sanitizer)};
    Matrix::MatrixCreator matrixCreator;
    matrixCreator.createMatrix(documentList);
    std::cout << matrixCreator << '\n';

    delete sanitizer;
    return 0;
}
