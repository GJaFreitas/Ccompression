#include "../fun.h"
#include <fcntl.h>
#include <string.h>

/*
 *
 *	The objective here is to compress all strings given in this way:
 *
 *	aabcdaaacd
 *
 *	> 1bcd1acd
 *	> 1b21a2
 *
 *	with normal text it looks like this:
 *
 *	Hey there how are you doing?
 *
 *	Hey there how are you doing?
 *	1y t1re how are you doing?
 *
 *	Hey there how are you doing?
 *	1y t12 how a2 you doing?
 *
 *	A tB Cw D yE FGH
 *
 */


// Substitute the current char with its compressed pair form and then move the array back
void	substitute(Pair *pair, t_file *out, size_t j)
{
	out->str[j++] = pair->compressed;
	out->size--;
	memmove(&out->str[j], &out->str[j+1], out->size);
}

#define PairFound(in, pair, i) (!strncmp(&in->str[i], pair->c, 2))
#define PairNotSubbed(out, in, i, j) (in->str[i] == out->str[j])

// When pairSearch gets called the second time the strings are
// not alligned anymore, i need to account for that
void	pairSearch(t_file *in, t_file *out, Pair *pair)
{
	if (!in->str[0] || !in->str[1] || !in->str[2]) return ;

	for (size_t i = 0, j = 0; i < in->size-2; i++, j++) {

		if (PairFound(in, pair, i)) {
			if (PairNotSubbed(out, in, i, j))
				substitute(pair, out, j);
			i++;
		}

	}
}

char	*compress(t_file in, int fd_out)
{
	t_hashtable	*freqTable = create_freq_table(in);
	Pair	**pairs;
	t_file	*out = calloc(1, sizeof(t_file));
	size_t	num_pairs = getPairsFromTable(freqTable, &pairs);

	out = memcpy(out, &in, sizeof(t_file));

	for (size_t i = 1; i < 127 && i < num_pairs; i++) {
		pairs[i]->compressed = i;
		pairSearch(&in, out, pairs[i]);
	}

	hashtable_foreach(freqTable, write_table_to_file, &fd_out);

	return (out->str);
}

int	main(int argc, char **argv)
{
	int	input_fd;
	int	output_fd;

	if (argc < 2) { print_usage(); return 0; }
	if (!input_file_exists(argv[1], &input_fd)) return 0;

	output_fd = open(argv[2], O_CREAT);

	t_file	in;
	if (!read_whole_file(input_fd, &in.str, &in.size)) { printf("Empty input\n"); return 0; }

	char	*output = NULL;
	size_t	len = strlen(in.str);
	size_t	before = len;
	size_t	out_len;
	for (size_t i = 0; ; i++) {
		if (!output)
			output = compress(in, output_fd);
		else
			output = compress((t_file) {output, out_len}, output_fd);

		out_len = strlen(output);
		if (len == out_len)
			break ;
		printf("Iteration: %ld\nBefore: %ld	After: %ld\nGain: %ld\n\n", i, len, out_len, len - out_len);
		len = out_len;
	}

	printf("Total compression %ld bytes from a %ld byte file\nFinal size: %ld bytes\n", before - len, before, len);

	return (0);
}
