#include "../fun.h"

void	getPair(char *str, size_t i, Pair *pair)
{
	pair->c[0] = str[i];
	pair->c[1] = str[i+1];
}

void	printPair(void *ptr)
{
	Pair	*pair = ptr;

	printf("Pair: %s   Freq: %ld\n", pair->c, pair->n);
}

// Creates a frequency table of Pairs that exist in the file
// and how many times they appear
ht_t	*create_freq_table(t_file input)
{
	ht_t	*table = ht_new(10000);
	Pair	*table_pair;
	Pair	current;
	Pair	*temp;

	// += 2 since we are analyzing pairs
	for (size_t i = 0; i < input.size - 1; i += 2) {
		getPair(input.str, i, &current);
		if (ht_contains(table, NULL, current.c)) {
			// If the current pair already exists in the table:
			// increment the counter on the pair
			temp = ht_get(table, current.c);
			temp->n++;
		} else {
			// If the current pair doesnt exist in the table:
			// Increment the counter (to 1) and add it
			table_pair = calloc(1, sizeof(Pair));
			table_pair->c[0] = current.c[0];
			table_pair->c[1] = current.c[1];
			table_pair->n++;
			ht_insert(table, table_pair, table_pair->c);
		}
	}
	// print_table(table, printPair);
	return (table);
}

static int	__compare_pair(const void *pair1, const void *pair2)
{
	return ((*(Pair **)pair1)->n < (*(Pair **)pair2)->n);
}

// Returns an array of Pair * that is ordered from most occuring to least
// All pairs that occur only twice or less get removed
size_t	getPairsFromTable(ht_t *ht, Pair ***origin)
{
	Pair	**pairs;
	size_t	n = 0;

	pairs = calloc(ht->num_elems + 1, sizeof(Pair *));
	for (size_t i = 0; i < ht->size; i++) {
		if (ht->elems[i]) {
			if (((Pair *)(ht->elems[i]))->n > 2) 
				pairs[n++] = (void*)ht->elems[i];
			else {
				// If there were only 2 or less pairs of a certain type
				// the algo that im using wouldnt gain a single byte,
				// as such they dont need to be considered
				free(ht_pop(ht, NULL, ((Pair *)(ht->elems[i]))->c));
			}
		}
	}
	// Huge leaks here somehow???
	pairs = realloc(pairs, (n + 1) * sizeof(Pair *));

	qsort(pairs, n, sizeof(Pair *), __compare_pair);

	pairs[n] = 0;
	*origin = pairs;
	return (n);
}

// TODO: This is not working for some reason
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

	write(fd, str, 4);
}
