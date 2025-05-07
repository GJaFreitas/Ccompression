#include "ht.h"

ht_t	*ht_new(size_t size)
{
	ht_t	*new;

	new = calloc(1, sizeof(ht_t));
	new->elems = calloc(size, sizeof(void *));
	new->size = size;
	return (new);
}

void	ht_destroy(ht_t *ht, void (*f)(void *))
{
	for (size_t i = 0; i < ht->size; i++) {
		if (ht->elems[i])
			f(ht->elems[i]);
	}
	free(ht->elems);
}

static size_t	__hf(const char *str)
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

// Transform the hash into an index
static size_t	__hf_i(const ht_t *restrict ht, const char *key)
{
	size_t	index;

	index = __hf(key) % ht->size;
	return (index);
}

int	ht_contains(const ht_t *restrict ht, const void *value, const char *key)
{
	if (!ht || (!value && !key))
		return 0;
	if (key)
		return ((unsigned long)(ht->elems[__hf_i(ht, key)]) > 0);
	for (size_t i = 0; i < ht->size; i++) {
		if (ht->elems[i] == value)
			return (1);
	}
	return (0);
}

void	*ht_get(const ht_t *restrict ht, const char *key)
{
	if (!ht || !key)
		return 0;
	return (ht->elems[__hf_i(ht, key)]);
}

void	*ht_pop(ht_t *restrict ht, void *value, const char *key)
{
	if (!ht || (!value && !key))
		return 0;
	if (key)
	{
		void	*ptr = ht->elems[__hf_i(ht, key)];
		ht->elems[__hf_i(ht, key)] = NULL;
		ht->num_elems--;
		return (ptr);
	}
	for (size_t i = 0; i < ht->size; i++) {
		if (ht->elems[i] == value)
		{
			void	*ptr = ht->elems[i];
			ht->elems[i] = NULL;
			ht->num_elems--;
			return (ptr);
		}
	}
	return (0);
}

void	ht_foreach(ht_t *restrict ht, void (*f)(void *, void *), void *p)
{
	for (size_t i = 0; i < ht->size; i++) {
		if (ht->elems[i])
			f(ht->elems[i], p);
	}
}
