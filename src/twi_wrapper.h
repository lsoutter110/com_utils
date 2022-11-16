/*
===== TWI Wrapper =====

twi_init:		initialises TWI interface (sets up TWBR/TWSR)
twi_start:		begins TWI communication with device present at 'adr', and in mode 'rw' (either TW_READ or TW_WRITE)
twi_stop:		send stop bit to stop TWI communication (you cannot always do this!)
twi_tx:			send byte 'b' to TWI bus, wait for acknowledge signal(?)
twi_rx:			wait to recieve byte from TWI bus, send acknowledge signal, and return bit
twi_rx_NACK:	wait to recieve byte from TWI bus, DO NOT send acknowledge signal, and return bit
*/

#include <avr/io.h>
#include <util/twi.h>

void twi_init(void);
void twi_start(uint8_t adr, uint8_t rw);
void twi_stop(void);
void twi_tx(uint8_t b);
uint8_t twi_rx(void);
uint8_t twi_rx_NACK(void);