#include "../fun.h"

// My retarded self made all hashtable functions like this:
// foo(..., hashtable *self)
// so yeah its the last parameter

void	getPair(char *str, size_t i, Pair *pair)
{
	pair->c[0] = str[i];
	pair->c[1] = str[i+1];
	pair->c[2] = 0;
}

void	printPair(void *ptr)
{
	Pair	*pair = ptr;

	printf("Pair: %s   Freq: %ld\n", pair->c, pair->n);
}

// if Pair already exists:
// 	pop the value and update n
// else
// 	insert value with n = 1
t_hashtable	*create_freq_table(t_file input)
{
	t_hashtable	*table = new_hashtable(10000);
	Pair	*current;
	Pair	*temp;

	for (size_t i = 0; i < input.size - 1; i++) {
		current = calloc(1, sizeof(Pair));
		getPair(input.str, i, current);
		if (table->contains(current->c, table)) {
			temp = table->lookup(current->c, table);
			temp->n++;
			free(current);
		} else {
			current->n++;
			table->insert(current->c, current, table);
		}
		i++;
	}
	return (table);
}

static int	__compare_pair(const void *pair1, const void *pair2)
{
	return ((*(Pair **)pair1)->n < (*(Pair **)pair2)->n);
}

// Returns an array of Pair * that is ordered from most occuring to least
// All pairs that occur only once get removed since the line needed for no info loss
// will occupy more size than a pair by itself
size_t	getPairsFromTable(t_hashtable *ht, Pair ***origin)
{
	Pair	**pairs;
	size_t	n = 0;

	pairs = calloc(ht->n_elems + 1, sizeof(Pair *));
	for (size_t i = 0; i < ht->size; i++) {
		if (ht->elements[i]) {
			if (((Pair *)(ht->elements[i]->value))->n > 1) 
				pairs[n++] = ht->elements[i]->value;
			else {
				ht->remove(((Pair *)(ht->elements[i]->value))->c, ht);
			}

		}
	}
	pairs = realloc(pairs, (n + 1) * sizeof(Pair *));

	qsort(pairs, n, sizeof(Pair *), __compare_pair);

	pairs[n] = 0;
	*origin = pairs;
	return (n);
}

// Todo: This is not working for some reason
// do i remember how to use write()???
void	write_table_to_file(void *value, void *fd_ptr)
{
	Pair	*pair = value;
	int	fd = *(int *)fd_ptr;

	char	str[4];
	str[0] = pair->c[0];
	str[1] = pair->c[1];
	str[2] = pair->compressed;
	str[3] = '\n';

	printf("pair: %s\n", pair->c);

	write(fd, str, 4);
}
