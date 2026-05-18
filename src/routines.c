/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:47:48 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/18 16:25:42 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void compile_routine(t_coder *coder)
{
    t_dongle  *left;
    t_dongle  *right;

    if (coder->left < coder->right)
    {
        left = &coder->data->dongles[coder->left];
        right = &coder->data->dongles[coder->right];
    }
    else
    {
        left = &coder->data->dongles[coder->right];
        right = &coder->data->dongles[coder->left];
    }

    request_dongles(coder, left, right);

    log_action(coder, "has taken a dongle");
	log_action(coder, "has taken a dongle");

    pthread_mutex_lock(&coder->data->state_mutex);

    coder->last_compile_start =
        timestamp_in_ms(coder);

    pthread_mutex_unlock(&coder->data->state_mutex);

    log_action(coder, "is compiling");

    usleep(coder->data->time_to_compil * 1000);

    release_dongles(coder, left, right);
}

void	debug_routine(t_coder *coder)
{
	log_action(coder, "is debugging");
	usleep(coder->data->time_to_debug * 1000);
}

void	refactor_routine(t_coder *coder)
{
	log_action(coder, "is refactoring");
	usleep(coder->data->time_to_refactor * 1000);
}
