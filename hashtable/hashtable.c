#include "hashtable.h"

size_t	__count_elems(t_hashtable *ht);
int	__insert(const char *key, void *value, t_hashtable *self);
void	*__lookup(const char *key, t_hashtable *self);
void	__remove(const char *key, t_hashtable *self);
void	*__pull_out(const char *key, t_hashtable *self);
void	__destroy(t_hashtable *self, void (*boom)(void *));
int	__contains(const char *key, t_hashtable *self);

// No this isnt an iterator its the hashtable index
unsigned long	hti(t_hashtable *ht, const char *key)
{
	unsigned long	index;

	index = ht->hashf(key) % ht->size;
	return (index);
}

static unsigned long	hf(const char *str)
{
	unsigned long	hash;
	int		i;
        int 		c;

	hash = 5381;
	i = 0;
	c = str[i++];
	while (c)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		c = str[i++];
	}
        return (hash);
}

// Creates a new instance of a hashtable with size elements
t_hashtable	*new_hashtable(unsigned long size)
{
	t_hashtable	*table;

	table = calloc(1, sizeof(t_hashtable));
	table->hashf = hf;
	table->size = size;
	table->elements = calloc(1, sizeof(t_entry *) * size);
	table->insert = __insert;
	table->lookup = __lookup;
	table->contains = __contains;
	table->pop = __pull_out;
	table->remove = __remove;
	table->destroy = __destroy;
	return (table);
}
