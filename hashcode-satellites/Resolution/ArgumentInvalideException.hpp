#pragma once

#include <stdexcept>

class ArgumentInvalideException : public std::runtime_error
{
    public:

        ArgumentInvalideException(char* desc) noexcept;
};