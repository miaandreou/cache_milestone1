


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
	int x;
	x=b-1;
	if (b==0){
		y=1;}
	else{
		y=a;
	
	for (i=0; i<x; i++){
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