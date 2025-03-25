/*
** File: InvertedIndex.hpp                                                     *
** Project: CAU_NLP                                                            *
** Created Date: Tu Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Wed Mar 26 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#pragma once

#include <string>
#include <vector>
#include "MatrixCreator.hpp"
#include "QueryHandler.hpp"
#include <unordered_map>

namespace Shared {
    class DocumentHandler;
}

namespace Boolean {
    class InvertedIndex
    {
        public:
            using Token = std::string;
            using DocumentId = std::string;
            using DocumentWithOcc = std::vector<DocumentId>;
            using InvertedMap = std::unordered_map<Token, DocumentWithOcc>;

        private:
            InvertedMap _invertedMap;

        public:
            explicit InvertedIndex(Shared::MatrixCreator &aMatrix);
            InvertedIndex() = default;
            ~InvertedIndex() = default;

            // Rule of Five
            InvertedIndex(const InvertedIndex &) = default;                // Copy constructor
            InvertedIndex &operator=(const InvertedIndex &) = default;     // Copy assignment operator
            InvertedIndex(InvertedIndex &&) noexcept = default;            // Move constructor
            InvertedIndex &operator=(InvertedIndex &&) noexcept = default; // Move assignment operator

            // Member functions
            auto createInvertedIndex(Shared::MatrixCreator &aMatrix) -> void;
            auto getInvertedMap() const -> const InvertedMap &;
            auto getQueryResults(QueryHandler::Query &aQuery) -> DocumentWithOcc;

            auto dumpInvertedMap() const -> void;
            auto loadInvertedMap(const std::string &aPath) -> bool;

        private:
            static auto getIntersection(const DocumentWithOcc &aDoc1, const DocumentWithOcc &aDoc2) -> DocumentWithOcc;
            static auto getUnion(const DocumentWithOcc &aDoc1, const DocumentWithOcc &aDoc2) -> DocumentWithOcc;
            static auto getDifference(const DocumentWithOcc &aDoc1, const DocumentWithOcc &aDoc2) -> DocumentWithOcc;
    };

    // Override the << operator for InvertedIndex
    std::ostream &operator<<(std::ostream &os, const InvertedIndex &index);
} // namespace Boolean