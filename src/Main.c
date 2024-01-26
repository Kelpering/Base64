#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../include/Base64.h"

void PrintData(void* Data, size_t Size);

int main()
{
    uint8_t Data[] = {'a', 22, 0x53, 0, '7'};
    // uint8_t Data[] = "Teste";
    char* test;
    ByteArr testArr;
    
    printf("\n");
    printf("Original Data: \n");
    PrintData(Data, sizeof(Data));

    test = BytetoB64(Data, sizeof(Data));
    printf("\nString returned: %s\n", test);
    printf("IsB64: %s\n\n", ValidateB64(test) ? "True" : "False"); //* Valid

    testArr = B64toByte(test);
    printf("Size of Data: %d\n", testArr.Size);
    printf("Data Returned: \n");
    PrintData(testArr.Array, testArr.Size);

    free(test);
    free(testArr.Array);

    return 0;
}

void PrintData(void* Data, size_t Size)
{
    uint8_t* DataCast = (uint8_t*) Data;
    for (int i = 0; i < Size - 1; i++)
    {
        printf("0x%X, ", DataCast[i]);
    }
    printf("0x%X", DataCast[Size - 1]);
}
