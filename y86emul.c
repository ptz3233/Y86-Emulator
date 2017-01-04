#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned char * mem;
int reg[9];
int pc;
int memsize;

bool zf,of,cf;

union converter{
	unsigned int integer;
	unsigned char bytes[4];
	
	
	
};

void clearFlags(){
	
	zf = false;
	of = false;
	cf = false;
}


 


void NOP(){
	pc+=1;
			//printf("nop ran\n");
	
	
}

void HALT(){
	
	pc+=1;
			printf("\nProgram exited with status HLT.\n");
			exit(0);
	
	
}

void RRMOVL(){
	
	pc+=1;
			int rregs = (int)mem[pc];

			
			char regs[2];
			sprintf(&regs[0], "%x", rregs);
			int reg1 = (int) regs[0] - '0';
			int reg2 = (int) regs[1] - '0';
			
			reg[reg2] = reg[reg1];
			
			
			
			

			
			pc+=1;

	
}




void IRMOVL(){
	
	pc+=1;
			//printf("made it into irmovl");
			
			int rregsI = (int) mem [pc];
			rregsI = rregsI - 0xf0;
			
			int value;
			

			
			pc+=1;
			
			
			
			
			char bytes[12];
			
		
				
			sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);

			value = (int)strtol(bytes,NULL,16);
			
			reg[rregsI] = value;
			
			// printf("Mving %d into reg",value);
			// printf("%d\n",rregsI);
			pc+=4;
	
}

void RMMOVL(){
	pc+=1;
	
	
	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
	unsigned char arg2 = (mem[pc] & 0x0f);
		
	int reg1 = (int) arg1;
	int reg2 = (int) arg2;
	
	
	int disp;
	pc+=1;
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	

	
	if (disp + reg[reg2] > memsize){
		
		printf("Encountered address outside of memory bounds.\n Program exited with status ADR.");
		exit(0);
	}
	
	int val = reg[reg1];
	
	memcpy(&mem[disp + reg[reg2]],&val,4);
	
	
	pc+=4;
	
}

void MRMOVL(){
	
	pc+=1;
	
	
	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
	unsigned char arg2 = (mem[pc] & 0x0f);
		
	int reg1 = (int) arg1;
	int reg2 = (int) arg2;
	
	int disp;
	pc+=1;
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
		
	if(disp + reg[reg2] > memsize){
		printf("Encountered address outside of memory bounds.\n Program exited with status ADR.");
		exit(0);
		
	}
	
	memcpy(&reg[reg1], &mem[disp + reg[reg2]], 4);
	
	
	pc+=4;
}

void ADDL(){
	
	pc+=1;
	clearFlags();
	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
	unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	
	int sum = reg[reg1] + reg[reg2];
	
	reg[reg2] = sum;
	
	of = (unsigned int) reg[reg2] < (unsigned int) reg[reg1];
	
	if(sum == 0){
		
		zf = true;
		
	}
	
	if (sum<0){
		
		cf = true;
		
	}
	pc+=1;
	
}

void SUBL(){
	
	pc+=1;
	 clearFlags();

	 
	 	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
		unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	 
	
	
	
	int diff = reg[reg2] - reg[reg1];
	
	reg[reg2] = diff;
	
	
	
	of = ((reg[reg1] < 0 && reg[reg2] > 0 && diff < 0)||  (reg[reg1] > 0 && reg[reg2] < 0 && diff > 0));
	
	if(diff == 0){ 
		
		zf = true;
		
	}
	
	if (diff<0){
		
		cf = true;
		
	}
	pc+=1;
	
}


void ANDL(){
	pc+=1;
	clearFlags();
		 	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
		unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	
	int sum = reg[reg1] & reg[reg2];
	
	reg[reg2] = sum;
	
	if (sum == 0){
		zf = true;
	}
	
	if (sum < 0){
		cf = true;
		
	}
	pc+=1;
	
	
	
}

void XORL(){
	pc+=1;
	 clearFlags();
		 	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
		unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	
	int sum = reg[reg1] ^ reg[reg2];
	
	reg[reg2] = sum;
	
	if (sum == 0){
		zf = true;
	}
	
	if (sum < 0){
		cf = true;
		
	}
	pc+=1;
	
	
	
}

