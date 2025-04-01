/*
** File: QueryHandler.cpp                                                      *
** Project: CAU_NLP                                                            *
** Created Date: Tu Mar 2025                                                   *
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

#include "QueryHandler.hpp"
#include <algorithm>
#include <iostream>
#include "Utils.hpp"

auto Boolean::QueryHandler::getQuery(const std::string &aText) -> std::tuple<Query, std::string>
{
    Query query;
    std::string queryString;

    std::cout << aText;
    std::getline(std::cin, queryString);
    query = Shared::Utils::tokenize(queryString);

    return {query, queryString};
}

auto Boolean::QueryHandler::isQueryOperator(const Token &aToken) -> bool
{
    return std::ranges::any_of(QueryOperators, [&aToken](const auto &queryOperator) {
        return aToken == queryOperator;
    });
}
