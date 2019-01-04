#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) 
{
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

__device__ int is_a_match(char *attempt) {
  char a[] = "FR2138";
  char b[] = "AV7264";
  char c[] = "WW2246";
  char d[] = "YL6075";


  char *first = attempt;
  char *second = attempt;
  char *third = attempt;
  char *fourth = attempt;
  char *password1 = a;
  char *password2 = b;
  char *password3 = c;
  char *password4 = d;

  while(*first == *password1) { 
   if(*first == '\0') 
    {
	printf("Password Found: %s\n",a);
      break;
    }

    first++;
    password1++;
  }
	
  while(*second == *password2) { 
   if(*second == '\0') 
    {
	printf("Password Found: %s\n",b);
      break;
    }

    second++;
    password2++;
  }

  while(*third == *password3) { 
   if(*third == '\0') 
    {
	printf("Password Found: %s\n",c);
      break;
    }

    third++;
    password3++;
  }

  while(*fourth == *password4) { 
   if(*fourth == '\0') 
    {
	printf("Password Found: %s\n",d);
      return 1;
    }

    fourth++;
    password4++;
  }
  return 0;

}


/****************************************************************************
  The kernel function assume that there will be only one thread and uses 
  nested loops to generate all possible passwords and test whether they match
  the hidden password.
*****************************************************************************/

__global__ void  kernel() {
char w, x, y, z;
  
  char password[7];                                                 
  password[6] = '\0';

int q = blockIdx.x+65;
int t = threadIdx.x+65;
char firstInitial = q; 
char secondInitial = t; 
    
password[0] = firstInitial;
password[1] = secondInitial;
	for(w='0'; w<='9'; w++){
	  for(x='0'; x<='9'; x++){
	   for(y='0'; y<='9'; y++){
	     for(z='0'; z<='9'; z++){
	        password[2] = w;
	        password[3] = x;
	        password[4] = y;
	        password[5] = z; 
	      if(is_a_match(password)) {
		//printf("Success");
	      } 
             else {
	        //printf("tried: %s\n", password);		  
	         }
	      }
	   }
	}
    }
}


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed
					, (time_elapsed/1.0e9)); 
  return 0;
}



