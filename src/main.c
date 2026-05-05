/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:16:48 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/05 22:43:59 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


int main(int argc, char **argv)
{
        t_data data;
        
        
	if (parse_args(argc, argv, &data))
                return (1);
        if(init_all(&data))
                return (1);
        
        create_threads(&data);
        join_threads(&data);
}