#pragma once

#include <exception>

class ArgumentInvalideException : public std::exception
{
    public:

        ArgumentInvalideException(char* desc) noexcept;
};