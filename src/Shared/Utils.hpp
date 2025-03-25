/*
** File: Utils.hpp                                                             *
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

namespace Shared {
    class Utils
    {
        public:
            static auto tokenize(const std::string &line) -> std::vector<std::string>;
            static auto getDocumentContent(const std::string &aPath) -> std::string;
            static auto openFolder(const std::string &path = ".") -> std::vector<std::string>;
    };
} // namespace Shared
