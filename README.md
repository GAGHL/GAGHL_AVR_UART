<h1 align="center">In the name of GOD</h1>

# GAGHL_AVR_UART

**A lightweight and minimal UART driver for AVR microcontrollers**

GAGHL_AVR_UART is a simple UART (Universal Asynchronous Receiver/Transmitter) driver written in C, designed for use with AVR-based systems. It supports basic UART operations including initialization, transmitting & receiving data, sending strings from RAM or program memory, and converting integers to ASCII formats (decimal & hex).



## 📦 Features

- ✅ Auto Baud rate selection
- ✅ Supports configurable data bits (5 to 8), parity (none, even, odd), and stop bits (1 or 2)
- ✅ Send:
  - Single characters
  - Null-terminated strings from RAM
  - Strings from program memory (PROGMEM)
  - 32-bit unsigned integers as decimal or hex
- ✅ Receive single bytes or strings with CR/LF detection and simple backspace handling


## 📚 API Overview

| Function           | Parameters                                                                          | Description                                                 |
| ------------------ | ----------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| `uart_init()`      | `uint32_t baud, UART_DataBits databits, UART_StopBits stopbits, UART_Parity parity` | Initialize UART with settings                               |
| `uart_putchar()`   | `uint8_t data`                                                                      | Transmit one byte                                           |
| `uart_puts()`      | `const uint8_t *str`                                                                | Transmit null-terminated string from RAM                    |
| `uart_puts_P()`    | `const uint8_t *progmem_s`                                                          | Transmit null-terminated string from program memory (FLASH) |
| `uart_putdec()`    | `uint32_t val`                                                                      | Transmit 32-bit unsigned integer as decimal string          |
| `uart_puthex()`    | `uint32_t val`                                                                      | Transmit 32-bit unsigned integer as hexadecimal string      |
| `uart_getchar()`   | *(void)*                                                                            | Blocking receive one byte                                   |
| `uart_gets()`      | `uint8_t *buffer, uint8_t maxlength`                                                | Receive string until CR/LF or buffer full                   |
| `uart_available()` | *(void)*                                                                            | Check if data is available in receive buffer                |
| `uart_flush()`     | *(void)*                                                                            | Flush receive buffer                                        |

We appreciate the time and effort you've put into this pull request.
To help us review it efficiently, please ensure you've gone through the following checklist:
Submission Checklist 📝

I have updated existing examples or added new ones (if applicable).
I have used cargo xtask fmt-packages command to ensure that all changed code is formatted correctly.
My changes were added to the CHANGELOG.md in the proper section.
I have added necessary changes to user code to the Migration Guide.

    My changes are in accordance to the esp-rs developer guidelines

Extra:

    I have read the CONTRIBUTING.md guide and followed its instructions.

Pull Request Details 📖

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
    uart_init(9600, UART_DATABITS_8, UART_STOPBITS_1, UART_PARITY_NONE);
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

- [x] Add support for 20 MHz operation. (Implemented in version V0.2.1)
- [x] Add configuration options for parity and stop bits. (Implemented in version V0.2.0)
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
