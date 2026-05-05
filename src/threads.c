/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:37:38 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/05 22:42:39 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/codexion.h"



void *routine(void *arg)
{
    t_coder *c = (t_coder *)arg;
    int i= 0;
    
    while ((!c->data->stop) && (c->compil_count < c->data->required_compiles))
    {
        usleep(c->data->time_to_compil);
         
        log_action(c, "is compiling");
        usleep(c->data->time_to_debug);
        log_action(c, "is debugging");
        usleep(c->data->time_to_refactor);
        log_action(c, "is refactoring");
        
        i++;
        c->compil_count++;
    }

    return NULL;
}
int create_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->nb_coders)
    {
        data->coders[i].id = i + 1;
        data->coders[i].data = data;
        data ->coders[i].last_compile_start = data->start_time;
        data->coders[i].compil_count = 0;
        data->coders[i].left = i;
        data->coders[i].right = (i + 1) % data->nb_coders;
        
        if (pthread_create(&data->coders[i].thread, NULL, routine, &data->coders[i]) != 0)
            return (-1);
        i++;
    }
    return (0);
}

void join_threads(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->nb_coders)
    {
        pthread_join(data->coders[i].thread, NULL);
        i++;
    }
    free(data->coders);
}
