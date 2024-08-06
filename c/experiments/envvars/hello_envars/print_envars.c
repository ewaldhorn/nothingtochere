
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv, char **envp) {
  char *value;

  value = getenv("HOME");
  printf("Home: %s\n", value);
  value = getenv("USER");
  printf("User: %s\n", value);
  value = getenv("PATH");
  printf("Path: %s\n", value);

  // list all known environment variables
  for (int i = 0; envp[i]!=NULL;i++) {
    printf("%d: %s\n", i, envp[i]);
  }

  // use the C standard environ variable
  for (int i = 0; environ[i]!=NULL;i++){
    printf("%d: %s\n", i, environ[i]);
  }

  return 0;
}
