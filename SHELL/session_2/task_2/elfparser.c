#include <stdio.h>
#include <elf.h>


int main (int argc,char** argv)
{	
	int i=0 ; 



	FILE* elfFile = fopen(argv[1],"r");
	Elf64_Ehdr elfHeader ;
	
	fread(&elfHeader ,sizeof(elfHeader),1,elfFile);
	

	
	printf("Magic : ");
	for (i=0 ; i< EI_NIDENT	; i++)
	{
		printf("  %02x",elfHeader.e_ident[i]);
	}
	printf("\n");	

	printf("Class : ");
	switch(elfHeader.e_ident[EI_CLASS])
	{
		case ELFCLASS32 : printf("\t\tELF32\n");  break;
		case ELFCLASS64 : printf("\t\tELF64\n");  break;
		default   	: printf("\t\tINVALIDCLASS\n") ; break;
	}
	
	
	printf(	"Data :");	
	switch (elfHeader.e_ident[EI_DATA])
	{
		case  ELFDATANONE : printf("\t\tUnknown data format\n");  break;
		case  ELFDATA2LSB : printf("\t\tTwo's complement, littel-endian\n"); break;
		case  ELFDATA2MSB : printf("\t\tTwo's complement, big-endian\n"); break ; 
	
	}
	
	printf("Version :");
	
	switch (elfHeader.e_ident[EI_VERSION])
	{
		case EV_NONE   : printf("\t\tInvalid version\n"); break; 
		case EV_CURRENT: printf("\t\t1 (Current version)\n"); break; 
	}
	
	
	printf("OS/ABI : ");
	
	switch (elfHeader.e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV	 : printf("\t\tUNIX System V ABI\n");  		break;
		case ELFOSABI_HPUX 	 : printf("\t\tHP-UX ABI\n");  			break;
		case ELFOSABI_NETBSD 	 : printf("\t\tNetBSD ABI\n"); 			break;
		case ELFOSABI_LINUX 	 : printf("\t\tLinux ABI\n");  			break;
		case ELFOSABI_SOLARIS  	 : printf("\t\tSolaris ABI\n");  		break;
		case ELFOSABI_IRIX 	 : printf("\t\tIRIX ABI\n");  			break;
		case ELFOSABI_FREEBSD 	 : printf("\t\tFreeBSD ABI\n");  		break;
		case ELFOSABI_TRU64 	 : printf("\t\tTRU64 UNIX ABI\n"); 		break;
		case ELFOSABI_ARM 	 : printf("\t\tARM architecture ABI\n"); 	break;
		case ELFOSABI_STANDALONE : printf("\t\tStand-alone (embedded) ABI\n");	break;
	}
	
	
	
	printf("ABI Version :\t\t %d \n",elfHeader.e_ident[EI_ABIVERSION]);


	printf("Type :");
	switch (elfHeader.e_type)
	{
		case ET_NONE :  printf("\t\tUnknown type\n");	break;
		case ET_REL  :  printf("\t\tA relocatable file\n"); break;
		case ET_EXEC  :  printf("\t\tAn executable file\n"); break;
		case ET_DYN  :  printf("\t\tDYN (A shared object file)\n"); break;
		case ET_CORE  :  printf("\t\tA core file\n"); break;  
	}
	
	
	
	printf("Machine :");
	
	switch (elfHeader.e_machine)
	{
		case EM_NONE :  printf("\t\tAn unknown machine\n");	break;
		case EM_M32  :  printf("\t\tAT&T WE 32100\n"); break;
		case EM_SPARC  :  printf("\t\tSun Microsystems SPARC\n"); break;
		case EM_386  :  printf("\t\tIntel 80386\n"); break;
		case EM_68K  :  printf("\t\tMotorola 68000\n"); break;
		case EM_88K  :  printf("\t\tMotorola 88000\n"); break;
		case EM_860  :  printf("\t\tIntel 80860\n"); break;
		case EM_MIPS  :  printf("\t\tMIPS RS3000 (big-endian only)\n"); break;
		case EM_PARISC  :  printf("\t\tHP/PA\n"); break;
		case EM_SPARC32PLUS  :  printf("\t\tSPARC with enhanced instruction set\n"); break;
		case EM_PPC  :  printf("\t\tPowerPC\n"); break;
		case EM_PPC64  :  printf("\t\tPowerPC 64-bit\n"); break;
		case EM_S390  :  printf("\t\tIBM S/390\n"); break;
		case EM_ARM  :  printf("\t\tAdvanced RISC Machines\n"); break;
		case EM_SH  :  printf("\t\tRenesas SuperH\n"); break;
		case EM_SPARCV9  :  printf("\t\tSPARC v9 64-bit\n"); break;  
		case EM_IA_64  :  printf("\t\tIntel Itanium\n"); break;
		case EM_X86_64  :  printf("\t\tAMD x86-64\n"); break;
		case EM_VAX  :  printf("\t\tDEC Vax\n"); break;
	
	}
	
	
	printf("Version :");
	switch (elfHeader.e_version)
	{
		case EV_NONE    : printf("\t\tinvalid version\n"); break;
		case EV_CURRENT : printf("\t\tcurrent version (0x%x)\n",elfHeader.e_machine); break;
	}
	
	
	printf("Entry point address :\t\t0x%08lx\n",elfHeader.e_entry);
	
	
	printf("Start of program headers :\t\t%lx\n",elfHeader.e_phoff);
	
	
	printf("Start of section headers :\t\t%ld\n",elfHeader.e_shoff);
	
	
	printf("Flags : \t\t 0x%02x\n",elfHeader.e_flags);
	
	
	printf("Size of this header :\t\t%d  (in bytes)\n",elfHeader.e_ehsize);
	
	
	printf("Size of program headers :\t\t%d  (in bytes)\n",elfHeader.e_phentsize);
	
	printf("Number of program headers :\t\t%d\n  ",elfHeader.e_phnum);
	
	
	printf("Size of section headers :\t\t%d  (in bytes)\n",elfHeader.e_shentsize);
	
	printf("Number of section headers :\t\t%d\n  ",elfHeader.e_shnum);
	
	
	

	
	
	printf("Section header string table index :\t\t%d\n  ",elfHeader.e_shstrndx);
	
	
	return 0 ;
}

