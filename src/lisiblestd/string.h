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
typedef struct StringView StringView;

String String_new(Allocator *allocator, const char *str);
void String_destroy(Allocator *allocator, String *string);
bool String_eq(const String *lhs, const String *rhs);
StringView String_view(const String *str);
usize String_length(const String *string);

struct StringView {
  const char *value;
  usize length;
};

StringView StringView_from_str(const char *data);

#endif // LSTD_STRING_H
