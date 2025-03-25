/*
** File: DocumentHandler.cpp                                                          *
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

#include "DocumentHandler.hpp"
#include <vector>
#include "Sanitizer.hpp"
#include "Utils.hpp"

Shared::DocumentHandler::DocumentHandler(const std::string &aPath, std::string aName,
                                         const Shared::Sanitizer *aSanitizer)
    : _sanitizer(aSanitizer),
      _documentId(std::move(aName))
{
    std::string fileContent;

    fileContent = Shared::Utils::getDocumentContent(aPath);
    this->_tokens = Shared::Utils::tokenize(fileContent);
    this->_sanitizer->sanitizeTokenList(this->_tokens);
}

auto Shared::DocumentHandler::getTokens() const -> const std::vector<std::string> &
{
    return this->_tokens;
}

auto Shared::DocumentHandler::getDocumentId() const -> const std::string &
{
    return this->_documentId;
}
