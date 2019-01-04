#include <time.h>
#include <pthread.h>
#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
 


int n_passwords = 4;

char *encrypted_passwords[] = {

 "$6$KB$yPvAP5BWyF7oqOITVloN9mCAVdel.65miUZrEel72LcJy2KQDuYE6xccHS2ycoxqXDzW.lvbtDU5HuZ733K0X0",

"$6$KB$H8RIsbCyr2r7L1lklCPKY0tLK9k5WudNWpxkNbx2bCBRHCsI3qyVRY.0nrovdkDLDJRsogQE9mA3OqcIafVsV0",

"$6$KB$zd0hywe3NHS5T209L69g1LWlJjEXoT7OCwzWs.tL5mjK6.DlCY8azuxxy/ucDmebOMWKgWvS/A2..Ht1MyfI1/",

"$6$KB$yRaZFVbx3SBqrI7KCFC572n/v5hWxyQXR3Y8WVbh05yX6GNeBGWN1tTCPT51Etagi4EQ8Vdd91ldNm6tIrIV40"
};
 
void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

 

void crack(){
   int k;
  pthread_t m1, m2;

  void *first();
  void *second();
  
  for(k=0;k<n_passwords;k<k++) {
    pthread_create(&m1, NULL, first, encrypted_passwords[k] );
    pthread_create(&m2, NULL, second, encrypted_passwords[k]);
  
  pthread_join(m1, NULL);
  pthread_join(m2, NULL);
}
}

void *first(char *salt_and_encrypted){
 int a,b,c;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='M'; a++){
    for(b='A'; b<='Z'; b++){
       for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a,b,c);
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
printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
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

void *second(char *salt_and_encrypted){
int x, y, z;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;  
  substr(salt, salt_and_encrypted, 0, 6);

  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
       for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z);
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
   printf("%d solutions explored\n", count);
}

 

int main(int argc, char *argv[]) {
   
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  
    crack();
    
    
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 


  return 0;
}
