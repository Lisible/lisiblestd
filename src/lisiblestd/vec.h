#ifndef LSTD_VEC_H
#define LSTD_VEC_H

#include "assert.h"
#include "memory.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

#define DECL_VEC(T, name)                                                      \
  struct name {                                                                \
    Allocator *allocator;                                                      \
    T *data;                                                                   \
    size_t length;                                                             \
    size_t capacity;                                                           \
  };                                                                           \
  typedef struct name name;                                                    \
  void name##_init(Allocator *allocator, name *vec);                           \
  void name##_deinit(name *vec);                                               \
  void name##_reserve(name *vec, size_t length_to_reserve);                    \
  void name##_push_back(name *vec, T value);                                   \
  T name##_pop_back(name *vec);                                                \
  void name##_append(name *vec, const T *values, size_t count);                \
  void name##_clear(name *vec);                                                \
  size_t name##_length(name *vec);                                             \
  size_t name##_capacity(name *vec);

#define DEF_VEC(T, name, initial_capacity)                                     \
  void name##_init(Allocator *allocator, name *vec) {                          \
    LSTD_ASSERT(vec != NULL);                                                  \
    vec->allocator = allocator;                                                \
    vec->capacity = initial_capacity;                                          \
    vec->data = Allocator_allocate(allocator, vec->capacity * sizeof(T));      \
    vec->length = 0;                                                           \
  }                                                                            \
  void name##_deinit(name *vec) {                                              \
    LSTD_ASSERT(vec != NULL);                                                  \
    Allocator_free(vec->allocator, vec->data);                                 \
    vec->data = NULL;                                                          \
    vec->capacity = 0;                                                         \
    vec->length = 0;                                                           \
  }                                                                            \
  void name##_reserve(name *vec, size_t length_to_reserve) {                   \
    LSTD_ASSERT(vec != NULL);                                                  \
    if (vec->length + length_to_reserve < vec->capacity) {                     \
      /* No need to reallocate as there is still enough capacity */            \
      return;                                                                  \
    }                                                                          \
                                                                               \
    size_t new_capacity = vec->capacity * 2;                                   \
    if (vec->length + length_to_reserve > new_capacity) {                      \
      new_capacity = vec->length + length_to_reserve;                          \
    }                                                                          \
                                                                               \
    vec->data = Allocator_reallocate(vec->allocator, vec->data,                \
                                     vec->capacity * sizeof(T),                \
                                     new_capacity * sizeof(T));                \
    if (!vec->data) {                                                          \
      /* TODO maybe improve that error handling? */                            \
      LOG0_ERROR("Vec reallocation failed, no memory left");                   \
      abort();                                                                 \
    }                                                                          \
    vec->capacity = new_capacity;                                              \
  }                                                                            \
  void name##_push_back(name *vec, T value) {                                  \
    LSTD_ASSERT(vec != NULL);                                                  \
    name##_reserve(vec, vec->length + 1);                                      \
    vec->data[vec->length] = value;                                            \
    vec->length++;                                                             \
  }                                                                            \
  T name##_pop_back(name *vec) {                                               \
    LSTD_ASSERT(vec != NULL);                                                  \
    vec->length--;                                                             \
    return vec->data[vec->length];                                             \
  }                                                                            \
  void name##_append(name *vec, const T *values, size_t count) {               \
    LSTD_ASSERT(vec != NULL);                                                  \
    LSTD_ASSERT(values != NULL);                                               \
    name##_reserve(vec, vec->length + count);                                  \
    memmove(&vec->data[vec->length], values, count * sizeof(T));               \
    vec->length += count;                                                      \
  }                                                                            \
  void name##_clear(name *vec) {                                               \
    LSTD_ASSERT(vec != NULL);                                                  \
    vec->length = 0;                                                           \
  }                                                                            \
  size_t name##_length(name *vec) {                                            \
    LSTD_ASSERT(vec != NULL);                                                  \
    return vec->length;                                                        \
  }                                                                            \
  size_t name##_capacity(name *vec) {                                          \
    LSTD_ASSERT(vec != NULL);                                                  \
    return vec->capacity;                                                      \
  }

#define VEC_IMPL(T, name, initial_capacity)                                    \
  DECL_VEC(T, name)                                                            \
  DEF_VEC(T, name, initial_capacity)

#define VEC_FOR_EACH(vec, elt_identifier, T, ...)                              \
  do {                                                                         \
    for (size_t i = 0; i < (vec)->length; i++) {                               \
      T *elt_identifier = &(vec)->data[i];                                     \
      __VA_ARGS__                                                              \
    }                                                                          \
  } while (0);

DECL_VEC(char *, StringVec)
DECL_VEC(u8, u8vec)

#endif // LSTD_VEC_H
