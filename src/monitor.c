/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:08:33 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 12:13:14 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

long timestamp_now_in_ms(t_data *data)
{
    long actual_time;
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    actual_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (actual_time - data->start_time);
}

void *monitor(void *arg)
{
    t_data *data;
    long now;
    int i;
    int done_count;
    
    data = (t_data *)arg;

    while (!data->stop)
    {
        i = 0;
        done_count = 0;
        while (i < data->nb_coders)
        {
            pthread_mutex_lock(&data->state_mutex);
            now = timestamp_now_in_ms(data);
            if (data->coders[i].compil_count >= data->required_compiles)
            {
                done_count++;
                pthread_mutex_unlock(&data->state_mutex);
                i++;
                continue;
            }
            if (now - data->coders[i].last_compile_start
                > data->time_to_burnout)
            {
                data->stop = 1;
                pthread_mutex_unlock(&data->state_mutex);
                pthread_mutex_lock(&data->print_mutex);

                printf("%ld %d burned out\n",
                    now,
                    data->coders[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->state_mutex);
            i++;
        }
        if (done_count == data->nb_coders)
        {
            pthread_mutex_lock(&data->state_mutex);
            data->stop = 1;
            pthread_mutex_unlock(&data->state_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}