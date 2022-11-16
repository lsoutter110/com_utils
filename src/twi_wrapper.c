#include "twi_wrapper.h"

/*
===== TWI Wrapper Function Definitions =====

~ REGISTERS ~
TWCR: Control Register
TWSR: Status Register
TWDR: Data Register (also used for sending the address, as address is data)
TWBR: Bit rate Register
(TWAR: Address Register, within address match hardware)

! Due to quirks with interrupt bits, it is NOT safe to perform "TWCR |= XXX" !

~ Control bits [in TWCR] ~
TWINT: Interrupt flag (usually set after operation is completed. WRITING 1 to this
	   bit will CLEAR it (set it to 0) (which usually begins the operation))
TWSTA: send Start bit (when set, TWI sends a start bit)
TWEN: Enable (set to enable TWI)
TWIE: Interrupt Enable (this code runs with interrupts disabled)
*/

void twi_init(void) {
	//initialise TWI unit
	TWBR = 0x34;
	TWSR = 0x00;
	/* F_SCL = F_CPU/120 */
}

void twi_start(uint8_t adr, uint8_t rw) {
	//start a TWI communication
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); //enable TWI, send start bit
	while(!(TWCR & _BV(TWINT))); //wait for operation to finish
	//assert(TW_STATUS == TW_START);
	twi_tx(adr | rw);
}

void twi_stop(void) {
	//end a TWI communication
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); //enable TWI, send stop bit
}

void twi_tx(uint8_t b) {
	//send a byte on the TWI
	TWDR = b; //load byte into data register
	TWCR = _BV(TWINT) | _BV(TWEN); //send byte
	while(!(TWCR & _BV(TWINT))); //wait for operation to finish
	//assert(TW_STATUS == TW_MR_SLA_ACK);
}

uint8_t twi_rx(void) {
	//recieve a byte on the TWI
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA); //enable TWI
	while(!(TWCR & _BV(TWINT)));
	return TWDR;
	//assert(TW_STATUS == TW_MR_DATA_NACK);
}

uint8_t twi_rx_NACK(void) {
	//recieve a byte on the TWI
	TWCR = _BV(TWINT) | _BV(TWEN); //enable TWI
	while(!(TWCR & _BV(TWINT)));
	return TWDR;
	//assert(TW_STATUS == TW_MR_DATA_NACK);
}