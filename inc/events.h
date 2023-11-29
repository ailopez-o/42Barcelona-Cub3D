/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:17:51 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:17:54 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	key_press(int key, void *param);
int	key_release(int key, void *param);
int	mouse_release(int button, int x, int y, void *param);
int	mouse_press(int button, int x, int y, void *param);
int	mouse_move(int button, int x, int y, void *param);
int	terminate_program(void *param);
