#include "ft_ssl.h"

void	test_exec(void* master)
{
	(void)master;
}

void	command_add(const int command_index, t_command *commands,
					const char *command_name, void (*exec)(void* master))
{
	commands[command_index].name = alloc_str(command_name);
	commands[command_index].exec = exec;
}

void	load_commands(t_master *m)
{
	m->command_number = 2;
	m->commands = malloc(2 * sizeof(t_command));
	command_add(0, &(m->commands), "md5", test_exec);
	command_add(1, &(m->commands), "sha256", test_exec);
}
//3: passer a travers les noms de fonctions et si il y a match avec la chaine donnee appeler la fonction correspondante.
