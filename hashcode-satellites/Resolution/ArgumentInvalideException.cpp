#include "ArgumentInvalideException.hpp"

ArgumentInvalideException::ArgumentInvalideException(char* desc) noexcept :
    std::runtime_error(desc)
{ }