#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>

#include "util.h"
#include "read.h"

using std::ofstream, std::ifstream;

template <typename T>
static bool test_file(const std::string& fn_name,
		      const std::string& value_name,
		      ofstream::pos_type pos,
		      const T& expected, const T& actual)
{
    if (expected == actual) return true;

    std::cout << fn_name << "test failed at file offset " << pos << ". Expected " << value_name << " of '" << expected << "' but was '" << actual << "'." << std::endl;

    return false;
}

static const char* test_filename = "../file1.bin";

static struct {
    float x;
    float y;
    float z;
    char name[40];
    int health;
} entities[] = {
    {3.0, 2.5, -76, "Player 1", 100},
    {3.5, 80.3, 0.06, "Goomba 1", 5},
    {-4, 0, 8, "Red Koopa 3", 10}
};

static bool test_read_game_entity()
{
    std::ifstream file(test_filename);

    file.seekg(233);
    
    for (int i = 0; i < LEN(entities); i++)
    {
	std::string expected_name(entities[i].name);
	int expected_health = entities[i].health;
	float expected_x = entities[i].x;
	float expected_y = entities[i].y;
	float expected_z = entities[i].z;

	std::string actual_name;
	int actual_health;
	float actual_x, actual_y, actual_z;

	read_game_entity(file, actual_x, actual_y, actual_z, actual_name, actual_health);

	if (actual_x != expected_x
	    || actual_y != expected_y
	    || actual_z != expected_z
	    || actual_name != expected_name
	    || actual_health != expected_health)
	{
	    std::cout << "read_game_entity test failed. Expected\n{"
		      << expected_x << ", " << expected_y << ", " << expected_z << ", "
		      << "'" << expected_name << "', "
		      << expected_health << "}\nbut got\n{"
		      << actual_x << ", " << actual_y << ", " << actual_z << ", "
		      << "'" << actual_name << "', "
		      << actual_health << "}.\n";

	    return false;
	}
    }
    
    return true;
}

static bool test_convert_to_int()
{
    int expected_ints[] = {128, 777, -300, 46};

    for (int i = 0; i < LEN(expected_ints); i++)
    {
	int actual = convert_to_int((char*)&expected_ints[i]);
	int expected = expected_ints[i];
	if (actual != expected)
	{
	    std::cout << "convert_to_int test failed. Expected '" << expected << "' but was '" << actual << "'\n";
	    return false;
	}
    }

    int actual_ints[LEN(expected_ints)];
    convert_to_ints((char*)&expected_ints, actual_ints, sizeof(actual_ints));

    int result = memcmp(expected_ints, actual_ints, sizeof(actual_ints));

    if (result != 0)
    {
	std::cout << "convert_to_ints test failed. Expected {";
	for (int i = 0; i < LEN(expected_ints); i++)
	{
	    std::cout << expected_ints[i];
	    if (i != LEN(expected_ints) - 1) std::cout << ", ";
	}
	std::cout << "} but was {";
	for (int i = 0; i < LEN(actual_ints); i++)
	{
	    std::cout << actual_ints[i];
	    if (i != LEN(actual_ints) - 1) std::cout << ", ";
	}
	std::cout << "}\n";
	return false;
    }

    return true;
}

static struct {
  ofstream::pos_type pos;
  std::vector<char> str;
} nstr_tests[] = {
    114,
    {'T', 'o', 'm', 'o', 'r', 'r', 'o', 'w', ' ', 'a', 'n', 'd', ' ', 't', 'o',
     'm', 'o', 'r', 'r', 'o', 'w', ' ', 'a', 'n', 'd', ' ', 't', 'o', 'm', 'o',
     'r', 'r', 'o', 'w', ' ', 'c', 'r', 'e', 'e', 'p', 's', ' ', 'i', 'n', ' ',
     't', 'h', 'i', 's', ' ', 'p', 'e', 't', 't', 'y', ' ', 'p', 'a', 'c', 'e',
     ' ', 'f', 'r', 'o', 'm', ' ', 'd', 'a', 'y', ' ', 't', 'o', ' ', 'd', 'a',
     'y', ' ', 't', 'o', ' ', 't', 'h', 'e', ' ', 'l', 'a', 's', 't', ' ', 's',
     'y', 'l', 'l', 'a', 'b', 'l', 'e', ' ', 'o', 'f', ' ', 'r', 'e', 'c', 'o',
     'r', 'd', 'e', 'd', ' ', 'h', 'i', 's', 't', 'o', 'r', 'y', '.'}
    };

static bool test_read_nstr()
{
    ifstream file(test_filename);
    for (int i = 0; i < LEN(nstr_tests); i++)
    {
	file.seekg(nstr_tests[i].pos);
	const std::vector<char>& expected_str = nstr_tests[i].str;
	std::string actual_str = read_null_terminated_string(file);
	if (expected_str.size() != actual_str.size())
	{
	    std::cout << "read_null_terminated_string() test failed at file offset " << nstr_tests[i].pos << ". Expected string length of '" << expected_str.size() << "' but was '" << actual_str.size() << "'." << std::endl;
	    return false;
	}
	int result = memcmp(expected_str.data(), actual_str.data(), actual_str.size());
	if (result != 0)
	{
	    std::cout << "read_null_terminated_string() test failed at file offset " << nstr_tests[i].pos << ". Expected string value of '" << expected_str << "' but was '" << actual_str << "'." << std::endl;
	    return false;
	}
    }

    return true;
  
}

