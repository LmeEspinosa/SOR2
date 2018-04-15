#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char first_byte;
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    char start_sector[4];
    char length_sectors[4];
} __attribute((packed)) PartitionTable;

typedef struct {
      //char un byte
     //short 2 bytes
    //long 4 bytes
    unsigned char jmp[3];
    unsigned char oem[8];
    unsigned short sector_size; // 2 bytes
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char number_of_fats;
    unsigned short root_dir_entries;
    unsigned short total_sectors_short;
    unsigned char media_descriptor;
    unsigned short fat_size_sectors;
    unsigned short sectors_per_track;
    unsigned short number_of_heads;
    unsigned int hidden_sectors;
    unsigned int total_sectors_long;
    unsigned char drive_number;
    unsigned char current_head;
    unsigned char Extended_boot_signature;
    unsigned int  volume_id;
    unsigned char volume_label[11];
    unsigned char fs_type[8]; // Type in ascii
    unsigned char boot_code[448];
    unsigned short boot_sector_signature;
} __attribute((packed)) Fat12BootSector;

int main() {
    FILE * in = fopen("test.img", "rb");
    int i;
    PartitionTable pt[4];
    Fat12BootSector bs;
    
    fseek(in, 0x1BE, SEEK_SET); // Ir al inicio de la tabla de particiones
    fread(pt, sizeof(PartitionTable), 4, in); // leo entradas 
    
    for(i=0; i<4; i++) {        
        printf("Partition type: %d\n", pt[i].partition_type);
        if(pt[i].partition_type == 1) {
            printf("Encontrado FAT12 %d\n", i);
            break;
        }
    }
    
    if(i == 4) {
        printf("No FAT12 filesystem found, exiting...\n");
        return -1;
    }
    
    fseek(in, 0, SEEK_SET);
    fread(&bs, sizeof(Fat12BootSector), 1, in);
    printf("  Jump code: %02X:%02X:%02X\n", bs.jmp[0], bs.jmp[1], bs.jmp[2]);
    printf("  OEM code: [%.8s]\n", bs.oem);
    printf("  sector_size: %d\n", bs.sector_size);
    printf("  sector_per_cluster %d\n",bs.sectors_per_cluster);
    printf("  reserved_sector %d\n",bs.reserved_sectors);
    printf("  number_of_fats %d\n",bs.number_of_fats);
    printf("  root_dir_entries: %d\n", bs.root_dir_entries);
    printf("  total_sectors_short: %d\n", bs.total_sectors_short);
    printf("  media_descriptor: 0x%02X\n", bs.media_descriptor);
    printf("  fat_size_sectors: %d\n", bs.fat_size_sectors);
    printf("  sectors_per_track: %d\n", bs.sectors_per_track);
    printf("  number_of_heads: %d\n", bs.number_of_heads);
    printf("  hidden_sectors: %d\n",bs.hidden_sectors);
    printf("  total_sectors_long: %d\n",bs.total_sectors_long);
    printf("  drive_number: 0x%02X\n", bs.drive_number);
    printf("  current_head: 0x%02X\n", bs.current_head);
    printf("  Extended_boot_signature: 0x%02X\n", bs.Extended_boot_signature);
    printf("  volume_id: 0x%d\n",bs.volume_id);
    printf("  Volume label: [%.11s]\n", bs.volume_label);
    printf("  Filesystem type: [%.8s]\n", bs.fs_type);
    printf("  boot code 0x%lu\n",(unsigned long)bs.boot_code);
    printf("  Boot sector signature: 0x%04X\n", bs.boot_sector_signature);
    
    fclose(in);
    return 0;
}
