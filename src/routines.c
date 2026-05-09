/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:47:48 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 16:49:19 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	compile_routine(t_coder *coder)
{
	
	if (coder->id % 2 == 0)
	{
		request_dongle(coder, &coder->data->dongles[coder->right]);
		log_action(coder, "has taken a dongle");
		request_dongle(coder, &coder->data->dongles[coder->left]);
		log_action(coder, "has taken a dongle");
	}
	else
	{
		request_dongle(coder, &coder->data->dongles[coder->left]);
		log_action(coder, "has taken a dongle");
		request_dongle(coder, &coder->data->dongles[coder->right]);
		log_action(coder, "has taken a dongle");
	}
	log_action(coder, "is compiling");
	usleep(coder->data->time_to_compil * 1000);
	release_dongle(coder, &coder->data->dongles[coder->left]);
	release_dongle(coder, &coder->data->dongles[coder->right]);
}

void	debug_routine(t_coder *coder)
{
	log_action(coder, "is debugging");
	usleep(coder->data->time_to_debug * 1000);
}

void	refactor_routine(t_coder *coder)
{
	log_action(coder, "is refactoring");
	usleep(coder->data->time_to_refactor * 1000);
}
