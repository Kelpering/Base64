#include "../include/Base64.h"
#include <stdio.h>

char Base64Arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

ByteArr B64toByte(char* B64String)
{
    ByteArr test = 
    {
        .Array = NULL,
        .Size = 0
    };
    return test;
}

char* BytetoB64(uint8_t* Array, size_t Size)
{
    //? Size of string generated in Malloc
    size_t StringSize = 4 * ((Size + (3 - (Size % 3))) / 3) + 1;

    //? The malloc string here is 4 characters per 3 bytes, plus 1 '\0'.
    char* B64String = malloc(StringSize);

    //? This runs all but padding Base64 steps
    for (size_t i = 0, j = 0; i < Size - (Size % 3); i+=3)
    {
        B64String[j++] = Base64Arr[(Array[i] >> 2)];
        B64String[j++] = Base64Arr[((Array[i] & 0b11) << 4) | (Array[i+1] >> 4)];
        B64String[j++] = Base64Arr[((Array[i+1] & 0b1111) << 2) | (Array[i+2] >> 6)];
        B64String[j++] = Base64Arr[(Array[i+2] & 0b111111)];
    }
    //! Switch is temporary; it should be further automatable.
    switch (Size % 3)
    {
    case 1:
        //? Size / 3 has a remainder of 1 (2 bytes padding)
        B64String[StringSize - 5] = Base64Arr[(Array[Size - 1] >> 2)];
        B64String[StringSize - 4] = Base64Arr[((Array[Size - 1] & 0b11) << 4) | 0];
        B64String[StringSize - 3] = '=';
        B64String[StringSize - 2] = '=';
        break;
    case 2:
        //? Size / 3 has a remainder of 2 (1 byte padding)
        B64String[StringSize - 5] = Base64Arr[(Array[Size - 2] >> 2)];
        B64String[StringSize - 4] = Base64Arr[((Array[Size - 2] & 0b11) << 4) | (Array[Size - 1] >> 4)];
        B64String[StringSize - 3] = Base64Arr[((Array[Size - 1] & 0b1111) << 2) | 0];
        B64String[StringSize - 2] = '=';
        break;
    }
    B64String[StringSize - 1] = '\0';

    //! Warning, returns allocated string. Must be de-allocated after use.
    return B64String;
}
