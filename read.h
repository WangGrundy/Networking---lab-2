#include <fstream>
#include <string>

template <typename T>
T read(std::ifstream& file)
{
    // TODO: YOUR CODE HERE
    return T();
}

template <typename T>
void read_n(std::ifstream& file, T* out_array, size_t len)
{
    // TODO: YOUR CODE HERE
    return;
}

std::string read_length_prefixed_string(std::ifstream& file);
std::string read_null_terminated_string(std::ifstream& file);

int convert_to_int(char* bytes);
void convert_to_ints(char* bytes, int* int_array, size_t len);

void read_game_entity(std::istream& file,
		      float& x, float& y, float& z,
		      std::string& name,
		      int& health);

