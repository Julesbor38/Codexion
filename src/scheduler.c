/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:41:14 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/18 15:39:02 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	request_dongles(t_coder *coder, t_dongle *left, t_dongle *right)
{
	t_request	req;

	pthread_mutex_lock(&left->mutex);
	pthread_mutex_lock(&right->mutex);
	req.coder = coder;
	req.arrival_order = left->arrival_counter++;
	push_request(coder, left, req);
	req.arrival_order = right->arrival_counter++;
	push_request(coder, right, req);
	
	wait_for_turn(coder, left, right);
	left->busy = 1;
	right->busy = 1;
	pop_front(left);
	pop_front(right);
	pthread_mutex_unlock(&left->mutex);
	pthread_mutex_unlock(&right->mutex);
}

void	release_dongles(t_coder *coder, t_dongle *left, t_dongle *right)
{
	pthread_mutex_lock(&left->mutex);
	pthread_mutex_lock(&right->mutex);
	left->busy = 0;
	right->busy = 0;
	left->cooldown_until = timestamp_in_ms(coder)
		+ coder->data->dongle_cooldown;
	right->cooldown_until = timestamp_in_ms(coder)
		+ coder->data->dongle_cooldown;
	pthread_mutex_unlock(&left->mutex);
	pthread_mutex_unlock(&right->mutex);
}
