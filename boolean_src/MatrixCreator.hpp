/*
** File: MatrixCreator.hpp                                                     *
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

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace Document {
    class DocumentHandler;
} // namespace Document

namespace Matrix {
    class MatrixCreator
    {
        public:
            using Matrix = std::vector<std::vector<int>>;
            using UniqueTokensIndices = std::unordered_map<std::string, int>;
            using DocumentList = std::vector<Document::DocumentHandler>;

        private:
            UniqueTokensIndices _uniqueTokensIndices;
            Matrix _matrix;

        public:
            MatrixCreator() = default;
            ~MatrixCreator() = default;

            // Rule of Five: Explicitly define or delete special member functions
            MatrixCreator(const MatrixCreator &) = delete;                 // Copy constructor
            MatrixCreator &operator=(const MatrixCreator &) = delete;      // Copy assignment operator
            MatrixCreator(MatrixCreator &&) noexcept = default;            // Move constructor
            MatrixCreator &operator=(MatrixCreator &&) noexcept = default; // Move assignment operator

            // Member functions
            auto createMatrix(DocumentList &ADocumentHandlerList) -> void;

            auto getMatrix() const -> const Matrix &;
    };

    std::ostream &operator<<(std::ostream &aOs, const MatrixCreator &aMatrixCreator);
} // namespace Matrix
