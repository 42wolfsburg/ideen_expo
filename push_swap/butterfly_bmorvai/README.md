*This project has been created as part of the 42 curriculum by bmorvai.*

---

## Description

This project implements a sorting algorithm using two stacks and a limited set of operations. The goal is to sort a stack of integers with the minimum number of moves.

Development began with the fundamental building blocks: implementing the stacks and all operations capable of pushing elements between them. From this simple mechanic, everything else emerged.

After coding the operations, the stack initialization system was built — taking command-line arguments, converting them to integers, and validating them. A dedicated checker handles all error cases: duplicates, integer overflow, and non-numeric input.

## Operations

As per the concept of linked lists, the nodes point to each other, except the last node of the list which points to null. Exploiting this we are able to sever or make ties on demand enabling us to execute our operations. 


---

## Algorithm — Butterfly Sort

A lesser-known method, studied from the work of a fellow student and through a Russian YouTube video with auto-generated subtitles, which presented its own unique challenges.

The unsorted data is first **indexed** by value. A sliding **range window** — sized according to the total dataset — then targets elements for pushing to stack B. The push counter increases with each push.

The crux of the method: elements with an index equal to or below the current push count are pushed *and rotated* to the far side of index 0, while elements slightly above (the margin determined by dataset size, see `chunk_size`) are pushed without rotation. Index 0 becomes an origin point — a cornerstone — and through statistical tendency, the data in stack B forms two wings around it: a butterfly.

Since maximum values always cluster near the edges of the wings, locating them and pushing them back to stack A is a low-cost operation that reconstructs the stack in ascending order.

# Algorithm — Sort Small
 
Integer stacks up to size five receive different treatment. An algorithm hardcoded on their relative positions takes care of their sorting.
 
Sort two is self-explanatory and needs no further discussion.
 
---
 
**sort_3** is the root of this mechanism. It uses a doubly-branching structure — depending on the relative value of the first element, a subfunction is called, which then calls another subfunction determined by the relative positions of the remaining two nodes.
 
At any given moment one of the three numbers will be the lowest, the middle, and the highest ranking.
 
**First element is lowest:**
Two cases. If the following two are in order, the stack is already sorted — nothing to do. Otherwise the first element is pushed to B, the remaining two are rotated into order, and it is pushed back.
 
**First element is middle:**
Two cases. In the first (middle, low, high), middle and low are pushed to B where they are rotated — middle ends up on top and is available to be pushed back to its proper position, with low following after. In the second case (middle, high, low), a single reverse rotation brings low to the top and the stack is sorted.
 
**First element is highest:**
Two cases. If highest is followed by low then middle, a single rotation moves highest to the back and the stack is sorted. If highest is followed by middle then low (the fully reversed stack), highest is pushed to B, A is rotated to bring low to the top, highest is pushed back, and a final rotation places it correctly.
 
---
 
**sort_4** and **sort_5** both reduce to sort_3. The one or two minimum elements are located, rotated to the top, and pushed to B. Once the remaining three are sorted via sort_3, the minimums are pushed back to their rightful place at the top of the stack.
 


---

## Instructions
Construction:

```bash
make
./push_swap 3 1 2 5 4
./push_swap "3 1 2 5 4"
```

Checking sortedness and operation count:
```bash
ARG="15 77 85 3 9 4 6"; ./push_swap $ARG | ./checker_linux $ARG
ARG="15 77 85 3 9 4 6"; ./push_swap $ARG | wc -l
```

---

## Resources

- [gannemar — Russian language explanation](https://www.youtube.com/watch?v=GA9aKzl86nA&t=220s) *(auto-subtitled)*
- yyakuben — assistance with clarifying the algorithm
- Claude AI — assistance with concepts and implementation

---