void MULL(){
	
	pc+=1;
	 clearFlags();
		 	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
		unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	
	int prod = reg[reg1] * reg[reg2];
	
	reg[reg2] = prod;
	
	of = (reg[reg1] > 0 && reg[reg2] > 0 && prod < 0) || (reg[reg1] < 0 && reg[reg2] < 0 && prod > 0) ||(reg[reg1] < 0 && reg[reg2] > 0 && prod > 0) ||(reg[reg1] < 0 && reg[reg2] < 0 && prod > 0) ;
	
	
	if (prod == 0){
		
		zf = true;
	}
	
	if (prod< 0){
		
		cf = true;
	}
	pc+=1;
}
void CMPL(){
	
	pc+=1;
	 clearFlags();
		 	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
		unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	
	int val = reg[reg1] - reg[reg2];
	
	if(val==0){
		
		zf = true;
	}
	if(val<0){
		
		cf = true;
	}
	if((val > 0 && reg[reg1] > 0 && reg[reg2] < 0) || ( val < 0 && reg[reg1] < 0 && reg[reg2] >0)){
		
		of = true;
		
		
	}
	pc+=1;
	
}

void JMP(){
	pc+=1;
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);

	
	
	disp = (int) strtol(bytes,NULL,16);
	
	pc = disp;
	
}
void JLE(){
	
	pc+=1;
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	
	
	if (zf == true || (cf ^ of))
	{
		pc = disp;
		return;
	}else{
		
		pc+=4;
	}
	
	
}


void JL(){
	
	pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	
	if(zf==false && (cf ^ of)){
		
		pc = disp;
		return;
	}else{
		
		pc+=4;
		
	}
	
	
	
}


void JE(){
	
	pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	if (zf==true){
		
		pc = disp;
		return;
	}else{
		
		pc+=4;
	}
	
	
	
}


void JNE(){
	
	
		pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	if (zf==false){
		
		pc = disp;
		return;
	}else{
		
		pc+=4;
	}
	
	
	
}


void JGE(){
	
	pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	if (!(zf==false && (cf ^ of))){
		
		pc = disp;
		return;
	}else{
		
		pc+=4;
	}	
	
	
	
}

void JG(){
	
		pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	if (!(zf==true && (cf ^ of))){
		
		pc = disp;
		return;
	}else{
		
		pc+=4;
	}	
	
	
	
	
}

void CALL(){
	
	pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	
	
	reg[4] = reg[4] - 4;
	
	union converter con;
	
	con.integer = pc+4;
	
	mem[reg[4] + 0] = con.bytes[0]; 
	mem[reg[4] + 1] = con.bytes[1]; 
	mem[reg[4] + 2] = con.bytes[2]; 
	mem[reg[4] + 3] = con.bytes[3]; 
	
	
	
	pc = disp;
	
	//pc+=4;
}

void RET(){
	pc+=1;
	int value = reg[4];
	
	union converter con;
	
	con.bytes[0] = mem[value];
	con.bytes[1] = mem[value+1];
	con.bytes[2] = mem[value+2];
	con.bytes[3] = mem[value+3];
	
	// printf("\n\nret bytes: %x%x%x%x",mem[value],mem[value+1],mem[value+2],mem[value+3]);
	
	// printf("ret sending me to %d",con.integer);
	
	pc = con.integer;
	
	reg[4] = value + 4;

	
}

void PUSHL(){
	pc+=1;
	
	
	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
	
		
	int reg1 = (int) arg1;
		
	
	reg[4] = reg[4] -4;
	
	
	

	
	int value = reg[reg1];
	
	
	union converter con;
	con.integer = value;
	
	
	
	mem[reg[4] + 0] = con.bytes[0]; 
	mem[reg[4] + 1] = con.bytes[1]; 
	mem[reg[4] + 2] = con.bytes[2]; 
	mem[reg[4] + 3] = con.bytes[3]; 
	
	
	
	pc+=1;
	
	
	
	
	
	
}

void POPL(){
	pc+=1;
	
	int rregs = (int)mem[pc];
	char regs[2];
	sprintf(&regs[0], "%x", rregs);
	int reg1 = (int) regs[0] - '0';

	union converter con;
	
	con.bytes[0] = mem[reg[4]];
	con.bytes[1] = mem[reg[4]+1];
	con.bytes[2] = mem[reg[4]+2];
	con.bytes[3] = mem[reg[4]+3];	
	
	int val = con.integer;
	
	reg[reg1] = val;
	
	reg[4] = reg[4] + 4;

	pc+=1;
	
}
void READB(){
	pc+=1;
	 clearFlags();
	//printf("reading...");
	int rregs = (int)mem[pc];
	char regs[2];
	sprintf(&regs[0], "%x", rregs);
	int reg1 = (int) regs[0] - '0';
	pc+=1;
	unsigned int in;
	reg[2] = 30;
	
	scanf("%x", &in);
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	mem[disp+reg[reg1]] = in;
	
	if(in==EOF){
		
		zf = true;
	}else{
		
		zf = false;
	}
	
	
	//printf("Byte read to mem %x", mem[disp+reg[reg1]]);
	
	
	pc+=4;
	
	 
}

