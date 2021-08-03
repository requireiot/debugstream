/**
 * @file 		  debugstream_avruart.h
 * Created		: 07-Mar-2020
 * Author		: Bernd Waldmann
 * Tabsize		: 4
 *
 * This Revision: $Id: $
 *
 * @brief Defines a printf-style DEBUG_PRINTF macro (and a few variants, 
 * see below), for printing debugging messages to serial output, via a 
 * `debug_printf()` function which must be defined by the application.
 *
 * In non-Arduino projects, in your main application, include this header to 
 * implement a `debug_printf()` function, using the AvrUART library (see https://github.com/requireiot/AvrUART)
 * 
 * In all source modules (.cpp files),
 * include debugstream.h and use the DEBUG_PRINTx macros (see below)
 */
 
/*
   Copyright (C) 2020,2021 Bernd Waldmann

   This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
   If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/

   SPDX-License-Identifier: MPL-2.0
*/

#ifndef __debugstream_avruart_h
#define __debugstream_avruart_h

#include <avr/pgmspace.h>
#include <AvrUART.h>

extern AvrUART0 uart0;

void debug_print( const char* fmt) 						
{ 
    if (!uart0.isDisabled()) 
        uart0.puts_p(fmt); 
}	

void debug_printf( const char* fmt, ... ) 	        	
{ 							
    if (!uart0.isDisabled()) {							
        va_list args; 										
        va_start (args, fmt);								
        uart0.vprintf_p(fmt,args); 							
        va_end (args);										
    }
}

#endif // __debugstream_avruart_h
