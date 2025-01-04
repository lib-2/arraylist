#ifndef G_2_ARRAYLIST_TYPES_H
#define G_2_ARRAYLIST_TYPES_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#include "-0/allocator_types.h"

typedef struct g_2_arraylist {
  g_0_allocator_t *allocator;
  size_t capacity;
  size_t length;
  size_t element_size;
  void *data;
} g_2_arraylist_t;

#endif
