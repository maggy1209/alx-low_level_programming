alx-low_level_programming
# 0x05. C - Pointers, arrays and strings.

## Mandatory Task
Task `0`  function that takes a pointer to an `int` as parameter and updates the value it points to to `98`.
Task `1` function that swaps the values of two integers.
Task `2` function that returns the length of a string.
Task `3`  function that prints a string, followed by a new line, to `stdout`.
Task `4` function that prints a string, in reverse, followed by a new line.
Task`5` function that reverses a string.
Task `6` function that prints every other character of a string, starting with the first character, followed by a new line.
Task `7`  function that prints half of a string, followed by a new line.
Task `8` function that prints n elements of an array of integers, followed by a new line.

*Prototype: void print_array(int *a, int n);
*where `n` is the number of elements of the array to be printed
*Numbers must be separated by comma, followed by a space
*The numbers should be displayed in the same order as they are stored in the array
*You are allowed to use(` printf`)
Task `9` function that copies the string pointed to by src, including the terminating null byte (\0), to the buffer pointed to by dest.

Return value: the pointer to dest
## Advance Task##
Task `10`  function that convert a string to an integer.

*Prototype: int _atoi(char *s);
*The number in the string can be preceded by an infinite number of characters
*You need to take into account all the - and + signs before the number
*If there are no numbers in the string, the function must return 0
*You are not allowed to use long
*You are not allowed to declare new variables of “type” array
*You are not allowed to hard-code special values
*We will use the -fsanitize=signed-integer-overflow gcc flag to compile your code.
Task `11` program that generates random valid passwords for the program 101-crackme.

*You are allowed to use the standard library
*You don’t have to pass the betty-style tests (you still need to pass the betty-doc tests)
*man srand, rand, time
*gdb and objdump can help
