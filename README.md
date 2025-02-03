# Peltia

Project for controlling temperature in thermal chambers using STM32 microcontrollers. It includes tools and configurations for firmware development, debugging, and serial communication.

## See also
- [API Docs placeholder](https://placehold.co/600x400)
- [To Do List](TODO.md)

## Quickstart

### Prerequisites

- **CMake** >= v3.22.0
- **Ninja** >= v1.11.0
- **gcc-arm-none-eabi** >= v13.3.0 (host to ARM cross-compiler for STM32)
- **GCC/MSVC** >= v14.2.1/v19.40.33811 (optional native compiler for docs, admin and test suite)
- **Qt Framework** >= v6.7.0 (optional for admin)
- **Doxygen** >= v1.12.0 (optional for docs generation)
- **Graphviz** >= v12.2.0 (optional for docs generation)
- **PuTTY, Minicom** or similar program to read serial COM port
- **STM32CubeProg** >= v2.17.0 used for flashing FW
- **STM32CubeIDE** (optional Eclipse based IDE used for programming and debugging STM32 projects)
- **STM32CubeMX** (optional auto project generator)

#### Installation Windows

You can use the `winget` pkg manager to get the previously mentioned prerequisites via command:
```
winget install Kitware.CMake Ninja-build.Ninja Arm.GnuArmEmbeddedToolchain DimitriVanHeesch.Doxygen PuTTY.PuTTY Graphviz.Graphviz
```

For native compiler please consider installing a compatible version of [Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/) or consider using [Cygwin](https://cygwin.com/), [MSYS2](https://www.msys2.org/) or [MinGW-W64](https://www.mingw-w64.org/)

For Qt Framework you can use their official [online installer](https://doc.qt.io/qt-6/qt-online-installation.html) or unofficial Python based [aqtinstall](https://aqtinstall.readthedocs.io/en/latest/getting_started.html).

Make sure to reload the PowerShell session after installation, or add any additional missing installation directories to your `$env:PATH`. Alternatively, run the PowerShell script under `misc\env.ps1`, which temporarily adds `gcc-arm-none-eabi` and `STM32CubeProg` (installed in default locations) to your `$env:PATH`.

#### Installation Ubuntu

```
# apt install cmake ninja gcc-arm-none-eabi g++ qt6-base-dev qt6-tools-dev qt6-tools-dev-tools doxygen graphviz minicom
```

#### STM32Cube Installation

If you plan on using `STM32CubeIDE`, `STM32CubeProg` comes bundled with it.

Note: A [myST](https://my.st.com) account is required to download STM32Cube Development Tools from the ST website.

You can get them under following links:
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html#st-get-software)
- [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html#st-get-software)
- [STM32CubeProg](https://www.st.com/en/development-tools/stm32cubeprog.html#st-get-software)

### Usage

#### Configure

Configure the project by issuing following command with optional `-DENABLE_TESTS=ON -DENABLE_DOCS=ON -DENABLE_ADMIN=ON` flags, these are set to `OFF` by default:
```
cmake -S . -B build -G Ninja -DENABLE_TESTS=ON -DENABLE_DOCS=ON -DENABLE_ADMIN=ON
```

#### Compile

Compile the project by issuing following command:
```
cmake --build build -j [num of CPU threads]
```

#### Flash

To flash the firmware first connect the STLink via USB to your PC and issue command:
```
cmake --build build --target flash
```

#### Read COM Windows

In order to list all available COM ports issue the following command:
```
Get-WmiObject Win32_SerialPort | Select-Object DeviceID, Caption, Description
```
Look for device with caption `Silicon Labs CP210x USB to UART Bridge (COM7)`. Launch `PuTTY` by issuing following command:
```
putty -serial COM7 -sercfg 115200,8,n,1,N
```

#### Read COM Ubuntu

List available serial ports:
```
$ ls /dev/ttyUSB*
```

Launch minicom and listen to `/dev/ttyUSB0`:
```
$ minicom -D /dev/ttyUSB0
```

#### Build docs

```
cmake --build build --target docs
```