#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static uint8_t MEMORY_POOL[64];

struct free_entry {
  void *ptr;
  uint64_t size;      //  Size of hole
};

typedef struct free_entry free_entry_t;

static free_entry_t FREE_LIST[64] = {
  (free_entry_t){
    .ptr = MEMORY_POOL,
    .size = 64,
  },
};

static uint64_t FREE_LIST_USED = 1;

//  size: 64-bit unsigned
void print_free_list() {
printf("FREE LIST:\n");

  for (uint64_t i=0; i<FREE_LIST_USED; i++) {
    free_entry_t *entry;
    entry = &FREE_LIST[i];

    printf("  %p (%llu)\n", entry->ptr, entry->size);
  }

}

//  Iterate through the 'free_entry' and 
//  find the first entry that is big enough to hold our allocation.
//  Then, return an entry

//  Loop through all of the entries and 
//  stick the best entry here!
free_entry_t *find_free_entry(size_t size) {

  // Trick here is that 
  // we can treat 'FREE_LIST' like a pointer (memory address)
  free_entry_t *best_entry = FREE_LIST;

  for (uint64_t i=0; i<FREE_LIST_USED; i++) {
    free_entry_t *entry;
    entry = &FREE_LIST[i];

    if (entry->size >= size && entry->size < best_entry->size) {
      best_entry = entry;
    }
  }

  return best_entry;
}


// uint64_t *malloc(uint64_t size) {
void *malloc(size_t size) {
  size +=8;

  free_entry_t *entry;
  entry = find_free_entry(size);

  void *base_ptr;
  uint64_t *size_ptr;   // Memory address
  void *user_ptr;

  base_ptr = entry->ptr;
  size_ptr = base_ptr;
  user_ptr = base_ptr + 8;

  *size_ptr = size;

  entry->ptr += size;
  entry->size -= size;
  
  print_free_list();

  return user_ptr;
}


void free(void *user_ptr) {
  free_entry_t *entry;

  entry = &FREE_LIST[FREE_LIST_USED];

  void *base_ptr;
  uint64_t *size_ptr;
  uint64_t size;

  base_ptr = user_ptr - 8;
  size_ptr = base_ptr;

  //  Read size from memory address of (size_ptr)
  size = *size_ptr;

  entry->ptr = base_ptr;
  entry->size = size;

  FREE_LIST_USED++;
  
  printf("FREE\n");
  print_free_list();
}


int main() {

  print_free_list();

  char *a;
  char *b;
  char *c;
  char *d;

  //  Allcate 4 bytes
  a = malloc(4);
  b = malloc(4);
  c = malloc(4);

  //  Terminated by null character
  //  0 byte indicates the end.
  strcpy(a, "foo\0");
  strcpy(b, "bar\0");
  strcpy(c, "baz\0");

  printf("%p\n", a);
  printf("%p\n", b);
  printf("%p\n", c);

  free(b);

  //  Since the memory allocation of 'b' was freed,
  //  d will have the same memory address of 'b'.
  d = malloc(4);
  

  printf("%p\n", d);


}