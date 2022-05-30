#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <math.h>
#define LSIZ 128
#define RSIZ 10
int main(int argc , char * argv[])
{
	//int * arr;
	int my_rank;		/* rank of process	*/
	int p,numbers_per_rank;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest=0;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	int size =1;
	char message[100];	/* storage for message	*/
	char line[RSIZ][LSIZ];
    FILE *fptr = NULL;
    int i = 0;
    int tot =0;
    int z=0 ;
    int count=0 ;
	 int sumofcount=0 ;
    int grade[100][3];
    int id[100][8];
	int my_first, my_last;
	MPI_Status status;	/* return status for 	*/

				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	//printf("HI \n ",my_rank);
	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);
		 // printf("the number of student passed the exam is %d\n",my_rank);
	///////////////////////////
	//if( my_rank != 0){
	//my_first = (my_rank * numbers_per_rank)-numbers_per_rank;}
	
	
	if( my_rank == 0){
fptr=fopen("/shared/grades1.txt", "r");
    while(fgets(line[i++], LSIZ, fptr))
	{
      //  line[i][strlen(line[i]) - 1]= '\0';
        //i++;		
    }
	fclose(fptr);
	   
    tot = i-1;
	printf(" the total num is  %d\n",tot);
	int q;
	int remain=0;
	numbers_per_rank =tot/(p-1);
	q=numbers_per_rank*(p-1);
	
		remain=tot-q;
	
    printf(" num per rank %d\n",numbers_per_rank);

    source = 1;
 		for( ; source < p ; source++)
		{
			if(source==p-1){
			int u=numbers_per_rank+remain;
		     MPI_Send(&u, 1,MPI_INT, source, tag, MPI_COMM_WORLD);
			my_first=(source * numbers_per_rank)-numbers_per_rank;
            my_last = my_first + u;
			}
			else{
			my_first=(source* numbers_per_rank)-numbers_per_rank;
            my_last = my_first + numbers_per_rank;
			MPI_Send(&numbers_per_rank, 1,MPI_INT, source, tag, MPI_COMM_WORLD);
			}
			//size=numbers_per_rank;
			
			int index=my_first;
				
			for(;index<my_last;index++){	
		   MPI_Send(&line[index],11,MPI_CHAR, source, tag, MPI_COMM_WORLD);
			}
		 //  size=1;
		}
		
				for( source = 1; source < p ; source++)
		{
			MPI_Recv(&count, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
			sumofcount+=count;			
		}
		  printf("the number of student passed the exam is %d",sumofcount);
		  	  printf(" out of %d\n",tot);
		}
      else{
	 int n;
	 count=0;
	//char line1[RSIZ][LSIZ];
	 MPI_Recv( &numbers_per_rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &status );
	 	int k=0;
		 my_first = (my_rank * numbers_per_rank)-numbers_per_rank;
         my_last = my_first + numbers_per_rank;
		  int ind = my_first;
		for(;k<numbers_per_rank;k++){
	  MPI_Recv(line, 11, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &status );
	     //printf("%d\n",my_rank);
	     //printf("%s\n",line[0]);
		 
		int j=0;
        for(;j<11;j++){
            if(j<9){
            z=(int)(line[0][j])-48;
            id[k][j]=z;
            }else{
            z=(int)(line[0][j])-48;
            grade[k][j]=z;
            }	
        } 
		}
 
	int in=0;
    for(;in<numbers_per_rank;in++){
	int j=0;
    for(;j<8;j++){
         printf("%d",id[in][j]);
        }
    if(grade[in][9]<6){
           printf(" Failed Please Repeat The Exam \n");
    }
    else{
        printf(" Passed The Exam \n");
        count++;
    }
}

MPI_Send( &count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
	//MPI_Send( &count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
 }
////////////////////////////

	/*if( my_rank != 0)
	{
	
		sprintf( message, "Greetings from process %d !",my_rank);
		dest = 0;
		
		MPI_Send( message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}*/
	/*
	else
	{	
		for( source = 1; source < p ; source++)
		{
			MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status );
			printf("%s\n" , message);
		}
	}*/

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
