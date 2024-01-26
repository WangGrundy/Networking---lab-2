# Objective #

This assignment is designed to help you familiarize yourself with and
practice working with binary-encoded data. The primary mechanisms
through which we will practice this are the `ostream::write()` and
`istream::read()` functions. This will help us when we need to use
similar logic when we transition to network programming.

# Questions #

## Q1

In read.h, implement the `read()` and `read_n()` templated functions:
```c++
template <typename T>
T read(std::ifstream& file)
```
- Parameters:
  - `file`: the file to read from.
- Return value:
  - The value that was read.
  
```c++
template <typename T>
void read_n(std::ifstream& file, T* out_array, size_t len)
```
- Parameters:
  - `file`: the file to read from
  - `out_array`: a pointer to a buffer of integers to write to
  - `len`: the number of elements that should be read from the file
    and written into `out_array`.
- **Your implementation should call `file.read()` _exactly once_.**

Hint: If you're finding this question difficult, try writing these
functions to help you understand what needs to be done:

```c++
int read_int(std::ifstream& file);
```

```c++
void read_ints(std::ifstream& file, int* int_array, size_t len);
```

## Q2

In read.cpp, implement the `read_length_prefixed_string()` and
`read_null_terminated_string()` functions:

```c++
std::string read_length_prefixed_string(std::ifstream& file)
```
- Read 4 bytes (one `int`) from the file. This will tell you the length of the string.
- Read the string of that length and return it.


```c++
std::string read_null_terminated_string(std::ifstream& file)
```
- Read a byte at a time, stopping when you read a byte whose value is
  `'\0'`, called a "null terminator".
- Return a string that contains all the bytes before the null
  terminator `'\0'`. DO NOT include the null terminator in the
  resulting string.
  
## Q3

In read.cpp, implement `convert_to_int()` and `convert_to_ints()`:

```c++
int convert_to_int(char* bytes)
```

Convert the bytes pointed to by `bytes` to an int.

```c++
void convert_to_ints(char* bytes, int* int_array, size_t len);
```
Convert `len` bytes (_not_ `int`s) from `bytes` into `int`s, copying
them into `int_array`. You can assume `int_array` is long enough to
store `len` bytes worth of `int`s.

Hint: Loop through the bytes, copying them into `int_array` one at a
time.

## Q4

In read.cpp, implement `read_game_entity()`:

```c++
void read_game_entity(std::istream& file,
		      float& x, float& y, float& z,
		      std::string& name,
		      int& health);
```

- Write the `read_game_entity()` function. Note that game entities
  take the following format, in order:
  - An x, y, and z position, each of which is a float
  - A name, which is up to 40 bytes long
  - A health value, which is always an integral value
	- `read_game_entity()` should write to each of the given output
      parameters.

Hint: It may help to make a struct that describes this object.
