#include "lisiblestd/memory.h"
#include "test.h"
#include <lisiblestd/string.h>

void t_String_from_str(void) {
  String string;
  String_from_str(&system_allocator, &string, "Some string");
  T_ASSERT(strncmp(string.value, "Some string", 11));
  T_ASSERT_EQ(string.length, 11);

  String_destroy(&system_allocator, &string);
}

TEST_SUITE(TEST(t_String_from_str))
