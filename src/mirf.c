/**
 * Mirf
 *
 * @authors jvidal & cpallardo
 *
 */

/*
    Copyright (c) 2010 AISoy Robotics S.L.<info@aisoy.com>
*/

#include "mirf.h"

/**
 * Configure channel, payload and all of the nRF24l01 fields.
 */
void init(){
	channel = 0;//Hay que ponerlo en min = 0, medio = 64, maximo = 127, el ideal es el medio 2400MHz + 64MHz = 2064 Mhz
	payload = 14;

    // Initialize spi module
    InitConfig();
    ceLow();
}


// Sets the important registers in the MiRF module and powers the module
// in receiving mode
// NB: channel and payload must be set now.
//void config(){
void config(int canal, int sizeBuf){

	ConfTestRXSensibilidad(canal,sizeBuf);//Le pasamos el canal

    // Set RF channel
	configRegister(RF_CH,channel);

    // Set length of incoming payload 
	configRegister(RX_PW_P0, payload);
	configRegister(RX_PW_P1, payload);

    // Start receiver 
    powerUpRx();
    flushRx();
}

// Sets the receiving address
void setRADDR(uint8_t * adr){
	ceLow();
	writeRegister(RX_ADDR_P1, adr, mirf_ADDR_LEN);
	ceHi();
}

// Sets the transmitting address
void setTADDR(uint8_t * adr){
	// RX_ADDR_P0 must be set to the sending addr for auto ack to work.
	writeRegister(RX_ADDR_P0,adr,mirf_ADDR_LEN);
	writeRegister(TX_ADDR,adr,mirf_ADDR_LEN);
}

// Checks if data is available for reading
extern bool dataReady(){
    // See note in getData() function - just checking RX_DR isn't good enough
	uint8_t status = getStatus();

    // We can short circuit on RX_DR, but if it's not set, we still need
    // to check the FIFO for any pending packets
    if ( status & (1 << RX_DR) ) return 1;
    return !rxFifoEmpty();
}

/**
 * Function that tests if the rxfifo is empty or not
 */
extern bool rxFifoEmpty(){
	uint8_t fifoStatus;

	readRegister(FIFO_STATUS,&fifoStatus,sizeof(uint8_t));
	return (fifoStatus & (1 << RX_EMPTY));
}

// Reads payload bytes into data array
extern void getData(uint8_t * data){
//    csnLow();                               // Pull down chip select
	AISOY_RADIO_spi_read_register(iFd, R_RX_PAYLOAD, data, payload);
	data[payload]=0;
	/*TEST*/uint8_t aux;
//	/*TEST*/ //printf("GETDATA: El valor es: %s\n\r", data);

	/**
     *  NVI: per product spec, p 67, note c:
     *  "The RX_DR IRQ is asserted by a new packet arrival event. The procedure
     *  for handling this interrupt should be: 1) read payload through SPI,
     *  2) clear RX_DR IRQ, 3) read FIFO_STATUS to check if there are more
     *  payloads available in RX FIFO, 4) if there are more data in RX FIFO,
     *  repeat from step 1)."
     *  So if we're going to clear RX_DR here, we need to check the RX FIFO
     * in the dataReady() function
     */
    configRegister(STATUS,(1<<RX_DR));   // Reset status register
}

// Clocks only one byte into the given MiRF register
void configRegister(uint8_t reg, uint8_t value){

//	/*TEST*/uint8_t aux;
//	/*TEST*/readRegister(reg, &aux, 1);
//	/*TEST*/printf("[configRegister]El valor de %X ANTES es %i\n\r", reg, aux);
//	/*TEST*/printf("[configRegister]Y el de values es %i\n\r", value);

    AISOY_RADIO_spi_write_register(iFd, reg, &value, sizeof(uint8_t));

//	/*TEST*/readRegister(reg, &aux, 1);
//	/*TEST*/printf("[configRegister]El valor de %X DESPUÉS es %i\n\r", reg, aux);
}

// Reads an array of bytes from the given start position in the MiRF registers.
void readRegister(uint8_t reg, uint8_t * value, uint8_t len){
    AISOY_RADIO_spi_read_register(iFd, reg, value, len);
}

