/*
** File: QueryHandler.cpp                                                      *
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

#include "QueryHandler.hpp"
#include <algorithm>
#include <iostream>
#include "Utils.hpp"

auto Boolean::QueryHandler::getQuery(const std::string &aText) -> Query
{
    std::string query;

    std::cout << aText;
    std::getline(std::cin, query);
    return Shared::Utils::tokenize(query);
}

auto Boolean::QueryHandler::isQueryOperator(const Token &aToken) -> bool
{
    return std::ranges::any_of(QueryOperators, [&aToken](const auto &queryOperator) {
        return aToken == queryOperator;
    });
}
