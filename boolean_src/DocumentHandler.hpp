/*
** File: DocumentHandler.hpp                                                          *
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
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>
#include <vector>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <unordered_map>

namespace Document {
    class Sanitizer;
} // namespace Document

namespace Document {
    class DocumentHandler
    {
        private:
            const Document::Sanitizer *_sanitizer;
            std::vector<std::string> _tokens;
            std::unordered_map<std::string, int> _uniqueTokensIndices;
            boost::uuids::uuid _documentId;

        public:
            explicit DocumentHandler(const std::string &path, const Document::Sanitizer *sanitizer);
            ~DocumentHandler() = default;

            // Rule of Five: Explicitly define or delete special member functions
            DocumentHandler(const DocumentHandler &) = default;                // Copy constructor
            DocumentHandler &operator=(const DocumentHandler &) = default;     // Copy assignment operator
            DocumentHandler(DocumentHandler &&) noexcept = default;            // Move constructor
            DocumentHandler &operator=(DocumentHandler &&) noexcept = default; // Move assignment operator

            auto getTokens() const -> const std::vector<std::string> &;
            auto getUUID() const -> const boost::uuids::uuid &;
    };
} // namespace Document
