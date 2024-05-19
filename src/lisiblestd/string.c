#include "string.h"
#include "assert.h"
#include "src/lisiblestd/memory.h"

#include <string.h>

String String_new(Allocator *allocator, const char *str) {
  LSTD_ASSERT(allocator != NULL);
  LSTD_ASSERT(str != NULL);

  usize length = strlen(str);
  char *value = Allocator_allocate(allocator, length + 1);
  LSTD_ASSERT(value != NULL);

  strncpy(value, str, length);
  value[length] = '\0';

  return (String){.value = value, .length = length};
}

void String_destroy(Allocator *allocator, String *string) {
  LSTD_ASSERT(allocator != NULL);
  LSTD_ASSERT(string != NULL);
  Allocator_free(allocator, string->value);
}

bool String_eq(const String *lhs, const String *rhs) {
  if (lhs == NULL || rhs == NULL || lhs->length != rhs->length) {
    return false;
  }

  return strncmp(lhs->value, rhs->value, lhs->length) == 0;
}

StringView String_view(const String *str) {
  return (StringView){.value = str->value, .length = str->length};
}

usize String_length(const String *string) {
  LSTD_ASSERT(string != NULL);
  return string->length;
}

StringView StringView_from_str(const char *data) {
  LSTD_ASSERT(data != NULL);
  return (StringView){.value = data, .length = strlen(data)};
}
