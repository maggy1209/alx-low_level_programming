#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ELF_MAGIC_SIZE 16

// ELF header structure
typedef struct {
    unsigned char e_ident[ELF_MAGIC_SIZE];  // ELF magic number and identification info
    uint16_t      e_type;                   // Object file type
    uint16_t      e_machine;                // Architecture
    uint32_t      e_version;                // Object file version
    uint64_t      e_entry;                  // Entry point virtual address
    uint64_t      e_phoff;                  // Program header table file offset
    uint64_t      e_shoff;                  // Section header table file offset
    uint32_t      e_flags;                  // Processor-specific flags
    uint16_t      e_ehsize;                 // ELF header size in bytes
    uint16_t      e_phentsize;              // Size of program header entry
    uint16_t      e_phnum;                  // Number of program header entries
    uint16_t      e_shentsize;              // Size of section header entry
    uint16_t      e_shnum;                  // Number of section header entries
    uint16_t      e_shstrndx;               // Section name string table index
} Elf64_Ehdr;

// Function to print ELF header information
void print_elf_header(const Elf64_Ehdr *header) {
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < ELF_MAGIC_SIZE; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");
    printf("  Class:                             ");
    if (header->e_ident[4] == 1) {
        printf("ELF32\n");
    } else if (header->e_ident[4] == 2) {
        printf("ELF64\n");
    } else {
        printf("<unknown>\n");
    }
    printf("  Data:                              2's complement, %s\n", (header->e_ident[5] == 1) ? "little endian" : "big endian");
    printf("  Version:                           %u (current)\n", header->e_ident[6]);
    printf("  OS/ABI:                            ");
    switch (header->e_ident[7]) {
        case 0: printf("UNIX - System V\n"); break;
        case 1: printf("HP-UX\n"); break;
        case 2: printf("NetBSD\n"); break;
        case 3: printf("Linux\n"); break;
        case 6: printf("Solaris\n"); break;
        case 7: printf("AIX\n"); break;
        case 8: printf("IRIX\n"); break;
        case 9: printf("FreeBSD\n"); break;
        case 10: printf("Tru64\n"); break;
        case 11: printf("Novell Modesto\n"); break;
        case 12: printf("OpenBSD\n"); break;
        case 13: printf("OpenVMS\n"); break;
        case 14: printf("NonStop Kernel\n"); break;
        case 15: printf("AROS\n"); break;
        case 16: printf("Fenix OS\n"); break;
        case 17: printf("CloudABI\n"); break;
        default: printf("<unknown: %u>\n", header->e_ident[7]); break;
    }
    printf("  ABI Version:                       %u\n", header->e_ident[8]);
    printf("  Type:                              ");
    switch (header->e_type) {
        case 1: printf("REL (Relocatable file)\n"); break;
        case 2: printf("EXEC (Executable file)\n"); break;
        case 3: printf("DYN (Shared object file)\n"); break;
        case 4: printf("CORE (Core file)\n"); break;
        default: printf("<unknown: %u>\n", header->e_type); break;
    }
    printf("  Entry point address:               0x%lx\n", header->e_entry);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 98;
    }

    Elf64_Ehdr header;
    ssize_t read_size = read(fd, &header, sizeof(header));
    if (read_size != sizeof(header)) {
        fprintf(stderr, "Error reading ELF header\n");
        close(fd);
        return 98;
    }

    if (header.e_ident[0] != 0x7F || strncmp((char *)&header.e_ident[1], "ELF", 3) != 0) {
        fprintf(stderr, "Error: Not an ELF file\n");
        close(fd);
        return 98;
    }

    print_elf_header(&header);

    close(fd);
    return 0;
}

