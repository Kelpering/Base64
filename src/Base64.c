#include "../include/Base64.h"

char Base64Arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// Make inverse of array, should be about 128 max size, can be lowered to probably ~90 but whitespace between lowercase plays a factor.
uint8_t InvalidBytes[] = {0x2C, 0x2D, 0x2E, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F, 0x40, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60};

bool ValidateB64(char* B64String)
{
    //? Find size (exclude '\0')
    size_t StrSize;
    for (StrSize = 0; B64String[StrSize] != '\0'; StrSize++);

    //? Check remainder, as it is fastest.
    if (StrSize % 4 != 0)
        return false;

    for (size_t i = 0; i < StrSize; i++)
    {
        //? Checks majority as OoB
        //! Lowercase is giving errors
        if ((0x2A >= B64String[i]) | (B64String[i] >= 0x7B))
            return false;
        
        //? If '=' is anywhere but the last 2 characters, return false.
        if (B64String[i] == '=' && i < (StrSize - 2))
            return false;

        //? Check Invalid characters
        for (uint8_t j = 0; j < 15; j++)
        {
            //? If the character is invalid, return false.
            if (B64String[i] == InvalidBytes[j])
                return false;
        }
    }

    if (B64String[StrSize-2] == '=' && B64String[StrSize-1] != '=')
        return false;

    return true;
}

ByteArr B64toByte(char* B64String)
{
    //? If not valid, return NULL pointer and a size of 0.
    if (ValidateB64(B64String) == false)
        return (ByteArr) {NULL, 0};

    size_t CharSize;
    ByteArr B64Arr;

    // Just chars, not null terminator
    for (CharSize; B64String[CharSize] != '\0'; CharSize++);
    
    // Calculate size of ByteArr, then malloc
    B64Arr.Size = (CharSize / 4)*3;
    B64Arr.Array = malloc(B64Arr.Size);

    for (size_t i = 0, j = 0; i < CharSize - 4; i+=4)
    {
        //! Double check the math; it was a complete guess.
        //! I know that the B64String[i] is wrong, we need to convert that into B64 bytes.
        B64Arr.Array[j++] = (B64String[i] << 2) | (B64String[i+1] >> 4)                     //? (First 6), next 2
        B64Arr.Array[j++] = ((B64String[i+1] << 2) & 0b00111100) | ((B64String[i+2] >> 2))  //? Next 4, third 4
        B64Arr.Array[j++] = ((B64String[i+2] << 6) & 0b00110000) | B64String[i+3]           //? third 2, (fourth 6)
    }
    //! Here needs the final 4 with 
    
    // while loop through the string until the last 4 characters
    // Possibly fix last 4 automatically, if not, use special alg for those alone.
    
    // When ByteArr is ready, set pointer to ByteArr.Array and size to its size.
    // return ByteArr
    //! ByteArr itself should not need to be freed, but Array* need to be.
    return B64Arr;
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
        B64String[j++] = Base64Arr[((Array[i] & 0x03) << 4) | (Array[i+1] >> 4)];
        B64String[j++] = Base64Arr[((Array[i+1] & 0x0F) << 2) | (Array[i+2] >> 6)];
        B64String[j++] = Base64Arr[(Array[i+2] & 0x3F)];
    }
    //! Switch is temporary; it should be further automatable.
    switch (Size % 3)
    {
    case 1:
        //? Size / 3 has a remainder of 1 (2 bytes padding)
        B64String[StringSize - 5] = Base64Arr[(Array[Size - 1] >> 2)];
        B64String[StringSize - 4] = Base64Arr[((Array[Size - 1] & 0x03) << 4) | 0];
        B64String[StringSize - 3] = '=';
        B64String[StringSize - 2] = '=';
        break;
    case 2:
        //? Size / 3 has a remainder of 2 (1 byte padding)
        B64String[StringSize - 5] = Base64Arr[(Array[Size - 2] >> 2)];
        B64String[StringSize - 4] = Base64Arr[((Array[Size - 2] & 0x03) << 4) | (Array[Size - 1] >> 4)];
        B64String[StringSize - 3] = Base64Arr[((Array[Size - 1] & 0x0F) << 2) | 0];
        B64String[StringSize - 2] = '=';
        break;
    }
    B64String[StringSize - 1] = '\0';

    //! Warning, returns allocated string. Must be de-allocated after use.
    return B64String;
}
