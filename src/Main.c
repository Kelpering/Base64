#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../include/Base64.h"

int main()
{
    uint8_t Data[] = "Test string";
    char* test;
    ByteArr testArr;
    
    printf("\nOriginal String: %s\n", Data);
    test = BytetoB64(Data, sizeof(Data));
    printf("String returned: %s\n", test);
    printf("IsB64: %s\n\n", ValidateB64(test) ? "True" : "False"); //* Valid

    testArr = B64toByte(test);
    printf("Size of Data: %d\n", testArr.Size);
    printf("Data string salvaged: %s\n", testArr.Array);

    return 0;
}
