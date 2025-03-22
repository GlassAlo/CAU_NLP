/*
** File: Utils.cpp                                                             *
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

#include "Utils.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>

auto Shared::Utils::tokenize(const std::string &aLine) -> std::vector<std::string>
{
    std::istringstream stream(aLine);
    std::string token;
    std::vector<std::string> tokens;

    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

auto Shared::Utils::getDocumentContent(const std::string &aPath) -> std::string
{
    std::string fullContent;
    std::string line;
    std::ifstream file(aPath);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file at path: " + aPath);
    }

    while (std::getline(file, line)) {
        boost::algorithm::to_lower(line);
        fullContent += line + " ";
    }
    if (file.is_open()) {
        file.close();
    }

    return fullContent;
}
