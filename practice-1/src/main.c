#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  if (argc > 1)
  {
    printf("Привет, %s", argv[1]);
  }
  else
  {
    printf("Привет, %s", getenv("USERNAME"));
  }

  return 0;
}