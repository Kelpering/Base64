#include "../include/Base64.h"

char Base64Arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
uint8_t Base64Inv[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0};
uint8_t InvalidBytes[] = {0x2C, 0x2D, 0x2E, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F, 0x40, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60};

bool ValidateB64(char* B64String)
{
    //? Find string size (excluding '\0').
    size_t StrSize;
    for (StrSize = 0; B64String[StrSize] != '\0'; StrSize++);

    //? Check if the number of characters is a multiple of 4.
    if (StrSize % 4 != 0)
        return false;

    //? Checks for edge case "AA=A" where '=' is in the last 2, but still invalid.
    if (B64String[StrSize-2] == '=' && B64String[StrSize-1] != '=')
        return false;

    for (size_t i = 0; i < StrSize; i++)
    {
        //? Checks if the lower or upper bound is reached.
        if ((0x2A >= B64String[i]) | (B64String[i] >= 0x7B))
            return false;
        
        //? Checks if padding character '=' is out of place.
        if (B64String[i] == '=' && i < (StrSize - 2))
            return false;

        //? Check Invalid characters
        for (uint8_t j = 0; j < sizeof(InvalidBytes); j++)
        {
            if (B64String[i] == InvalidBytes[j])
                return false;
        }
    }

    return true;
}

ByteArr B64toByte(char* B64String)
{
    //? If not valid, return NULL pointer and a size of 0.
    if (ValidateB64(B64String) == false)
        return (ByteArr) {NULL, 0};

    size_t CharSize;
    ByteArr B64Arr;

    //? Find string size (excluding '\0').
    for (CharSize = 0; B64String[CharSize] != '\0'; CharSize++);
    
    //? Calculate size of ByteArr, then malloc
    B64Arr.Size = (CharSize / 4)*3;
    B64Arr.Array = malloc(B64Arr.Size);

    for (size_t i = 0, j = 0; i < CharSize; i+=4)
    {
        B64Arr.Array[j++] = (Base64Inv[B64String[i]] << 2) | (Base64Inv[B64String[i+1]] >> 4);                     //? First 6, Next 2
        B64Arr.Array[j++] = ((Base64Inv[B64String[i+1]] << 4) & 0b11110000) | ((Base64Inv[B64String[i+2]] >> 2));  //? Next 4,  Third 4
        B64Arr.Array[j++] = ((Base64Inv[B64String[i+2]] << 6) & 0b11000000) | Base64Inv[B64String[i+3]];           //? Third 2, Fourth 6
    }
    
    //? Removes padding, if necessary.
    if (B64String[CharSize-2] == '=')
        B64Arr.Size -= 2;
    else if (B64String[CharSize-1] == '=')
        B64Arr.Size -= 1;
    
    //? Reallocates the array to account for padding.
    B64Arr.Array = realloc(B64Arr.Array, B64Arr.Size);

    //! ByteArr itself should not need to be freed, but ByteArr.Array must be freed by the user.
    return B64Arr;
}

char* BytetoB64(uint8_t* Array, size_t Size)
{
    //? Size of string generated in Malloc
    size_t StringSize = 4*((Size + 2 - ((Size - 1) % 3))/3) + 1;
    //! StringSize must have a better equation for this.

    //? The malloc string here is 4 characters per 3 bytes w/ pad, plus 1 '\0'.
    char* B64String = malloc(StringSize);

    //? This runs all but padding Base64 steps
    for (size_t i = 0, j = 0; i < Size - (Size % 3); i+=3)
    {
        B64String[j++] = Base64Arr[(Array[i] >> 2)];
        B64String[j++] = Base64Arr[((Array[i] & 0x03) << 4) | (Array[i+1] >> 4)];
        B64String[j++] = Base64Arr[((Array[i+1] & 0x0F) << 2) | (Array[i+2] >> 6)];
        B64String[j++] = Base64Arr[(Array[i+2] & 0x3F)];
    }

    if ((Size % 3) == 1)
    {
        B64String[StringSize - 5] = Base64Arr[(Array[Size - 1] >> 2)];
        B64String[StringSize - 4] = Base64Arr[((Array[Size - 1] & 0x03) << 4) | 0];
        B64String[StringSize - 3] = '=';
        B64String[StringSize - 2] = '=';
    }
    else if ((Size % 3) == 2)
    {
        B64String[StringSize - 5] = Base64Arr[(Array[Size - 2] >> 2)];
        B64String[StringSize - 4] = Base64Arr[((Array[Size - 2] & 0x03) << 4) | (Array[Size - 1] >> 4)];
        B64String[StringSize - 3] = Base64Arr[((Array[Size - 1] & 0x0F) << 2) | 0];
        B64String[StringSize - 2] = '=';
    }
    //? Make B64String a valid string.
    B64String[StringSize - 1] = '\0';

    //! Warning, returns allocated string. Must be de-allocated after use.
    return B64String;
}
