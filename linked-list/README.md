# Linked list

A singly linked list of `int`s (`LList`): insert and delete at either end, copy constructor, assignment operator and destructor, driven by a command file.

Lab 08, Spring 2012.

```sh
make && ./linked-list test.input
```

```
5 inserted at front of list
10 inserted at end of list
30 inserted at front of list
8 30 5 10 40
```

`test.input` holds one command per line: `I n` inserts at the front, `J n` at the end, and so on (see `Lab08app.cpp`).

**Changed in 2026:** `InsertLast` had no `return true;`. That's undefined behavior, and here it made every successful insert report "not inserted".
