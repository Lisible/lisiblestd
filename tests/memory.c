#include "test.h"
#include <lisiblestd/log.h>
#include <lisiblestd/memory.h>

void t_arena_create(void) {
  Arena arena;
  Arena_init(&arena, &system_allocator, 1024);
  T_ASSERT_EQ(arena.capacity, 1024);
  T_ASSERT_EQ(arena.size, 0);
  T_ASSERT_NOT_NULL(arena.data);
  Arena_deinit(&arena, &system_allocator);
}

void t_arena_allocate(void) {
  Arena arena;
  Arena_init(&arena, &system_allocator, 10);
  void *ptr = Arena_allocate(&arena, 10);
  T_ASSERT_NOT_NULL(ptr);
  T_ASSERT_EQ(arena.size, 10);
  T_ASSERT_EQ(arena.capacity, 10);
  Arena_deinit(&arena, &system_allocator);
}

void t_arena_allocate_array(void) {
  Arena arena;
  Arena_init(&arena, &system_allocator, 100);
  void *ptr = Arena_allocate_array(&arena, 10, sizeof(int));
  T_ASSERT_NOT_NULL(ptr);
  T_ASSERT_EQ(arena.size, 10 * sizeof(int));
  T_ASSERT_EQ(arena.capacity, 100);
  Arena_deinit(&arena, &system_allocator);
}

void t_arena_allocate_clear(void) {
  Arena arena;
  Arena_init(&arena, &system_allocator, 100);
  Arena_allocate(&arena, 8);
  T_ASSERT_EQ(arena.size, 8);
  T_ASSERT_EQ(arena.capacity, 100);
  Arena_allocate(&arena, 4);
  T_ASSERT_EQ(arena.size, 12);
  T_ASSERT_EQ(arena.capacity, 100);
  Arena_clear(&arena);
  T_ASSERT_EQ(arena.size, 0);
  T_ASSERT_EQ(arena.capacity, 100);
  Arena_deinit(&arena, &system_allocator);
}

TEST_SUITE(TEST(t_arena_create), TEST(t_arena_allocate),
           TEST(t_arena_allocate_array), TEST(t_arena_allocate_clear))
