/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:12:13 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/15 19:39:34 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define	CODEXION_H

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
	int		n_compile;
	int		dongle_cd;
	char	*schedule;
}	t_config;

typedef struct coders
{
	int	id;
	int	state;
	int	time_bo;
	int	time_tc;
	int	time_tdb;
	int	time_trf;
	int	n_compile;	//Pendiente posible dongle CD
}	t_coder;

typedef struct dongle
{
	int	id;
	int	dongle_cd;
	int	state;
}	t_dongle;

void	coder_act(t_config parameters);
void	create_dongles(t_config parameters, t_dongle *dongles);

#endif
