<h1 align="center">In the name of GOD</h1>

# GAGHL_AVR_UART

**A lightweight and minimal UART driver for AVR microcontrollers**

GAGHL_AVR_UART is a simple UART (Universal Asynchronous Receiver/Transmitter) driver written in C, designed for use with AVR-based systems. It supports basic UART operations including initialization, transmitting & receiving data, sending strings from RAM or program memory, and converting integers to ASCII formats (decimal & hex).



## 📦 Features

- ✅ Baud rate selection for `F_CPU = 8MHz` or `16MHz`
- ✅ Send:
  - Single characters
  - Null-terminated strings from RAM
  - Strings from program memory (PROGMEM)
  - 32-bit unsigned integers as decimal or hex
- ✅ Receive characters or strings with CR/LF detection


## 📚 API Overview

| Function             | Parameters                     | Description                                                  |
|----------------------|--------------------------------|--------------------------------------------------------------|
| `uart_init()`        | `uart_baud_t baud`             | Initializes UART with given baud rate                        |
| `uart_putchar()`     | `uint8_t data`                 | Sends a single byte over UART                                |
| `uart_puts()`        | `const uint8_t *str`           | Sends a null-terminated string from RAM                      |
| `uart_puts_P()`      | `const uint8_t *progmem_s`     | Sends a null-terminated string from program memory (FLASH)   |
| `uart_putdec()`      | `uint32_t val`                 | Sends a 32-bit unsigned integer as a decimal string          |
| `uart_puthex()`      | `uint32_t val`                 | Sends a 32-bit unsigned integer as a hexadecimal string      |
| `uart_getchar()`     | *(void)*                       | Receives a single byte from UART (blocking)                  |
| `uart_gets()`        | `uint8_t *buffer, uint8_t len` | Reads a string until CR/LF into buffer, null-terminated      |
| `uart_available()`   | *(void)*                       | Returns 1 if data is available in UART receive buffer        |

## 🚀 Getting Started

### 1. Add the files to your project

Copy these files into your AVR project:

- `GAGHL_AVR_UART.c`
- `GAGHL_AVR_UART.h`

### 2. Define `F_CPU`

In your project (before including headers), make sure to define CPU frequency:

```c
#define F_CPU 8000000UL  // or 16000000UL
```
### 3.Initialize UART
```c
#define F_CPU 8000000UL

#include "GAGHL_UART.h"

int main(void) {
    uart_init(UART_BAUD_9600);
    uart_puts("Hello, UART!\r\n");
    
    while (1) {
        if (uart_available()) {
            uart_putchar(uart_getchar());  // Echo back
        }
    }
}
```
---

## 🔧 Requirements

- AVR microcontroller (e.g. **ATmega32**, **ATmega16**, etc.)
- AVR-GCC or any compatible C toolchain
- `F_CPU` must be defined as either:
  - `8000000UL` (8 MHz)
  - `16000000UL` (16 MHz)

## 🛠️ TODO

- [ ] Add support for 20 MHz operation
- [ ] Add configuration options for parity and stop bits
- [ ] Implement optional interrupt-based RX/TX handling
- [ ] Add unit tests or simulation examples (e.g., with simavr or Proteus)



## 🤝 Contributing

Contributions are welcome!  
Whether it's bug fixes, feature suggestions, or improvements — your help is appreciated.

- Fork the repository
- Create a new branch (`git checkout -b feature/my-feature`)
- Commit your changes (`git commit -am 'Add new feature'`)
- Push to the branch (`git push origin feature/my-feature`)
- Open a Pull Request

If you’re using this library in your project, feel free to let me know — I’d love to check it out!

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).

You are free to:
- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material

Under the following terms:
- **Attribution** — You must give appropriate credit to the author (GAGHL).
- **NonCommercial** — You may not use the material for commercial purposes without explicit permission.

For more information, see the full license: [https://creativecommons.org/licenses/by-nc/4.0/](https://creativecommons.org/licenses/by-nc/4.0/)

© 2025 GAGHL. All rights reserved.

## Author

Developed by [GAGHL](https://github.com/GAGHL)
