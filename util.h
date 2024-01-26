#include <ios>
#include <vector>

std::ostream& operator<<(std::ostream& stream, std::vector<char> vec);

#define LEN(x) sizeof(x) / sizeof(*x)
