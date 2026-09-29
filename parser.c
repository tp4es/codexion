#include "codexion.h"

static int	valid_number(char *value)
{
	int	index;

	index = 0;
	if (!value[0])
		return (0);
	while (value[index])
	{
		if (value[index] < '0' || value[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

static int	load_number(char *value, int *number)
{
	long	loaded;
	int		index;

	if (!valid_number(value))
		return (1);
	loaded = 0; index = 0;
	while (value[index])
	{
		loaded = loaded * 10 + value[index] - '0';
		if (loaded > 2147483647)
			return (1);
		index++;
	}
	if (loaded < 0)
		return (1);
	*number = (int)loaded;
	return (0);
}

int	parse_config(int argc, char **argv, t_config *cfg)
{
	int	*values[7];
	int	index;

	if (argc != 9)
		return (1);
	(values[0] = &cfg->coders, values[1] = &cfg->burnout);
	(values[2] = &cfg->compile, values[3] = &cfg->debug);
	(values[4] = &cfg->refactor, values[5] = &cfg->required);
	(values[6] = &cfg->cooldown);
	index = 0;
	while (index < 7)
	{
		if (load_number(argv[index + 1], values[index]))
			return (1);
		index++;
	}
	if (!cfg->coders || !cfg->burnout || !cfg->required)
		return (1);
	if (!strcmp(argv[8], "fifo"))
		cfg->edf = 0;
	else if (!strcmp(argv[8], "edf"))
		cfg->edf = 1;
	else
		return (1);
	return (0);
}
