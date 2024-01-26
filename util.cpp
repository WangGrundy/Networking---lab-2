#include "util.h"

#include <iostream>

std::ostream& operator<<(std::ostream& stream, std::vector<char> vec)
{
    for (char c : vec)
    {
	stream << c;
    }
    
    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, int x)
{
    throw std::runtime_error("operator>>() is not allowed!");
}

std::istream& operator>>(std::istream& stream, int x)
{
    throw std::runtime_error("operator>>() is not allowed!");
}

