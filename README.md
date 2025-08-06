# STM32F411CEU6 Template Project

A complete development template for STM32F411CEU6 microcontroller using GCC toolchain and Makefiles, eliminating the need for IDE dependencies. This template uses the STM32F4xx Standard Peripheral Library (SPL) for easy hardware abstraction.

## Features

- **IDE-Free Development**: Uses GCC and Makefiles instead of proprietary IDEs
- **Standard Peripheral Library**: Pre-configured with STM32F4xx SPL
- **Ready-to-Use Examples**: LED blinking and USART communication
- **Automated Build System**: Simple make commands for building and flashing
- **OpenOCD Integration**: Flash programming via ST-Link debugger
- **Optimized Configuration**: Tailored for STM32F411CEU6 with 25MHz HSE crystal

## Project Structure

```
STM32F411CEU6-Template/
├── Src/                    # Source files
│   ├── main.c              # Main application
│   ├── init_config.c       # Hardware initialization
│   ├── delay_lib.c         # Timer-based delay functions
│   └── stm32f4xx_it.c      # Interrupt handlers
├── Inc/                    # Header files
│   ├── init_config.h
│   ├── delay_lib.h
│   └── stm32f4xx_conf.h    # SPL configuration
├── Drivers/                # STM32 drivers
│   ├── CMSIS/              # ARM CMSIS headers
│   └── STM32F4xx_StdPeriph_Driver/  # Standard peripheral library
├── build/                  # Build output directory
├── Makefile               # Build configuration
├── STM32F411XX_FLASH.ld   # Linker script
└── startup_stm32f411xe.s  # Startup assembly file
```

## Hardware Requirements

- **Microcontroller**: STM32F411CEU6 (BlackPill or similar board)
- **External Crystal**: 25MHz HSE crystal (configured in project)
- **Debugger**: ST-Link V2 or compatible
- **USB-Serial Adapter**: For USART communication (optional)

## Software Requirements

### Required Tools

1. **ARM GCC Toolchain**
   - Download from: https://developer.arm.com/downloads/-/gnu-rm
   - Add to system PATH

2. **Make Utility**
   - Windows: Install via MSYS2, MinGW, or use Windows Subsystem for Linux
   - Linux/macOS: Usually pre-installed

3. **OpenOCD** (for flashing)
   - Download from: https://gnutoolchains.com/arm-eabi/openocd/
   - Add to system PATH

### Optional Tools

- **Serial Terminal**: PuTTY, Tera Term, or similar for USART communication

## Installation & Setup

### 1. Install ARM GCC Toolchain

**Windows:**
```bash
# Download and install ARM GCC from ARM Developer website
# Add installation path to system PATH environment variable
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi
```

**macOS:**
```bash
brew install arm-none-eabi-gcc
```

### 2. Install OpenOCD

**Windows:**
- Download pre-compiled binaries from GNU ARM Eclipse
- Extract and add to system PATH

**Linux:**
```bash
sudo apt install openocd
```

**macOS:**
```bash
brew install openocd
```

### 3. Verify Installation

```bash
arm-none-eabi-gcc --version
make --version
openocd --version
```

## Usage

### Building the Project

```bash
# Clean previous build
make clean

# Build the project
make

# Or build with specific optimization
make OPT=-Os  # Size optimization
make OPT=-O2  # Speed optimization
```

### Flashing to MCU

```bash
# Flash the built firmware
make flash

# Erase flash memory
make erase
```

### Build Output

The build process generates several files in the `build/` directory:
- `template.elf` - ELF executable with debug symbols
- `template.hex` - Intel HEX format for programming
- `template.bin` - Raw binary format
- `template.map` - Memory mapping file

## Default Hardware Configuration

### GPIO Configuration

- **PC13**: Output (LED) - Built-in LED on BlackPill
- **PA10**: Output (LED) - Additional LED output
- **PA2**: USART2 TX - Serial communication output
- **PA3**: USART2 RX - Serial communication input (configured but not used in example)

### USART Configuration

- **Peripheral**: USART2
- **Baud Rate**: 115200
- **Data Bits**: 8
- **Parity**: None
- **Stop Bits**: 1
- **Flow Control**: None

### Clock Configuration

- **HSE**: 25MHz external crystal
- **System Clock**: Configured via system_stm32f4xx.c
- **Peripheral Clocks**: Enabled as needed in init_config.c

## Example Application

The default application demonstrates:

1. **LED Blinking**: Alternately blinks LEDs on PC13 and PA10 every second
2. **USART Communication**: Sends "hello_world\r\n" via USART2 every 2 seconds
3. **Timer-based Delays**: Uses SysTick timer for accurate delays

### Serial Output

Connect a USB-serial adapter to PA2 (TX) and monitor at 115200 baud to see the output.

## Customization

### Adding New Source Files

1. Place `.c` files in the `Src/` directory
2. Place `.h` files in the `Inc/` directory  
3. Update `Makefile` to include new source files:

```makefile
C_SOURCES += Src/your_new_file.c
```

### Enabling Additional SPL Modules

Uncomment required modules in `Makefile`:

```makefile
# Example: Enable SPI and I2C
C_SOURCES += Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
C_SOURCES += Drivers/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
```

Update `stm32f4xx_conf.h` to include corresponding headers:

```c
#define USE_STDPERIPH_DRIVER
#include "stm32f4xx_spi.h"
#include "stm32f4xx_i2c.h"
```

## Troubleshooting

### Build Errors

- **"arm-none-eabi-gcc: command not found"**: ARM GCC toolchain not in PATH
- **"make: command not found"**: Make utility not installed
- **Linker errors**: Check linker script and memory definitions

### Flash Programming Issues

- **"Error: unable to find a matching target"**: ST-Link not connected or drivers not installed
- **"Error: target not halted"**: Try power cycling the board
- **Permission denied (Linux)**: Add user to dialout group or use sudo

### Serial Communication Issues

- **No output on serial terminal**: Check wiring, baud rate, and COM port
- **Garbled text**: Verify baud rate and crystal frequency configuration

## Advanced Usage

### Debug Configuration

For debugging with GDB:

```bash
# Start OpenOCD server
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

# In another terminal, start GDB
arm-none-eabi-gdb build/template.elf
(gdb) target remote :3333
(gdb) load
(gdb) break main
(gdb) continue
```

### Memory Usage Analysis

```bash
# View memory usage
arm-none-eabi-size build/template.elf

# Detailed memory map
arm-none-eabi-nm build/template.elf | sort
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is released under the MIT License. See LICENSE file for details.

## References

- [STM32F411 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00119316.pdf)
- [STM32F411 Datasheet](https://www.st.com/resource/en/datasheet/stm32f411ce.pdf)
- [STM32F4xx Standard Peripheral Library](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32065.html)
- [ARM GCC Toolchain](https://developer.arm.com/downloads/-/gnu-rm)

## Support

For issues and questions:
- Check the troubleshooting section above
- Review STM32F411 documentation
- Create an issue in this repository

---
