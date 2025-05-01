#include "hashtable.h"

int	__contains(const char *key, t_hashtable *self)
{
	t_entry		*tmp;

	if (!key || !self)
		return (0);
	tmp = self->elements[hti(self, key)];
	while (tmp && strncmp(key, tmp->key, 128))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	return (1);
}

void	print_table(const t_hashtable *ht, void (*p)(void *))
{
	size_t	i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->elements[i])
			p(ht->elements[i]->value);
		i++;
	}
}

void	hashtable_foreach(const t_hashtable *ht, void (*p)(void *, void *), void *ptr)
{
	size_t	i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->elements[i])
			p(ht->elements[i], ptr);
		i++;
	}
}
