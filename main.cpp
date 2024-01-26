#include <iomanip>
#include <stdio.h>
#include <vector>
#include <ios>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

#include "read.h"
#include "tests.h"
#include "util.h"

using std::ofstream, std::ifstream;

union IntConverter
{
    int as_int;
    unsigned char as_chars[sizeof(int)];
};

struct Weapon
{
    int max_ammunition;
    int cur_ammunition;
    bool is_melee;
    char display_name[14];
};

// template <typename T>
std::ostream& operator<<(std::ostream& stream, IntConverter item)
{
    stream << "Dec: " << item.as_int << std::endl;
    stream << "Hex: 0x" << std::setfill('0') << std::setw(8) << std::hex << std::right << item.as_int << std::endl;
    stream << "Bytes: ";

    for (int i = 0; i < sizeof(int); i++)
    {
	stream << "0x" << std::setfill('0') << std::setw(2) << +item.as_chars[i] << " ";
    }

    return stream;
}

std::ostream& print_bytes(std::ostream& stream, char *value, size_t len)
{
    for (int i = 0; i < len; i++)
    {
	std::cout << "0x" << std::setfill('0') << std::setw(2) << +(unsigned char)value[i] << " ";
    }
    std::cout << std::endl;

    return stream;
}

int main()
{
    return run_all_tests();
}
