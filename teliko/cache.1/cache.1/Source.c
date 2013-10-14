// christodoulos christodoulou michalis andreou project of cache milestone 1
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
 
#define megethos_ram 256 //bytes
#define megethos_cache 128 //bytes
#define megethos_leksis 4 //bytes
#define sinolika_flushes 6
#define pollaplasiastis_sinolikwn_entolwn 3
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
	  for(i=0;i<log2(megethos_ram/megethos_leksis);i++){
		  a[i]=0;}
	  i=0;
      while(dec>0) 
      { 
           a[i]=dec%2; 
           i++; 
           dec=dec/2;
      }
     
 }
//sinartisi elegxou power of2?
int isPowerOfTwo(int x);
int isPowerOfTwo(int x)
	{
    return ((x != 0) && ((x & (~x + 1)) == x));
	}

int main(){
	
	int megethos_block; //se le3is
	int grammes;
	int leksis;
	int bits_addressing;
	int bits_index;
	int bits_tag;
	int bits_block_offset;
	int eidos;
	int ways;
	int i,j;
	int diey8insi;
	int r_entoli;
	int address_atoi;
	int entries;
	int binary[megethos_leksis*8];
	int flushes_counter=0;
	int flushes_frequency;
	int instruction_counter_exF=0;
	int sinolikes_entoles;
	FILE *dedomena;
	FILE *out;
	errno_t oppeningerror1;
	errno_t oppeningerror3;
	errno_t oppeningerror2;
	//metavlites gia parsing arxeiou
	const int MAX_CHARS_PER_LINE = 64;
	const int MAX_TOKENS_PER_LINE = 2;
	const char*  DELIMITER = "\t"; //diaxwristiko
	char buf[64];
	char *command;
	char *address;
	char *a;
	const char  READ[1] = {'R'};
	const char  WRITE[1] = {'W'};
	const char  MODIFY[1] = {'M'};
	const char FLUSH[1] = {'F'};

	srand((unsigned)time(NULL)); //rand me vasi rologiu

	if (megethos_cache>megethos_ram){
		printf("ERROR: adinato i cache na einai megaliteri apo tin ram");
			return 0;}

	//arxikos ka8olikos ipologismos entries, leksewn, periorismwn flushes
	entries=megethos_ram/megethos_leksis;
	bits_addressing=log2(entries);
	leksis=megethos_cache/megethos_leksis;
	sinolikes_entoles = pollaplasiastis_sinolikwn_entolwn * entries;
	flushes_frequency = sinolikes_entoles / sinolika_flushes;
	
	//eisagwgi stoixeia apo ton xristi
	printf("Dwse tipo cache/n An i cache einai direct mapped pliktrologise 1\nAn i cache set associative pliktrologise 2\n");
    printf("nAn i cache einai fully associative pliktrologise 3\n");
	scanf_s("%d", &eidos);
	printf("Dwse leksis ana block");
	scanf_s("%d", &megethos_block);
	if (isPowerOfTwo(megethos_block)==0){
		printf("ERROR: leksis ana block den einai dinami tou 2");
		return 0;
	}

	
	
	//ipologismoi pediwn addressing gia direct mapped
	if (eidos==1){
		grammes=leksis/megethos_block;
		bits_block_offset=log2(megethos_block);
		bits_index=log2(grammes);
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}

	//ipologismoi pediwn addressing gia n way associative
	else if (eidos==2){
		printf("Dwse arithmo ways\n");
		scanf_s("%d", &ways);
		grammes=leksis/megethos_block/ways;
		if (grammes<1){
			printf("ERROR: Ipervolika ways");
			return 0;}
		else{
		bits_index=log2(grammes);
		bits_block_offset=log2(megethos_block);
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	}

	//ipologismoi pediwn addressing gia full associative
	else if (eidos==3){
		megethos_block=leksis;
		bits_block_offset=log2(megethos_block);
		bits_index=0;
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	//LATHOS EPILOGI
	else {
		printf("ERROR INPUT TRY AGAIN");
		return 0;
		}

	//anoigma arxeiou dedomenwn gia gra4imo kai elegxos an anoi3ei to arxeio swsta
	oppeningerror3 = fopen_s(&dedomena,"file.txt", "w+"); 
	if( oppeningerror3 == 0 ) 
	  {
      printf( "The file 'file.txt' was opened\n" );
	 }
	 else
	 {
      printf( "The file 'file.txt' was not opened\n" );
	 }


	// kataskeyi arxeiou dedomenwn kai random generetor
	for(i=0;i<sinolikes_entoles;i++){
		r_entoli=rand()%4;
		if ((r_entoli==0) || (r_entoli==1) || (r_entoli==2)){
			diey8insi=rand()%entries;
		}
		
		if (r_entoli==0){
			fprintf(dedomena, "W\t%d\n", diey8insi );
			instruction_counter_exF= instruction_counter_exF+1;
		}
		else if (r_entoli==1){
			fprintf(dedomena, "R\t%d\n", diey8insi );
			instruction_counter_exF= instruction_counter_exF+1;
		}
		else if (r_entoli==2){
			fprintf(dedomena, "M\t%d\n", diey8insi );
			instruction_counter_exF= instruction_counter_exF+1;
			}
		else  {if (instruction_counter_exF>flushes_frequency){
			fprintf(dedomena, "F\n");
			flushes_counter=flushes_counter+1;
			instruction_counter_exF=0;}
		else {i=i-1;}
			   }
	}



		fclose(dedomena); //klisimo arxeiou


	//parsing arceiou
	oppeningerror1= fopen_s( &dedomena, "file.txt", "r+"); //anoigma arxeiou
	if( oppeningerror1 == 0 ) // elegxos an anoi3ei t arxeio swsta
	  {
      printf( "The file 'file.txt' was opened\n" );
	 }
	 else
	 {
      printf( "The file 'file.txt' was not opened\n" );
	 }


	oppeningerror2=fopen_s(&out,"out.txt", "w+");
	if( oppeningerror2 == 0 ) // elegxos an anoi3ei t arxeio swsta
	  {
      printf( "The file 'out.txt' was opened\n" );
	 }
	 else
	 {
      printf( "The file 'out.txt' was not opened\n" );
	 }
	
		 while (!feof(dedomena)){
			  fgets(buf,MAX_CHARS_PER_LINE,dedomena);
				command = strtok_s(buf, DELIMITER, &a);
				
				if (command[0]==READ[0]){
					address=strtok_s(0, DELIMITER, &a);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s READ\t%d\t", command, address,address_atoi );
					for(j=bits_addressing-1;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=bits_addressing-1;j>bits_addressing-1-bits_tag;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nindex bits are:");
					for(j=bits_addressing-1-bits_tag;j>bits_addressing-1-bits_tag-bits_index;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\n");
				}

				else if (command[0]==WRITE[0]){
					address=strtok_s(0, DELIMITER, &a);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s WRITE\t%d\n", command, address, address_atoi );
					for(j=bits_addressing-1;j>=0;j--) {
						  fprintf(out, "%d",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=bits_addressing-1;j>bits_addressing-1-bits_tag;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nindex bits are:");
					for(j=bits_addressing-1-bits_tag;j>bits_addressing-1-bits_tag-bits_index;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\n");
				}

				else if (command[0]==MODIFY[0]){
					address=strtok_s(0, DELIMITER, &a);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s MODIFY\t%d\n", command, address, address_atoi );
					for(j=bits_addressing-1;j>=0;j--) {
						  fprintf(out, "%d",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=bits_addressing-1;j>bits_addressing-1-bits_tag;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nindex bits are:");
					for(j=bits_addressing-1-bits_tag;j>bits_addressing-1-bits_tag-bits_index;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index;j>=0;j--) {
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