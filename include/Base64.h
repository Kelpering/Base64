#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t* Array;
    size_t   Size;
} ByteArr;

/// @brief Checks whether a string is Base64 encoding.
/// @param B64String The string to check.
/// @return A boolean value.
bool ValidateB64(char* B64String);

/// @brief Translates a Base64 string into a byte array. (RFC4748 Compliant) -DOUBLE CHECK IF TRUE-
/// @param B64String A Base64 string to be translated, null terminated.
/// @returns A ByteArr struct, containing an allocated uint8_t array pointer and the Size of said array.
/// @note If B64String is found to be an invalid Base64 string, the function returns (ByteArr) {NULL, 0}.
/// @warning Returns an allocated array. MUST be de-allocated to prevent memory leak.
ByteArr B64toByte(char* B64String);

/// @brief Translate a byte array into a Base64 string. (RFC4648 Compliant) -DOUBLE CHECK IF TRUE-
/// @param Array A byte array to be translated to Base64.
/// @param Size The size of the byte array to translate.
/// @returns An allocated Base64, null terminated string.
/// @warning Returns an allocated string. MUST be de-allocated to prevent memory leak.
char* BytetoB64(uint8_t* Array, size_t Size);
