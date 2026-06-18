*This project has been created as part of the 42 curriculum by lflorin.*

# push_swap

`push_swap` is a 42 school project that sorts integer input using only the allowed stack operations. The program reads numbers from command-line arguments, validates them, builds stack A, and prints the operations needed to sort stack A in ascending order.

## Usage

Compile:

```sh
make
```

Run:

```sh
./push_swap 3 2 1
```

Or with a quoted string:

```sh
./push_swap "3 2 1"
```

The program prints a sequence of operations, one per line, to sort stack A.

## Make targets

- make — build executable
- make clean — remove object files
- make fclean — remove executable and object files
- make re — fclean then make

## Project structure

- push_swap.c
- swap.c
- push.c
- rotate.c
- reverse_rotate.c
- sort_2.c
- sort_3.c
- sort_5.c
- radix.c
- radix_helper.c
- min_max.c
- lists.c
- split.c
- ft_split_spaces.c
- atoi.c
- errorhandling.c
- free.c
- helper.c
- push_swap.h
- Makefile

## Function overview (sorted like in push_swap.h)

### Lists
- ft_newlist(int content) — create a new stack node.
- ft_last(t_stack *stack) — return the last node of a stack.

### Swap
- swap(t_stack **s) — swap first two elements of stack s.
- sa(t_stack **stack_a) — swap A and print `sa`.
- sb(t_stack **stack_b) — swap B and print `sb`.
- ss(t_stack **a, t_stack **b) — swap both and print `ss`.

### Push
- push(t_stack **from, t_stack **to) — move top element from one stack to another.
- pa(t_stack **a, t_stack **b) — push top of B to A and print `pa`.
- pb(t_stack **a, t_stack **b) — push top of A to B and print `pb`.

### Rotate
- rotate(t_stack **s) — rotate stack up (first becomes last).
- ra(t_stack **a) — rotate A and print `ra`.
- rb(t_stack **b) — rotate B and print `rb`.
- rr(t_stack **a, t_stack **b) — rotate both and print `rr`.

### Reverse rotate
- reverse_rotate(t_stack **s) — rotate stack down (last becomes first).
- rra(t_stack **a) — reverse rotate A and print `rra`.
- rrb(t_stack **b) — reverse rotate B and print `rrb`.
- rrr(t_stack **a, t_stack **b) — reverse rotate both and print `rrr`.

### Helper
- ft_putstr(const char *str) — write a string to stdout.
- ft_lstsize(t_stack *lst) — return number of elements in a stack.
- is_sorted(t_stack *stack_a) — check if stack A is sorted ascending.
- duplicate_check(t_stack *stack_a, long value) — check for duplicates.
- ft_strlen(char *str) — return string length.

### Atoi / parsing
- ft_atol(char *str) — convert string to long with sign handling.

### Error handling
- error(void) — print `Error` to stderr and return error code.
- is_valid_input(char *string) — validate integer token format.

### Min/Max
- get_min(t_stack *stack_a) — return node with minimum value.
- get_max(t_stack *stack_a) — return node with maximum value.

### Split / input processing
- ft_split_spaces(char *str) — split a string by spaces into tokens.
- process_token(char *token, t_stack **stack_a) — validate token, convert, check duplicates, append to stack A.
- free_split(char **split) — free split array.
- ft_substr(const char *s, unsigned int start, size_t len) — substring helper.
- ft_strdup(const char *s1) — duplicate a string.

### Sorting helpers
- sort_2(t_stack **stack_a) — sort two elements.
- sort_3(t_stack **stack_a) — sort three elements with minimal ops.
- sort_5(t_stack **stack_a, t_stack **stack_b) — sort up to five elements using B.
- sort_5_helper(t_stack **stack_a) — helper to position small elements.

### Radix helpers
- find_index(int *sorted, int size, int value) — find value index in sorted array.
- sort_int_array(int *array, int size) — sort array for index assignment.
- assign_indexes(t_stack *stack_a) — assign ranks to values for radix.
- get_max_amount_bits(t_stack *stack_a) — compute bits needed for radix.

### Radix
- radix_sort(t_stack **stack_a, t_stack **stack_b) — sort larger stacks using binary radix on indexes.

### Free
- free_all(t_stack **stack) — free all nodes in a stack.

### push_swap (main flow)
- handle_tokens(char **tokens, t_stack **stack_a) — parse tokens and add to stack A.
- parse_arguments(int argc, char **argv, t_stack **stack_a) — handle argv and quoted strings.
- init_stacks(t_stack **stack_a, t_stack **stack_b) — initialize stack pointers.
- calling_function(t_stack **stack_a, t_stack **stack_b) — select sorting algorithm based on size.
- main(int argc, char **argv) — entry point: parse, sort, free.
