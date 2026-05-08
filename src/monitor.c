/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:08:33 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/07 01:42:59 by jbordeli         ###   ########.fr       */
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

    data = (t_data *)arg;

    while (!data->stop)
    {
        i = 0;
        while (i < data->nb_coders)
        {
            now = timestamp_now_in_ms(data);

            if (now - data->coders[i].last_compile_start
                > data->time_to_burnout)
            {
                pthread_mutex_lock(&data->print_mutex);

                printf("%ld %d burned out\n",
                    now,
                    data->coders[i].id);

                pthread_mutex_unlock(&data->print_mutex);

                data->stop = 1;
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}