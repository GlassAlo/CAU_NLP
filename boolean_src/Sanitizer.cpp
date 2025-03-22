/*
** File: Sanitizer.cpp                                                         *
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

#include "Sanitizer.hpp"
#include "Utils.hpp"
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

Document::Sanitizer::Sanitizer(const std::string &aPath)
{
    std::string fileContent;
    std::vector<std::string> tokens;

    fileContent = Shared::Utils::getDocumentContent(aPath);
    tokens = Shared::Utils::tokenize(fileContent);

    _badWords = tokens;
}

auto Document::Sanitizer::getBadWords() const -> const std::vector<std::string> &
{
    return _badWords;
}

auto Document::Sanitizer::sanitizeTokenList(std::vector<std::string> &aTokens) const -> void
{
    for (auto &token : aTokens) {
        removePonctuation(token);
        stem(token);
    }
    for (const auto &badWord : _badWords) {
        boost::range::remove_erase_if(aTokens, [&badWord](const std::string &token) {
            return token == badWord;
        });
    }
}

auto Document::Sanitizer::removePonctuation(std::string &aToken) -> void
{
    aToken.erase(boost::range::remove_if(aToken, ispunct), aToken.end());
}

auto Document::Sanitizer::stem(std::string &token) -> void
{
    if (token.size() > 4 && token.substr(token.size() - 3) == "ing") {
        token.erase(token.size() - 3);
    }
}
