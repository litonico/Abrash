#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    FILE *CheckFile;
    int Byte;
    unsigned int Checksum;

    if ( argc != 2 ) {
        printf("usage: checksum filename\n");
        return 1;
    }

    CheckFile = fopen(argv[1], "rb");
    if (CheckFile == NULL) {
        printf("Can't open file %s\n", argv[1]);
    }

    Checksum = 0;

    Byte = getc(CheckFile);
    while (Byte != EOF) {
        Checksum += (unsigned int)Byte;
        Byte = getc(CheckFile);
    }

    printf("The checksum is: %u\n", Checksum);
    return 0;
}
