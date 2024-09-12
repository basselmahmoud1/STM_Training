#include "functions.h"

uint8_t f_l, f_a, f_t, f_u, f_c, f_i, f_f, f_d, f_1, f_noopt, f_error, f_showaccess, f_showmod, f_symlink,f_multipesource;
// index of the
uint8_t argv_index_beg1 = 0; // is used inside the opendir function
uint8_t argv_index_beg2 = 0;

// function that handle the input
void options(int argc, char **argv)
{

    // options must be supported -latucifd1
    int opt;
    f_noopt = 1;
    while ((opt = getopt(argc, argv, "latucifd1")) != -1)
    {
        f_noopt = 0;
#ifdef debug
        printf("opt=%d (%c) , optind = %d\n", opt, printable(opt), optind);
#endif
        switch (opt)
        {
        case 'l':
            f_l = 1;
            break;
        case 'a':
            f_a = 1;
            break;
        case 't':
            f_t = 1;
            break;
        case 'u':
            f_u = 1;
            break;
        case 'c':
            f_c = 1;
            break;
        case 'i':
            f_i = 1;
            break;
        case 'f':
            f_f = 1;
            break;
        case 'd':
            f_d = 1;
            break;
        case '1':
            f_1 = 1;
            break;
        case '?':
            f_error = 1;
            break;
        case ':':
            f_error = 1;
            break;
        }
    }
}

// function that get open the dir and read it's content
int dir_table(int argc, char **argv, all_info **nodes)
{
    argv_index_beg1 = optind;
    optind++;
    DIR *dp;
    // if(argv[argv_index_beg1] == NULL)
    // {
    //     // use the current working directory
    //     dp =opendir(".");
    // }
    // else
    dp = opendir(argv[argv_index_beg1]);
    if (dp == NULL)
    {
        perror("opening directory");
        exit(0);
    }
    struct dirent *entry = readdir(dp);
    if (entry == NULL && errno != 0)
    {
        perror("readdir failed");
        exit(0);
    }
    // a3mel malloc lel size of direc_struct * initail no
    int size_unit = 10;
    *nodes = (all_info *)malloc(sizeof(all_info) * size_unit);
    if (*nodes == NULL)
    {
        perror("malloc failed");
    }
    all_info *copy_struct = *nodes;

    int count = -1;
    do
    {
        count++;
        copy_struct->dir_info.inode_no = entry->d_ino;
        copy_struct->dir_info.d_name = strdup(entry->d_name);
        copy_struct++;
        if (count >= size_unit)
        {
            size_unit += 10;
            *nodes = (all_info *)realloc(nodes, size_unit * sizeof(all_info));
            if (*nodes == NULL)
            {
                perror("malloc failed");
            }
        }
        entry = readdir(dp);
        if (entry == NULL && errno != 0)
        {
            perror("readdir failed");
            exit(0);
        }

    } while (entry != NULL);
    closedir(dp);
    return count;
}

// function to get inode info
void inode_info(char **argv, int no_entry, all_info **nodes)
{
    all_info *carry = *nodes;
    char argv_copy[4096]; // Buffer to hold the full path

    for (int i = 0; i <= no_entry; i++)
    {
        // Create a copy of the directory path
        snprintf(argv_copy, sizeof(argv_copy), "%s/%s", argv[argv_index_beg1], carry->dir_info.d_name);

        // Retrieve inode information using lstat
        if (lstat(argv_copy, &carry->inode_info) == -1)
        {
            perror("lstat");
            continue; // Continue to the next entry in case of an error
        }

// Print inode information
#ifdef debug
        printf("\nmode: %o\n", carry->inode_info.st_mode);
        printf("link count: %ld\n", carry->inode_info.st_nlink);
        printf("user: %d\n", carry->inode_info.st_uid);
        printf("group: %d\n", carry->inode_info.st_gid);
        printf("size: %ld\n", carry->inode_info.st_size);
        printf("modtime: %ld\n", carry->inode_info.st_mtime);
        printf("name: %s\n", argv_copy);
        printf("\n");
#endif
        carry++; // Move to the next entry
    }
}

const char *uid_to_name(all_info *node)
{

    struct passwd *user = getpwuid(node->inode_info.st_uid);
    if (user == NULL)
    {
        if (errno == 0)
            printf("Record not found in passwd file.\n");
        else
            perror("getpwuid failed");
    }

    return user->pw_name;
}

