#include <stdio.h>
#include <stdlib.h>

    int main() {
    FILE * in = fopen("test.img", "rb");
    unsigned int i, start_sector, length_sectors;

    fseek(in, 0x1BE, SEEK_SET); // Voy al inicio... 
    for(i=1; i<=4; i++) { // Leo las entradas
        unsigned char byte =fgetc(in); 
        printf("|----------------------------------------------------------\n");
        printf("|  Partition entry %d: First byte 0x%02X\n", i, byte);
        if ((byte==128)) {printf("|  Booteable\n");}else{printf("|  No Booteable\n");}
        printf("|  Partition start in CHS: %02X:%02X:%02X\n", fgetc(in), fgetc(in), fgetc(in));
        printf("|  Partition type 0x%02X\n", fgetc(in));
        printf("|  Partition end in CHS: %02X:%02X:%02X\n", fgetc(in), fgetc(in), fgetc(in));
        
        fread(&start_sector, 4, 1, in);
        fread(&length_sectors, 4, 1, in);
        printf("|  Relative LBA address 0x%08X, %d sectors long\n", start_sector, length_sectors);
        printf("|----------------------------------------------------------\n\n");

    }
    
    fclose(in);
    return 0;
}
