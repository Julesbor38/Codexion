/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_scheduler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:42:19 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 14:45:33 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	pop_front(t_dongle *dongle)
{
	int	i;

	if (dongle->queue.size <= 0)
		return ;
	i = 0;
	while (i < dongle->queue.size - 1)
	{
		dongle->queue.arr[i] = dongle->queue.arr[i + 1];
		i++;
	}
	dongle->queue.size--;
}

void	enqueue_fifo(t_dongle *dongle, t_request req)
{
	if (dongle->queue.size >= dongle->queue.capacity)
		return ;
	dongle->queue.arr[dongle->queue.size] = req;
	dongle->queue.size++;
}

void	enqueue_edf(t_dongle *dongle, t_request req)
{
	int	i;

	if (dongle->queue.size >= dongle->queue.capacity)
		return ;
	i = dongle->queue.size;
	while (i > 0
		&& (dongle->queue.arr[i - 1].priority > req.priority
			|| (
				dongle->queue.arr[i - 1].priority == req.priority
				&& dongle->queue.arr[i - 1].arrival_order
				> req.arrival_order)))
	{
		dongle->queue.arr[i] = dongle->queue.arr[i - 1];
		i--;
	}
	dongle->queue.arr[i] = req;
	dongle->queue.size++;
}
