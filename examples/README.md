# CHERI-SDRaD Examples

This folder contains examples of how to use the CHERI-SDRaD library.

## Prerequisites

Before compiling and running the examples, make sure you have built the CHERI-SDRaD library (`libcheri_sdrad.so`) and add the source directory containing the shared library to the Linux dynamic linker search path.

To compile the library, run `make`in [src/](../src/):

```
cd ../src
make
```

To add the library to the dynamic linker search path, you have to set the environnemtal variable `LD_LIBRARY_PATH` with the [src/](../src/) directory:

```
export LD_LIBRARY_PATH='/path/to/cheri-sdrad/src'
```

## Building and running the CHERI-SDRaD examples

To builds the examples, run `make` in the [examples/](../examples/) directry:
```
make
```

### cheri_sdrad_alloc
This example demonstrates memory allocation within distinct domains.
```
./cheri_sdrad_alloc
Inside domain: 0
CHERI-SDRaD Heap: 0x80800000 [rwRW,0x80800000-0x580800000]
a: 0x480800010 [rwRW,0x480800010-0x480800011]

Inside domain: 1
CHERI-SDRaD Heap: 0x580800000 [rwRW,0x580800000-0xa80800000]
a: 0x980800010 [rwRW,0x980800010-0x980800011]
``` 
### cheri_sdrad_overflow

This example show an application by asking the user to give some inputs, when having more than 4 digits the stack overflow is detected.
```
./cheri_sdrad_overflow
Waiting for the request:
1234
Handling the request
This domain is already initialised
Waiting for the request:
12345
SIGPROT detected
Bad input!
This domain is already initialised
Waiting for the request:
1234
Handling the request
This domain is already initialised
Waiting for the request:
12345
SIGPROT detected
Bad input!
This domain is already initialised
Waiting for the request:
12345
SIGPROT detected
Bad input!
```