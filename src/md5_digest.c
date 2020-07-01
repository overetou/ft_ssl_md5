#include "ft_ssl.h"

void	md5_init_hash(unsigned int *h)
{
	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
}

void	set_round_shift_table(unsigned char **r)
{
	*r = secure_malloc(64);
	char table[] = {	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
						5,  9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
						4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
						6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	memcopy((char*)(*r), (char*)table, 64);
}

unsigned int	left_rotate(unsigned int n, unsigned long times)
{
	// printf("x = %u, times = %lu\n", n, times);
	return ((n << times % 32) | (n >> (32 - times % 32)));
}

void	print_deca(const unsigned char *data, unsigned long size)
{
	unsigned long	i;

	i = 0;
	while (i != size)
	{
		printf("%x ", data[i]);
		i++;
	}
	puts("");
}

void	set_end_bits_len(unsigned char *adr, unsigned long val)
{
	int i;
	int	j;
	unsigned char	*vals;

	i = 7;
	j = 0;
	vals = (unsigned char*)(&val);
	while (i >= 0)
	{
		adr[i] = vals[j];
		i--;
		j++;
	}
}

unsigned char	*md5_digest(const char *input)
{
	t_md5_data	data;
	unsigned char	*round_shift_amount;
	unsigned int	*h = secure_malloc(sizeof(int) * 4);
	// printf("allocated h with a size of %ld bits\n", sizeof(long) * 4 * 8);
	unsigned int	f, g;
	unsigned char	*w;
	unsigned int k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	data.initial_len = str_len(input);
	if (64 - data.initial_len % 64 > 8)
		data.full_len = data.initial_len + 64 - (data.initial_len % 64);
	else
		data.full_len = data.initial_len + (64 - (data.initial_len + 8) % 64);
	// printf("initial length: %ld bits.\nAllocated length: %ld bits. Alloc_len %% 512 = %ld bits\n"
	// , data.initial_len * 8, data.full_len * 8, (data.full_len * 8) % 512);

	data.full_msg = secure_malloc(data.full_len);
	memcopy((char*)(data.full_msg), input, data.initial_len);
	data.full_msg[data.initial_len] = 128;
	// printf("allocated len in bytes: %lu, initial len: %lu we b_zero: %lu bytes\n", data.full_len, data.initial_len, data.full_len - data.initial_len);
	b_zero(data.full_msg + data.initial_len + 1, data.full_len - data.initial_len - 9);
	data.initial_len *= 8;
	memcopy((char*)(data.full_msg) + data.full_len - 8, (char*)(&(data.initial_len)), 8);
	// print_deca(data.full_msg, data.full_len);
	set_round_shift_table(&round_shift_amount);
	md5_init_hash(h);
	data.bloc_pos = 0;
	while (data.bloc_pos != data.full_len)
	{
		w = data.full_msg + data.bloc_pos;
		data.word_pos = 0;
		data.A = h[0];
		data.B = h[1];
		data.C = h[2];
		data.D = h[3];
		while (data.word_pos != 64)//wordpos is in bits!!
		{
			if (data.word_pos < 16)
			{
				// printf("input : B=%x, C=%x, D=%x\n", data.B, data.C, data.D);
				f = (data.B & data.C) | ((~data.B) & data.D);
				g = data.word_pos;
			}
			else if (data.word_pos < 32)
			{
				f = (data.B & data.D) | (data.C & (~(data.D)));
				g = (5 * data.word_pos + 1) % 16;
			}
			else if (data.word_pos < 48)
			{
				f = data.B ^ data.C ^ data.D;
				g = (3 * data.word_pos + 5) % 16;
			}
			else
			{
				f = data.C ^ (data.B | (~data.D));
				g = (7 * data.word_pos) % 16;
			}
			data.temp = data.D;
			data.D = data.C;
			data.C = data.B;
			data.B = data.B + left_rotate(data.A + f + k[data.word_pos] + *(((unsigned int*)w) + g), round_shift_amount[data.word_pos]);
			data.A = data.temp;
			// if (data.word_pos == 48)
			// {
			// 	printf("f = %u, g = %u, k[i] = %u, w[g] = %u, round_shift = %u\n", f, g, (unsigned int)(k[data.word_pos]),
			// 	*(((unsigned int*)w) + g), round_shift_amount[data.word_pos]);
			// 	printf("A=%x, B=%x, C=%x, D=%x\n", data.A, data.B, data.C, data.D);
			// 	exit(0);
			// }
			(data.word_pos)++;
		}
		h[0] += data.A;
		h[1] += data.B;
		h[2] += data.C;
		h[3] += data.D;
		data.bloc_pos += 64;
	}
	// printf("%x\n", h[0]);
	// printf("%x\n", h[1]);
	// printf("%x\n", h[2]);
	// printf("%x\n", h[3]);
	free(data.full_msg);
	free(round_shift_amount);
	return((unsigned char*)h);
}
