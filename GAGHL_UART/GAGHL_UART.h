/**
 * @file GAGHL_UART.c
 * @brief UART driver for AVR microcontrollers
 * 
 * This file provides a lightweight UART (Universal Asynchronous Receiver/Transmitter) driver
 * for AVR-based systems. It includes functions for initializing UART with selectable baud rates,
 * transmitting and receiving characters, sending strings from RAM and program memory (FLASH),
 * and converting and transmitting numerical data in decimal and hexadecimal formats.
 * 
 * Supported features:
 *  - Baud rate selection at compile-time for F_CPU = 8MHz or 16MHz
 *  - Transmit single characters, strings, and 32-bit numbers (decimal/hex)
 *  - Receive characters and strings with end-of-line detection
 *  - Optional support for strings stored in program memory using `pgm_read_byte`
 *  - Utility function to check availability of received data
 * 
 * @author GAGHL
 * @date 2025-07-05
 */
#ifndef GAGHL_UART_H_
#define GAGHL_UART_H_

/**
 * @brief Enumeration of supported UART baud rates.
 */
typedef enum{
	UART_BAUDRATE_2400,
	UART_BAUDRATE_4800,
	UART_BAUDRATE_9600,
	UART_BAUDRATE_14400,
	UART_BAUDRATE_19200,
	UART_BAUDRATE_28800,
	UART_BAUDRATE_38400,
	UART_BAUDRATE_57600,
	UART_BAUDRATE_76800
} Baudrate;

/**
 * @brief Initializes the UART peripheral with the specified baud rate.
 * 
 * @param Baud The baud rate selected from the Baudrate enum.
 */
void uart_init(Baudrate Baud);

/**
 * @brief Sends a single byte over UART.
 * 
 * @param data The byte to send.
 */
void uart_putchar(uint8_t data);

/**
 * @brief Sends a 32-bit unsigned integer as ASCII decimal digits.
 * 
 * @param val The value to send (e.g., 12345 will be sent as '1''2''3''4''5').
 */
void uart_putdec(uint32_t val);

/**
 * @brief Sends a null-terminated string over UART.
 * 
 * @param str Pointer to the string to send.
 */
void uart_puts(const uint8_t *str);

/**
 * @brief Sends a null-terminated string stored in program memory (FLASH).
 *
 * Reads the string using `pgm_read_byte` and sends it via UART.
 *
 * @param progmem_s Pointer to the string in program memory (FLASH).
 */
void uart_puts_P(const uint8_t *progmem_s);

/**
 * @brief Sends a 32-bit unsigned integer in hexadecimal format over UART.
 *
 * Format: `0x` prefix followed by hexadecimal digits (no leading zeros unless value is 0).
 *
 * Examples:
 *  - 0 ? `0x0`
 *  - 255 ? `0xFF`
 *  - 305419896 ? `0x12345678`
 *
 * @param val The value to send.
 */
void uart_puthex(uint32_t val);

/**
 * @brief Receives a single byte over UART (blocking).
 * 
 * @return Received byte.
 */
uint8_t uart_getchar(void);

/**
 * @brief Receives a string until newline or carriage return.
 * 
 * @param buffer Pointer to buffer to store the received string.
 * @param length Maximum length of buffer (including terminating null).
 * @return Number of characters received (not counting the null terminator).
 */
uint8_t uart_gets(uint8_t *buffer, uint8_t length);

/**
 * @brief Checks if data is available to read from UART.
 * 
 * @return 1 if data is available, 0 otherwise.
 */
uint8_t uart_available(void);

#endif /* GAGHL_UART_H_ */
