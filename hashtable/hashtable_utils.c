#include "hashtable.h"

int	__insert(const char *key, void *value, t_hashtable *self)
{
	t_entry		*e;
	unsigned long	index;

	if (!key || !value || !self)
		return (0);
	index = hti(self, key);
	if (self->lookup(key, self) != NULL)
		return (0);
	e = calloc(1, sizeof(t_entry));
	e->value = value;
	e->key = strdup(key);
	self->elements[index] = e;
	self->n_elems++;
	return (1);
}

void	*__lookup(const char *key, t_hashtable *self)
{
	t_entry		*tmp;

	if (!key || !self)
		return (NULL);
	tmp = self->elements[hti(self, key)];
	while (tmp && strncmp(key, tmp->key, 128))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

void	__remove(const char *key, t_hashtable *self)
{
	t_entry		*tmp;
	t_entry		*prev;
	unsigned long	index;

	if (!key || !self)
		return ;
	index = hti(self, key);
	tmp = self->elements[index];
	prev = NULL;
	while (tmp && strncmp(key, tmp->key, 128))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (!prev)
		self->elements[index] = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->value);
	free(tmp->key);
	free(tmp);
	self->n_elems--;
}

void	*__pull_out(const char *key, t_hashtable *self)
{
	void		*ret;
	t_entry		*tmp;
	t_entry		*prev;
	unsigned long	index;

	if (!key || !self)
		return (NULL);
	index = hti(self, key);
	tmp = self->elements[index];
	prev = NULL;
	while (tmp && strncmp(key, tmp->key, 128))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	if (!prev)
		self->elements[index] = tmp->next;
	else
		prev->next = tmp->next;
	ret = tmp->value;
	free(tmp->key);
	free(tmp);
	self->n_elems--;
	return (ret);
}

// You have to pass the destructor of the thing you
// are storing in the hashtable
void	__destroy(t_hashtable *self, void (*boom)(void *))
{
	unsigned long	i;
	t_entry		*tmp;
	t_entry		*prev;

	i = 0;
	while (i < self->size)
	{
		tmp = self->elements[i];
		while (tmp)
		{
			boom(tmp->value);
			prev = tmp;
			tmp = tmp->next;
			free(prev->key);
			free(prev);
		}
		i++;
	}
	free(self->elements);
	free(self);
}
