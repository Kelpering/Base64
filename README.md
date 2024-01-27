# Base64

A project written entirely in C, designed to be a Base64 implementation. With functions to validate, convert to, and convert from Base64 strings.

## Methods

### ValidateB64()

Checks whether a string is a valid Base64 string, returns a boolean.

```C
int main()
{
    char Valid[] = "VGVzdCBEYXRhAA==";
    char Invalid[] = "Hello, World!";

    ValidateB64(Valid);     // Returns True  (1)
    ValidateB64(Invalid);   // Returns False (0)

    return 0;
}
```

### B64toByte()

Converts a valid Base64 string into an array of bytes, along with its size. **The array is dynamically allocated and must be de-allocated by the user to prevent memory leaks.**

```C
int main()
{
    char Data[] = "VGVzdCBEYXRhAA==";
    // ByteArr is a typedef struct that contains an array pointer and size value.
    ByteArr Bytes;

    Bytes = B64toByte(Data);
    Bytes.Array;    // uint8_t[] pointer
    Bytes.Size      // Size of uint8_t[] Array

    free(Array);    // Array must be freed.

    return 0;
}
```

### BytetoB64()

Converts a byte array into a valid Base64 string. **The string is dynamically allocated and must be de-allocated by the user to prevent memory leaks.**

```C
int main()
{
    // Data can be anything, including strings.
    char Data[] = {'t', 'e', 's', 't', '\0'};
    
    char* B64String = BytetoB64(Data, 5); // (Byte array, Size of Byte array)

    ValidateB64(B64String); // Returns True (1)

    free(B64String) // String must be freed.

    return 0;
}
```
