//? Convert Base64 String into [?]
//? Convert [?] into Base64 String

// [?] options
// Byte array w/ variable size, Vector

#include <stdio.h>
#include "../include/Base64.h"

int main()
{
    uint8_t Data[] = {'y', 'n'};
    BytetoB64(Data, 2);
    return 0;
}
