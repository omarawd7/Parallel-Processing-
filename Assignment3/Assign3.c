
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <math.h>
#define LSIZ 1280
#define RSIZ 1000
int main(int argc , char * argv[])
{
	//int * arr;
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	char line[RSIZ][LSIZ];
	int *ptr1=NULL;
	int x[100];
	int y[100];
    int all[100];	
    FILE *fptr = NULL;
    int i = 0;
    int tot =0;
    int z=0 ;
    int dataperprocess;
	 int bar ;
	char *ptr;
	int te;
	int np;
	int count [RSIZ];
	int finalcount [RSIZ];
	int range;
	int ba;
	int t;
	int ii;
	MPI_Status status;	/* return status for 	*/

				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if( my_rank == 0){
fptr=fopen("/shared/dataset.txt", "r");
    while(fgets(line[i++], LSIZ, fptr))
	{

    }
	fclose(fptr);
	   
    tot = i-1;
	 printf("Enter the number of bars: \n");
     scanf("%d", &bar);
   	 printf("Enter the number of points: \n");
     scanf("%d", &np);
  // printf(" the total num of BarsPerProcess is:   %d\n",BarsPerProcess);
    i=0;

	for(;i<np;i++){
	 z=strtol(line[i], &ptr, 10);
	 x[i]=z;
	}
	//Sort the array in ascending order  
	int j,temp;
    for ( i = 0; i < np; i++) {     
        for ( j = i+1; j < np; j++) {     
           if(x[i] > x[j]) {    
               temp = x[i];    
               x[i] = x[j];    
               x[j] = temp;    
           }     
        }     
    } 


   //pading
           for ( j = np; j < np*2; j++) {     
                x[j] =-1;
           }
    //inializing the count with zeros
	           for ( j = 0; j <= bar; j++) {     
                count[j] =0;
           }
	// printf(" max :%d\n",x[tot-1]);
	   dataperprocess=np/p;
	   int ch=dataperprocess*p;
	   if(ch<np){
		  dataperprocess++; 
	   }
	   
	   range=x[np-1]/bar;
	   ch=range*bar;
	   if(ch<x[np-1]){
		  range++; 
	   }
	// printf(" range :%d\n",range);
	
	
	}
	 MPI_Bcast(&range, 1, MPI_INT, 0, MPI_COMM_WORLD);
	 MPI_Bcast(&bar, 1, MPI_INT, 0, MPI_COMM_WORLD);
	 MPI_Bcast(&count, bar+1, MPI_INT, 0, MPI_COMM_WORLD);
	 MPI_Bcast(&dataperprocess, 1, MPI_INT, 0, MPI_COMM_WORLD);
	 MPI_Scatter(&x, dataperprocess, MPI_INT, &y, dataperprocess, MPI_INT, 0, MPI_COMM_WORLD);	
	 int jj=0;
	// printf("process: %d\n", my_rank);
	 ba=bar;
#pragma omp parallel shared (ba)
{    
#pragma omp for schedule(dynamic)
for(jj=0;jj<dataperprocess;jj++){
	// printf(" data :%d\n",y[jj]);	
	
while(ba!=0){
	t=ba*range;
	if(y[jj]<=t&&y[jj]>=(t-range+1)&&y[jj]!=-1){
		count[ba]++; 
	}
	ba--;
}
ba=	bar;
}
}
i=1;
	for(;i<= bar;i++){
 MPI_Gather(&count[i], 1, MPI_INT, &all, 1, MPI_INT, 0,MPI_COMM_WORLD);
 
 ii=0;
for(;ii<p;ii++){
	finalcount[i]+=all[ii];
}
}
if(my_rank==0){
	ii=1;
	int s=0;
	int e=range;
	for(;ii<=bar;ii++){
	printf("range start with %d , end with %d with count %d \n",s,e,finalcount[ii]);
	s+=range;
	e+=range;
}
	
}
	MPI_Finalize();
	return 0;
}
