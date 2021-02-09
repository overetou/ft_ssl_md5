/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: overetou <overetou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 18:07:38 by overetou          #+#    #+#             */
/*   Updated: 2021/01/29 15:19:56 by overetou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BOOL char
# define BUFF_MAX_SIZE 1048576

typedef struct		s_command
{
	char			*name;
	void			(*exec)(void*);
}					t_command;

typedef struct		s_master
{
	char			**argv;
	char			buffer[BUFF_MAX_SIZE];
	char			*stdin_string;
	char			*direct_string;
	int				argc;
	int				arg_pos;
	int				buff_pos;
	long long		buff_max;
	int				command_number;
	int				param_choice_number;
	int				final_funcs_number;
	t_command		*commands;
	t_command		*param_choice;
	BOOL			still_reading_args;
	BOOL			reverse_enabled;
	BOOL			quiet_enabled;
	BOOL			p_enabled;
	BOOL			s_enabled;
	char			**files_to_hash;
	int				files_to_hash_nb;
	void			(**final_exec_funcs)(struct s_master*);
	unsigned char	*(*digest)(const char*, unsigned long long);
	unsigned long long	msg_len;
}					t_master;

typedef struct		s_md5_data
{
	unsigned char	*full_msg;
	unsigned int	bloc_pos;
	unsigned int	word_pos;
	unsigned long long	initial_len;
	unsigned long long	full_len;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	unsigned long long	temp;
	unsigned char	round_shift_nb[64];
	unsigned int	*h;
	unsigned int	f;
	unsigned int	g;
	unsigned char	*w;
	unsigned int	k[64];
}					t_md5_data;

/* typedef struct		s_sha_data
{
	unsigned char	*full_msg;
	unsigned int	bloc_pos;
	unsigned int	word_pos;
	unsigned long long	initial_len;
	unsigned long long	full_len;
	unsigned int	a[8];
	unsigned int	*h;
	unsigned int	w[64];
	unsigned int	constants[64];
}					t_sha_data; */

typedef struct	s_sha_data
{
	unsigned long long	msg_len;
	unsigned long long	full_len;
	unsigned char	*blocks;
	unsigned int	*h;
	unsigned int	konstants[64];
}				t_sha_data;

void				putstr(const char *s);
char				*alloc_str(const char *content);
void				error_msg(const char *msg);
BOOL				str_cmp(const char *s1, const char *s2);
void				*secure_malloc(long size);
void				*secure_realloc(void *ptr, unsigned long ptr_size, unsigned long size);
void				command_add(const int command_index, t_command *commands,
const				char *command_name, void (*exec)(void *master));
void				free_commands(t_command *commands, int command_number);
BOOL				try_to_exec_command(t_master *m, const char *try_name);
void				md5_exec(void *master);
void				md5_p_exec(void *m);
void				q_exec(void *m);
void				r_exec(void *m);
void				md5_s_exec(void *m);
void				md5_execute_loaded(t_master *m);
void				load_stdin(t_master *m);
void				memcopy(char *dest, const char *src, int size);
void				add_final_exec_func(t_master *m,
void (*f)(struct s_master*));
void				md5_p_final_exec(t_master *m);
void				md5_s_final_exec(t_master *m);
unsigned int		str_len(const char *s);
void				b_zero(void *s, int len);
void				disp_sum(unsigned char *s, int size);
unsigned char		*md5_digest(const char *input, unsigned long long msg_len);
void				load_file(t_master *m, int fd, char **to_fill);
void				add_file_hash_task(t_master *m, char *file_name);
void				exec_file_hash(t_master *m, char *file_name);
unsigned int		left_rotate(unsigned int n, unsigned long times);
void				md5_set_k(unsigned int *to_set);
void				md5_init_hash(unsigned int *h);
void				set_round_shift_table(unsigned char *r);
void				md5_digest_init(t_md5_data *data, const char *input, unsigned long long l);
void				sha256_exec(void *master);
void				sha256_p_exec(void *m);
void				sha256_s_exec(void *m);
void				exec_files_hash_and_funcs(t_master *m);
void				exec_final_funcs(t_master *m);
unsigned char		*sha256_digest(const char *msg, unsigned long long msg_len);
void				parse_args(t_master *m);
unsigned int		right_rotate(unsigned int x, unsigned int n);
unsigned int		eps0(unsigned int x);
unsigned int		eps1(unsigned int x);
unsigned int		sig0(unsigned int x);
unsigned int		sig1(unsigned int x);
unsigned int		ch(unsigned int x, unsigned int y, unsigned int z);
void				sha_init_hash(t_sha_data *data);
void				sha256_init_constants(unsigned int *konstants);
void				loop_start(t_sha_data *data);
void				second_loop(t_sha_data *data);
void				change_h(t_sha_data *data);
unsigned int		maj(unsigned int x, unsigned int y, unsigned int z);
void				invert_endian(unsigned char *u, int l);
unsigned long long	remainer_to_64_bytes(unsigned long long l);
void	long_memcopy(unsigned char *dest, const unsigned char *src, unsigned long long len);

#endif
