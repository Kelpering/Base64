#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    uint8_t* Array;
    size_t   Size;
} ByteArr;

// We can make this public, as it is a useful function.
bool ValidateB64(char* B64String);

// ByteArr is struct
ByteArr B64toByte(char* B64String);

/// @brief Translate a Byte array into a Base64 string. (RFC4648 Compliant) -DOUBLE CHECK IF TRUE-
/// @param Array A byte array to be translated to Base64.
/// @param Size The size of the byte array to translate.
/// @returns An allocated Base64, null terminated string.
/// @warning Returns an allocated string. MUST be de-allocated to prevent memory leak.
char* BytetoB64(uint8_t* Array, size_t Size);
