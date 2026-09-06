/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:12:13 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/06 23:03:29 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define	CODEXION_H

# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

typedef struct config
{
	int		n_coders;
	int		time_bo;
	int		time_tc;
	int		time_tdb;
	int		time_trf;
	int		n_compile_r;
	int		dongle_cd;
	char	*schedule;
}	t_config;

int	setup(int len, char **input, t_config *load);

#endif
