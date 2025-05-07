#ifndef HT_T
# define HT_T

#include <stdlib.h>
#include <stdint.h>

typedef struct s_ht
{
	size_t	size;
	size_t	num_elems;
	void	**elems;
}	ht_t;

// Creates a new instance of a hashtable that can take size values
ht_t	*ht_new(size_t size);

// Frees all memory from the hashtable and applies 'f' to all elements;
// f should be a funtion to free an element
void	ht_destroy(ht_t *restrict, void (*f)(void *));

// Can search both by value or key;
// Search by value O(n)
// Search by key O(1)
int	ht_contains(const ht_t *restrict, const void *value, const char *key);

// Returns the pointer associated with 'key'
void	*ht_get(const ht_t *restrict, const char *key);

// Can pop both by value or key;
// Pop by value O(n)
// Pop by key O(1)
void	*ht_pop(ht_t *restrict, void *value, const char *key);

// Insert a new element in the table
int	ht_insert(ht_t *restrict, void *value, const char *key);

// Executes the functin f in every element of the hastable
// first void * is the element, second is passed by user
void	ht_foreach(ht_t *restrict, void (*f)(void *, void *), void *);

#endif // HT_T
