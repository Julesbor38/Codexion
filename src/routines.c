/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:47:48 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/07 00:04:22 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void compile_routine(t_coder *coder)
{
    
    if (coder->id % 2 == 0)
    {
        pthread_mutex_lock(&coder->data->dongles[coder->right].mutex);
        log_action(coder, "has taken a dongle");
        pthread_mutex_lock(&coder->data->dongles[coder->left].mutex);
        log_action(coder, "has taken a dongle");
    }
    else
    {
        pthread_mutex_lock(&coder->data->dongles[coder->left].mutex);
        log_action(coder, "has taken a dongle");
        pthread_mutex_lock(&coder->data->dongles[coder->right].mutex);
        log_action(coder, "has taken a dongle");
    }
    log_action(coder, "is compiling");
    usleep(coder->data->time_to_compil * 1000);
        
    pthread_mutex_unlock(&coder->data->dongles[coder->left].mutex);
    pthread_mutex_unlock(&coder->data->dongles[coder->right].mutex);

}
void debug_routine(t_coder *coder)
{
    log_action(coder, "is debugging");
    usleep(coder->data->time_to_debug * 1000);
}

void refactor_routine(t_coder *coder)
{
    log_action(coder, "is refactoring");
    usleep(coder->data->time_to_refactor * 1000);
}

