#include <fstream>
#include <iostream>
#include <vector>

#include "read.h"

union IntConverter
{
    int as_int;
    unsigned char as_bytes[sizeof(int)];
};

void read_game_entity(std::istream& file, float& x, float& y, float& z, std::string& name, int& health)
{
    using namespace std;
    std::ifstream* file_as_ifstream = (std::ifstream*)(&file);

    //x, y, z, (floats)
    //name, (up to 40 bytes)
    //health, (int)

    cout << "float amount of bytes: " << sizeof(float) << endl;
    cout << "int amount of bytes: " << sizeof(int) << endl;

    // the first 12 bytes split as [4][4][4] are all floats
    //read 12 bytes
    char coords[12];
    float floatCoords[3];
    read_n(*file_as_ifstream, coords, 12);

    IntConverter converter;
    convert_to_ints(coords, (int*)floatCoords, 12);

    x = floatCoords[0];
    y = floatCoords[1];
    z = floatCoords[2];

    //read the next bytes until delimiter
    name = read_null_terminated_string(*file_as_ifstream);

    //////////////////////////
    /////////////////////////
    ////////////////////////////
    /////////////////////////
    
    //I think the terminated string stole the last 4 bytes.
    /*char last4Bytes[4];

    last4Bytes[0] = name[name.size() - 3];
    last4Bytes[1] = name[name.size() - 2];
    last4Bytes[2] = name[name.size() - 1];
    last4Bytes[3] = name[name.size() - 0];

    int calculatedHealth;
    convert_to_ints(last4Bytes, &calculatedHealth, 4);

    cout << "health: " << calculatedHealth << endl;*/

    //////////////////////////////////////////////////////////////
    file.clear(); // clear fail and eof bits
    file.seekg(0, std::ios::beg); // back to the start!
    //first 3 floats = 12, string = 40, last 4 is int... = 56
    char entireFile[56];
    file.read(entireFile, 56);
    
    int calculatedHealth;
    char last4bytes[4] = { entireFile[0], entireFile[1] , entireFile[2] , entireFile[3] };
    convert_to_ints(last4bytes, &calculatedHealth, 4);
    health = calculatedHealth;

    //CANNOT READ HEALTH. WON'T RESET FILE READ POSITION. HEALTH SHOULD BE THE FIRST 4 BYTES BUT IS
    //CLEARLY NOT.

    ////////////////////////////////////////////

    //find the last remaining bytes and convert to int, its the health
    //this shit reads 4 bytes
    //last is [4]

    //char healthBytes[4];
    //file.read(healthBytes, 4);
    ////read_n(*file_as_ifstream, healthBytes, 4);

    ///*for each(auto byte in healthBytes) {
    //    cout << byte << endl;
    //}*/


    //int calculatedHealth;
    //convert_to_ints(healthBytes, &calculatedHealth, 4);

    //cout << calculatedHealth << endl;

    cout << endl << endl << endl << endl << endl << endl;
    return;
}

std::string read_length_prefixed_string(std::ifstream& file)
{
    // TODO: YOUR CODE HERE

    //read 4 bytes. this will tell me length and save the length of text in int
    int textSize = 0;
    file.read((char*)&textSize, 4);

    //create actual string, read that length calcuated above
    char* actualOutput = new char[textSize + 1];
    file.read(actualOutput, textSize);
    actualOutput[textSize] = '\0'; //we have to put this shit in even though we never got told to.

    return actualOutput;
}

std::string read_null_terminated_string(std::ifstream& file)
{
    // TODO: YOUR CODE HERE
    std::vector<char> allCharacters; //create a vector for all characters

    //Read characters from the file until a null terminator is encountered
    char singleChar;
    while (true) {
        file.read(&singleChar, 1); // Read a single character

        //If null terminator is encountered, stop reading
        if (singleChar == '\0') {
            break;
        }

        // Append the character to the vector
        allCharacters.push_back(singleChar);
    }

    // Convert the vector of characters to a string
    std::string result(allCharacters.begin(), allCharacters.end());

    return result;
}

int convert_to_int(char* bytes)
{
    // TODO: YOUR CODE HERE
    IntConverter converter;
    converter.as_bytes[0] = bytes[0];
    converter.as_bytes[1] = bytes[1];
    converter.as_bytes[2] = bytes[2];
    converter.as_bytes[3] = bytes[3];

    int convertedInt = converter.as_int;

    return convertedInt;
}

void convert_to_ints(char* bytes, int* int_array, size_t len)
{
    // TODO: YOUR CODE HERE
    int* convertedInts = new int[len/4];
    char currentBytes[4] = {'x', 'x' , 'x' , 'x' };

    IntConverter converter;
    int numOfNumbersInsideCurrentBytes = 0;
    int numOfNumbersInsideArray = 0;

    //4 byte = 1 int
    //go through every byte
    for (int byteNumber = 0; byteNumber < len; byteNumber++) {

        //add bytes
        currentBytes[numOfNumbersInsideCurrentBytes] = bytes[byteNumber];

        //update number of elements inside our current Bytes
        numOfNumbersInsideCurrentBytes++;

        //when our current Int in bytes is equal to 4 items
        if (numOfNumbersInsideCurrentBytes == 4) {
           
            for (auto index : currentBytes) {
                index = 'x';
            }

            //add all items inside converter
            for (int z = 0; z < 4; z++) {
                //0 -> 3
                converter.as_bytes[z] = currentBytes[z];
            }

            convertedInts[numOfNumbersInsideArray] = converter.as_int;

            //reset all items in our byte
            for (auto index : currentBytes) {
                index = 'x';
            }

            numOfNumbersInsideCurrentBytes = 0;
            numOfNumbersInsideArray++;
        }
    }

    for (int i = 0; i < (len/4); i++) {
        int_array[i] = convertedInts[i];
    }

    delete[] convertedInts;

    return;
}
