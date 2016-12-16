#include "ArgumentInvalideException.hpp"

ArgumentInvalideException::ArgumentInvalideException(char* desc) noexcept :
    std::exception(desc)
{ }