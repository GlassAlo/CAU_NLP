/*
** File: Sanitizer.hpp                                                         *
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

#pragma once

#include <string>
#include <vector>

namespace Shared {
    class Sanitizer
    {
        private:
            std::vector<std::string> _badWords;

        public:
            explicit Sanitizer(const std::string &path);
            ~Sanitizer() = default;

            // Rule of Five: Explicitly define or delete special member functions
            Sanitizer(const Sanitizer &) = default;                // Copy constructor
            Sanitizer &operator=(const Sanitizer &) = default;     // Copy assignment operator
            Sanitizer(Sanitizer &&) noexcept = default;            // Move constructor
            Sanitizer &operator=(Sanitizer &&) noexcept = default; // Move assignment operator

            // Member functions
            [[nodiscard]] auto getBadWords() const -> const std::vector<std::string> &;
            auto sanitizeTokenList(std::vector<std::string> &tokens, bool isQuery = false) const -> void;

        private:
            static auto removePonctuation(std::string &token) -> void;
            static auto stem(std::string &token) -> void;
    };
} // namespace Shared
