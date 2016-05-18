#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int Handle;
    unsigned char Byte;
    unsigned int Checksum;
    int ReadLength;

    if ( argc != 2 ) {
        printf("usage: checksum filename\n");
        return 1;
    }

    Handle = open(argv[1], O_RDONLY);
    if ( Handle == -1 ) {
        printf("Can't open file %s\n", argv[1]);
    }

    Checksum = 0;

    ReadLength = read(Handle, &Byte, sizeof(Byte));
    while (ReadLength > 0) {
        Checksum += (unsigned int)Byte;
        ReadLength = read(Handle, &Byte, sizeof(Byte));
    }
    if ( ReadLength == -1 ) {
        printf("Error reading file %s\n", argv[1]);
        return 1;
    }

    printf("The checksum is: %u\n", Checksum);
    return 0;
}
