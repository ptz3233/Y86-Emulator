#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
unsigned char * mem;
int pc;
int size = 0;

// const char * regs[8];
// regs[0] = "%eax";
// regs[1] = "%ecx";
// regs[2] = "%edx";
// regs[3] = "%ebx";
// regs[4] = "%esp";
// regs[5] = "%ebp";
// regs[6] = "%esi";
// regs[7] = "%edi";


char regs[8][5];







void startRunning(){
	//printf("%x",mem[pc]);
	int inst = (int)mem[pc];
	
	unsigned char arg1;
	unsigned char arg2;
	int reg1;
	int reg2;
	int disp;
	char bytes[12];
	int value;
	strcpy(regs[0],"%eax");
	strcpy(regs[1],"%ecx");
	strcpy(regs[2],"%edx");
	strcpy(regs[3],"%ebx");
	strcpy(regs[4],"%esp");
	strcpy(regs[5],"%ebp");
	strcpy(regs[6],"%esi");
	strcpy(regs[7],"%edi");
	

while(1){
	inst = (int)mem[pc];
	
	if (pc>=size){
		exit(0);
		
	}
	
	
	switch(inst){
		case(0x00):
		printf("NOP\n");
		pc+=1;	
			break;
		case(0x10):
		printf("HALT\n");
		pc+=1;	
			break;
		case(0x20):	
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		 arg2 = (mem[pc] & 0x0f);
		
		 reg1 = (int) arg1;
		 reg2 = (int) arg2;
		
		
		
		
		printf("RRMOVL %s, %s\n",regs[reg1],regs[reg2]);
		pc+=1;	
		break;
		
		case(0x30):
		pc+=1;
		int rregsI = (int) mem [pc];
		rregsI = rregsI - 0xf0;
		
		pc+=1;
			
			
			
			
	   
			
		
				
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);

		value = (int)strtol(bytes,NULL,16);
		
		printf("IRMOVL %d, %s\n",value,regs[rregsI]);
		pc+=4;
		
		
		
			
			break;
		case(0x40):
		
		pc+=1;
	
	
		arg1 = (mem[pc] & 0xf0) >> 4;
		arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;
	
	
		
		pc+=1;
		
	
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("RMMOVL  %s, %s + %d\n",regs[reg1], regs[reg2], disp);
		
		pc+=4;
		
			
			break;
		case(0x50):
				pc+=1;
	
	
		arg1 = (mem[pc] & 0xf0) >> 4;
		arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;
	
	
		
		pc+=1;
		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("MRMOVL %d + %s, %s\n", disp, regs[reg2], regs[reg1]);
		pc+=4;
		
			
			break;
		case(0x60):
	    //printf("addl");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		
		printf("ADDL %s, %s\n", regs[reg1], regs[reg2] );
		pc+=1;
	
		
			break;
		case(0x61):
		//printf("subl");
		pc+=1;
				arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		
		printf("SUBL %s, %s\n", regs[reg1], regs[reg2] );
		pc+=1;
			break;
		case(0x62):
		//printf("andl");
		pc+=1;
				arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		
		printf("ANDL %s, %s\n", regs[reg1], regs[reg2] );
		pc+=1;
			break;
		case(0x63):
		//printf("xorl");
		pc+=1;
				arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		
		printf("XORL %s, %s\n", regs[reg1], regs[reg2] );
		pc+=1;
			break;
		case(0x64):
		//printf("mull");
		pc+=1;
					arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		
		printf("MULL %s, %s\n", regs[reg1], regs[reg2] );
		pc+=1;	
			break;
		case(0x65):
		//printf("cmpl");
		pc+=1;
							arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		
		printf("CMPL %s, %s\n", regs[reg1], regs[reg2] );
		pc+=1;		
			break;
		case(0x70):
		//printf("jmp");
		pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JMP, %d\n",disp);
		pc+=4;
		
		
			break;
		case(0x71):
		//printf("jle");
				pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JLE, %d\n",disp);
		pc+=4;
			break;
		case(0x72):
		//printf("jl");
				pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JL, %d\n",disp);
		pc+=4;
			break;
		case(0x73):
		//printf("je");
				pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JE, %d\n",disp);
		pc+=4;
			break;
		case(0x74):
		//printf("jne");
				pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JNE, %d\n",disp);
		pc+=4;
			break;
		case(0x75):
		//printf("JGE");
				pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JGE, %d\n",disp);
		pc+=4;
			break;
		case(0x76):
		//printf("Jg");
				pc+=1;

		
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("JG, %d\n",disp);
		pc+=4;
			break;
		case(0x80):
		//printf("call");
			pc+=1;
			sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
			disp = (int) strtol(bytes,NULL,16);
			
			printf("CALL, %d\n", disp);
			pc+=4;
			break;
		case(0x90):
		//printf("ret");
			pc+=1;
			printf("RET\n");
			
			break;
		case(0xa0):
		//printf("pushl");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		reg1 = (int) arg1;
		printf("PUSHL, %s\n", regs[reg1]);
		pc+=1;
		
		
			break;
		case(0xb0):
		//printf("popl");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		reg1 = (int) arg1;
		printf("POPL, %s\n", regs[reg1]);
		pc+=1;
			break;
		case(0xc0):
		//printf("readb");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		reg1 = (int) arg1;
		pc+=1;
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("READB, %d + %s\n",disp, regs[reg1]);
		pc+=4;
			
			
			break;
		case(0xc1):
		//printf("readl");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		reg1 = (int) arg1;
		pc+=1;
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("READL, %d + %s\n",disp, regs[reg1]);
		pc+=4;
		break;
		case(0xd0):
		//printf("writeb");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		reg1 = (int) arg1;
		pc+=1;
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("WRITEB, %d + %s\n",disp, regs[reg1]);
		pc+=4;	
			
			
			
			
			break;
		case(0xd1):
		//printf("writel");
			pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
		reg1 = (int) arg1;
		pc+=1;
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		
		printf("WRITEL, %d + %s\n",disp, regs[reg1]);
		pc+=4;	
			break;
		case(0xe0):
		//printf("movsbl");
		pc+=1;
		arg1 = (mem[pc] & 0xf0) >> 4;
	    arg2 = (mem[pc] & 0x0f);
		
		reg1 = (int) arg1;
		reg2 = (int) arg2;	
		pc+=1;
		sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
		disp = (int) strtol(bytes,NULL,16);
		printf("MOVSBL %d + %s, %s\n", disp, regs[reg2], regs[reg1]);
		pc+=4;
		
			break;
		default:
		printf("Invalid instruction encountered.");
		
	}
}
	
}

