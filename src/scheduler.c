/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 01:56:02 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 13:47:32 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static void pop_front(t_dongle *dongle)
{
    int i;

    if (dongle->queue.size <= 0)
        return ;

    i = 0;

    while (i < dongle->queue.size - 1)
    {
        dongle->queue.arr[i] =
            dongle->queue.arr[i + 1];

        i++;
    }

    dongle->queue.size--;
}

static void enqueue_fifo(t_dongle *dongle, t_request req)
{
    if (dongle->queue.size >= dongle->queue.capacity)
        return ;

    dongle->queue.arr[dongle->queue.size] = req;

    dongle->queue.size++;
}

static void enqueue_edf(t_dongle *dongle, t_request req)
{
    int i;

    if (dongle->queue.size >= dongle->queue.capacity)
        return ;

    i = dongle->queue.size;

    while (
        i > 0
        && (
            dongle->queue.arr[i - 1].priority
                > req.priority

            || (

                dongle->queue.arr[i - 1].priority
                    == req.priority

                &&

                dongle->queue.arr[i - 1].arrival_order
                    > req.arrival_order
            )
        )
    )
    {
        dongle->queue.arr[i] =
            dongle->queue.arr[i - 1];

        i--;
    }

    dongle->queue.arr[i] = req;

    dongle->queue.size++;
}

void request_dongle(t_coder *coder, t_dongle *dongle)
{
    t_request  req;
    long       now;

    pthread_mutex_lock(&dongle->mutex);

    req.coder = coder;

    req.arrival_order =
        dongle->arrival_counter++;

    if (coder->data->scheduler_type == FIFO)
    {
        req.priority = req.arrival_order;

        enqueue_fifo(dongle, req);
    }
    else
    {
        req.priority =
            coder->last_compile_start
            + coder->data->time_to_burnout;

        enqueue_edf(dongle, req);
    }

    while (1)
    {
        now = timestamp_in_ms(coder);

        if (
            !dongle->busy
            && dongle->queue.size > 0
            && dongle->queue.arr[0].coder == coder
            && now >= dongle->cooldown_until
        )
            break ;

        pthread_mutex_unlock(&dongle->mutex);

        usleep(1000);

        pthread_mutex_lock(&dongle->mutex);
    }

    dongle->busy = 1;

    pop_front(dongle);

    pthread_mutex_unlock(&dongle->mutex);
}

void release_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->mutex);

    dongle->busy = 0;

    dongle->cooldown_until =
        timestamp_now_in_ms(coder->data)
        + coder->data->dongle_cooldown;

    pthread_cond_broadcast(&dongle->cond);

    pthread_mutex_unlock(&dongle->mutex);
}