#ifndef LSTD_MEMORY_H
#define LSTD_MEMORY_H

#include "types.h"

typedef struct {
  void *(*allocate)(usize size, void *ctx);
  void *(*allocate_aligned)(usize alignment, usize size, void *ctx);
  void *(*allocate_array)(usize count, usize item_size, void *ctx);
  void *(*reallocate)(void *ptr, usize old_size, usize new_size, void *ctx);
  void (*free)(void *ptr, void *ctx);
  void *ctx;
} Allocator;

void *Allocator_allocate(Allocator *allocator, usize size);
void *Allocator_allocate_aligned(Allocator *allocator, usize alignment,
                                 usize size);
void *Allocator_allocate_array(Allocator *allocator, usize count,
                               usize item_size);
void *Allocator_reallocate(Allocator *allocator, void *ptr, usize old_size,
                           usize new_size);
void Allocator_free(Allocator *allocator, void *ptr);

extern Allocator system_allocator;

typedef struct {
  usize capacity;
  usize size;
  u8 *data;
} Arena;

Allocator Arena_allocator(Arena *arena);
void Arena_init(Arena *arena, Allocator *allocator, usize size);
void *Arena_allocate(Arena *arena, usize size);
void *Arena_allocate_array(Arena *arena, usize count, usize item_size);
void Arena_clear(Arena *arena);
void Arena_deinit(Arena *arena, Allocator *allocator);

char *memory_clone_string(Allocator *allocator, const char *str);

#endif // LSTD_MEMORY_H
