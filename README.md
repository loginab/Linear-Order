Linear-Order
============
Implemention of a structure that maintains a linear order.
The structure supports the following operations:-
- o_t * create_order() creates an empty linear ordered set
- void insert_before(o_t *ord, key_t a, key_t b) inserts the key a immediately before key b in the ordered set.
- void insert_after(o_t *ord, key_t a, key_t b) inserts the key a immediately after key b in the ordered set.
- void insert_top(o_t *ord, key_t a) inserts the key a as largest element in the ordered set 
- void insert_bottom(o_t *ord, key_t a) inserts the key a as smallest element in the ordered set
- void delete_o(o_t *ord, key_t a) deletes the key a from the ordered set
- int is_before(o_t *ord, key_t a, key_t b) returns 1 if key a occurs before key b in the ordered set, 0 else.
Here key_t is a number type that allows comparisons.
=======================================================================================================================
