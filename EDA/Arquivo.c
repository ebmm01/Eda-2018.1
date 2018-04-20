#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

  int n,status;
  char *c;
  FILE *file;
  file = fopen("asphalt_01.txt", "r");

  if(file == NULL){
     printf("Can not open file!\n");
  }
fscanf(file, "%d%c", &n, c);
  while(!feof(file)){
      printf("%d", n);
       fscanf(file, "%d%c", &n, c);


  }
  fclose(file);

  return 0;
}
