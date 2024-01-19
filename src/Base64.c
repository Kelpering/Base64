#include "../include/Base64.h"

char Base64Arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

ByteArr B64toByte(char* B64String)
{

}

char* BytetoB64(uint8_t* Array, size_t Size)
{
    size_t NewSize = Size + (Size % 3);
    // Split every 3 bytes into 4 chars
    // Pad array first?
    uint8_t* NewArr = malloc(NewSize);
    for (size_t i = 0; i < Size; i++)
    {
        NewArr[i] = Array[i];
    }
    for (size_t i = Size; i < NewSize; i++)
    {
        NewArr[i] = 0;
        // Should run once, twice, or never
    }

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

    char* B64String = malloc((NewSize/3) * 4)
    for (size_t i = 0, j = 0; i < Size; i+=3)
    {
        B64String[j++] = Base64Arr[(NewArr[i] >> 2)];
        B64String[j++] = Base64Arr[((NewArr[i] & 0b11) << 4) | (NewArr[i+1] >> 4)];
        B64String[j++] = Base64Arr[((NewArr[i+1] & 0b1111) << 2) | (NewArr[i+2] >> 6)];
        B64String[j++] = Base64Arr[(NewArr[i+2] & 0b111111)];
        // I am unsure if this is correct, as the pad has to be '='. This is never reached
        //! Either the Base64Arr[] is wrong, or the pad byte is special and must be applied later
        //! Size - 3 might be the new for loop, different step for padding.
    }
}
