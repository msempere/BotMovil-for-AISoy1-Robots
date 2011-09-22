/*
 * AISoyAPI.h
 *
 *  Created on: 02/06/2010
 *      Author: jvidal
 */

#ifndef AISOYAPI_H_
#define AISOYAPI_H_

void pabort(const char *);
void InitConfig(void);
void output_low_CE(void);
void output_high_CE(void);
void PulseCE(void);
bool Radio_activity(void);
void Reset_Radio_Activity();
int AISOY_RADIO_spi_write_register (int, unsigned char, unsigned char *,int);
//DESHUSO: int AISOY_RADIO_spi_read_payload(int, unsigned char, unsigned char *, int);
int AISOY_RADIO_spi_read_register(int, unsigned char, unsigned char *,int);
void setChannel(uint8_t canal);//De 0 a 127
void setPayloadWidth(uint8_t anchura);//De 1 a 32 bytes

#endif /* AISOYAPI_H_ */
