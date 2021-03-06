/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_list_modifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qperez <qperez42@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/30 17:48:19 by qperez            #+#    #+#             */
/*   Updated: 2014/12/02 12:02:57 by qperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <This file contains s_list_modifier method>
** < push_back, push_front, pop_back, pop_front, erase >
** Copyright (C) <2013>  Quentin Perez <qperez42@gmail.com>
** This file is part of 42-toolkit.
** 42-toolkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <f_secure/f_secure.h>
#include <list/s_list.h>
#include <f_error/m_error.h>

bool		f_list_push_back(t_list *v_this, void *data)
{
	t_list_cell	*cell;

	cell = D_LIST_CELL(create)(v_this->v_end, NULL, data);
	if (cell == NULL)
		return (M_ERROR(false, "Bad alloc"));
	if (v_this->v_size == 0)
		v_this->v_begin = cell;
	else
		v_this->v_end->v_next = cell;
	v_this->v_end = cell;
	v_this->v_size = v_this->v_size + 1;
	return (true);
}

bool		f_list_push_front(t_list *v_this, void *data)
{
	t_list_cell	*cell;

	cell = D_LIST_CELL(create)(NULL, v_this->v_begin, data);
	if (cell == NULL)
		return (M_ERROR(false, "Bad alloc"));
	if (v_this->v_size == 0)
		v_this->v_end = cell;
	else
		v_this->v_begin->v_prev = cell;
	v_this->v_begin = cell;
	v_this->v_size = v_this->v_size + 1;
	return (true);
}

void		f_list_pop_back(t_list *v_this)
{
	t_list_cell	*tmp;

	if (v_this->v_end != NULL)
	{
		v_this->f_destroy(v_this->v_end->v_data);
		tmp = v_this->v_end->v_prev;
		uf_free_s((void **)&v_this->v_end);
		v_this->v_end = tmp;
		v_this->v_size = v_this->v_size - 1;
		if (v_this->v_end != NULL)
			v_this->v_end->v_next = NULL;
		else
			v_this->v_begin = NULL;
	}
}

void		f_list_pop_front(t_list *v_this)
{
	t_list_cell	*tmp;

	if (v_this->v_begin != NULL)
	{
		v_this->f_destroy(v_this->v_begin->v_data);
		tmp = v_this->v_begin->v_next;
		uf_free_s((void **)&v_this->v_begin);
		v_this->v_begin = tmp;
		v_this->v_size = v_this->v_size - 1;
		if (v_this->v_begin != NULL)
			v_this->v_begin->v_prev = NULL;
		else
			v_this->v_end = NULL;
	}
}

t_list_cell	*f_list_erase(t_list *v_this, t_list_cell *erase, void **data)
{
	t_list_cell	*ret;

	ret = erase->v_next;
	if (data != NULL)
		*data = erase->v_data;
	if (erase == v_this->v_begin)
		v_this->v_begin = ret;
	else if (erase == v_this->v_end)
		v_this->v_end = erase->v_prev;
	if (erase->v_prev != NULL)
		erase->v_prev->v_next = erase->v_next;
	if (erase->v_next != NULL)
		erase->v_next->v_prev = erase->v_prev;
	uf_free_s((void **)&erase);
	v_this->v_size = v_this->v_size - 1;
	if (v_this->v_size == 0)
	{
		v_this->v_begin = NULL;
		v_this->v_end = NULL;
	}
	return (ret);
}
