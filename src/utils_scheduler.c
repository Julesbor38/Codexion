/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scheduler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:40:05 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/18 14:57:20 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	can_take_dongles(t_coder *coder,
			t_dongle *left, t_dongle *right, long now)
{
	if (left->busy || right->busy)
		return (0);
	if (left->queue.size <= 0 | right->queue.size <= 0)
		return (0);
	if (left->queue.arr[0].coder != coder)
		return (0);
	if (right->queue.arr[0].coder != coder)
		return (0);
	if (now < left->cooldown_until)
		return (0);
	if (now < right->cooldown_until)
		return (0);
	return (1);
}

long	get_edf_priority(t_coder *coder)
{
	long	priority;

	pthread_mutex_lock(&coder->data->state_mutex);
	priority = coder->last_compile_start
		+ coder->data->time_to_burnout;
	pthread_mutex_unlock(&coder->data->state_mutex);
	return (priority);
}

void	push_request(t_coder *coder,
			t_dongle *dongle, t_request req)
{
	if (coder->data->scheduler_type == FIFO)
	{
		req.priority = req.arrival_order;
		enqueue_fifo(dongle, req);
	}
	else
	{
		req.priority = get_edf_priority(coder);
		enqueue_edf(dongle, req);
	}
}

void	wait_for_turn(t_coder *coder,
			t_dongle *left, t_dongle *right)
{
	long	now;

	while (1)
	{
		now = timestamp_in_ms(coder);
		if (can_take_dongles(coder, left, right, now))
			break ;
		pthread_mutex_unlock(&left->mutex);
		pthread_mutex_unlock(&right->mutex);
		usleep(1000);
		pthread_mutex_lock(&left->mutex);
		pthread_mutex_lock(&right->mutex);
	}
}
