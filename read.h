#include <fstream>
#include <string>

template <typename T>
T read(std::ifstream& file)
{
    // TODO: YOUR CODE HERE

    //read 1 element of type T from file
    T dataToRead;
    file.read((char*)&dataToRead, sizeof(dataToRead));
    return dataToRead;
}

template <typename T>
void read_n(std::ifstream& file, T* out_array, size_t len)
{
    // TODO: YOUR CODE HERE
    //file: the file to read from
    //out_array : a pointer to a buffer of integers to write to
    //len : the number of elements that should be read from the file and written into out_array

    T singleTypeT;

    //read len of (elements) 
    file.read((char*)out_array, sizeof(singleTypeT) * len);
}

std::string read_length_prefixed_string(std::ifstream& file);
std::string read_null_terminated_string(std::ifstream& file);

int convert_to_int(char* bytes);
void convert_to_ints(char* bytes, int* int_array, size_t len);

void read_game_entity(std::istream& file,
    float& x, float& y, float& z,
    std::string& name,
    int& health);