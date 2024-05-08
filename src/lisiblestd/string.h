#ifndef LSTD_STRING_H
#define LSTD_STRING_H

#include "memory.h"
#include "types.h"
#include <stdbool.h>

struct String {
  char *value;
  usize length;
};

typedef struct String String;

bool String_from_str(Allocator *allocator, String *string, const char *str);
void String_destroy(Allocator *allocator, String *string);
usize String_length(const String *string);

#endif // LSTD_STRING_H
