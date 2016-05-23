#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 0x8000 // 32kb

int main(int argc, char *argv[])
{
    int Handle;
    unsigned int Checksum;
    unsigned char *WorkingBuffer, *WorkingPtr;
    int WorkingLength, LengthCount;

    if ( argc != 2 ) {
        printf("usage: checksum filename\n");
        return 1;
    }

    Handle = open(argv[1], O_RDONLY);
    if (Handle == -1) {
        printf("Can't open file %s\n", argv[1]);
        return 1;
    }

    WorkingBuffer = malloc(BUFFER_SIZE);

    if ( WorkingBuffer == NULL ) {
        printf("Not enough memory!");
        return 1;
    }

    Checksum = 0;

    do {
        WorkingLength = read(Handle, WorkingBuffer, BUFFER_SIZE);
        if ( WorkingLength == -1 ) {
            printf("error reading file");
        }
        WorkingPtr = WorkingBuffer;
        LengthCount = WorkingLength;
        while ( LengthCount-- ) { // Walk through the buffer
            Checksum += (unsigned int)*WorkingPtr;
            WorkingPtr++;
        }
    } while ( WorkingLength );
    printf("The checksum is: %u\n", Checksum);
    return 0;
}
