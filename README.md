# CHERI-SDRaD

This repository contains the source code for the Master Thesis [Secure Rewind and Discard on Arm Morello](https://secure-rewind-and-discard.github.io/files/Master_Thesis___Secure_Rewind_on_Discard_on_ARM_Morello.pdf).

This project adapts [Secure Rewind & Dicard of Isolated Domains](https://github.com/secure-rewind-and-discard/secure-rewind-and-discard/tree/main) for CHERI architecture on Arm Morello Board.

## Abstract
Memory-unsafe programming languages such as C and C++ are the preferred languages for systems programming, embedded systems, and performance-critical applications. The widespread use of these languages makes the risk of memory-related attacks very high. There are well-known detection mechanisms, but they do not address software resilience.
An earlier approach proposes the Secure Domain Rewind and Discard (SDRaD) of isolated domains as a method to enhance the resilience of software targeted by runtime attacks on x86 architecture, based on hardware-enforced Memory Protection
Key (MPK).
In this work, SDRaD has been adapted to work with the Capability Hardware Enhanced RISC Instructions (CHERI) architecture to be more lightweight and performant.
The results obtained in this thesis show that CHERI-SDRaD, the prototype adaption that leverages the memory-safety properties inherent to the CHERI architecture, results in a solution with less performance degradation (2.2\% in Nginx benchmarks) compared to earlier results obtained with the original SDRaD prototype on an Intel-based architecture. The adaption to CHERI additionally allowed limitations inherent to the MPK-based approach to be resolved.

## Getting started

Clone this repository using the following command:
```
git clone git@github.com:secure-rewind-and-discard/cheri-sdrad.git
```

Compile the library by using `make` in the src folder:
```
cd src
make
```
Before using any application that relies on the `cheri-sdrad` library (`libcheri_sdrad.so`), ensure that the library’s path is added to the `LD_LIBRARY_PATH` environment variable. This allows the dynamic linker to locate and load the necessary library.
```
export LD_LIBRARY_PATH=/path/to/cheri-sdrad/src:$LD_LIBRARY_PATH
```

If the application relies on pre-built binaries which make calls to the `malloc()` family of functions, you additionally need to ensure that `libcheri_sdrad.so` is loaded before all other shared libraries to ensure it can override the `malloc()` functions with its own versions. This can be achieved, for example, by setting the `LD_PRELOAD` environmental variable to point to `libcheri_sdrad.so` to instruct the Linux dynamic linker to preload `libcheri_sdrad.so` before `glibc`.

```
LD_PRELOAD=/path/to/cheri-sdrad/src/libcheri_sdrad.so
``` 

## Hardware requirement

The cheri-sdrad library require an Arm CPU using CHERI such as the Arm Morello Board.

## Simple examples
Some examples are at your disposal to demonstrate the library's use in [examples/](./examples/)

## License 
© Ericsson AB 2024

BSD 3-Clause License

The modified TLSF implementation by mattconte/tlsf licensed under BSD 3-Clause License