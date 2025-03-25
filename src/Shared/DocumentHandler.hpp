/*
** File: DocumentHandler.hpp                                                          *
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
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Shared {
    class Sanitizer;
} // namespace Shared

namespace Shared {
    class DocumentHandler
    {
        private:
            const Shared::Sanitizer *_sanitizer;
            std::vector<std::string> _tokens;
            std::unordered_map<std::string, int> _uniqueTokensIndices;
            const std::string _documentId;

        public:
            explicit DocumentHandler(const std::string &path, std::string name, const Shared::Sanitizer *sanitizer);
            ~DocumentHandler() = default;

            // Rule of Five: Explicitly define or delete special member functions
            DocumentHandler(const DocumentHandler &) = default;               // Copy constructor
            DocumentHandler &operator=(const DocumentHandler &) = delete;     // Copy assignment operator
            DocumentHandler(DocumentHandler &&) noexcept = default;           // Move constructor
            DocumentHandler &operator=(DocumentHandler &&) noexcept = delete; // Move assignment operator

            auto getTokens() const -> const std::vector<std::string> &;
            auto getDocumentId() const -> const std::string &;
    };
} // namespace Shared
