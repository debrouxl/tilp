/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __TILP_VERSION__
#define __TILP_VERSION__

/*
  This file contains version number
  and library requirements.
*/

#ifdef __WIN32__
# define TILP_VERSION "1.17"		// For Win32
#else
# define TILP_VERSION VERSION
#endif

#define TILP_REQUIRES_LIBCABLES_VERSION	"1.3.0"
#define TILP_REQUIRES_LIBCALCS_VERSION 	"1.1.8"
#define TILP_REQUIRES_LIBFILES_VERSION	"1.1.6"
#define TILP_REQUIRES_LIBCONV_VERSION	"1.1.4"

#endif
