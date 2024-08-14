#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>

#define UUID_SIZE (sizeof(uuid_t) * 2) + 5

int main() {
  uuid_t myuuid;
  uuid_generate(myuuid);
  char uuidtext[UUID_SIZE];
  uuid_unparse(myuuid, uuidtext);

  printf("UUID as string: %s\n", uuidtext);

  return EXIT_SUCCESS;
}