void READL(){
	 clearFlags();
	pc+=1;
	int rregs = (int)mem[pc];
	char regs[2];
	sprintf(&regs[0], "%x", rregs);
	int reg1 = (int) regs[0] - '0';
	pc+=1;
	
	unsigned  int in;
	
	scanf("%d", &in);
	
	
	
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	union converter con;
	
	con.integer = in;
	
	mem[disp+reg[reg1]] = con.bytes[0];
	mem[disp+reg[reg1]+1] = con.bytes[1];
	mem[disp+reg[reg1]+2] = con.bytes[2];
	mem[disp+reg[reg1]+3] = con.bytes[3];
	
	pc+=4;
	
}

void WRITEB(){
	pc+=1;
	
	int rregs = (int)mem[pc];
	char regs[2];
	sprintf(&regs[0], "%x", rregs);
	int reg1 = (int) regs[0] - '0';
	pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);

	
	if (disp + reg[reg1] > memsize){
		
		printf("Encountered address outside of memory bounds.\n Program exited with status ADR.");
		exit(0);
	}
	
	
	
	
	printf("%c",mem[disp+reg[reg1]]);

	
	pc+=4;
}

void WRITEL(){
	pc+=1;
	
	int rregs = (int)mem[pc];
	char regs[2];
	sprintf(&regs[0], "%x", rregs);
	int reg1 = (int) regs[0] - '0';
	pc+=1;
	
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	
	disp = (int) strtol(bytes,NULL,16);
	
	if (disp + reg[reg1] > memsize){
		
		printf("Encountered address outside of memory bounds.\n Program exited with status ADR.");
		exit(0);
	}
	

	
	int val;
	
	memcpy(&val,&mem[disp+reg[reg1]+0],4);
	
	
	printf("%d",val);
	
	
	
	
	pc+=4;
}

void MOVSBL(){
	pc+=1;
		 	unsigned char arg1 = (mem[pc] & 0xf0) >> 4;
		unsigned char arg2 = (mem[pc] & 0x0f);
		
		int reg1 = (int) arg1;
		int reg2 = (int) arg2;
	pc+=1;
	int disp;
	
	char bytes[12];
	
	sprintf(bytes, "0x%.02x%.02x%.02x%.02x", mem[pc+3], mem[pc+2], mem[pc+1], mem[pc+0]);
	

	
	
	disp = (int) strtol(bytes,NULL,16);
	
	if(reg2 + disp > memsize){
		
		printf("Encountered address outside of memory bounds.\n Program exited with status ADR.");
		exit(0);
		
	}
	
	
	unsigned char src = mem[reg[reg2]+disp];
	
	unsigned char dest[4];
	
	unsigned char test = src & 0x80;
	//printf("%x\n",src);
	
	//printf("%x",test);
	
	
	if(test==0x80){
		dest[3] = src;
		dest[2] = 0xff;
		dest[1] = 0xff;
		dest[0] = 0xff;
		
		
	}else{
		dest[3] = src;
		dest[2] = 0x00;
		dest[1] = 0x00;
		dest[0] = 0x00;
		
		
	}
	 char destbytes[12];
	 
	 // printf("\nmovsbling value at reg%d + + %d into reg%d",reg2,disp,reg1);
	 
	sprintf(destbytes, "0x%.02x%.02x%.02x%.02x", dest[0],dest[1],dest[2], dest[3]);
	
	int final = (int) strtol(destbytes,NULL,16);
	
	reg[reg1] = final;
	
	pc+=4;
	
	
	
	
}