const char *gid_to_name(all_info *node)
{
    struct group *userG = getgrgid(node->inode_info.st_uid);
    if (userG == NULL)
    {
        if (errno == 0)
            printf("Record not found in /etc/group file.\n");
        else
            perror("getgrgid failed");
    }
    return userG->gr_name;
}

const char *filetype_conversion(all_info *node, mode type)
{
    f_symlink = 0;
    if ((node->inode_info.st_mode & 0170000) == 0010000)
    {
        const char *cons = (type == short_formate) ? "p" : "Pipe";
        return cons;
    }
    else if ((node->inode_info.st_mode & 0170000) == 0020000)
    {
        // printf("%s is a Character Special file\n");
        const char *cons = (type == short_formate) ? "c" : "Character Special file";
        return cons;
    }
    else if ((node->inode_info.st_mode & 0170000) == 0040000)
    {
        // printf("%s is a Directory\n");
        const char *cons = (type == short_formate) ? "d" : "Directory";
        return cons;
    }
    else if ((node->inode_info.st_mode & 0170000) == 0060000)
    {
        // printf("%s is a Block Special file\n");
        const char *cons = (type == short_formate) ? "b" : "Block Special file";
        return cons;
    }
    else if ((node->inode_info.st_mode & 0170000) == 0100000)
    {
        // printf("%s is a Regular file\n");
        const char *cons = (type == short_formate) ? "-" : "Regular file";
        return cons;
    }
    else if ((node->inode_info.st_mode & 0170000) == 0120000)
    {
        // printf("%s is a Soft link\n");
        const char *cons = (type == short_formate) ? "l" : "Soft link";
        f_symlink = 1;
        return cons;
    }
    else if ((node->inode_info.st_mode & 0170000) == 0140000)
    {
        // printf("%s is a Socket\n");
        const char *cons = (type == short_formate) ? "s" : "Socket";
        return cons;
    }
    else
    {
        // printf("Unknwon mode\n");
        perror("Unknwon mode");
        exit(0);
    }
}

const char *permissions(all_info *node)
{
    char str[] = "---------";
    int mode = node->inode_info.st_mode;
    // owner  permissions
    if ((mode & 0000400) == 0000400)
        str[0] = 'r';
    if ((mode & 0000200) == 0000200)
        str[1] = 'w';
    if ((mode & 0000100) == 0000100)
        str[2] = 'x';
    // group permissions
    if ((mode & 0000040) == 0000040)
        str[3] = 'r';
    if ((mode & 0000020) == 0000020)
        str[4] = 'w';
    if ((mode & 0000010) == 0000010)
        str[5] = 'x';
    // others  permissions
    if ((mode & 0000004) == 0000004)
        str[6] = 'r';
    if ((mode & 0000002) == 0000002)
        str[7] = 'w';
    if ((mode & 0000001) == 0000001)
        str[8] = 'x';
    // special  permissions
    if ((mode & 0004000) == 0004000)
        str[2] = 's';
    if ((mode & 0002000) == 0002000)
        str[5] = 's';
    if ((mode & 0001000) == 0001000)
        str[8] = 't';
    const char *copy = strdup(str);
    return copy;
}

const char *time_conversion(all_info *node, mode type)
{
    switch (type)
    {
    case accesstime:
        return ctime(&(node->inode_info.st_atime));
        break;
    case modificationtime:
        return ctime(&(node->inode_info.st_mtime));
        break;
    case changetime:
        return ctime(&(node->inode_info.st_ctime));
        break;
    }
}


static int cmp_name(const void *p1, const void *p2)
{
    const all_info *info1 = (const all_info *)p1;
    const all_info *info2 = (const all_info *)p2;
    return strcoll(info1->dir_info.d_name,info2->dir_info.d_name);
}

static int cmp_time_mod(const void *p1, const void *p2)
{
    const all_info *info1 = (const all_info *)p1;
    const all_info *info2 = (const all_info *)p2;
    if (info1->inode_info.st_mtime > info2->inode_info.st_mtime)
        return -1;
    else if (info1->inode_info.st_mtime < info2->inode_info.st_mtime)
        return 1;
    else if (info1->inode_info.st_mtime == info2->inode_info.st_mtime)
        return 0;
}

