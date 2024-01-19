#include "../include/Base64.h"

char Base64Arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

ByteArr B64toByte(char* B64String)
{

}

char* BytetoB64(uint8_t* Array, size_t Size)
{
    // size_t NewSize = Size + (Size % 3);
    // Split every 3 bytes into 4 chars
    // Pad array first?
    // uint8_t* NewArr = malloc(NewSize);
    // for (size_t i = 0; i < Size; i++)
    // {
    //     NewArr[i] = Array[i];
    // }
    // for (size_t i = Size; i < NewSize; i++)
    // {
    //     NewArr[i] = 0;
    //     // Should run once, twice, or never
    // }

    // NewSize should be divisible by 3 bytes
    // For every 3 bytes, there should be 4 chars
    //! This might work, might not.
        // NewArr[i];      // First Byte
        // NewArr[i+1];    // Next Byte
        // NewArr[i+2];    // Last Byte
        // (NewArr[i] >> 2);                                   // First letter
        // ((NewArr[i] & 0b11) << 4) | (NewArr[i+1] >> 4);     // Second letter
        // ((NewArr[i+1] & 0b1111) << 2) | (NewArr[i+2] >> 6); // Third letter
        // (NewArr[i+2] & 0b111111);                           // Final Letter

    char* B64String = malloc(((Size/3) * 4) + 1);
    B64String[((Size/3) * 4) + 1] = '\0';
    for (size_t i = 0, j = 0; i < Size - (Size % 3); i+=3)
    {
        B64String[j++] = Base64Arr[(Array[i] >> 2)];
        B64String[j++] = Base64Arr[((Array[i] & 0b11) << 4) | (Array[i+1] >> 4)];
        B64String[j++] = Base64Arr[((Array[i+1] & 0b1111) << 2) | (Array[i+2] >> 6)];
        B64String[j++] = Base64Arr[(Array[i+2] & 0b111111)];
    }
    if ((Size % 3) == 1)
    {
        // No idea if this is right
        B64String[((Size/3) * 4) - 3] = Base64Arr[(Array[Size-2] >> 2)];
        B64String[((Size/3) * 4) - 2] = Base64Arr[((Array[Size-2] & 0b11) << 4) | (Array[Size-1] >> 4)];
        B64String[((Size/3) * 4) - 1] = Base64Arr[((Array[Size-1] & 0b1111) << 2) | (Array[Size] >> 6)];
        B64String[((Size/3) * 4) - 0] = Base64Arr[(Array[Size] & 0b111111)];
    }
    else if ((Size % 3) == 2)
    {

    }
    
    // There are either 0, 1, or 2 bytes to add
    // 0: done
    // 1: 8 '0' bits are needed
    // 2: 16 '0' bits are needed

}
