/*
 * GAGHL_UART.c
 *
 * Created: 7/5/2025 2:47:27 PM
 *  Author: GAGHL
 */ 
/*
 * GAGHL_UART.c
 *
 * Created: 7/5/2025 2:47:27 PM
 * Author : GAGHL
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "GAGHL_UART.h"

void uart_init(Baudrate Baud, UART_DataBits databits, UART_StopBits stopbits, UART_Parity parity) {
	
	uint8_t ucsrc_val = (1 << URSEL);
	
	#if (F_CPU==8000000UL)
	
	switch(Baud){
		case UART_BAUDRATE_2400:  UBRRH = 0; UBRRL = 207; UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_4800:  UBRRH = 0; UBRRL = 103; UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_9600:  UBRRH = 0; UBRRL = 51;  UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_14400: UBRRH = 0; UBRRL = 68;  UCSRA |= (1 << U2X);  break; //Error =  0.6%
		case UART_BAUDRATE_19200: UBRRH = 0; UBRRL = 25;  UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_28800: UBRRH = 0; UBRRL = 34;  UCSRA |= (1 << U2X);  break; //Error = -0.8%
		case UART_BAUDRATE_38400: UBRRH = 0; UBRRL = 25;  UCSRA |= (1 << U2X);  break; //Error =  0.2%
		case UART_BAUDRATE_57600: UBRRH = 0; UBRRL = 16;  UCSRA |=  (1 << U2X); break; //Error =  2.1%!
		case UART_BAUDRATE_76800: UBRRH = 0; UBRRL = 12;  UCSRA |=  (1 << U2X); break; //Error =  0.2%
	}
	
	#elif (F_CPU==16000000UL)
	
	switch(Baud){
		case UART_BAUDRATE_4800:  UBRRH = 0; UBRRL = 207; UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_9600:  UBRRH = 0; UBRRL = 103; UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_14400: UBRRH = 0; UBRRL = 138; UCSRA |= (1 << U2X);  break; //Error = -0.1%
		case UART_BAUDRATE_19200: UBRRH = 0; UBRRL = 51;  UCSRA &= ~(1 << U2X); break; //Error =  0.2%
		case UART_BAUDRATE_28800: UBRRH = 0; UBRRL = 68;  UCSRA |= (1 << U2X);  break; //Error =  0.6%
		case UART_BAUDRATE_38400: UBRRH = 0; UBRRL = 51;  UCSRA |= (1 << U2X);  break; //Error =  0.2%
		case UART_BAUDRATE_57600: UBRRH = 0; UBRRL = 34;  UCSRA |= (1 << U2X);  break; //Error = -0.8%
		case UART_BAUDRATE_76800: UBRRH = 0; UBRRL = 25;  UCSRA |= (1 << U2X);  break; //Error =  0.2%
	}
	#else
		#error "Unsupported F_CPU! Please define as 8MHz or 16MHz."
	#endif
	
	// ---------- Setting Data Bits ----------
	ucsrc_val &= ~((1 << UCSZ1) | (1 << UCSZ0));

	switch(databits){
		case UART_DATABITS_5: break; // 00
		case UART_DATABITS_6: ucsrc_val |= (1 << UCSZ0); break; // 01
		case UART_DATABITS_7: ucsrc_val |= (1 << UCSZ1); break; // 10
		case UART_DATABITS_8: ucsrc_val |= (1 << UCSZ1) | (1 << UCSZ0); break; // 11
	}

	// ---------- Setting Stop Bit ----------
	ucsrc_val &= ~(1 << USBS);
	if(stopbits == UART_STOPBITS_2)
	ucsrc_val |= (1 << USBS);

	// ---------- Setting Parity ----------
	ucsrc_val &= ~((1 << UPM1) | (1 << UPM0));
	switch(parity){
		case UART_PARITY_NONE: break;
		case UART_PARITY_EVEN: ucsrc_val |= (1 << UPM1); break;
		case UART_PARITY_ODD:  ucsrc_val |= (1 << UPM1) | (1 << UPM0); break;
	}
	
	// ---------- Enable RX & TX ----------
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = ucsrc_val;
}

void uart_putchar(uint8_t data){
	while (!(UCSRA & (1 << UDRE)));  // Wait until buffer is empty
	UDR = data;
}

void uart_putdec(uint32_t val){
	uint8_t buf[11];
	uint8_t i = 0;

	if (val == 0) {
		uart_putchar('0');
		return;
	}

	// Convert number to characters (in reverse order)
	while (val && i < sizeof(buf)) {
		buf[i++] = '0' + (val % 10);
		val /= 10;
	}

	// Send characters in correct order
	while (i) uart_putchar(buf[--i]);
}

void uart_puts(const uint8_t *str){
	while (*str) {
		uart_putchar(*str++);
	}
}

void uart_puts_P(const uint8_t *progmem_s){
	uint8_t c;
	while((c=pgm_read_byte(progmem_s++))){
		uart_putchar(c);
	}
}

void uart_puthex(uint32_t val){
	static const char hex_chars[] = "0123456789ABCDEF";

	uart_putchar('0');
	uart_putchar('x');

	if(val==0){
		uart_putchar('0');
		return;
	}

	uint8_t started=0;
	for (int8_t shift=28; shift>=0; shift-=4){
		uint8_t nibble=(val>>shift)&0x0F;

		if(!started){
			if(nibble==0)
			continue;
			started=1;
		}

		uart_putchar(hex_chars[nibble]);
	}
}

uint8_t uart_getchar(void){
	while (!(UCSRA & (1 << RXC)));  // Wait for data
	return UDR;
}

uint8_t uart_gets(uint8_t *buffer, uint8_t maxlength){
	uint8_t idx = 0;

	while (idx < (maxlength - 1)) {
		uint8_t c = uart_getchar();

		// Stop on CR or LF
		if (c == '\r' || c == '\n') {
			// Handle optional CRLF
			if (c == '\r' && uart_available()) {
				uint8_t next = uart_getchar();
				if (next != '\n') {
					// Unhandled: could push back
				}
			}
			break;
		}
		
		// Backspace (ASCII 8 or 127)
		if ((c == 8 || c == 127) && idx > 0) {
			idx--;
			uart_putchar(' ');  // erase character
			uart_putchar('\b'); // move cursor back
			continue;
		}
		
		buffer[idx++] = c;
	}

	buffer[idx] = '\0';  // Null-terminate
	return idx;
}

uint8_t uart_available(void){
	return (UCSRA & (1 << RXC)) ? 1 : 0;
}

void uart_flush(void){
	while (UCSRA & (1 << RXC)) {
		volatile uint8_t dummy = UDR;
		(void)dummy;
	}
}