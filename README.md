debugstream.h
=============

printf-style debug output for ATmega controller projects.

### Function 
Defines a function `void debug_printf( const char* fmt, ... )` to output formatted debug messages via UART, and a function `void debug_print( const char* fmt )` to output a fixed text via UART.

On Arduino projects, it uses my `DebugSerial` library for actual output, which will suppress all output unless it detects that a terminal (an FTDI or other USB-serial-converter) is connected.

On non-Arduino ATmega projects, it uses my `AvrUART` library for output. This also suppresses all output unless it detects that a terminal (an FTDI or other USB-serial-converter) is connected.

### Usage

* In each module, `#include <debugstream.h>`
* In your main module, for an Arduino project, `#define IMPLEMENT_DEBUGSTREAM_ARDUINO` before including `debugstream.h`
* In your main module, for an non-Arduino project, `#define IMPLEMENT_DEBUGSTREAM_AVRUART` before including `debugstream.h`

### Example

A typical Arduino project would look like this
```C
#include <Arduino.h>
#define IMPLEMENT_DEBUGSTREAM_ARDUINO
#include <debugstream.h>

void setup()
{
    // ... do something ...
    debug_print("Setup complete.\r\n");
}

void loop()
{
    int magic = 42;
    debug_printf("The answer is %d\r\n", magic);
}
```

### Memory usage

The format specification string for `debug_printf` or the constant text for `debug_print` are stored in program memory, to conserve RAM.

### ANSI terminal control

if your terminal understands ANSI control sequences, you can make your debug outputs more colorful by including ANSI control sequences;
```C
#include <ansi.h>

void some_function() {
    int magic = 42;
    debug_printf( 
        "The answer is " 
        ANSI_BOLD ANSI_RED "%d" ANSI_RESET 
        "\r\n", 
        magic
    );
}
```

If you use Platformio, then you can make the terminal interpret ANSI sequences by adding these lines to the `platformio.ini` file:
```
[env:yourenvironment]
monitor_flags=
  --filter 
  direct
```
