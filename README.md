# Implementing memory allocators from scatch

The goal of this mini-project was to implement a simple memory allocator.

It implements <a href="http://man7.org/linux/man-pages/man3/free.3.html">malloc()</a> and <a href="http://man7.org/linux/man-pages/man3/free.3.html">free()</a>.

#### Compile and Run ####
```
gcc malloc.c -o malloc && ./malloc
```

#### Constraints ####

The implementation has a huge constraint:
- This implementation wastes a lot of memory and time.

The other constraints are: 
1. Only has a 64-byte memory pool
2. Has fixed size free list

But the implementation works.

The modern malloc has much more complex data structures, more metadata, coalescing adjacent blocks , etc. but the underlined ideas are similar.

Questions to dive: 
1. Where does the malloc comes from in the real malloc?
2. Where does the memory allocator gets its memory? -> Take a look at 'man brk' and 'man sbrk'.


#### References ####
- [Malloc tutorial](https://danluu.com/malloc-tutorial/)

- [Implementing malloc and free](https://medium.com/@andrestc/implementing-malloc-and-free-ba7e7704a473)

- [How to write your own Malloc and Free using C?](http://tharikasblogs.blogspot.com/p/how-to-write-your-own-malloc-and-free.html)

- [C Programming/stdlib.h/malloc](https://en.wikibooks.org/wiki/C_Programming/stdlib.h/malloc)

- [Memory Allocators 101 - Write a simple memory allocator](https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory)