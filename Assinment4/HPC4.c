
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <math.h>
#define LSIZ 1280
#define RSIZ 1000
#include<time.h>
//#include "timer.h"
#include <unistd.h>  	// for sleep()
int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
    int i = 0;
    int tot =0;
    float z ;
    int dataperprocess;
	int alldata;
	 int n ;
	 int u ;
	 int my_first;
	 int my_last;
     int remain=0;
	 int s=3;
	 float  sum=0 ;
	 float  tot_sum;
     float error;
	 float runtime;
	int ba;
	float  t;
	float parallel_tot_time_spent;
	int ii;
	float  expected =1.202056903159594;
	float time_spent=0.0;
		float serial_time_spent=0.0;
	 int j=0;
	 float speedup=0.0;
	 float percentageofparaller=0.0;
	float ps=0.0;
float ssum=0.0;
float efficiency=0.0;
char line[RSIZ][LSIZ];
FILE *fptr = NULL;
FILE *out_file = fopen("/shared/OutputParallel.txt", "a+"); // write only
FILE *out_file1 = fopen("/shared/OutputSerial.txt", "a+"); // write only
fptr=fopen("/shared/OutputSerial.txt", "r");

FILE *file =out_file;
FILE *file1 =out_file1;
double start ,finish, elapsed;
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
	/* Start up MPI */
	MPI_Init( &argc , &argv );
	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if( p == 1){ //check if we have single process 
	start=MPI_Wtime();
	 	 printf("Enter the n: \n");
         scanf("%d", &n);
		 i=1;
	 		 for(;i<=n;i++){
		 
		 t =(float ) 1/power(i, s);
		 sum+=t;

	 }
		printf("total sum :%f\n", sum);
		error=expected -sum;
		printf("total error :%f\n", error);		
		finish=MPI_Wtime();
		elapsed=finish-start;
		printf(" serial elapsed time :%f\n", elapsed);
       fprintf(file1, "%f\n", elapsed); // write to file 
	}
	else{	
	if( my_rank == 0){
		
		    while(fgets(line[i++], LSIZ, fptr))
	{
	
    }
	fclose(fptr);
    z=(float) atof(line[0]);
	start=MPI_Wtime();

	 printf("Enter the n: \n");
     scanf("%d", &n);
     dataperprocess=n/p;
	 alldata=dataperprocess*p;
	 remain=n-alldata;
     serial_time_spent = z;
	//printf(" serial_time_spent :%f\n", serial_time_spent);
	}
	 MPI_Bcast(&serial_time_spent, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	 MPI_Bcast(&remain, 1, MPI_INT, 0, MPI_COMM_WORLD);
	 MPI_Bcast(&dataperprocess, 1, MPI_INT, 0, MPI_COMM_WORLD);
	 MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);	 
	if( my_rank == p-1){
		      u=dataperprocess+remain;
		      my_first = (my_rank * dataperprocess)+1;
              my_last = my_first + u;
	 }else{
		   my_first = (my_rank * dataperprocess)+1;
           my_last = my_first + dataperprocess;
	 }
	 i=my_first;
	 for(;i<my_last;i++){
		 
		 t =(float ) 1/power(i, s);
		 sum+=t;
	 }				

MPI_Reduce(&sum, &tot_sum, 1, MPI_FLOAT, MPI_SUM, 0,
           MPI_COMM_WORLD);
    if(my_rank==0){		
		printf("total sum :%f\n", tot_sum);
		error=expected -tot_sum;
		printf("total error :%f\n", error);
		finish=MPI_Wtime();
		printf(" serial_time_spent :%f\n", serial_time_spent);
		parallel_tot_time_spent=finish-start;
     	runtime=parallel_tot_time_spent;
		printf("runtime :%f\n", runtime);
		speedup=serial_time_spent/parallel_tot_time_spent;
		printf("speedup :%f\n", speedup);
		efficiency=speedup/p;
		printf("efficiency :%f\n", efficiency);
		         if (out_file == NULL) 
            {   
              printf("Error! Could not open file\n"); 
              exit(-1); // must include stdlib.h 
            }else{
			 fprintf(file, " Number of process of : %d\n", p); // write to file 
			 fprintf(file, "serial time spent = %f\n", serial_time_spent); // write to file 
			 fprintf(file, "runtime = %f\n", runtime); // write to file 
             fprintf(file, "speedup :%f\n", speedup); // write to file 
			 fprintf(file, "efficiency :%f\n", efficiency); // write to file 
			 fprintf(file,"\n"); // write to file 

				
			} 
			

	}
	                    }



	MPI_Finalize();
	return 0;
}

int power(int base, int exponent)
{
int result=1;
for (exponent; exponent>0; exponent--)
{
result = result * base;
}
return result;
}
