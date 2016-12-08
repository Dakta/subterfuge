#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char **argv)
{
  FILE *fin, *tmp ;
  int q ;

  if (argc != 2) {
    printf("Usage : pgm inputfile\n") ;
    exit(1) ;
  }


  fin = fopen(argv[1],"r") ;
  if (fin == NULL) {
    printf("can't open file %s\n",argv[1]) ;
    exit(1) ;
  }

  tmp = fopen("temporary_junk8765", "w") ;
  if (tmp == NULL) {
    printf("can't open temp file\n") ;
    exit(1) ;
  }



  q = fgetc(fin) ;
  while (q != EOF) {
    if ((q == '(') || (q == ')')) {
      fputc(' ', tmp) ;
      fputc(q, tmp) ;
      fputc(' ', tmp) ;
    } else {
      fputc(q, tmp) ;
    }
    q = fgetc(fin) ;
  }


  fclose(fin) ;
  fclose(tmp) ;


  // ------------------------------------------

  tmp = fopen("temporary_junk8765", "r") ;
  if (tmp == NULL) {
    printf("can't open temp file\n") ;
    exit(1) ;
  }

  int n ;
  char w[100] ;
  while (1) {
    n = fscanf(tmp,"%s",w) ;
    if (n != 1) { break ; }
    printf("the token is : %s\n",w) ;
  }

  system("rm temporary_junk8765") ;
}


