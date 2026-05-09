/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scheduler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:40:05 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 14:45:28 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	can_take_dongle(t_coder *coder,
			t_dongle *dongle, long now)
{
	if (dongle->busy)
		return (0);
	if (dongle->queue.size <= 0)
		return (0);
	if (dongle->queue.arr[0].coder != coder)
		return (0);
	if (now < dongle->cooldown_until)
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
			t_dongle *dongle)
{
	long	now;

	while (1)
	{
		now = timestamp_in_ms(coder);
		if (can_take_dongle(coder, dongle, now))
			break ;
		pthread_mutex_unlock(&dongle->mutex);
		usleep(1000);
		pthread_mutex_lock(&dongle->mutex);
	}
}
