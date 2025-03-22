/*
** File: DocumentHandler.cpp                                                          *
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

#include "DocumentHandler.hpp"
#include <iostream>
#include <vector>
#include "Sanitizer.hpp"
#include "Utils.hpp"

Document::DocumentHandler::DocumentHandler(const std::string &aPath, const Document::Sanitizer *aSanitizer)
    : _sanitizer(aSanitizer),
      _documentId(boost::uuids::random_generator()())
{
    std::string fileContent;

    fileContent = Shared::Utils::getDocumentContent(aPath);
    this->_tokens = Shared::Utils::tokenize(fileContent);
    this->_sanitizer->sanitizeTokenList(this->_tokens);

    std::cout << "Document content: " << '\n';
    for (const auto &token : this->_tokens) {
        std::cout << token << '\n';
    }
}

auto Document::DocumentHandler::getTokens() const -> const std::vector<std::string> &
{
    return this->_tokens;
}

auto Document::DocumentHandler::getUUID() const -> const boost::uuids::uuid &
{
    return this->_documentId;
}
