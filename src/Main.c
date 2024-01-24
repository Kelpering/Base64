//? Convert Base64 String into [?]
//? Convert [?] into Base64 String

// [?] options
// Byte array w/ variable size, Vector

#include <stdio.h>
#include <stdbool.h>
#include "../include/Base64.h"

int main()
{
    // uint8_t Data[] = {'y', 'n'};
    // BytetoB64(Data, 2);
    printf("IsB64: %d\n", ValidateB64("AE==")); //* Valid
    printf("IsB64: %d\n", ValidateB64("A===")); //! Invalid
    printf("IsB64: %d\n", ValidateB64("A[==")); //! Invalid
    printf("IsB64: %d\n", ValidateB64("AB=")); //! Invalid
    printf("IsB64: %d\n", ValidateB64("ABC=")); //* Valid
    printf("IsB64: %d\n", ValidateB64("AECD")); //* Valid
    return 0;
}
