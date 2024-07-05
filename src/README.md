This folder contains the source code of the CHERI-SDRaD library.

## Changing CHERI-SDRaD Heap Size:

By default, the Heap has a size of `0x500000000` (20GB)

This value can be modified by defining the `APP_HEAP_SIZE` environment variable:
```
export APP_HEAP_SIZE=<customize_value>
```

## Changing the Number of Domains Used
By default, you can use up to 15 domains. You can change this value by updating the `NUMBER_MAX_DOMAIN` variable in *`cheri_sdrad.h`*.
