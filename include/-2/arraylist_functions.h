#ifndef G_2_ARRAYLIST_FUNCTIONS_H
#define G_2_ARRAYLIST_FUNCTIONS_H

#ifdef __cplusplus
#include <cstddef.h>
#else
#include <stddef.h>
#endif

#include "-0/allocator_types.h"
#include "-0_common.h"

#include "arraylist_types.h"

#ifdef __cplusplus
extern "C" {
#endif

g_2_arraylist_t *g_2_arraylist(size_t capacity, size_t element_size,
                               g_0_allocator_t *allocator);

g_err_t g_2_arraylist_push(g_2_arraylist_t *self, size_t count,
                           const void *data, size_t *out_first_index);

void g_2_arraylist_set(g_2_arraylist_t *self, size_t index, size_t count,
                       const void *data);

void g_2_arraylist_get(g_2_arraylist_t *self, size_t index, size_t count,
                       void *data);

void *g_2_arraylist_get_addr(g_2_arraylist_t *self, size_t index);

void g_2_arraylist_remove(g_2_arraylist_t *self, size_t index, size_t count);

g_err_t g_2_arraylist_insert(g_2_arraylist_t *self, size_t index, size_t count,
                             const void *data);

g_err_t g_2_arraylist_replace(g_2_arraylist_t *self, size_t index,
                              size_t count_remove, size_t count_insert,
                              const void *data_insert);

g_err_t g_2_arraylist_shrink_to_fit(g_2_arraylist_t *self);

void g_2_arraylist_dispose(g_2_arraylist_t *self);

#ifdef __cplusplus
}
#endif

#endif
