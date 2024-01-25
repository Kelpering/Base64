#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../include/Base64.h"

int main()
{
    uint8_t Data[] = {'y', 'n'};
    char* test = BytetoB64(Data, 2);
    B64toByte("eW4fabc=");
    printf("B64String returned: %s\n", test);
    printf("IsB64: %s\n", ValidateB64(test) ? "True" : "False"); //* Valid

    return 0;
}