void put(char* directive, char* address, char* data){
	
	if (strcmp(directive,".size")==0){
		int size = (int)strtol (address, NULL, 16);
		
		//NEED TO FIND OUT EXACT MEANING OF size DIRECTIVE, num of chars or bytes
		
		
		 mem = (unsigned char *) malloc(sizeof(char)*size);
	}


	else if(strcmp(directive,".text")==0){
		int add = (int) strtol (address,NULL,16);
		pc = add;
		
		char byte[3];
		
		
		
		
		while(*data!='\0'){
			
			byte[0] = *data;
			data++;
			byte[1] = *data;
			data++;
			byte[2] = '\0';
			
			//unsigned int bytedata = (unsigned int) strtol (byte,NULL,16);
			//printf("%x",(char)bytedata);
			mem[add] = (char) strtol(byte,NULL,16);
			add++;
		}
		size = add;
		
		
		
	}
	
		
	else{
		
		return;
	}
		
		
	
	
	
	
}



void processLine(char * line){
	
	char* directive;
	char* address;
	char* data;
	
	
	directive = strtok(line," 	");

	address = strtok(NULL,"	 ");
		size_t lena =strlen(address)-1;
		if(address[lena]=='\n'){
			address[lena] = '\0';
		}

	
	data = strtok(NULL,"	");
	if(data!=NULL){
		size_t lend = strlen(data)-1;
		if(data[lend]=='\n'){
			data[lend]='\0';
		}
	}	
	
	
	put(directive,address,data);
	
	
	
}






int main(int argc, char ** argv){
	
	if(argc!=2){
		
		printf("Argument must be specified.\n");
		exit(0);
		
	}
	
	
	if (strcmp(argv[1],"-h")==0){
		
		printf("Usage: y86emu file.y86.\n");
		exit(0);
		
	}
	
	FILE *file;
	
	file = fopen(argv[1], "r");
	
	if (file == NULL){
		printf("There is no file, or it could not be opened.\n");
		exit(0);
	}
	
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	
	while((read = getline(&line, &len, file)) != -1){
		

	processLine(line);	
		
	}
	
	startRunning();

	
	return 0;
}