static int cmp_time_access(const void *p1, const void *p2)
{
    const all_info *info1 = (const all_info *)p1;
    const all_info *info2 = (const all_info *)p2;
    if (info1->inode_info.st_atime > info2->inode_info.st_atime)
        return -1;
    else if (info1->inode_info.st_atime < info2->inode_info.st_atime)
        return 1;
    else if (info1->inode_info.st_atime == info2->inode_info.st_atime)
        return 0;
}

void sort_nodes(all_info *nodes, int no_entry, mode type)
{
    no_entry++;
    if (type == sort_name)
    {
        qsort(nodes, no_entry, sizeof(all_info), cmp_name);
    }
    else if (type == sort_access_time)
    {
        qsort(nodes, no_entry, sizeof(all_info), cmp_time_access);
    }
    else if (type == sort_mod_time)
    {
        qsort(nodes, no_entry, sizeof(all_info), cmp_time_mod);
    }
}

void sort_flags(all_info *nodes, int no_entry)
{
    f_showaccess = 0, f_showmod = 0;
    if (f_f == 1)
    {
        return;
    }
    else if (f_u == 1)
    {
        if (f_l == 1 && f_t == 1)
        {
            // sort by access time & show access time
            sort_nodes(nodes, no_entry, sort_access_time);
            f_showaccess = 1;
            return;
        }
        else if (f_l == 1)
        {
            // sort by name & show access time
            sort_nodes(nodes, no_entry, sort_name);
            f_showaccess = 1;
            return;
        }
        else
        {
            // only sort by access time (short format)
            sort_nodes(nodes, no_entry, sort_access_time);
            return;
        }
    }
    else if (f_c == 1)
    {
        if (f_l == 1 && f_t == 1)
        {
            // sort by modq time & show mod time
            sort_nodes(nodes, no_entry, sort_mod_time);
            f_showmod = 1;
            return;
        }
        else if (f_l == 1)
        {
            // sort by name & show mod time
            sort_nodes(nodes, no_entry, sort_name);
            f_showmod = 1;
            return;
        }
        else
        {
            // only sort by mod time (short format)
            sort_nodes(nodes, no_entry, sort_mod_time);
            return;
        }
    }
    else if (f_t == 1)
    {
        sort_nodes(nodes, no_entry, sort_mod_time);
        return;
    }
    else 
    {
        sort_nodes(nodes, no_entry, sort_name);
        return;
    }
}

void print_time(all_info *node)
{
    if (f_showaccess == 1)
    {
        printf("%.12s ", time_conversion(node, accesstime) + 4);
        return;
    }
    else if (f_showmod == 1)
    {
        printf("%.12s ", time_conversion(node, modificationtime) + 4);
        return;
    }
    else
    {
        printf("%.12s ", time_conversion(node, accesstime) + 4);
        return;
    }
}

void print_file_name(all_info *node, char **argv, int counter)
{
    char *color_code = "\033[0m";
    if (S_ISDIR(node->inode_info.st_mode)) {
        color_code = "\033[1;34m";  // Blue for directories
    } else if (S_ISLNK(node->inode_info.st_mode)) {
        color_code = "\033[1;36m";  // Cyan for symbolic links
    } else if (node->inode_info.st_mode & S_IXUSR) {
        color_code = "\033[1;32m";  // Green for executable files
    }
    if (f_l == 1)
    {
        if (f_symlink == 1)
        {
            char argv_copy[4096];
            #ifdef debug
            printf("the index of the sym link is the path no :%d/n", argv_index_beg2 - (counter));
            #endif
            snprintf(argv_copy, sizeof(argv_copy), "%s/%s", argv[argv_index_beg2 - (counter)], node->dir_info.d_name);
            char buffer[4096];
            int error = readlink(argv_copy, buffer, 4096);
            if (error == -1)
            {
                perror("readlink");
                exit(0);
            }
            buffer[error] = '\0';
            printf("%s%s\033[0m -> %s\n",color_code, node->dir_info.d_name, buffer);
        }
        else
        {
            printf("%s%s\033[0m \n", color_code,node->dir_info.d_name);
        }
    }
    else 
    {
        
        printf("%s%-10s\033[0m  ",color_code,node->dir_info.d_name);
    }
}
