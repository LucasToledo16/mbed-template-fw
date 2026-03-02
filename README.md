# LNLS Template for Mbed OS–Based Firmwares

This is a template repository for Mbed OS-based firmwares using LNLS in-house
developed libraries.

> NOTE: Currently, only LPC1768 target is supported.

## Directory structure

```
|-- app
|       Files specific to the application.
|
|-- lib
|   |-- mbed-mods
|   |      LNLS in-house developed modules library.
|   |
|   |-- mbed-libs
|   |      LNLS in-house developed peripherals library.
|
|-- mbed-os
|   |   LNLS Mbed OS Community Edition fork.
|
|-- newboot
|   |   LNLS in-house developed bootloader for LPC176{4,8} devices.
```

## How to build

Assuming the toolchain is already installed [1], use `./scripts/cmake_build.sh`
script.

```
Usage: ./cmake_build.sh <CMAKE_BUILD_TYPE>
  CMAKE_BUILD_TYPE: Debug | Develop | Release
```

[1] https://mbed-ce.dev/getting-started/toolchain-install/

## How to flash

Assuming `openocd` is already installed, use `./scripts/flash.sh` script.
