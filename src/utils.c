/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:35:28 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 13:18:16 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

long timestamp_in_ms(t_coder *coder)
{
    long actual_time;
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    actual_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (actual_time - coder->data->start_time);
}

void log_action(t_coder *coder, char *str)
{
    long time_since_start;
    
    pthread_mutex_lock(&coder->data->state_mutex);
    pthread_mutex_lock(&coder->data->print_mutex);
    if(coder->data->stop)
    {
        pthread_mutex_unlock(&coder->data->state_mutex);
        pthread_mutex_unlock(&coder->data->print_mutex);
        return;
    }
    time_since_start = timestamp_in_ms(coder);
    if (strcmp(str, "is compiling") == 0)
        coder->last_compile_start = time_since_start;
    
    printf("%ld %d %s\n", time_since_start, coder->id, str);
    pthread_mutex_unlock(&coder->data->print_mutex);
    pthread_mutex_unlock(&coder->data->state_mutex);   
}

void free_all(t_data *data)
{
    int i;
    
    i = 0;
    
    while(i < data->nb_coders)
    {
        if(data->dongles[i].queue.arr)
            free(data->dongles[i].queue.arr);
        i++;
    }
    if (data->dongles)
        free(data->dongles);
}