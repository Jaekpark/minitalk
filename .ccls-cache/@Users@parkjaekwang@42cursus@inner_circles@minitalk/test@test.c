#include <stdio.h>
#include <string.h>

int main(int argc, wchar_t **argv)
{
  printf("leng = %lu\n", strlen(argv[1]));
  printf("char = %c\n", argv[1][0]);
  printf("size = %lu\n", sizeof(argv[1]));
  printf("text = %s\n", argv[1]);
  return (0);
}
