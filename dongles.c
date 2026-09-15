/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:47:41 by tide.oli          #+#    #+#             */
/*   Updated: 2026/09/15 20:47:56 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void create_dongles(t_config parameters, t_dongle *dongles)
{
    int i;

    i = 0;
    while (i < parameters.n_coders)
    {
        dongles[i].id = i;
        dongles[i].dongle_cd = parameters.dongle_cd;
        dongles[i].state = 0;
		pthread_mutex_init(&dongles[i].d_mutex, NULL);
    	pthread_cond_init(&dongles[i].d_condition, NULL);
        i++;
    }
}
