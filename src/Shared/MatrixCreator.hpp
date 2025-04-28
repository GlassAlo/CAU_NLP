/*
** File: MatrixCreator.hpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Su Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Fri Apr 25 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#pragma once

#include <Eigen/Dense>
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
            using occurences = double;
            using Token = std::string;
            using DocumentName = std::string;
            using Matrix = std::unordered_map<DocumentName, std::unordered_map<Token, occurences>>;
            using DocumentList = std::vector<Shared::DocumentHandler>;
            using DocumentWithOcc = std::vector<DocumentName>;
            using InvertedMap = std::unordered_map<Token, DocumentWithOcc>;
            using InvIndexFreq = std::unordered_map<Token, double>;

        private:
            Matrix _matrix;
            Eigen::MatrixXd _matrixEigen;
            std::unordered_map<std::string, int> _term_to_index;

        public:
            MatrixCreator() = default;
            ~MatrixCreator() = default;

            // Rule of Five: Explicitly define or delete special member functions
            MatrixCreator(const MatrixCreator &) = delete;                 // Copy constructor
            MatrixCreator &operator=(const MatrixCreator &) = delete;      // Copy assignment operator
            MatrixCreator(MatrixCreator &&) noexcept = default;            // Move constructor
            MatrixCreator &operator=(MatrixCreator &&) noexcept = default; // Move assignment operator

            // Member functions
            auto createMatrix(const DocumentList &aDocumentHandlerList) -> void;
            auto setTokensWeight(const DocumentList &aDocumentHandlerList) -> void;

            auto createEigenMatrix() -> void;

            auto getMatrix() const -> const Matrix &;
            auto getEigenMatrix() const -> const Eigen::MatrixXd &;
            auto getTermToIndex() const -> const std::unordered_map<std::string, int> &;

            auto dumpMatrix() const -> void;

            auto loadMatrix(const std::string &aPath) -> bool;

        private:
            auto getInvIndexFreq(const DocumentList &aDocumentHandlerLists) -> InvIndexFreq;
    };

    std::ostream &operator<<(std::ostream &aOs, const MatrixCreator &aMatrixCreator);
} // namespace Shared
