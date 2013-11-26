// christodoulos christodoulou michalis andreou project of cache milestone 1
#define _CRT_SECURE_NO_WARNINGS
#include "voi8itikes_sinartisis.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
 



typedef struct cache {
	int dirty[16];
  int valid[16];
  int ctag[16]; // estw maximum blocks size 16 leksis
} newcache;


typedef struct nwayAndfully {
  int dirty[16];
  int valid[16];// estw maximum blocks size 16 leksis
  int ctag[16]; 
  int FifoAndLru[16];
} newnwayAndfully;

/*typedef struct ways {
	
	nwayAndfully  way;
} newnways;*/

typedef struct victim {
  int ctag; 
  int FIFO;
} newvictim;


int main(){
	
	
	int grammes;
	int leksis;
	int bits_addressing;
	int bits_index;
	int bits_tag;
	int bits_block_offset;
	
	
	int i,j,q,p, k,m;
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
	int modify=0;
	char bbits[64]; //block offset bits
    char sbits[64]; //index bits
    int tbits[64]; //tag bits
	int setadd;
    int totalset=0;
	int tagadd;
	int totaltag=0;
	int bladd;
	int totalbl=0;
	int randomcounter =0;
	int randomcounter1 =0;
	int compulsory=0;
	int conflict=0;
	int capacity=0;
	int dways=1;
	int totalkikloi;
	float missrate;
	float hitrate;
	int helpcounter_fifo_and_lru=0;
//	int fully;//help deiktis gia fully associative
	int ifhit;
	int write_flag;
	int deiktis_ekdiwksis;
	int flag_compulsory;
	int flag_campacity;
	int flag_conflict;
	int min;
	newcache* mycache;
//	newnways* mycache1;
	newnwayAndfully* mycache2;
	newvictim* myvictim;
	


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
	  
	  //allocate memory for victim cache
	  if (victim_cache=1){
		  myvictim=(newvictim *) malloc( sizeof(newvictim *)*(megethos_victim+2));}




	  
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
		printf("index %d tag%d bo %d\n", bits_index, bits_tag, bits_block_offset);

		//allocate cacheeee/////
		 mycache=(newcache *) malloc( sizeof(newcache *)*(leksis*1000));

		//initial cache
			for(i=0;i<dways;i++) {
				for (j=0;j<megethos_block;j++){
					randomcounter +=1;
					printf("counter value: %d\n", randomcounter);
					mycache[i].ctag[j]=-1;
					mycache[i].valid[j] = 0;
					mycache[i].dirty[j]=0;
					randomcounter1 +=1;
					printf("counter value11111 is: %d\n", randomcounter1);}
		
    }
		
		printf("leksis!!!!!1: %d\n", leksis);
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
			bits_block_offset=log2(megethos_block);//}
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);}
	}

	//ipologismoi pediwn addressing gia full associative
	else if (eidos==3){
		dways=leksis/megethos_block;
		bits_block_offset=log2(megethos_block);//}
		bits_index=0;
		bits_tag=bits_addressing-(bits_block_offset)-(bits_index);
		printf("index %d tag%d bo %d", bits_index, bits_tag, bits_block_offset);
		
		//allocate cacheeee/////
		mycache2=(newnwayAndfully *) malloc( sizeof(newnwayAndfully *)*(leksis*1000));

		//initial cache
			for(i=0;i<leksis;i++) {
				for (j=0;j<megethos_block;j++){
					randomcounter +=1;
					printf("counter value: %d\n", randomcounter);
					mycache2[i].ctag[j]=-1;
					mycache2[i].valid[j] = 0;
					mycache2[i].FifoAndLru[j]=0;
					mycache2[i].dirty[j]=0;
					randomcounter1 +=1;
					printf("counter value11111 is: %d\n", randomcounter1);}
    }
		
		printf("leksis!!!!!1: %d\n", leksis);


	
	
	}
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
			 //initial meta apo ka8e entoli
			 setadd = 0;
			 totalset = 0;
			 tagadd = 0;
			 totaltag = 0;
			 bladd = 0;
			 totalbl = 0;
			 ifhit=0;
			 write_flag=0;
			 flag_compulsory=1;
			 flag_campacity=1;
			 flag_conflict=0;


			  fgets(buf1,MAX_CHARS_PER_LINE,dedomena);
				command = strtok_s(buf1, DELIMITER, &a);
				
				//an einai read
				if ((command[0]=='R')|| (command[0]=='W')||(command[0]=='M')){
					address=strtok_s(0, DELIMITER, &a);
					address_atoi=atoi(address);
					dec2bin(binary, address_atoi);
					if (command[0]=='R'){
						fprintf(out, "%s\t%s READ\t%d\t", command, address,address_atoi );}
					else if (command[0]=='M'){
						fprintf(out, "%s\t%s MODIFY\t%d\t", command, address,address_atoi );}
					else if (command[0]=='W'){
						fprintf(out, "%s\t%s WRITE\t%d\t", command, address,address_atoi );}
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
						  sbits[i]=binary[j]+48;
						  
					   }
					fprintf(out, "\nblock offset bits are:");
					for(j=bits_addressing-1-bits_tag-bits_index,i=0;j>=0;j--,i++) {
						  fprintf(out, "%d ",binary[j]);
						  bbits[i]=binary[j]+48;
						  
					   }
					fprintf(out, "\n");

				if (eidos==1){ //an einai direct
					//Convert set bits from char array into ints
					for(q = 0, p = (bits_index -1); q < bits_index; q ++, p--) {
						if (sbits[q] == '1')
							 setadd = 1;
					    if (sbits[q] == '0')
							 setadd = 0;
					    setadd = setadd * pow(2, p);
					    totalset += setadd;
				  }
				}
					printf("totalset %d\n", totalset);

					//CONVERT TAG BITS
					for(k = 0, m = (bits_tag-1); k < bits_tag; k ++, m--) {
						if (tbits[k] == 1)
							 tagadd = 1;
					    if (tbits[k] == 0)
							 tagadd = 0;
					    tagadd = tagadd * pow(2, m);
					    totaltag += tagadd;
				  }
					
					printf("totaltag %d\n", totaltag);

					//convert block offset bits
					for(k = 0, m = (bits_block_offset-1); k < bits_block_offset; k ++, m--) {
						if (bbits[k] == '1')
							 bladd = 1;
					    if (bbits[k] == '0')
							 bladd = 0;
					    bladd = bladd * pow(2, m);
					    totalbl += bladd;
				  }
					
					printf("totalblockoffset %d\n", totalbl);

					//...........................................................
					//AN EINAI DIRECT MAPPED
					//...........................................................

				if (eidos==1){ 
					if ((command[0]=='R')||(command[0]=='M')){  //Calculating Hits and Misses an einai read
			    	
						if ((mycache[totalset].valid[totalbl] == 1) && (mycache[totalset].ctag[totalbl]==totaltag))
						  {  // Hit 
						   cacheHit++;
						   read++;
						   fprintf(out, "гит\n");
							}
						 else {   // Miss (cache entry invalid, or wrong tag) 
							 if (mycache[totalset].valid[totalbl] == 0){
								 compulsory=compulsory+1;
								 fprintf(out, "miss! type: compulsory\n");
							 }
							 if ((mycache[totalset].valid[totalbl] == 1) && (mycache[totalset].ctag[totalbl]!=totaltag)){
								  conflict=conflict+1;
								 fprintf(out, "miss! type: conflict\n");
							 }

							  cacheMiss++;
						      read++;
							 } 
					}

					if (command[0]=='W'){
						 //Calculating Hits and Misses
						if ((mycache[totalset].valid[totalbl] == 1) && (mycache[totalset].ctag[totalbl]==totaltag))
						  {  // Hit 
						  cacheHit++;
						   write++;
						   fprintf(out, "гит\n");
						  }
					  else
						 { // Miss (cache entry invalid, or wrong tag) 
						   cacheMiss++;
						   write++;
						   mycache[totalset].valid[totalbl] = 1;
						   mycache[totalset].ctag[totalbl]=totaltag;
						 }
					}

				} //end off an einai direct

				//.................................
				//an einai fully
				//.................................
				if (eidos==3){
					if ((command[0]=='R')||(command[0]=='M')||(command[0]=='W')){  //Calculating Hits and Misses an einai read
						if ((command[0]=='R')||(command[0]=='M')){
											 read++;}
										 if (command[0]=='W'){
											 write++;}
						for(i=0;(i<dways)&&(ifhit==0);i++){
								if ((mycache2[i].valid[totalbl] == 1) && (mycache2[i].ctag[totalbl]==totaltag)){ 
									// Hit 
									if (politiki_antikatastasis==2){
										mycache2[i].FifoAndLru[totalbl]=helpcounter_fifo_and_lru;}
						   cacheHit++;
						   fprintf(out, "гит\n");
						   ifhit=1;
								}}

								if (ifhit==0) {   // Miss (cache entry invalid, or wrong tag) 
									for(i=0;(i<dways)&&(ifhit==0);i++){
									if ((mycache2[i].valid[totalbl] != 0)){
										flag_compulsory=0;
									}
									if((mycache2[i].valid[totalbl]==0)){
										flag_campacity=0;}
									
									if ((mycache2[i].valid[totalbl] == 1) && (mycache2[i].ctag[totalbl]!=totaltag)){
										flag_conflict=1;}
									}


									if (flag_compulsory==1){
										 compulsory=compulsory+1;
										 cacheMiss++;
										 fprintf(out, "miss! type: compulsory\n");			 
										 if (command[0]=='W'){
											  for(k=0; ((k<dways)&&(write_flag!=1));k++){
											  if (mycache2[k].valid[totalbl]==0){
												  mycache2[k].valid[totalbl] = 1;
												  mycache2[k].ctag[totalbl]=totaltag; //
												  mycache2[i].FifoAndLru[totalbl]=helpcounter_fifo_and_lru;
												  write_flag=1;}
											}
										 }
									} //end of an einai compulsory


									if (flag_campacity==1){
										 capacity=capacity+1;
										 fprintf(out, "miss! type: capacity\n");
										 if (politiki_antikatastasis==3){
											 deiktis_ekdiwksis=rand()%dways;}
										 if ((politiki_antikatastasis==1)||(politiki_antikatastasis==2)){
											 min=999999999;
											 for(k=0; k<dways;k++){
												 if (mycache2[k].FifoAndLru[totalbl]<min){
													 min=mycache2[k].FifoAndLru[totalbl];
												 }
											 }
											 deiktis_ekdiwksis=min;
										 }
										  if (command[0]=='W'){
											  mycache2[deiktis_ekdiwksis].valid[totalbl] = 1;
											  mycache2[deiktis_ekdiwksis].ctag[totalbl]=totaltag; //
											  mycache2[i].FifoAndLru[totalbl]=helpcounter_fifo_and_lru;
											  write_flag=1;
											
										 }
										 cacheMiss++;
										 } //end of an einai campacity



									if ((flag_conflict==1)&&(flag_campacity!=1)&&(flag_compulsory!=1)){
										 conflict=conflict+1;
										  cacheMiss++;
										 fprintf(out, "miss! type: conflict\n");
										 if (command[0]=='W'){
										 for(k=0; ((k<dways)&&(write_flag!=1));k++){
										 if (mycache2[k].valid[totalbl]==0){
												  mycache2[k].valid[totalbl] = 1;
												  mycache2[k].ctag[totalbl]=totaltag; //
												  mycache2[i].FifoAndLru[totalbl]=helpcounter_fifo_and_lru;
												  write_flag=1;}
										 }

										if (write_flag==0){
											if (politiki_antikatastasis==3){
												 deiktis_ekdiwksis=rand()%dways;}
											if ((politiki_antikatastasis==1)||(politiki_antikatastasis==2)){
											 min=999999999;
											 for(k=0; k<dways;k++){
												 if (mycache2[k].FifoAndLru[totalbl]<min){
													 min=mycache2[k].FifoAndLru[totalbl];
												 }
											 }
											 deiktis_ekdiwksis=min;
											 }
										    printf("deiktis ekdiwksis: %d", deiktis_ekdiwksis);
										    mycache2[deiktis_ekdiwksis].valid[totalbl] = 1;
											mycache2[deiktis_ekdiwksis].ctag[totalbl]=totaltag; //
											mycache2[i].FifoAndLru[totalbl]=helpcounter_fifo_and_lru;
											write_flag=1;	
										 }
										 }
										
										 } //end of an einai conflict


					
							 } //end of miss

							
					//	} //loop
					}
				}




				}



				

				//an einai flush
				else if (command[0]=='F')
				{
					//initial cache
				  if (eidos==1){ //an einai direct mapped
						for(i=0;i<leksis;i++) {
							for (j=0;j<megethos_block;j++){
							mycache[i].ctag[j]=-1;
							mycache[i].valid[j] = 0;}
						}
					}

				  if (eidos==3){
					  //initial cache
			for(i=0;i<dways;i++) {
				for (j=0;j<megethos_block;j++){
					randomcounter +=1;
					mycache2[i].ctag[j]=-1;
					mycache2[i].valid[j] = 0;
					mycache2[i].dirty[j]=0;
					mycache2[i].FifoAndLru[j]=0;
					randomcounter1 +=1;
    }
				  }
				  }
					fprintf(out, "%sFLUSH\n", command );	
					helpcounter_fifo_and_lru=0;
				}
				
				helpcounter_fifo_and_lru=helpcounter_fifo_and_lru+1;
				}
				
		 fclose(dedomena); //klisimo arxeiou
		 fclose(out);
		 totalkikloi=(cacheMiss*kikloi_miss)+(cacheMiss*kikloi_hit);
		 missrate=((float)cacheMiss/(read+write))*100;
		 hitrate=((float)cacheHit/(read+write))*100;
		 printf("Hits: %d\n", cacheHit);
	     printf("Misses: %d\n", cacheMiss);
		 printf("Writes: %d\n", write);
		 printf("Reads: %d\n", read);
		 printf("Modifys %d\n", modify);
		 printf("misses compulsory %d\n", compulsory);
		 printf("misses conflict %d\n", conflict);
		 printf("misses capacity %d\n", capacity);
		 printf("sinolikoi kikloi %d\n", totalkikloi);
		 printf("missrate: %.2f tis ekato\n", missrate);
		 printf("hitrate: %.2f tis ekato\n", hitrate);

		 if (eidos==1){
			 free(mycache);}
		 if (eidos==3){
			 free(mycache2);}
		
			 
		 
	    system("Pause");

		return 0;
	}