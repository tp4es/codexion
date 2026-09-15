/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide.oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 06:04:32 by tide-oli          #+#    #+#             */
/*   Updated: 2026/09/15 17:10:41 by tide.oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void	*coder_routine(void *arg)
{
    t_coder	*coder;
    int		i;

    coder = (t_coder *)arg;
    i = 0;
    while (i <= coder->n_compile)
    {
        printf("Coder %d: %d\n", coder->id, i);
        i++;
    }
    free(coder);
    return (NULL);
}

void	coder_load(t_coder *coder, t_config parameters, int id)
{
    coder->id = id;
    coder->state = 0;
    coder->time_bo = parameters.time_bo;
    coder->time_tc = parameters.time_tc;
    coder->time_tdb = parameters.time_tdb;
    coder->time_trf = parameters.time_trf;
    coder->n_compile = parameters.n_compile;
}

void	coder_act(t_config parameters)
{
    pthread_t	*coders;
    t_coder		*coder;
    int			i;

    coders = malloc(sizeof(pthread_t) * parameters.n_coders);
    if (!coders)
        return ;
    i = 0;
    while (i < parameters.n_coders)
    {
        coder = malloc(sizeof(*coder));
        if (!coder)
            return ;
        coder_load(coder, parameters, i);
        pthread_create(&coders[i], NULL, coder_routine, coder);
        i++;
    }
    i = 0;
    while (i < parameters.n_coders)
    {
        pthread_join(coders[i], NULL);
        i++;
    }
    free(coders);
}