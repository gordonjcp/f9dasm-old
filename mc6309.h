/***************************************************************************
 * f9dasm -- Portable M6800/M6809/H6309/OS9/FLEX disassembler              *
 * HEAVILY modified by H.Seib to adapt it to his needs.                    *
 *                                                                         *
 * Line Disassembler Engine Copyright (C) 2000  Arto Salmi                 *
 * Various additions        Copyright (c) 2001-2009 Hermann Seib           *
 * Further additions        Copyright (c) 2014  Rainer Buchty              *
 *    - output nicing using separator after BRA/JMP/PULx PC/RTx/SWIx       *
 *    - label-overrun fix                                                  *
 *    - improved usage info for label-file parser                          *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program; if not, write to the Free Software             *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *
 ***************************************************************************/

// opcodes for 6309 - header

#ifndef _MC6309_H
#define _MC6309_H

extern byte h6309_codes[];
extern byte h6309_codes10[];
extern byte h6309_codes11[];
extern char *h6309_exg_tfr[];

#endif