void startRunning(){
	//printf("%x",mem[pc]);
	int inst = (int)mem[pc];
	

while(1){
	inst = (int)mem[pc];
	//printf("executing at pc = %d",pc);
	//printf("\n0:%d 1:%d 2:%d 3:%d 4:%d 5:%d 6:%d 7:%d\n",reg[0],reg[1],reg[2],reg[3],reg[4],reg[5],reg[6],reg[7]);
	switch(inst){
		case(0x00):
		//printf("nop");
			NOP();
			break;
		case(0x10):
		//printf("halt");
			HALT();
			break;
		case(0x20):	
		//printf("rrmovl");
			RRMOVL();
			break;
		
		case(0x30):
		//printf("irmovl");
			IRMOVL();
			break;
		case(0x40):
		//printf("rmmovl");
			RMMOVL();
			break;
		case(0x50):
		//printf("mrmovl");
			MRMOVL();
			break;
		case(0x60):
	    //printf("addl");
			ADDL();
			break;
		case(0x61):
		//printf("subl");
			SUBL();
			break;
		case(0x62):
		//printf("andl");
			ANDL();
			break;
		case(0x63):
		//printf("xorl");
			XORL();
			break;
		case(0x64):
		//printf("mull");
			MULL();
			break;
		case(0x65):
		//printf("cmpl");
			CMPL();
			break;
		case(0x70):
		//printf("jmp");
			JMP();
			break;
		case(0x71):
		//printf("jle");
			JLE();
			break;
		case(0x72):
		//printf("jl");
			JL();
			break;
		case(0x73):
		//printf("je");
			JE();
			break;
		case(0x74):
		//printf("jne");
			JNE();
			break;
		case(0x75):
		//printf("JGE");
			JGE();
			break;
		case(0x76):
		//printf("Jg");
			JG();
			break;
		case(0x80):
		//printf("call");
			CALL();
			break;
		case(0x90):
		//printf("ret");
			RET();
			break;
		case(0xa0):
		//printf("pushl");
			PUSHL();
			break;
		case(0xb0):
		//printf("popl");
			POPL();
			break;
		case(0xc0):
		//printf("readb");
			READB();
			break;
		case(0xc1):
		//printf("readl");
			READL();
			break;
		case(0xd0):
		//printf("writeb");
			WRITEB();
			break;
		case(0xd1):
		//printf("writel");
			WRITEL();
			break;
		case(0xe0):
		//printf("movsbl");
			MOVSBL();
			break;
		default:
		printf("Invalid instruction encountered.\nProgram exited with status INS.");
		exit(0);
	}
}
	
}



void put(char* directive, char* address, char* data){
	
	if (strcmp(directive,".size")==0){
		int size = (int)strtol (address, NULL, 16);
		
		//NEED TO FIND OUT EXACT MEANING OF size DIRECTIVE, num of chars or bytes
		
		
		 mem = (unsigned char *) malloc(sizeof(char)*size);
		 
		 memsize = size*sizeof(char);
		 
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
		
		
		
		
	}
	
		
	else if(strcmp(directive,".string")==0){
		int add = (int) strtol (address,NULL,16);
		data ++;
		mem[add] = *data;
		data++;
		//printf("%s",data);
		int i =1;
		while(*data!='\0'){
			
			mem[add+i] = *data;
			i++;
			data++;
		}
	}

	else if(strcmp(directive,".long")==0){
		int add = (int) strtol (address,NULL,16);
		
		//printf("Data: %s\n",data);
		
		
		unsigned int value = (int) strtol (data,NULL,16);
		union converter con;
		
		con.integer = value;
		
		
		//printf("Value: %d\n",value);
		
		//printf("\n%x%x%x%x",con.bytes[0],con.bytes[1],con.bytes[2],con.bytes[3]);
		
		mem[add] = con.bytes[0];
		mem[add+1] = con.bytes[1];
		mem[add+2] = con.bytes[2];
		mem[add+3] = con.bytes[3];
		
		
		
	}

	else if(strcmp(directive,".byte")==0){
		int add = (int) strtol (address,NULL,16);
		
		
		int bytedata = (int) strtol (data,NULL,16);
		
		
		mem[add] = (char) bytedata;
		
		
	}
	
	
	
}

void processLine(char * line){
	
	char* directive;
	char* address;
	char* data;
	
	
	directive = strtok(line," 	");
	//printf("Directive: %s\n",directive);
	
	address = strtok(NULL,"	 ");
		size_t lena =strlen(address)-1;
		if(address[lena]=='\n'){
			address[lena] = '\0';
		}
	//printf("Address: %s\n",address);
	
	data = strtok(NULL,"	");
	if(data!=NULL){
		size_t lend = strlen(data)-1;
		if(data[lend]=='\n'){
			data[lend]='\0';
		}
	}	
	//printf("Data: %s\n",data);
	
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
