#include "lisiblestd/memory.h"
#include "test.h"
#include <lisiblestd/string.h>

void t_String_new(void) {
  String string = String_new(&system_allocator, "Some string");
  T_ASSERT(strncmp(string.value, "Some string", 11) == 0);
  T_ASSERT_EQ(string.length, 11);
  String_destroy(&system_allocator, &string);
}

void t_String_eq(void) {
  String first_string = String_new(&system_allocator, "abc");
  String second_string = String_new(&system_allocator, "abc");
  String third_string = String_new(&system_allocator, "bcd");
  T_ASSERT(String_eq(&first_string, &second_string));
  T_ASSERT(!String_eq(&second_string, &third_string));
  T_ASSERT(!String_eq(&second_string, NULL));
  T_ASSERT(!String_eq(NULL, NULL));
  String_destroy(&system_allocator, &first_string);
  String_destroy(&system_allocator, &second_string);
  String_destroy(&system_allocator, &third_string);
}

void t_String_view(void) {
  String string = String_new(&system_allocator, "abc");
  StringView string_view = String_view(&string);
  T_ASSERT_EQ(string_view.length, 3);
  T_ASSERT(strncmp(string_view.value, "abc", 3) == 0);
  String_destroy(&system_allocator, &string);
}

TEST_SUITE(TEST(t_String_new), TEST(t_String_eq), TEST(t_String_view))
