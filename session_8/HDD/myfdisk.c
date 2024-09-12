#include "myfdisk.h"

int i = 5 ; 
int flag=0 ;
int printed = 0 ; 
void print_table(partition_entry* table, case_type typeentry, uint8_t index_extended, uint32_t fd, char** argv) {
    if (typeentry == normalMBR) {
        if(printed == 0 )
        {
            printf("%-10s %-12s %-10s %-10s %-10s \t%-10s    %-10s %-10s\n","Device","Boot","Start","End","Sector","Size","ID","Type");
            printed = 1 ;
        }

        uint64_t end = table->LBA + table->sec_no - 1;
        uint64_t size = (uint64_t)table->sec_no ;
        double category_size = 0;
        char category;

        // Determine the appropriate size unit and convert size accordingly
        if (size < 2) 
        {
            category_size = size ;
            category = 'B';
        } 
        else if (size < 2 * 1024) 
        {
            category = 'K';
            category_size = size / 1024.0;
        } 
        else if (size < 2 * 1024 * 1024) 
        {
            category = 'M';
            category_size = size / (1024.0 * 1024.0);
        } 
        else 
        {
            category = 'G';
            category_size = size / (1024.0 * 1024.0 * 1024.0);
        }

        printf("%s%d %-12c %-10u %-10lu %-10u   %8.1f%cB %10X\n",
            argv[1],                       
            index_extended,
            (table->status == 0x80) ? '*' : ' ', 
            table->LBA,                  
            end,                       
            table->sec_no,                  
            category_size*512,                      
            category,                  
            table->type                    
        );
        if(index_extended >= 4)
        {
            index_extended =  i;
            i++;
        }
    }

    if (typeentry == Extended) {
        make_extendedlist(table, index_extended, fd, argv);
    }

    if (typeentry == GPT) {
        if(flag == 0)
        {
            if(flag == 0)
            {
                //system("clear");
                printf("%-10s   %-10s %-10s %-10s %-10s %s\n", "Device", "Start", "End", "Sectors", "Size", "Type");
                printed =1 ;

            }
            flag=1;

            make_GPT(fd,argv);
            return;
        }
        //char buf[512];
        GUID_entry* carry = (GUID_entry*) table ;
        char buf[37];
        char* type;
        uuid_unparse(carry->partition_type_guid, buf);

        if(strcmp(buf, "48616821-4964-6f6e-744e-656564454649") == 0) 
            type = strdup("BIOS boot");
        else if (strcmp(buf, "28732ac1-1ff8-d211-ba4b-00a0c93ec93b") == 0) 
            type = strdup("EFI System");
        else if (strcmp(buf, "af3dc60f-8384-7247-8e79-3d69d8477de4") == 0) 
            type = strdup("Linux filesystem");
        else 
            type = strdup("Unknown");

        // Get partition size
        uint64_t size = carry->last_LBA - carry->first_LBA + 1; // Include the last LBA sector
        double category_size = 0;
        char category;

        // Determine the appropriate size unit and convert size accordingly
        if (size < 2) 
        {
            category_size = size ;
            category = 'B';
        } 
        else if (size < 2 * 1024) 
        {
            category = 'K';
            category_size = size / 1024.0;
        } 
        else if (size < 2 * 1024 * 1024) 
        {
            category = 'M';
            category_size = size / (1024.0 * 1024.0);
        } 
        else 
        {
            category = 'G';
            category_size = size / (1024.0 * 1024.0 * 1024.0);
        } 

        // Display partition info
        printf("%s%d    %-10lu %-10lu %-10lu %.1lf%-3c  %-10s\n",
            argv[1],
            index_extended,
            carry->first_LBA,
            carry->last_LBA,
            size, // Include the last LBA sector
            category_size * 512,
            category,
            type);
        
        

    }
}
void make_extendedlist(partition_entry* table , uint8_t index_extended ,uint32_t fd,char** argv)
{
    //make the offset from begining of the file to the first extended entry
    //uint64_t first_offset =  ; 
    // multiply the offset with 512 since the offset carry the value of sectors
    i=5;
    char buf[512]={0} ;
    u_int64_t relative_offset = table->LBA;
    u_int64_t error=lseek(fd,relative_offset*512,SEEK_SET);
    uint64_t jump = table->LBA ;
    if(error == -1  )
    {
        perror("relative_offset");
        exit(0);
    }
    // off_t current_offset = (fd,relative_offset+446,SEEK_SET);
    ssize_t counter= read(fd,buf, 512 );
    if(counter == -1 )
    {
        perror("read");
        exit(0);
    }
    // get the first entrt structure and print its content 
    partition_entry* extended_entry = (partition_entry*) &buf[446];
    // if(extended_entry->type != 0 ) 
    //     print_table(extended_entry,normalMBR,index_extended,fd,argv);

    uint32_t internal_counter = 0 ;
    //extended_entry++;
    u_int64_t new_offset=relative_offset;
    while ( extended_entry->type != 0)
    {   
        
        if (extended_entry->type == 0x05)
        {
            // second entry analysis 
           // extended_entry++;
            if(extended_entry->sec_no == 0)
                break; 
            new_offset = relative_offset + (extended_entry->LBA);
            lseek(fd,new_offset*512,SEEK_SET);
            counter= read(fd,buf, 512 );
            if(counter == -1 )
            {
                perror("read");
                exit(0);
            }
            extended_entry = (partition_entry*) &buf[446];
            
           // relative_offset ;
        }
        // first entry analysis
        if(extended_entry->type != 0 )
        {
            partition_entry copy = *extended_entry;
            jump = new_offset ;
            copy.LBA += jump;
            
            print_table(&copy,normalMBR,i,fd,argv);
            extended_entry++;
        } 
        
        internal_counter ++ ;

    }
}


void make_GPT(uint64_t fd, char** argv) {
    char entry_buf[128];
    char buf[512];
    if (lseek(fd, 512, SEEK_SET) == -1) {
        perror("lseek");
        exit(0);
    }
    if (read(fd, buf, 512) == -1) {
        perror("read");
        exit(0);
    }
    gpt_partition_head* GPT_head = (gpt_partition_head*)&buf[0];

    for (int j = 0; j < GPT_head->size_entry; j++) {
        lseek(fd, (GPT_head->start_LBA_arr_entry * 512) + (j * 128), SEEK_SET);
        read(fd, entry_buf, 128);
        GUID_entry* entry = (GUID_entry*)&entry_buf[0];
        if (entry->first_LBA == 0) break;
        print_table((partition_entry*)entry, GPT, j + 1, fd, argv);
    }
}
