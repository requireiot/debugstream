/**
 * @file 		  debugstream_arduino.h
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
 * In Arduino-based projects, include this header file to implement a `debug_printf()` function, 
 * based on the Serial() class
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

#ifndef __debugstream_arduino_h
#define __debugstream_arduino_h

#include <avr/pgmspace.h>
#include <DebugSerial.h>

DebugSerialClass DebugSerial(Serial);					

void debug_print( const char* fmt) 						
{ 
    DebugSerial.print((__FlashStringHelper*)fmt); 
}  

void debug_printf( const char* fmt, ... ) 	        	
{ 
    va_list args; 
    va_start (args, fmt); 
    DebugSerial.vprintf((__FlashStringHelper*)fmt,args); 
    va_end (args); 
}

#endif // __debugstream_arduino_h
