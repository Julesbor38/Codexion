/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:16:48 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/09 14:18:44 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (parse_args(argc, argv, &data))
		return (1);
	if (init_all(&data))
		return (1);
	create_threads(&data);
	pthread_create(&monitor_thread, NULL, monitor, &data);
	pthread_join(monitor_thread, NULL);
	join_threads(&data);
	free_all(&data);
}
