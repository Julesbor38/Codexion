/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:03:51 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/07 02:24:43 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


typedef enum e_scheduler
{
    FIFO,
    EDF
}   t_scheduler;

typedef struct s_data
{
    int nb_coders;
    long time_to_burnout;
    long time_to_compil;
    long time_to_debug;
    long time_to_refactor;
    int required_compiles;
    long dongle_cooldown;
    t_scheduler scheduler;
    long start_time;
    int  stop;
    pthread_mutex_t print_mutex;
    struct s_coder *coders;
    struct s_dongle *dongles;
}   t_data;

typedef struct s_coder
{
	int id;
	int left;
    int right;
    long last_compile_start;
    int compil_count;
    pthread_t thread;
    t_data *data;
}	t_coder;

typedef struct s_request
{
    int         coder_id;
    long        priority;
} t_request;

typedef struct s_heap
{
    t_request *arr;
    int size;
    int capacity;
} t_heap;

typedef struct s_dongle
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    long            cooldown_until;
    t_heap queue;
    long arrival_counter;
    int in_use;
} t_dongle;




// parsing
int is_positive_number(char *str);
int fill_data(char **argv, t_data *data);
int parse_args(int argc, char **argv, t_data *data);
int def_args(int argc, char **argv);

// init
int init_memory(t_data *data);
int init_mutex(t_data *data);
int init_dongles(t_data *data);
void init_coders(t_data *data);
int init_all(t_data *data);
// threads
void    *routine(void *arg);
int create_threads(t_data *data);
void join_threads(t_data *data);
// utils
long timestamp_in_ms(t_coder *coder);
void log_action(t_coder *coder, char *str);
void free_all(t_data *data);

//routines
void compile_routine(t_coder *coder);
void debug_routine(t_coder *coder);
void refactor_routine(t_coder *coder);

//monitor
long timestamp_now_in_ms();
void *monitor(void *arg);
#endif
