#include "util.h"

void SRAM_test(void)
{
    unsigned int i;
    //Start address for the SRAM
    volatile char* ext_ram = (char*) 0x1800;
    unsigned int   werrors = 0;
    unsigned int   rerrors = 0;
    unsigned char  testvalue;

    int seed = rand();

    printf("Starting SRAM test...\r\n");
    srand(seed);
    for (i = 0; i < 0x800; i++)
    {
        testvalue  = rand();
        ext_ram[i] = testvalue;
        if (ext_ram[i] != testvalue)
        {
            printf("SRAM error (write phase): ext_ram[%d] = %02X \
                   (should be %02X)\r\n", i, ext_ram[i],
                   testvalue);
            werrors++;
        }
    }

    srand(seed);
    for (i = 0; i < 0x800; i++)
    {
        testvalue = rand();
        if (ext_ram[i] != testvalue)
        {
            printf("SRAM error (read phase): ext_ram[%d] = %02X \
                   (should be %02X)\r\n", i, ext_ram[i],
                   testvalue);
            rerrors++;
        }
    }
    printf("SRAM test completed with %d errors in write phase and %d errors \
           in read phase\r\n", werrors,
           rerrors);
}

