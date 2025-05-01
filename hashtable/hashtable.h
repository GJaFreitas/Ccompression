#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HTABLE_SIZE 1024

#include <string.h>
#include <stdlib.h>

typedef struct s_hashtable t_hashtable;
typedef struct s_entry t_entry;

typedef unsigned long (hashfunction)(const char *);

struct s_entry
{
	char	*key;
	void	*value;
	t_entry	*next;
};

struct s_hashtable
{
	unsigned long	size;
	unsigned long	n_elems;
	hashfunction	*hashf;
	t_entry		**elements;

	int	(*insert)(const char *key, void *value, t_hashtable *self);
	void	(*destroy)(t_hashtable *self, void (*f)(void *));
	void	(*remove)(const char *key, t_hashtable *self);
	void	*(*lookup)(const char *key, t_hashtable *self);
	int	(*contains)(const char *key, t_hashtable *self);
	void	*(*pop)(const char *key, t_hashtable *self);
};

t_hashtable	*new_hashtable(unsigned long size);
unsigned long	hti(t_hashtable *ht, const char *key);
void		print_table(const t_hashtable *ht, void (*p)(void *));
void		hashtable_foreach(const t_hashtable *ht, void (*p)(void *, void *), void *ptr);

#endif
