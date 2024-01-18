#pragma once
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint8_t* Array;
    size_t   Size;
} ByteArr;

// ByteArr is struct
ByteArr B64toByte(char* B64String);

// Not using ByteArr, this is easier and more formal.
char* BytetoB64(uint8_t* Array, size_t Size);