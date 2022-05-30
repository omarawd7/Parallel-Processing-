#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<math.h>
#define MAX 500000
#define LSIZ 1280
#define RSIZ 1000

int main(int argc, char* argv[])
{
    FILE* fptr = fopen("/shared/p.txt", "r");
    char ch;
    int chr[1000];
    int num = 0, n = 0, nums = 0;
    double x[100], y[100];
    double clusters[100][2];
    double lsum = 0, sum = 0;
    bool p = true;
    char line[RSIZ][LSIZ];
    int i = 0;
    int j = 0;
    int tot = 0;
    int z = 0;
	    while(fgets(line[i++], LSIZ, fptr))
	{
	
    }
	fclose(fptr);
	tot = i-1;
	  i=0;
		 for(;i<tot;i++){
           x[i]=-1;
		   y[i]=-1;
		 }
	  i=0;
	  j=1;
    for(;i<tot;i++){
		while(isdigit(line[i][j])){
			if(x[i]==-1){
				x[i]=(double)(line[i][j])-48;
			}else{
			z=(double)(line[i][j])-48;
			x[i]=(x[i]*10)+z;
			}			
			j++;
		}
		j++;
		while(isdigit(line[i][j])){
			if(y[i]==-1){
				y[i]=(double)(line[i][j])-48;
			}else{
			z=(double)(line[i][j])-48;
			y[i]=(y[i]*10)+z;
			}			
			j++;
		}
		j=1;
        }
		i=0;
		/* for(;i<tot;i++){
	  printf("%f\n",x[i]);
	  printf("%f\n",y[i]);
		 }*/

int num_iterations = 2;
int random;
    int k = 0;
    for (; k < tot-1 ; ++k) {
        random = (rand()% 10) +1 ;

        if(random>tot-1){
            k--;
        }
        else{
            clusters[k][0] = x[random];
            clusters[k][1] = y[random];
         //   printf("%d \n", random);
           // printf("%f \n", x[random]);
           // printf("%f \n", y[random]);
        }
    }

    int it = 0;
	int NOT;
    while (it < num_iterations) {
printf("the number of iterations= %d\n", it);
		
	int c[100][2];
    int threads[100];
    int c1 = 0;
    int index = 0;
	int count=0;
	int indthread[100];
	double arr2[100];
    double arr[100];
    double dest[100];
	double alldest[100];
#pragma omp parallel
    {
 NOT=omp_get_num_threads();
#pragma omp for schedule(dynamic)

        for (i = 0; i < tot; i++)
        {
            int k = 0;
			

            for (; k < omp_get_num_threads() ; k++) {
                arr[k] = abs(clusters[k][0] - x[i]);
                arr2[k] = abs(clusters[k][1] - y[i]);
                dest[k] = sqrt(pow(arr[k],2) + pow(arr2[k],2));
				indthread[count]=k;
				alldest[count] = sqrt(pow(arr[k],2) + pow(arr2[k],2));
             // printf("clusters[k][0]=%f\n",clusters[k][0]);

				count++;
            }
        }
	}
	    
  double min ;
  double a,b;
  int newi;
//printf("minnnnnnnnnn:%f\n", dest[0]);
int yu=(NOT)*tot;
//printf("not:%d\n", NOT);
        for (i=0; i < yu;i+=NOT)
        {
				
			min = alldest[i];
			index = i;
			newi=i+NOT;
		  for (j=i+1; j < newi; j++)
        {
		
	        if (min > alldest[j])
            {
                min = alldest[j];
                index = j;

            }

		}

				//printf("min:%f\n",min);
	          //  printf("index:%d\n",index);
		if(index%2==0){
	  a=x[(index/NOT)];
	  b=y[(index/NOT)];
		  
	  }else{
      	  a=x[((index)/NOT)];
	      b=y[((index)/NOT)];
	  }
	 //  printf("a=:%f\n", a);
	 //  printf("b=:%f\n", b);
        c[c1][0] = a;
        c[c1][1] = b;
        threads[c1] = indthread[index];
	//	printf("threads[c1]:%d\n", threads[c1]);
		//printf("c1:%d\n", c1);

        c1++;
        }

		int sum1,sum2;
#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (j = 0; j < NOT; j++)
        {						
             sum1 = 0, sum2 = 0;
             count = 0;
            for (i = 0; i < c1 ; i++) {
            //printf("threaaaads:%d\n",threads[i]);
                if (threads[i]== j){
                    sum1 += c[i][0];
                    sum2 += c[i][1];
                    count++;
                }
            }
			int h=0;
			for(;h<c1;h++){
			if(threads[h]==j){
		      clusters[j][0] = sum1 / (count);
              clusters[j][1] = sum2 / (count);
			}}

			 // printf("clusters[j][0] %f\n", clusters[j][0]);
		   //   printf("clusters[j][1] %f\n", clusters[j][1] );

        }

	}
        for (j = 0; j < NOT; j++)
        {
           printf("Cluster:%d\n", j);
            for (i = 0; i < c1 ; i++) {
                    if (threads[i] == j) {
                       printf("(%d,", c[i][0]);
                       printf("%d)\n", c[i][1]);
                    }
            }
        }
        it++;
    }
    
}
