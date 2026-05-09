/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 14:41:14 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 14:41:39 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	request_dongle(t_coder *coder, t_dongle *dongle)
{
	t_request	req;

	pthread_mutex_lock(&dongle->mutex);
	req.coder = coder;
	req.arrival_order = dongle->arrival_counter++;
	push_request(coder, dongle, req);
	wait_for_turn(coder, dongle);
	dongle->busy = 1;
	pop_front(dongle);
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->busy = 0;
	dongle->cooldown_until = timestamp_in_ms(coder)
		+ coder->data->dongle_cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}
