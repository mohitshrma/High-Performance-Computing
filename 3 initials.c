#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>


int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$MW$6Sxw0giqgyABD86bq9l7kfNIO75Uu6KSyTMMQy4v52MLt1NqHH6nKbrnvYgnmb7I3WYoQFKL5kPnhxHSupvMh.",

"$6$MW$ytACanRWpr3U6L7UrXDw6Ee7WARFwnsUJUuq/x6BaWM4pJtW3Tlcllk3xTWvJm5V3bvGAXDIf3ikgeY5iLAUK1",

"$6$MW$QdaXshD3QrtmJS./HpJY7iln/.43/fgInj9TdmkV2YClJNO6v/QJ48EGARgwgX2y0f47MHhIld0cKYAq4Q.Qo0",

"$6$MW$F0vgTfwFvk8E0Va38ocLHMSVSgr4Edrrt1k21lmXo2DWE53wVcp4bi80jX.DCJwSk3HMIq.PBy/ktHZdUVchT1"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  int x, y, r, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
     for(r='A'; r<='Z'; r++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%c%02d", x, y, r,z);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
   }
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main(int argc, char *argv[]){
  int i;
struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }
 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 

  return 0;
}


