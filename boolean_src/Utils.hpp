/*
** File: Utils.hpp                                                             *
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
#include <string>
#include <vector>

namespace Shared {
    class Utils
    {
        public:
            static auto tokenize(const std::string &line) -> std::vector<std::string>;
            static auto getDocumentContent(const std::string &aPath) -> std::string;
    };
} // namespace Shared
