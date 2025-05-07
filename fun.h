#ifndef COMPRESS_H
# define COMPRESS_H

#include "ht/ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFF_SIZE	2048

typedef struct	s_file_info
{
	char	*str;
	size_t	size;
}	t_file;

typedef struct	s_pair
{
	char	c[3];
	size_t	n;
	unsigned char	compressed;
}	Pair;

void	print_usage(void);
int	input_file_exists(char *input, int *);
size_t	read_whole_file(int fd, char **buf, size_t *buf_size);
ht_t	*create_freq_table(t_file input);
size_t	getPairsFromTable(ht_t *ht, Pair ***origin);
void	write_table_to_file(void *elem, void *fd);


void	destroy(ht_t *self, void (*boom)(void *));

#endif //COMPRESS_H
