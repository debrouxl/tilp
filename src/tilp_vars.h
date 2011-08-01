/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __TILP_VARS__
#define __TILP_VARS__

int tilp_dirlist_remote(void);

void tilp_vars_sort_by_name(void);
void tilp_vars_sort_by_info(void);
void tilp_vars_sort_by_type(void);
void tilp_vars_sort_by_size(void);

void tilp_var_get_size(VarEntry* vi, char **buf);

void tilp_vars_translate(char *);

#endif
