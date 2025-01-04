#include "-2_arraylist.h"

#include <stdbool.h>
#include <string.h>

#include "-0_allocator.h"

g_arraylist_t *g_arraylist(const size_t capacity, const size_t element_size,
                           g_allocator_t *allocator) {
  g_arraylist_t *const list = g_alloc(allocator, sizeof(g_arraylist_t));
  if (!list)
    return NULL;

  list->allocator = allocator;
  list->capacity = capacity;
  list->length = 0;
  list->element_size = element_size;
  list->data = g_alloc(allocator, capacity * element_size);
  if (!list->data) {
    g_dealloc(allocator, list);
    return NULL;
  }
  return list;
}

g_err_t g_arraylist_push(g_arraylist_t *self, const size_t count,
                         const void *data, size_t *out_first_index) {
  if (self->length + count > self->capacity) {
    const size_t new_capacity = (self->capacity * 2 > self->length + count)
                                    ? self->capacity * 2
                                    : self->length + count;
    void *const new_data = g_expand(self->allocator, self->data,
                                    new_capacity * self->element_size);
    if (!new_data)
      return true;

    self->data = new_data;
    self->capacity = new_capacity;
  }

  memcpy((char *)self->data + self->length * self->element_size, data,
         count * self->element_size);

  if (out_first_index)
    *out_first_index = self->length;
  self->length += count;
  return false;
}

void g_arraylist_set(g_arraylist_t *self, const size_t index,
                     const size_t count, const void *data) {
  memcpy((char *)self->data + index * self->element_size, data,
         count * self->element_size);
}

void g_arraylist_get(g_arraylist_t *self, const size_t index,
                     const size_t count, void *data) {
  memcpy(data, (char *)self->data + index * self->element_size,
         count * self->element_size);
}

void *g_arraylist_get_addr(g_arraylist_t *self, const size_t index) {
  return (char *)self->data + index * self->element_size;
}

void g_arraylist_remove(g_arraylist_t *self, const size_t index,
                        const size_t count) {
  void *dest = (char *)self->data + index * self->element_size;
  void *src = (char *)dest + count * self->element_size;
  const size_t bytes_to_move =
      (self->length - index - count) * self->element_size;

  memmove(dest, src, bytes_to_move);
  self->length -= count;
}

g_err_t g_arraylist_insert(g_arraylist_t *self, const size_t index,
                           const size_t count, const void *data) {
  if (self->length + count > self->capacity) {
    const size_t new_capacity = (self->capacity * 2 > self->length + count)
                                    ? self->capacity * 2
                                    : self->length + count;
    void *new_data = g_expand(self->allocator, self->data,
                              new_capacity * self->element_size);
    if (!new_data)
      return true;

    self->data = new_data;
    self->capacity = new_capacity;
  }

  void *dest = (char *)self->data + index * self->element_size;
  void *src = (char *)dest;
  const size_t bytes_to_move = (self->length - index) * self->element_size;

  memmove((char *)src + count * self->element_size, src, bytes_to_move);
  memcpy(dest, data, count * self->element_size);

  self->length += count;
  return false;
}

g_err_t g_arraylist_replace(g_arraylist_t *self, size_t index,
                            size_t count_remove, size_t count_insert,
                            const void *data_insert) {
  if (index + count_remove > self->length)
    return true;

  const size_t new_length = self->length - count_remove + count_insert;
  if (new_length > self->capacity) {
    const size_t new_capacity =
        (self->capacity * 2 > new_length) ? self->capacity * 2 : new_length;
    void *new_data = g_expand(self->allocator, self->data,
                              new_capacity * self->element_size);
    if (!new_data)
      return true;

    self->data = new_data;
    self->capacity = new_capacity;
  }

  void *remove_start = (char *)self->data + index * self->element_size;
  void *insert_end = (char *)remove_start + count_insert * self->element_size;
  void *remove_end = (char *)remove_start + count_remove * self->element_size;

  const size_t bytes_to_move =
      (self->length - index - count_remove) * self->element_size;

  memmove(insert_end, remove_end, bytes_to_move);
  memcpy(remove_start, data_insert, count_insert * self->element_size);

  self->length = new_length;
  return false;
}

g_err_t g_arraylist_shrink_to_fit(g_arraylist_t *self) {
  if (self->capacity > self->length) {
    void *new_data = g_expand(self->allocator, self->data,
                              self->length * self->element_size);
    if (!new_data && self->length > 0)
      return true;

    self->data = new_data;
    self->capacity = self->length;
  }
  return false;
}

void g_arraylist_dispose(g_arraylist_t *self) {
  g_dealloc(self->allocator, self->data);
  g_dealloc(self->allocator, self);
}
