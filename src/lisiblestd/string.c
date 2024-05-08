#include "string.h"
#include "assert.h"
#include "src/lisiblestd/memory.h"

#include <string.h>

bool String_from_str(Allocator *allocator, String *string, const char *str) {
  LSTD_ASSERT(allocator != NULL);
  LSTD_ASSERT(string != NULL);
  LSTD_ASSERT(str != NULL);

  usize length = strlen(str);
  char *value = Allocator_allocate_array(allocator, length + 1, sizeof(char));
  if (!value) {
    return false;
  }
  value[length] = '\0';

  string->value = value;
  string->length = length;
  return true;
}

void String_destroy(Allocator *allocator, String *string) {
  LSTD_ASSERT(allocator != NULL);
  LSTD_ASSERT(string != NULL);
  Allocator_free(allocator, string->value);
}

usize String_length(const String *string) {
  LSTD_ASSERT(string != NULL);
  return string->length;
}
