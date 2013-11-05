// christodoulos christodoulou michalis andreou project of cache milestone 1
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
 

//sinartisi gia logarithmo 2
int log2(int a);
int log2(int a){
	int i;
	for (i=0; a>1; i++){
		a=a/2;}
	return i;}

//sinartisi gia power
int pow(int a, int b);
int pow(int a, int b){
	int i;
	int y;
	if (b==0){
		y=1;}
	else{
		y=a;
	
	for (i=0; i<b; i++){
		y=y*a;}}
	return y;}





//sinartisi initial table
void initialhelp(char *b); 
void initialhelp(char *b)
{ int i=0;
       i=0;
	 // initial table binary
	  for(i=0;i<14;i++){
		  b[i]='\0';}
 }

//sinartisi convert decimal to binary
void dec2bin(int *a, int decimal); 
void dec2bin(int *a, int decimal){

      int dec, i=0;
	  dec=decimal;
	 // initial table binary
	  for(i=0;i<20;i++){
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

typedef struct cache {
  char *index;	
  char *tag;
  char *block_offset;
  int valid;
} newcache;




int main(){
	
	
	int grammes;
	int leksis;
	int bits_addressing;
	int bits_index;
	int bits_tag;
	int bits_block_offset;
	
	
	int i,j;
	int diey8insi;
	int r_entoli;
	int address_atoi;
	int entries;
	int binary[20];
	int flushes_counter=0;
	int flushes_frequency;
	int instruction_counter_exF=0;
	int sinolikes_entoles;
	FILE *dedomena;
	FILE *out;
	FILE *parametroi;
	errno_t oppeningerror1;
	errno_t oppeningerror3;
	errno_t oppeningerror2;
	errno_t oppeningerror4;
	//metavlites gia parsing arxeiou
	const int MAX_CHARS_PER_LINE = 64;
	const int MAX_TOKENS_PER_LINE = 2;
	const char*  DELIMITER = "\t"; //diaxwristiko
	char buf[64];
	char buf1[64];
	char *command;
	char *address;
	char *a;

	//gia arxeio parametrwn
	char *token1;
	char *token2;
	int counter_grammwn=0;
	char  help[14] = {'0'};
	int size;
	int megethos_ram; //bytes
    int megethos_cache; //bytes
	int megethos_leksis; //bytes
	int sinolika_flushes;
	int pollaplasiastis_sinolikwn_entolwn;
	int eidos; //arxitektonikis
	int megethos_block; //se le3is
	int ways;
    int kikloi_hit;
	int kikloi_miss;
	int politiki_antikatastasis;          //1_for_FIFO_2_LRU_3_RANDOM
	int politiki_eggrafis; //_1_for_write_back_2_write_through
	int pol_apotixias_eggrafis; //_1_for_allocate_2_non_allocate
	int victim_cache; //1_for_ipar3i_victim_cache_2_mi_ipar3i
	int megethos_victim;

	//counter metavlites g hit an miss
	int writeMiss = 0;
    int writeHit = 0;
    int cacheMiss = 0;
    int cacheHit = 0;
    int read = 0;
    int write = 0;
	char bbits[64]; //block offset bits
    char sbits[64]; //index bits
    char tbits[64]; //tag bits
	int setadd;
    int totalset=0;
	newcache* mycache;


	oppeningerror1= fopen_s( &parametroi, "parametroi.txt", "r+"); //anoigma arxeiou
	if( oppeningerror1 == 0 ) // elegxos an anoi3ei t arxeio swsta
	  {printf( "The file 'file.txt' was opened\n" );}
	 else{ printf( "The file 'file.txt' was not opened\n" );}

	  while (!feof(parametroi)){
			  fgets(buf,MAX_CHARS_PER_LINE,parametroi);
					token1 = strtok_s(buf, DELIMITER, &a);
					token2=strtok_s(0, DELIMITER, &a);
					size=strlen(token2);
					for(i=size; i>=0;i--){
						help[i]=token2[i];}
					if (counter_grammwn==0){
						megethos_ram=atoi(help);}

					else if(counter_grammwn==1){
						megethos_cache=atoi(help);}

					else if(counter_grammwn==2){
						megethos_leksis=atoi(help);}

					else if(counter_grammwn==3){
						sinolika_flushes=atoi(help);}

					else if(counter_grammwn==4){
						pollaplasiastis_sinolikwn_entolwn=atoi(help);}

					else if(counter_grammwn==5){
						eidos=atoi(help);}

					else if(counter_grammwn==6){
						megethos_block=atoi(help);}

					else if(counter_grammwn==7){
						ways=atoi(help);}

					else if(counter_grammwn==8){
						kikloi_hit=atoi(help);}

					else if(counter_grammwn==9){
						kikloi_miss=atoi(help);}

					else if(counter_grammwn==10){
						politiki_antikatastasis=atoi(help);}

					else if(counter_grammwn==11){
						 politiki_eggrafis=atoi(help);}

					else if(counter_grammwn==12){
						pol_apotixias_eggrafis=atoi(help);}

					else if(counter_grammwn==13){
						victim_cache=atoi(help);}

					else if(counter_grammwn==14){
						megethos_victim=atoi(help);}


					initialhelp(help);
						counter_grammwn=counter_grammwn+1;
	  }
					
	  fclose(parametroi);


	  //elegxos eisodwn
	if (megethos_cache>megethos_ram){
		printf("ERROR: adinato i cache na einai megaliteri apo tin ram\n");
		system("Pause");
			return 0;}
	if (megethos_leksis==0){
		printf("ERROR INVALID INPUT AT MEGETHOS LEKSIS\n");
		system("Pause");
	return 0;}
	if (isPowerOfTwo(megethos_block)==0){
		printf("ERROR: leksis ana block den einai dinami tou 2\n");
		system("Pause");
		return 0;}
	if (eidos>3){
		printf("ERROR: I TIMI GIA ARXITEKTONIKI PREPI NA EINAI 1,2,3\n");
		system("Pause");
			return 0;}
	if (politiki_antikatastasis>3){
		printf("ERROR: I TIMI GIA POLITIKI ANTIKATASTASIS PREPI NA EINAI 1,2,3\n");
		system("Pause");
			return 0;}
	if (politiki_eggrafis>2){
		printf("ERROR: I TIMI GIA POLITIKI EGGRAFIS PREPI NA EINAI 1,2\n");
		system("Pause");
			return 0;}
	if (pol_apotixias_eggrafis>2){
		printf("ERROR: I TIMI GIA POLITIKI APOTIXIAS EGGRAFIS PREPI NA EINAI 1,2\n");
		system("Pause");
			return 0;}


	//tipwsi parametrwn gia epivevewsi

	  printf("ram:%d\n cache:%d\n leksis:%d\n flushes:%d\n pollaplasiastis:%d\n", megethos_ram,megethos_cache,megethos_leksis, sinolika_flushes,pollaplasiastis_sinolikwn_entolwn);
	  printf("kykloi epitixias: %d kykloi apotixias: %d\n", kikloi_hit, kikloi_miss);
	  printf("I arxitektoniki einai:");
	  if (eidos==1){printf("DIRECT MAPPED\n");}
	  else if (eidos==2){printf("N-ASSOCIATIVE\n");}
	  else {printf("FYLLY ASSOCIATIVE\n");}
	  printf("I politiki antikatastasis einai:");
	  if (politiki_antikatastasis==1){printf("FIFO\n");}
	  else if (eidos==2){printf("LRU\n");}
	  else {printf("RANDOM\n");}
	  printf("I politiki eggrafis einai:");
	  if (politiki_eggrafis==1){printf("WRITE BACK\n");}
	  else {printf("WRITE THROUGH\n");}
	   printf("I politiki apotixias eggrafis einai:");
	   if (pol_apotixias_eggrafis==1){printf("WRITE ALLOCATE\n");}
	  else {printf("NON WRITE ALLOCATE\n");}
	  if (victim_cache=1){printf("YPARXEI VICTIM CACHE\n KAI TO MEGETHOS THS EINAI %d\n", megethos_victim);}
	  else {printf("DEN IPAXEI VICTIM CACHE\n");}
	  


	  
	srand((unsigned)time(NULL)); //rand me vasi rologiu

	

	//arxikos ka8olikos ipologismos entries, leksewn, periorismwn flushes
	entries=megethos_ram/megethos_leksis;
	bits_addressing=log2(entries);
	leksis=megethos_cache/megethos_leksis;
	sinolikes_entoles = pollaplasiastis_sinolikwn_entolwn * entries;
	
	if (sinolika_flushes==0){
		flushes_frequency = sinolikes_entoles;
	}
	flushes_frequency = sinolikes_entoles / sinolika_flushes;
	
	
	//ipologismoi pediwn addressing gia direct mapped kai dinamiko allocate
	if (eidos==1){
		grammes=leksis/megethos_block;
			bits_block_offset=log2(megethos_block);
		bits_index=log2(grammes);
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);
		mycache= mycache=(newcache *) malloc( sizeof(newcache *)*leksis );
		//initial cache
	
			for(i=0;i<leksis;i++) {
				//Allocating Space for Tag Bits, initiating tag and valid to 0s
		mycache[i].tag = (char *)malloc(sizeof(char)*(bits_tag+1));
		for(j=0;j<bits_tag;j++)
        {
			mycache[i].tag[j] = '0';
        }
		mycache[i].valid = 0;
    }
		




	}

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
		//if (megethos_block==1){bits_block_offset=1;}
		//else{
			bits_block_offset=log2(megethos_block);//}
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	}

	//ipologismoi pediwn addressing gia full associative
	else if (eidos==3){
		megethos_block=leksis;
		//if (megethos_block==1){bits_block_offset=1;}
		//else{
			bits_block_offset=log2(megethos_block);//}
		bits_index=0;
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	//LATHOS EPILOGI
	else {
		printf("ERROR INPUT TRY AGAIN");
		return 0;
		}

	//anoigma arxeiou dedomenwn gia gra4imo kai elegxos an anoi3ei to arxeio swsta
	oppeningerror2 = fopen_s(&dedomena,"file.txt", "w+"); 
	if( oppeningerror2 == 0 ) 
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
			fprintf(dedomena, "\nW\t%d", diey8insi );
			instruction_counter_exF= instruction_counter_exF+1;
		}
		else if (r_entoli==1){
			fprintf(dedomena, "\nR\t%d", diey8insi );
			instruction_counter_exF= instruction_counter_exF+1;
		}
		else if (r_entoli==2){
			fprintf(dedomena, "\nM\t%d", diey8insi );
			instruction_counter_exF= instruction_counter_exF+1;
			}
		else  {if (instruction_counter_exF>flushes_frequency){
			fprintf(dedomena, "\nF");
			flushes_counter=flushes_counter+1;
			instruction_counter_exF=0;}
		else {i=i-1;}
			   }
	}



		fclose(dedomena); //klisimo arxeiou


	//parsing arceiou
	oppeningerror3= fopen_s( &dedomena, "file.txt", "r"); //anoigma arxeiou
	if( oppeningerror3== 0 ) // elegxos an anoi3ei t arxeio swsta
	  {
      printf( "The file 'file.txt' was opened\n" );
	 }
	 else
	 {
      printf( "The file 'file.txt' was not opened\n" );
	 }


	oppeningerror4=fopen_s(&out,"out.txt", "w+");
	if( oppeningerror4 == 0 ) // elegxos an anoi3ei t arxeio swsta
	  { printf( "The file 'out.txt' was opened\n" );
	 }else {printf( "The file 'out.txt' was not opened\n" ); }
	


	 


		 while (!feof(dedomena)){
			  fgets(buf1,MAX_CHARS_PER_LINE,dedomena);
				command = strtok_s(buf1, DELIMITER, &a);
				
				//an einai read
				if (command[0]=='R'){
					address=strtok_s(0, DELIMITER, &a);
					size=strlen(address);
					for(i=size; i>=0;i--){
						help[i]=address[i];}
					address_atoi=atoi(help);
					initialhelp(help);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s READ\t%d\t", command, address,address_atoi );
					for(j=bits_addressing-1;j>=0;j--) {
						  fprintf(out, "%d ",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=bits_addressing-1,i=0;j>bits_addressing-1-bits_tag;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  tbits[i]=binary[j];
					   }
					fprintf(out, "\nindex bits are:");
					for(j=bits_addressing-1-bits_tag,i=0;j>bits_addressing-1-bits_tag-bits_index;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  sbits[i]=binary[j];
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index,i=0;j>=0;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  bbits[i]=binary[j];
					   }
					fprintf(out, "\n");

					//Convert set bits from char array into ints
					for(i = 0, j = (bits_index -1); i < bits_index; i ++, j--) {
						if (sbits[i] == '1')
							 setadd = 1;
					    if (sbits[i] == '0')
							 setadd = 0;
					    setadd = setadd * pow(2, j);
					    totalset += setadd;
				  }
			    	//Calculating Hits and Misses
						 if ((mycache[totalset].valid == 1) && (strcmp(mycache[totalset].tag, tbits) == 0))
						  {  /* Hit */
						   cacheHit++;
							}
						 else {   /* Miss (cache entry invalid, or wrong tag) */
							  cacheMiss++;
						      read++;
							  mycache[totalset].valid = 1;
							  strcpy(mycache[totalset].tag, tbits);
                              }   
				}



				//an einai write
				else if (command[0]=='W'){
					address=strtok_s(0, DELIMITER, &a);
					size=strlen(address);
					for(i=size; i>=0;i--){
						help[i]=address[i];}
					address_atoi=atoi(help);
					initialhelp(help);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s WRITE\t%d\n", command, address, address_atoi );
					for(j=bits_addressing-1;j>=0;j--) {
						  fprintf(out, "%d",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=bits_addressing-1,i=0;j>bits_addressing-1-bits_tag;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  tbits[i]=binary[j];
					   }
					fprintf(out, "\nindex bits are:");
					for(j=bits_addressing-1-bits_tag,i=0;j>bits_addressing-1-bits_tag-bits_index;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  sbits[i]=binary[j];
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index,i=0;j>=0;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  bbits[i]=binary[j];
					   }
					fprintf(out, "\n");

					//Convert set bits from char array into ints
					for(i = 0, j = (bits_index -1); i < bits_index; i ++, j--) {
						if (sbits[i] == '1')
							 setadd = 1;
					    if (sbits[i] == '0')
							 setadd = 0;
					    setadd = setadd * pow(2, j);
					    totalset += setadd;
				  }

					  //Calculating Hits and Misses
				     if ((mycache[totalset].valid == 1)&& (strcmp(mycache[totalset].tag, tbits) == 0))
					  {
					     /* Hit */ 
					   cacheHit++;
			           write++;
					  }
				    else
					 {
				    /* Miss (cache entry invalid, or wrong tag) */
				       cacheMiss++;
				       read++;
				       write++;
					   mycache[totalset].valid = 1;
					  strcpy(mycache[totalset].tag, tbits);
						 }


				}

				//an einai modify
				else if (command[0]=='M'){
					address=strtok_s(0, DELIMITER, &a);
					size=strlen(address);
					for(i=size; i>=0;i--){
						help[i]=address[i];}
					address_atoi=atoi(help);
					initialhelp(help);
					dec2bin(binary, address_atoi);
					fprintf(out, "%s\t%s MODIFY\t%d\n", command, address, address_atoi );
					for(j=bits_addressing-1;j>=0;j--) {
						  fprintf(out, "%d",binary[j]);
					   }
					fprintf(out, "\ntag bits are:");
					for(j=bits_addressing-1,i=0;j>bits_addressing-1-bits_tag;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  tbits[i]=binary[j];
					   }
					fprintf(out, "\nindex bits are:");
					for(j=bits_addressing-1-bits_tag,i=0;j>bits_addressing-1-bits_tag-bits_index;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  sbits[i]=binary[j];
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index,i=0;j>=0;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  bbits[i]=binary[j];
					   }
					fprintf(out, "\n");
					//Convert set bits from char array into ints
					for(i = 0, j = (bits_index -1); i < bits_index; i ++, j--) {
						if (sbits[i] == '1')
							 setadd = 1;
					    if (sbits[i] == '0')
							 setadd = 0;
					    setadd = setadd * pow(2, j);
					    totalset += setadd;
				  }
				//ypologismos Hits and Misses
						 if ((mycache[totalset].valid == 1) && (strcmp(mycache[totalset].tag, tbits) == 0))
						  {  /* Hit */
						   cacheHit++;
							}
						 else {   /* Miss (cache entry invalid, or wrong tag) */
							  cacheMiss++;
						      read++;
							  mycache[totalset].valid = 1;
							  strcpy(mycache[totalset].tag, tbits);
                              } 
				}

				//an einai flush
				else if (command[0]=='F')
				{
					fprintf(out, "%sFLUSH\n", command );	
				}
				
				
				}
				
		 fclose(dedomena); //klisimo arxeiou
		 fclose(out);
		 printf("Hits: %d\n", cacheHit);
	     printf("Misses: %d\n", cacheMiss);
		 printf("Writes: %d\n", write);
		 printf("Reads: %d\n", read);
		 
	    system("Pause");

		return 0;
	}