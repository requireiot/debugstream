/**
 * @file 		  debugstream.h
 * Created		: 07-Mar-2020
 * Author		: Bernd Waldmann
 * Tabsize		: 4
 *
 * This Revision: $Id: debugstream.h 1223 2021-08-03 16:20:49Z  $
 *
 * @brief Defines a printf-style DEBUG_PRINTF macro (and a few variants, 
 * see below), for printing debugging messages to serial output, via a 
 * `debug_printf()` function which must be defined by the application.
 *
 * In Arduino-based projects, in your main application, define `IMPLEMENT_DEBUGSTREAM_ARDUINO` 
 * before including debugstream.h, or `#include "debugstream_arduino.h"`, 
 * this will to implement a `debug_printf()` function, based on the Serial() class
 * 
 * In non-Arduino projects, in your main application, define `IMPLEMENT_DEBUGSTREAM_AVRUART` 
 * before including debugstream.h, or `#include "debugstream_avruart.h"`,
 * this will implement a `debug_printf()` function, using my AvrUART library (https://github.com/requireiot/AvrUART)
 * 
 * In all source modules (.cpp files) other than the one where you #define IMPLEMENT_DEBUGSTREAM_xxx,
 * just include this header file and use the DEBUG_PRINTx macros (see below)
 */
 
/*
   Copyright (C) 2020,2021 Bernd Waldmann

   This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
   If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/

   SPDX-License-Identifier: MPL-2.0
*/

#ifndef __debugstream_h
#define __debugstream_h

#include <avr/pgmspace.h>

/**
 * @brief formatted debug output. This function is defined by your application 
 * and, if defined, can be used in all modules
 * 
 * @param fmt  printf-like format string, in PROGMEM
 */
void debug_printf( const char* fmt, ... ) __attribute__ ((weak));


/**
 * @brief Plain string debug output. This function is defined by your application 
 * and, if defined, used in all modules
 * 
 * @param fmt  string in PROGMEM
 */
void debug_print( const char* fmt ) __attribute__ ((weak));


/** 
 * @def  IMPLEMENT_DEBUGSTREAM_ARDUINO  define this macro in application to define
 * debug output stream using Arduino Serial() class 
 * ... i.e. if the application uses Arduino libraries
 */
#if defined(IMPLEMENT_DEBUGSTREAM_ARDUINO) || defined(IMPLEMENT_ARDUINO_DEBUGSTREAM)
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
#endif 

/** 
 * @def  IMPLEMENT_DEBUGSTREAM_AVRUART  call this macro in application to define
 * debug output stream using direct UART output using my bwAvrUART class 
 * ... i.e. if the application is not an Arduino project
 */
#if defined(IMPLEMENT_DEBUGSTREAM_AVRUART) || defined(IMPLEMENT_AVRUART_DEBUGSTREAM)
	#include <AvrUART.h>
	extern AvrUART0 uart0;
	void debug_print( const char* fmt) 						
	{ if (!uart0.isDisabled()) uart0.puts_p(fmt); }	
	void debug_printf( const char* fmt, ... ) 	        	
	{ 							
		if (!uart0.isDisabled()) {							
			va_list args; 										
			va_start (args, fmt);								
			uart0.vprintf_p(fmt,args); 							
			va_end (args);										
		}
	}
#endif


#ifndef NO_DEBUG
	/** 
	 * @brief	print literal string to application-defined debug output stream
	 * @param	s	the string, must be a literal, stored in PROGMEM.
	 */
	#define DEBUG_PRINT(s)	if (debug_print) debug_print(PSTR(s))
	/** 
	 * @brief	print PROGMEM literal string to application-defined debug output stream
	 * @param	s	the string, stored in PROGMEM.
	 */
	#define DEBUG_PRINT_P(s)	if (debug_print) debug_print(s)
	/** 
	 * @brief	print formatted string to application-defined debug output stream, same as `printf()`.
	 * @param	fmt		the format string, must be a literal, stored in PROGMEM.
	 */
	#define DEBUG_PRINTF(fmt,...) if (debug_printf) debug_printf(PSTR(fmt),__VA_ARGS__)
#else
	#define DEBUG_PRINT(s)
	#define DEBUG_PRINT_P(s)
	#define DEBUG_PRINTF(fmt,...)
#endif


#endif // __debugstream_h