// Writes an array of bytes into inte the MiRF registers.
void writeRegister(uint8_t reg, uint8_t * value, uint8_t len){
	AISOY_RADIO_spi_write_register(iFd, reg, value, len);
}

// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.
void send(uint8_t * value){
	uint8_t status = getStatus();
    while (PTX) {
	    status = getStatus();
	    if((status & ((1 << TX_DS)  | (1 << MAX_RT)))){
		    PTX = 0;
		    break;
	    }
    }                  // Wait until last paket is send
    ceLow();
    powerUpTx();       // Set to transmitter mode , Power up

    uint8_t aux = NOP;
    AISOY_RADIO_spi_write_register(iFd, FLUSH_TX, &aux, 1);

//	/*TEST*/readRegister(CONFIG, &aux, 1);
//	/*TEST*/printf("[Inside-Send1]El valor de CONFIG ANTES es %i\n\r", aux);

	AISOY_RADIO_spi_write_register(iFd, W_TX_PAYLOAD, value, payload);

//	/*TEST*/readRegister(CONFIG, &aux, 1);
//	/*TEST*/printf("[Inside-Send2]El valor de CONFIG ANTES es %i\n\r", aux);

	ceHi();                     // Start transmission

//	/*TEST*/readRegister(CONFIG, &aux, 1);
//	/*TEST*/printf("[Inside-Send3]El valor de CONFIG ANTES es %i\n\r", aux);
}

/**
 * isSending.
 *
 * Test if chip is still sending.
 * When sending has finished return chip to listening.
 *
 */
bool isSending(){
	uint8_t status;
	if(PTX){
		status = getStatus();
//	    printf("Status raro vale %i\n\r", status);

		//  if sending successful (TX_DS) or max retries exceded (MAX_RT).
		if((status & ((1 << TX_DS)  | (1 << MAX_RT)))){
//			printf("Bajo el PTX\n\r");
//			powerUpRx();//JVR 2010-06-17 No dejamos que se ponga en modo RX
			return false; 
		}
		return true;
	}
	return false;
}

uint8_t getStatus(){
	uint8_t rv;
	readRegister(STATUS, &rv, 1);
	return rv;
}

void powerUpRx(){
	PTX = 0;
	ceLow();
//	printf("LO QUE JOSE QUIERE SABER DEL CONFIG (powerUpRx) es %i\n\r", (mirf_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) )));
	configRegister(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (1<<PRIM_RX) ) );
	ceHi();
//	printf("LO QUE JOSE QUIERE SABER DEL SATATUS es %i\n\r", ((1 << TX_DS) | (1 << MAX_RT)));
	configRegister(STATUS,(1 << TX_DS) | (1 << MAX_RT)); 
}

void flushRx(){
	uint8_t cero = NOP;
	AISOY_RADIO_spi_write_register(iFd, FLUSH_RX, &cero, 1);
    //Spi.transfer( FLUSH_RX );
}

void powerUpTx(){
	PTX = 1;
//	printf("LO QUE JOSE QUIERE SABER DEL CONFIG (powerUpTx) es %i\n\r", (mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) )));
	configRegister(CONFIG, mirf_CONFIG | ( (1<<PWR_UP) | (0<<PRIM_RX) ) );
}

void ceHi(){
	output_high_CE();
}

void ceLow(){
	output_low_CE();
}

//Este test pasa por los canales bajo, medio y alto para una frecuencia de 2Mbps
void ConfTestRXSensibilidad(int canal, int sizeBuf)
{
	channel = canal;
	payload = sizeBuf;

	configRegister(CONFIG, 0x03);
	configRegister(EN_AA, 0x00); //Disable auto-acknowledge
	configRegister(SETUP_RETR, 0x00);//Disable all auto-acknowledge
	configRegister(RF_CH, channel);
	configRegister(RF_SETUP, 0x0F); //Air data rate 2Mbit, 0dBm, Setup LNA
	configRegister(RX_PW_P0, 0x20);//32 bytes payload

}
