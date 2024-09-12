#ifndef MYFDISK_H
#define MYFDISK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <uuid/uuid.h>
#include <string.h>
//it is the begining of the entries where we skipped the bootloader part the first 446;
#define Entry_index_begin 446


typedef struct {  

    uint8_t status ; 
    uint8_t CHS_first [3];
    uint8_t type ;
    uint8_t CHS_last [3];
    uint32_t LBA ;
    uint32_t sec_no ;

}partition_entry;

typedef struct {
    uint8_t signature[8];
    uint32_t revision_no;
    uint32_t header_size ;
    uint32_t CRC32_header ;
    uint32_t reserved;
    uint64_t current_LBA;  
    uint64_t Backup_LBA ;
    uint64_t first_LBA;
    uint64_t last_LBA;
    uint8_t Disk_GUID[16];
    uint64_t start_LBA_arr_entry;
    uint32_t no_entry;
    uint32_t size_entry;
    uint32_t CRC32;
    //rest is zero
} gpt_partition_head;

typedef struct 
{
    uint8_t partition_type_guid[16];
    uint8_t unique_partition_guid[16];
    uint64_t first_LBA;
    uint64_t last_LBA;
    uint64_t attribute_flags;
    char partition_name[72];
}GUID_entry;



typedef enum {
    GPT,
    normalMBR,
    Extended
}case_type;

void print_table (partition_entry* table , case_type typeentry,uint8_t index_extended,uint32_t fd,char** argv);

void make_extendedlist(partition_entry* table , uint8_t index_extended ,uint32_t fd,char** argv);

void make_GPT (uint64_t fd ,char** argv);

















#endif