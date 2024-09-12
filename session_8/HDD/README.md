
# HDD Partition Reader

This project provides a utility to read and display information about partitions from an HDD. It supports both MBR (Master Boot Record) and GPT (GUID Partition Table) partitioning schemes, making it versatile for a wide range of disk formats.

## Features

- **MBR and GPT Support:** Reads and interprets both MBR and GPT partition tables.
- **Partition Information Display:** Displays details such as partition type, start sector, end sector, size, and more.
- **Automatic Size Conversion:** Converts partition sizes to human-readable formats (Bytes, KB, MB, GB).
- **Handles Extended Partitions:** Reads extended partitions for MBR partition tables.
- **Guid Partition Type Detection:** Uses UUID to detect and display the type of partitions in GPT.

## Prerequisites

To build and run this project, you need:

- A C compiler (like GCC)
- Linux or any POSIX-compliant system
- `libuuid` library installed (for GPT UUID handling)

## Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/yourusername/HDD_Partition_Reader.git
   cd HDD_Partition_Reader
   ```

2. **Compile the Program:**

   ```bash
   gcc -o myfdisk myfdisk.c -luuid
   ```

## Usage

Run the compiled program and provide the path to the disk device file. For example:

```bash
sudo ./myfdisk /dev/sda
```

The output will display the partition table information in a readable format:

```
Device       Start       End     Sectors      Size       Type
/dev/sda1    2048        4096    102400       50.0MB     Linux filesystem
...
```

## Code Overview

- **`myfdisk.c`:** Main source file that reads the partition table and processes both MBR and GPT formats.
- **`make_GPT()`:** Reads and processes GPT partition table entries.
- **`make_extendedlist()`:** Handles extended partitions in MBR format.
- **`print_table()`:** Prints partition details in a formatted output.

## Contributing

Feel free to fork this repository and submit pull requests. Contributions are welcome, especially for:

- Adding new features.
- Improving code quality and performance.
- Fixing bugs and issues.

