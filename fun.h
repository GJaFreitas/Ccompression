#ifndef COMPRESS_H
# define COMPRESS_H

#include "hashtable/hashtable.h"
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
t_hashtable	*create_freq_table(t_file input);
size_t	getPairsFromTable(t_hashtable *ht, Pair ***origin);
void	write_table_to_file(void *elem, void *fd);

#endif //COMPRESS_H
