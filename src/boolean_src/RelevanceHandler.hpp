/*
** File: RelevanceHandler.hpp                                                  *
** Project: CAU_NLP                                                            *
** Created Date: Tu Apr 2025                                                   *
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

#pragma once

#include <nlohmann/json.hpp>
#include <set>
#include "InvertedIndex.hpp"

namespace Boolean {
    class RelevanceHandler
    {
        public:
            using Query = std::string;
            using QueryRelevantData = std::set<std::string>;
            using RelevanceData = std::unordered_map<Query, QueryRelevantData>;

        private:
            RelevanceData _relevanceData;

        public:
            explicit RelevanceHandler(const std::string &aFileName = "relevance_judgment.json");
            ~RelevanceHandler() = default;

            RelevanceHandler(const RelevanceHandler &) = delete;
            RelevanceHandler &operator=(const RelevanceHandler &) = delete;
            RelevanceHandler(RelevanceHandler &&) = default;
            RelevanceHandler &operator=(RelevanceHandler &&) = default;

            [[nodiscard]] auto getRelevanceData() const -> const RelevanceData &
            {
                return _relevanceData;
            }

            [[nodiscard]] auto getRelevanceData(const Query &aQuery) const -> const QueryRelevantData &
            {
                return _relevanceData.at(aQuery);
            }

            auto getPrecision(const Query &aQuery, const InvertedIndex::DocumentWithOcc &aRelevantDocuments) const
                -> double;
            auto getRecall(const Query &aQuery, const InvertedIndex::DocumentWithOcc &aRelevantDocuments) const
                -> double;
            auto getF1Score(const Query &aQuery, const InvertedIndex::DocumentWithOcc &aRelevantDocuments) const
                -> double;

        private:
            void loadRelevanceJudgment(const std::string &aFileName);
    };

    std::ostream &operator<<(std::ostream &aOs, const RelevanceHandler &aRelevance);

} // namespace Boolean
