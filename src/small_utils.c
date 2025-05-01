#include "../fun.h"

void	print_usage(void)
{
	printf("Usage: ./compress <input file>\n");
}

int	input_file_exists(char *input, int *input_fd)
{
	*input_fd = open(input, O_RDONLY);
	if (*input_fd == -1) { fprintf(stderr, "Couldnt open %s\n", input); return 0; }

	return (1);
}

// If the buffer is still BUFF_SIZE then keep it like that
// else return half of it. Why? Because this:
// 1st iteration -> bufsize = 2048 >> reads in 2048
// 2nd iteration -> bufsize = 4096 >> reads in 2048
// 3rd iteration -> bufsize = 8192 >> reads in 4096
// This way the buffer is always full
#define bufferLeft(s) ((s == BUFF_SIZE) ? (s) : (s / 2))

// Reads everything in a file until EOF into buf, returns bytes read
// buf will get allocated here
size_t	read_whole_file(int fd, char **buf, size_t *buf_size)
{
	char	*temp;
	size_t	size_temp = BUFF_SIZE, already_read = 0;
	size_t	n = 0;

	temp = malloc(size_temp);
	while ((n = read(fd, temp + already_read, bufferLeft(size_temp))) != 0) {
		already_read += n;
		if (already_read < size_temp)
			break ;
		size_temp *= 2;
		temp = realloc(temp, size_temp);
	}
	already_read += n;
	*buf = realloc(temp, already_read);
	*buf_size = already_read;
	return (already_read);
}
