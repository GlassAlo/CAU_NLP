/*
** File: Sanitizer.cpp                                                         *
** Project: CAU_NLP                                                            *
** Created Date: Sa Mar 2025                                                   *
** Author: GlassAlo                                                            *
** Email: ofourpatat@gmail.com                                                 *
** -----                                                                       *
** Description: {Enter a description for the file}                             *
** -----                                                                       *
** Last Modified: Tue Apr 01 2025                                              *
** Modified By: GlassAlo                                                       *
** -----                                                                       *
** Copyright (c) 2025 Aurea-Games                                              *
** -----                                                                       *
** HISTORY:                                                                    *
** Date      	By	Comments                                                   *
** ----------	---	---------------------------------------------------------  *
*/

#include "Sanitizer.hpp"
#include "QueryHandler.hpp"
#include "Utils.hpp"
#include "boost/algorithm/string/case_conv.hpp"
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

Shared::Sanitizer::Sanitizer(const std::string &aPath)
{
    std::string fileContent;
    std::vector<std::string> tokens;

    fileContent = Shared::Utils::getDocumentContent(aPath);
    tokens = Shared::Utils::tokenize(fileContent);

    _badWords = tokens;
}

auto Shared::Sanitizer::getBadWords() const -> const std::vector<std::string> &
{
    return _badWords;
}

auto Shared::Sanitizer::sanitizeTokenList(std::vector<std::string> &aTokens, bool aIsQuery) const -> void
{
    if (aTokens.empty()) {
        return;
    }
    for (auto &token : aTokens) {
        if (!Boolean::QueryHandler::isQueryOperator(token)) {
            boost::algorithm::to_lower(token);
        }
        removePonctuation(token);
        stem(token);
    }
    for (const auto &badWord : _badWords) {
        if (aIsQuery && Boolean::QueryHandler::isQueryOperator(badWord)) {
            continue;
        }
        boost::range::remove_erase_if(aTokens, [&badWord](const std::string &token) {
            return token == badWord;
        });
    }
}

auto Shared::Sanitizer::removePonctuation(std::string &aToken) -> void
{
    aToken.erase(boost::range::remove_if(aToken, ispunct), aToken.end());
}

auto Shared::Sanitizer::stem(std::string &token) -> void
{
    if (token.size() > 4 && token.substr(token.size() - 3) == "ing") {
        token.erase(token.size() - 3);
    }
    if (token.size() > 3 && token.substr(token.size() - 2) == "ed") {
        token.erase(token.size() - 2);
    }
    if (token.size() > 2 && token.substr(token.size() - 1) == "s") {
        token.erase(token.size() - 1);
    }
}
