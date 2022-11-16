/*
Wrapper for an async UART connection, and some other helpful functions

Currently only supports UART0
*/

#include <avr/io.h>

// ===== UART 0 =====
void uart0_init(void);
void uart0_putchr(char ch);
void uart0_putstr(char *str);
char uart0_getchr(void);

// ===== Other Functions =====
char *uint_to_dec(unsigned x, char *s);