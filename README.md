What's qLibc?
=============

The goal of qLibc project is to provide a **simple but powerful general purpose C/C++ library** which includes all kinds of containers and general library routines. It provides ready-made set of common container APIs with constant look that can be used with any built-in types and with any user-defined types.

## qLibc Copyright

All of the deliverable code in qLibc has been dedicated to the public domain by the authors. Anyone is free to copy, modify, publish, use, compile, sell, or distribute the original qLibc code, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means. 

## API Reference

* [qlibc Core API Reference](http://wolkykim.github.io/qlibc/doc/qlibc/files.html)
  * Containers
    * List --- Doubly Linked List.
    * List Table --- KEY/VALUE paired table implemented on linked-list.
    * Hash Table --- Hash based KEY/VALUE paired table.
    * Static Hash Table --- Static(array/mmapped/shared) memory based KEY/VALUE paired table.
    * Vector --- implements a growable array of elements.
    * Queue --- FIFO(First In First Out) implementation.
    * Stack --- LIFO(Last In First Out) implementation.
  * General utilities.
    * String
    * I/O
    * File
    * IPC, Semaphore Shared-memory
    * En/decoders
    * Hashes
    * System
    * Time

* [qLibc Extension API Reference](http://wolkykim.github.io/qlibc/doc/qlibcext/files.html)
  * INI-style Configuration File Parser.
  * Apache-style Configuration File Parser.
  * Rotating File Logger.
  * HTTP client.
  * Database(MySQL) interface.

## Constant Look

All container APIs have constant look, basically it provides a creator function which usually returns a pointer of a container structure. And **every functions related to the container can be accessed through function pointers inside of the container**.

So regardless of what container you use, you can simple put elements into list like pContainer->put(pContainer, ...). It looks like C++ class but it's pure C implementation. Of course it works with both of your C and C++ codes**.

We used this concept as much as possible because it simplifies the thinking way and helps to improve readability. Consequently it helps people to write bugless codes more easily.
 
See the example below to see how it works.

```
  // create a hash-table with hash range 100.
  // Hash range does NOT mean maximum number of elements. Refer API doc.
  qhashtbl_t *tbl = qhashtbl(100);
  
  // add an element which key name is "score".
  int x = 12345;
  tbl->put(tbl, "score", &x, sizeof(int));
  
  // get the value of the element.
  int *px = tbl->get(tbl, "score", NULL, true);
  if(px != NULL) {
    printf("%d\n", *px);
    free(px);
  }
  
  // release table
  tbl->free(tbl);
```

Here is an identical implementation with Linked-List-Table container. You might noticed that there's not much code change entirely on switching the container type.

```
  // create a linked-list-table.
  qlisttbl_t *tbl = qlisttbl();
  
  // add an element which key name is "score".
  int x = 12345;
  tbl->put(tbl, "score", &x, sizeof(int), true);
  
  // get the value of the element.
  int *px = tbl->get(tbl, "score", NULL, true);
  if(px != NULL) {
    printf("%d\n", *px);             
    free(px);
  }
  
  // release table
  tbl->free(tbl);
```