static struct {
    ofstream::pos_type pos;
    int len;
    std::vector<char> str;
} str_tests[] = {{
    48,
    62,
    {'B', 'y', ' ', 't', 'h', 'e', ' ', 'p', 'r', 'i', 'c', 'k', 'i',
     'n', 'g', ' ', 'o', 'f', ' ', 'm', 'y', ' ', 't', 'h', 'u', 'm',
     'b', 's', ',', ' ', 's', 'o', 'm', 'e', 't', 'h', 'i', 'n', 'g',
     ' ', 'w', 'i', 'c', 'k', 'e', 'd', ' ', 't', 'h', 'i', 's', ' ',
     'w', 'a', 'y', ' ', 'c', 'o', 'm', 'e', 's', '.'}
    }
};

static bool test_read_prefixed_string()
{
    ifstream file(test_filename);
    for (int i = 0; i < LEN(str_tests); i++)
    {
	file.seekg(str_tests[i].pos);
	int expected_len = str_tests[i].len;
	const std::vector<char>& expected_str = str_tests[i].str;
	std::string actual_str = read_length_prefixed_string(file);
	if (actual_str.size() != expected_len)
	{
	    std::cout << "read_length_prefixed_string() test failed at file offset " << str_tests[i].pos << ". Expected length of " << expected_len << " but was " << actual_str.size() << std::endl;
	    return false;
	}
	int result = memcmp(expected_str.data(), actual_str.data(), actual_str.size());
	if (result != 0)
	{
	    std::cout << "read_length_prefixed_string() test failed at file offset " << str_tests[i].pos << ". Expected string value of '" << expected_str << "' but was '" << actual_str << "'." << std::endl;
	    return false;
	}
    }

    return true;
}

static struct {
    ofstream::pos_type pos;
    std::vector<int> expected;
} integer_tests[] = {
    {0, {812}},
    {16, {320}},
    {4, {24234, 99}},
    {8, {99, 150, 320, -55}},
    {0, {812, 24234, 99, 150, 320, -55, 0, 28}}
};

static bool test_read_integers()
{
    ifstream file(test_filename);
    for (int i = 0; i < LEN(integer_tests); i++)
    {
	
	ofstream::pos_type pos = integer_tests[i].pos;
	file.seekg(pos);
	std::vector<int> expected = integer_tests[i].expected;
	if (expected.size() == 1)
	{
	    int actual = read<int>(file);
	    if (actual != expected[0])
	    {
		std::cout << "read() test failed at file offset " << pos << ". Expected "
			  << expected[0] << " but was " << actual << std::endl;
		return false;
	    }
	}
	else
	{
	    std::vector<int> actual;
	    actual.resize(expected.size());
	    read_n(file, actual.data(), actual.size());
	    for (int j = 0; j < actual.size(); j++)
	    {
		if (actual[j] != expected[j])
		{
		    std::cout << "read_n() test failed reading " << actual.size()
			      << " ints from file offset " << pos << "."
			      << " Failed at the " << j << "th int. Expected "
			      << expected[j] << " but was " << actual[j] << std::endl;
		    return false;
		}
	    }
	}
    }

    return true;
}

static struct {
    bool (*test)();
    const char* name;
    int value;
} tests[] = {
    {test_read_integers, "test_read_integers", 5},
    {test_read_prefixed_string, "test_read_prefixed_string", 10},
    {test_read_nstr, "test_read_null_terminated_string", 5},
    {test_convert_to_int, "test_convert_to_int", 5},
    {test_read_game_entity, "test_read_game_entity", 5},
};

static bool tests_passed[sizeof(tests) / sizeof(tests[0])] = {false};

int run_all_tests() {
  int sum = 0;
  int total_possible = 0;
  bool passed_all_tests = true;
  for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
      auto test = tests[i];
      total_possible += test.value;
      std::cout << test.name << "\n------------\n";
      if (test.test())
      {
        sum += test.value;
        tests_passed[i] = true;
        std::cout << "Test passed\n\n";
      }
      else
      {
        std::cout << "Test failed\n\n";
        passed_all_tests = false;
      }
    }

  std::cout << "\n***  Scores  ***\n------------\n";
  for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
      auto test = tests[i];
      if (tests_passed[i])
      {
        std::cout << test.name << ": " << test.value << "/" << test.value << std::endl;
      }
      else
      {
        std::cout << test.name << ": " << 0 << "/" << test.value << std::endl;
      }
    }

  std::cout << "=====\nFinal score: " << sum << "/" << total_possible << std::endl;
  return passed_all_tests ? 0 : 1;
}
