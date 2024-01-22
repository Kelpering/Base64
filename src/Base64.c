#include "../include/Base64.h"

char Base64Arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
uint8_t Invalid[] = 
{   
    /*0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 

    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 

    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2C, 0x2D, 0x2E,*/ 
    0x3A, 0x3B, 0x3C, 0x3E, 0x3F, 

    0x40, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 

    0x60, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 
};
//! This byte array can also be improvised after 128 with a '>'
//! and another low '<'

bool ValidateB64(char* B64String)
{
    //? Check Size (Faster, so begin with it), (Chars % 4) = 0 

    //? For each byte, until '/0' (Null terminator of string)
        //? Check OoB greaters and lesses '>' & '<'
        //? Check invalid Array for each 
}

ByteArr B64toByte(char* B64String)
{
    ValidateB64(B64String);
        //! If not valid, return NULL pointer and a size of 0.
    //? Calculate size of ByteArr, then malloc
    //? while loop through the string until the last 4 characters
    //? Possibly fix last 4 automatically, if not, use special alg for those alone.
    
    //? When ByteArr is ready, set pointer to ByteArr.Array and size to its size.
    //? return ByteArr
    //! ByteArr itself should not need to be freed, but Array* need to be.
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
