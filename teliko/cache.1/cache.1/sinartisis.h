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

//sinartisi elegxou power of2?
int isPowerOfTwo(int x);
int isPowerOfTwo(int x)
	{
    return ((x != 0) && ((x & (~x + 1)) == x));
	}
