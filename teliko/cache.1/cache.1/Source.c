#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


#define _CRT_SECURE_NO_WARNINGS  
//sinartisi gia logarithmo 2
int log2(int a);
int log2(int a){
	int i;
	for (i=0; a>1; i++){
		a=a/2;}
	return i;}

//sinartisi convert decimal to binary
void dec2bin(int *a, int decimal); 
void dec2bin(int *a, int decimal)
{ 
      int dec, i=0;
	  dec=decimal;
	 // initial table binary
	  for(i=0;i<32;i++){
		  a[i]=0;}
	  i=0;
      while(dec>0) 
      { 
           a[i]=dec%2; 
           i++; 
           dec=dec/2;
      }
     
 }

int main(){
	int megethos_ram=128;
	int megethos_cache=1024;
	int megethos_block=8; //se le3is
	int megethos_leksis=32;
	int grammes;
	int leksis;
	int bits_index;
	int bits_tag;
	int bits_block_offset;
	int eidos;
	int ways;
	int i,j;
	int diey8insi;
	int r_entoli;
	int address_atoi;
	int binary[32];
	FILE *dedomena;
	FILE *out;
	//metavlites gia parsing arxeiou
	const int MAX_CHARS_PER_LINE = 64;
	const int MAX_TOKENS_PER_LINE = 2;
	const char*  DELIMITER = "\t"; //diaxwristiko
	char buf[64];
	char *command;
	char *address;
	const char  READ[1] = {'R'};
	const char  WRITE[1] = {'W'};
	const char  MODIFY[1] = {'M'};
	const char FLUSH[1] = {'F'};


	leksis=megethos_cache/megethos_leksis;

	printf("Dwse tipo cache/n An i cache einai direct mapped pliktrologise 1\nAn i cache set associative pliktrologise 2\n");
    printf("nAn i cache einai fully associative pliktrologise 3\n");
	scanf("%d", &eidos);
	
	if (eidos==1){
		grammes=leksis/megethos_block;
		bits_block_offset=log2(megethos_block);
		bits_index=log2(grammes);
		bits_tag=megethos_leksis-(bits_block_offset)-(bits_block_offset);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	else if (eidos==2){
		printf("Dwse arithmo ways\n");
		scanf("%d", &ways);
		grammes=leksis/megethos_block/ways;
		bits_index=log2(grammes);
		bits_block_offset=log2(megethos_block);
		bits_tag=megethos_leksis-(bits_block_offset)-(bits_block_offset);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	else if (eidos==3){
		megethos_block=leksis;
		bits_block_offset=log2(megethos_block);
		bits_index=0;
		bits_tag=megethos_leksis-(bits_block_offset)-(bits_block_offset);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	else {
		printf("ERROR INPUT TRY AGAIN");
		}
	dedomena= fopen("file.txt", "w"); //anoigma arxeiou dedomenwn
	//random generetor
	for(i=0;i<3*megethos_ram;i++){
		r_entoli=rand()%4;
		if ((r_entoli==0) || (r_entoli==1) || (r_entoli==2)){
			diey8insi=rand()%leksis;
		}
		
		if (r_entoli==0){
			fprintf(dedomena, "W\t%d\n", diey8insi );
		}
		else if (r_entoli==1){
			fprintf(dedomena, "R\t%d\n", diey8insi );}
		else if (r_entoli==2){
			fprintf(dedomena, "M\t%d\n", diey8insi );}
		else  {
			fprintf(dedomena, "F\n");}}



		fclose(dedomena); //klisimo arxeiou


	//parsing arceiou
	dedomena= fopen("file.txt", "r"); //anoigma arxeiou
	out=fopen("out.txt", "w");
	
		 while (!feof(dedomena)){
			  fgets(buf,MAX_CHARS_PER_LINE,dedomena);
				command = strtok(buf, DELIMITER);
				
				if (command[0]==READ[0]){
					address=strtok(0, DELIMITER);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s READ\t%d\t", command, address,address_atoi );
					for(j=31;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=31;j>31-bits_tag;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nindex bits are:");
					for(j=31-bits_tag;j>31-bits_tag-bits_index;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=31-bits_tag-bits_index-1;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\n");
				}

				else if (command[0]==WRITE[0]){
					address=strtok(0, DELIMITER);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s WRITE\t%d\n", command, address, address_atoi );
					for(j=31;j>=0;j--) {
						  fprintf(out, "%d",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=31;j>31-bits_tag;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nindex bits are:");
					for(j=31-bits_tag;j>31-bits_tag-bits_index;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=31-bits_tag-bits_index-1;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\n");
				}

				else if (command[0]==MODIFY[0]){
					address=strtok(0, DELIMITER);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s MODIFY\t%d\n", command, address, address_atoi );
					for(j=31;j>=0;j--) {
						  fprintf(out, "%d",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=31;j>31-bits_tag;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nindex bits are:");
					for(j=31-bits_tag;j>31-bits_tag-bits_index;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=31-bits_tag-bits_index-1;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\n");
				}

				else if (command[0]==FLUSH[0]){
					fprintf(out, "%sFLUSH\n", command );	
				}

				
				}


		 fclose(dedomena); //klisimo arxeiou
		 fclose(out);
	    system("Pause");
		return 0;
	}