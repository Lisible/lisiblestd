#include "memory.h"

#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "math.h"

static const usize MINIMUM_ALIGNMENT = sizeof(void *);

void *memory_allocate(usize size, void *ctx) {
  (void)ctx;
  return malloc(size);
}
void *memory_allocate_aligned(usize alignment, usize size, void *ctx) {
  (void)ctx;
  return aligned_alloc(MAX(alignment, MINIMUM_ALIGNMENT), size);
}
void *memory_allocate_array(usize count, usize item_size, void *ctx) {
  (void)ctx;
  return calloc(count, item_size);
}
void *memory_reallocate(void *ptr, usize old_size, usize new_size, void *ctx) {
  (void)old_size;
  (void)ctx;
  return realloc(ptr, new_size);
}
void memory_free(void *ptr, void *ctx) {
  (void)ctx;
  free(ptr);
}
Allocator system_allocator = {.allocate = memory_allocate,
                              .allocate_aligned = memory_allocate_aligned,
                              .allocate_array = memory_allocate_array,
                              .reallocate = memory_reallocate,
                              .free = memory_free,
                              NULL};
void *Allocator_allocate(Allocator *allocator, usize size) {
  LSTD_ASSERT(allocator != NULL);
  return allocator->allocate(size, allocator->ctx);
}
void *Allocator_allocate_aligned(Allocator *allocator, usize alignment,
                                 usize size) {
  LSTD_ASSERT(allocator != NULL);
  return allocator->allocate_aligned(alignment, size, allocator->ctx);
}
void *Allocator_allocate_array(Allocator *allocator, usize count,
                               usize item_size) {
  LSTD_ASSERT(allocator != NULL);
  return allocator->allocate_array(count, item_size, allocator->ctx);
}
void *Allocator_reallocate(Allocator *allocator, void *ptr, usize old_size,
                           usize new_size) {
  LSTD_ASSERT(allocator != NULL);
  return allocator->reallocate(ptr, old_size, new_size, allocator->ctx);
}
void Allocator_free(Allocator *allocator, void *ptr) {
  LSTD_ASSERT(allocator != NULL);
  allocator->free(ptr, allocator->ctx);
}

void *arena_allocator_allocate(usize size, void *ctx) {
  LSTD_ASSERT(ctx != NULL);
  return Arena_allocate((Arena *)ctx, size);
}
void *arena_allocator_allocate_aligned(usize alignment, usize size, void *ctx) {
  LSTD_ASSERT(ctx != NULL);
  (void)alignment;
  (void)size;
  LSTD_UNIMPLEMENTED();
  return NULL;
}
void *arena_allocator_allocate_array(usize count, usize item_size, void *ctx) {
  LSTD_ASSERT(ctx != NULL);
  return Arena_allocate_array((Arena *)ctx, count, item_size);
}
void *arena_allocator_reallocate(void *ptr, usize old_size, usize new_size,
                                 void *ctx) {
  (void)ptr;
  (void)old_size;
  (void)new_size;
  (void)ctx;
  LSTD_UNIMPLEMENTED();
  return NULL;
}

void arena_allocator_free(void *ptr, void *ctx) {
  (void)ptr;
  (void)ctx;
}

Allocator Arena_allocator(Arena *arena) {
  return (Allocator){.ctx = arena,
                     .allocate = arena_allocator_allocate,
                     .allocate_aligned = arena_allocator_allocate_aligned,
                     .allocate_array = arena_allocator_allocate_array,
                     .reallocate = arena_allocator_reallocate,
                     .free = arena_allocator_free};
}

void Arena_init(Arena *arena, Allocator *allocator, usize size) {
  LSTD_ASSERT(arena != NULL);
  LSTD_ASSERT(allocator != NULL);
  arena->size = 0;
  arena->capacity = size;
  arena->data = Allocator_allocate(allocator, size);
}
void *Arena_allocate(Arena *arena, usize size) {
  LSTD_ASSERT(arena->size + size <= arena->capacity);
  void *ptr = arena->data + arena->size;
  arena->size += size;
  return ptr;
}
void *Arena_allocate_array(Arena *arena, usize count, usize item_size) {
  void *ptr = Arena_allocate(arena, count * item_size);
  memset(ptr, 0, count * item_size);
  return ptr;
}
void *arena_reallocate(Arena *arena, void *ptr, usize old_size,
                       usize new_size) {
  LSTD_ASSERT(new_size > old_size);
  void *new_ptr = Arena_allocate(arena, new_size);
  memcpy(new_ptr, ptr, old_size);
  return new_ptr;
}
void Arena_clear(Arena *arena) { arena->size = 0; }
void Arena_deinit(Arena *arena, Allocator *allocator) {
  Allocator_free(allocator, arena->data);
}

char *memory_clone_string(Allocator *allocator, const char *str) {
  usize string_length = strlen(str) + 1;
  char *duplicate_string =
      Allocator_allocate_array(allocator, string_length, sizeof(char));
  memcpy(duplicate_string, str, strlen(str));
  return duplicate_string;
}
