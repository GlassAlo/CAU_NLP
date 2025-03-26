/*
** File: QueryHandler.hpp                                                      *
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

#pragma once

#include <array>
#include <string>
#include <vector>

namespace Boolean {
    constexpr std::array<const char *, 3> QueryOperators = {"AND", "OR", "NOT"};

    class QueryHandler
    {
        public:
            using Token = std::string;
            using Query = std::vector<Token>;

        public:
            QueryHandler() = delete;
            ~QueryHandler() = delete;

            // Rule of Five: Explicitly define or delete special member functions
            QueryHandler(const QueryHandler &) = delete;            // Delete copy constructor
            QueryHandler &operator=(const QueryHandler &) = delete; // Delete copy assignment operator
            QueryHandler(QueryHandler &&) = delete;                 // Default move constructor
            QueryHandler &operator=(QueryHandler &&) = delete;      // Default move assignment operator

            static auto getQuery(const std::string &aText = "Enter your query: ") -> Query;
            static auto isQueryOperator(const Token &aToken) -> bool;
    };
} // namespace Boolean
