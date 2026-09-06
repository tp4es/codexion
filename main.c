/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:01:37 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/06 19:41:39 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_value(char *value)
{
	return (atoi(value));
}

int	setup(int len, char **input, t_config load)
{
	int	i;
	int	*values[6];

	i = 0;
	values[0] = &load->n_coders;
	values[1] = &load->time_bo;
	values[2] = &load->time_tc;
	values[3] = &load->time_tdb;
	values[4] = &load->time_trf;
	values[5] = &load->n_compile_r;
	values[6] = &load->dongle_cd;
	while (i < 7)
	{
		if (!strcmp(values[i], "0"))
			values[i] = 0;
		else
			values[i] = get_value(input[i]);
		if (!values[i])
			return (1);
		i++;
	}
	if (!strcmp(input[i], "FIFO") || !strcmp(input[i], "EDF"))
		load->schedule = input[i];
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	load;
	if (argc != 9)
		return (1);
	if (setup((argc - 1), (argv + 1), load))
		return(1);
	printf("%d", load.n_coders);
	return(0);
}
