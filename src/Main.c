#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../include/Base64.h"

int main()
{
    uint8_t Data[] = "Test string, can use any binary data.";
    char* test;
    ByteArr testArr;
    
    test = BytetoB64(Data, sizeof(Data));
    printf("String returned: %s\n", test);
    printf("IsB64: %s\n", ValidateB64(test) ? "True" : "False"); //* Valid

    testArr = B64toByte(test);
    printf("Size of Data: %d", testArr.Size);
    printf("Data string salvaged: %s\n", testArr.Array);

    return 0;
}
