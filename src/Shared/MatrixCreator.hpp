/*
** File: MatrixCreator.hpp                                                     *
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

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace Shared {
    class DocumentHandler;
} // namespace Shared

namespace Shared {
    class MatrixCreator
    {
        public:
            using occurences = int;
            using Token = std::string;
            using DocumentName = std::string;
            using Matrix = std::unordered_map<DocumentName, std::unordered_map<Token, occurences>>;
            using DocumentList = std::vector<Shared::DocumentHandler>;

        private:
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
} // namespace Shared
