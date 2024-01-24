//? Convert Base64 String into [?]
//? Convert [?] into Base64 String

// [?] options
// Byte array w/ variable size, Vector

#include <stdio.h>
#include <stdbool.h>
#include "../include/Base64.h"

int main()
{
    uint8_t Data[] = {'y', 'n'};
    char* test = BytetoB64(Data, 2);
    printf("%s\n", test);
    printf("IsB64: %d\n", ValidateB64("Aa==")); //* Valid
    return 0;
}
