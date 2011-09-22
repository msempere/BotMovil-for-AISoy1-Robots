/*
 * DracoRadio.c
 *
 *  Created on: 2/06/2010
 *      Author: jvidal & cpallardo
 */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>  /* ioctl */
#include <stdint.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
//#include "DRACO_RADIO_module.h"
#include "AISoyGlobal.h"
#include "DRACO_GPIO_mod.h"
#include "nRF24L01.h"
#include "mirf.h"

/**
 * Funion que devuelve por pantalla un error y aborta la ejecución
 */
void pabort(const char *s)
{
        perror(s);
        abort();
}


//Inicia tanto el módulo de E/S como el SPI
void InitConfig(void)
{
	// preparación del entorno para el bus SPI
	iFd = open("/dev/spidev1.0", O_RDWR);
	if(iFd < 0)
		pabort("can't open device");

	int ret = 0;
	int mode = 0, bits = 0, speed = 10000000;

	/*
	 * spi mode
	 */
	ret = ioctl(iFd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
			pabort("can't set spi mode");

	ret = ioctl(iFd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
			pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(iFd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
			pabort("can't set bits per word");

	ret = ioctl(iFd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
			pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(iFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
			pabort("can't set max speed hz");

	ret = ioctl(iFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
			pabort("can't get max speed hz");

	//printf("spi mode: %d\n", mode);
	//printf("bits per word: %d\n", bits);
	//printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	// preparación de los GPIO
	iFile = open("/dev/DracoGpio", O_RDWR);
}

/**
 * Función que baja el CE
 */
void output_low_CE(void){
	unsigned long args [3];
//	printf("Ponemos a nivel BAJO el PIN177\n");
	args[0]=177;
	args[1]=0;
	ioctl(iFile,DRACO_GPIO_SET_IOC,args);
}

/**
 * Función que sube el CE
 */
void output_high_CE(void){
	unsigned long args [3];
//	printf("Ponemos a nivel ALTO el PIN177\n");
	args[0]=177;
	args[1]=1;
	ioctl(iFile,DRACO_GPIO_SET_IOC,args);
}

/**
 * Función que sube el CE durante un tiempo y luego lo vuelve a bajar
 */
void PulseCE(void)
{
	output_high_CE();
	usleep(1000);
	output_low_CE();
}

//Mira el estado de la patilla IRQ del micro de RF
bool Radio_activity(void)
{
	unsigned long args [3];
	args[0]=RF_IRQ;
    ioctl(iFile,DRACO_GPIO_GET_IOC,args);
	return (bool) args[1];
}

/**
 * Resetea el flag IRQ
 */
void Reset_Radio_Activity(){
	unsigned long args [3];
	args[0]=RF_IRQ;
	args[1]=0;
    ioctl(iFile,DRACO_GPIO_SET_IOC,args);
}

/**
 * Función creada a imagen de DRACO_RADIO_spi_write_register
 * para que escriba en los registros más grandes de los 1F.
 * Es decir, para escribir todos menos los de lectura
 */
int AISOY_RADIO_spi_write_register (int iFd, unsigned char cRegister, unsigned char *cData,int len)
{
//	  uint8_t retval;

	  if(cRegister < 0x20)//Entra aquí si el resgitro es de escritura o de lectura de registros (R_REGISTER y W_REGISTER)
	  {
			unsigned char cBuf[33]; // maximo command + 32 bytes
		    struct spi_ioc_transfer xfer[2];
		    int i;
			int status=0;
		    unsigned char cCommand=0;

		    //	printf("writing to register %x\n",cRegister);
		    cCommand=((cRegister & 0x1F) | 0x20); //cCommand = cRegister + 0x20;

		//	printf("cCommand %x\n",cCommand);
			memset(xfer, 0, sizeof xfer);
		    memset(cBuf, 0, sizeof cBuf);

			cBuf[0]=cCommand;
			for(i=1;i<=len;i++){
		    	cBuf[i]=cData[i-1];
		        //printf("cbuf %d = %x\n",i,cBuf[i]);
		    }

		    if (len > sizeof cBuf)
		    	len = sizeof cBuf;

		    //  printf("len %d\n",len);
		    xfer[0].tx_buf = (__u64) cBuf;
			xfer[0].len = len+1;

		    status = ioctl(iFd, SPI_IOC_MESSAGE(1), xfer);
		    if (status < 0) {
		    	perror("SPI_IOC_MESSAGE");
		        return;
			}
			return status;

	  }
	  else //Entra aquí si es otro registro (R_RX_PAYLOAD, W_TX_PAYLOAD, FLUSH_TX, FLUSH_RX, REUSE_TX_PL y NOP)
	  {
      //Entra aquí si es para escribir el contenido del buffer de envio (W_TX_PAYLOAD) o para leer el buffer de recepción (R_RX_PAYLOAD)
	    if((cRegister != FLUSH_TX) && (cRegister != FLUSH_RX) && (cRegister != REUSE_TX_PL) && (cRegister != NOP))
	    {
//	    	printf("EL VALOR DE cRegister es: %i\n\r", cRegister);
	    	unsigned char cBuf[33]; // maximo command + 32 bytes
	        struct spi_ioc_transfer xfer[2];
	        int i;
	    	int status=0;

	    	memset(xfer, 0, sizeof xfer);
	        memset(cBuf, 0, sizeof cBuf);

	        if (len > sizeof cBuf)
	        	len = sizeof cBuf;

	        cBuf[0]=cRegister;
	    	for(i=1;i<=len;i++){
	        	cBuf[i]=cData[i-1];
	        }
	        //  printf("len %d\n",len);
	        xfer[0].tx_buf = (__u64) cBuf;
	    	xfer[0].len = len+1;

	        status = ioctl(iFd, SPI_IOC_MESSAGE(1), xfer);
	        if (status < 0) {
	        	perror("SPI_IOC_MESSAGE");
	            return;
	    	}
	    	return status;
	    }
	    else //Sería para los que tienen 1 byte como FLUSH_TX, FLUSH_RX, REUSE_TX_PL, NOP
	    {
	    	unsigned char cBuf[33]; // maximo command + 32 bytes
			struct spi_ioc_transfer xfer[2];
			int i;
			int status=0;

			memset(xfer, 0, sizeof xfer);
			memset(cBuf, 0, sizeof cBuf);

			if (len > sizeof cBuf)
				len = sizeof cBuf;

			cBuf[0]=cRegister;
			for(i=1;i<=len;i++){
				cBuf[i]=cData[i-1];
			}
			//  printf("len %d\n",len);
			xfer[0].tx_buf = (__u64) cBuf;
			xfer[0].len = len+1;

			status = ioctl(iFd, SPI_IOC_MESSAGE(1), xfer);
			if (status < 0) {
				perror("SPI_IOC_MESSAGE");
				return;
			}
			return status;
	    }
	  }
}

/** En deshuso, usar AISOY_RADIO_spi_read_register **/
//int AISOY_RADIO_spi_read_payload(int iFd, unsigned char cRegister, unsigned char *cData,int len)
//{
//    //unsigned char cCommand=0;
//	int status=0;
//
//	unsigned char cBuf[33]; // maximo command + 32 bytes
//    struct spi_ioc_transfer xfer[2];
//    int i;
//	//printf("Reading from register %x\n",cRegister);
//    //cCommand=cRegister & 0x1F;
//
//	memset(xfer, 0, sizeof xfer);
//    memset(cBuf, 0, sizeof cBuf);
//
//	//cBuf[0]=cRegister;
//    if (len > sizeof cBuf){
//        len = sizeof cBuf;
//    }
//
//	cBuf[0] = cRegister;
//	xfer[0].tx_buf = (__u64) cBuf;
//	xfer[0].len = 1;
//
//	xfer[1].rx_buf = (__u64) cBuf;
//	xfer[1].len = len;
//
//	status = ioctl(iFd, SPI_IOC_MESSAGE(2), xfer);
//	if (status < 0) {
//		perror("SPI_IOC_MESSAGE");
//		return;
//	}
//
//	for(i=0;i<len;i++)
//	{
//		cData[i]=cBuf[i];
//		//printf("cData %d: %c\n",i,cData[i]);
//	}
//	cData[i+1]=NULL;
//	//printf("cData %s\n",cData);
//	return status;
//}

int AISOY_RADIO_spi_read_register(int iFd, unsigned char cRegister, unsigned char *cData,int len)
{
	//printf("ENTRAMOS EN AISOY_RADIO_spi_read_register\n\r");
    unsigned char cCommand=0;
	int status=0;

	unsigned char cBuf[33]; // maximo command + 32 bytes

	uint8_t mem = (int)((len-1)/7)+2;
	//printf("mem=%i\n\r",mem);
    struct spi_ioc_transfer xfer[mem];


    int i;
	//printf("Reading from register %x\n",cRegister);

    //Borramos el buffer
    for(i=0;i<33;i++) cBuf[i]=' ';
    cBuf[32]=0;

    if(cRegister < 0x20)//Entra aquí si el resgitro es de escritura o de lectura de registros (R_REGISTER y W_REGISTER)
    {
    	//printf("ENTRAMOS EN cRegister\n\r");

    	//printf("Reading from register %x\n",cRegister);
        cCommand=cRegister & 0x1F;

    	memset(xfer, 0, sizeof xfer);
    	memset(cBuf, 0, sizeof cBuf);

		cBuf[0]=cCommand;
		if (len > sizeof cBuf)
			len = sizeof cBuf;

		cBuf[0] = cCommand;
		xfer[0].tx_buf = (__u64) cBuf;
		xfer[0].len = 1;

		xfer[1].rx_buf = (__u64) cBuf;
		xfer[1].len = len;

		status = ioctl(iFd, SPI_IOC_MESSAGE(2), xfer);
    	if (status < 0) {
    			perror("SPI_IOC_MESSAGE");
    			return;
    	}

    	for(i=0;i<len;i++)
    	{
    //		printf("cbuf %d %x\n",i,cBuf[i]);
    			cData[i]=cBuf[i];
    	}
    	return status;

    }
    else if (cRegister == R_RX_PAYLOAD)
    {

    	//printf("ENTRAMOS EN R_RX_PAYLOAD\n\r");
    	memset(xfer, 0, sizeof xfer);//Llena todo de ceros el xfer
        memset(cBuf, 0, sizeof cBuf);//Llena todo de ceros el cBuf

        //printf("LEN0 = %i\n\r",len);
    	//cBuf[0]=cRegister;
        if (len > sizeof cBuf){
            len = sizeof cBuf;
        }
        //printf("LEN1 = %i\n\r",len);

		cBuf[0] = cRegister;
		xfer[0].tx_buf = (__u64) cBuf;
		xfer[0].len = 1;

		int j;
		for(j=1; j<mem; j++){ //Escribimos en tantas celdas comoo sea necesario
			xfer[j].rx_buf = (__u64) cBuf+((j-1)*7);
			xfer[j].len = 7;
		}

//		xfer[1].rx_buf = (__u64) cBuf;
//		xfer[1].len = 7;
////		xfer[1].delay_usecs = 100;
//
//		xfer[2].rx_buf = (__u64) cBuf+7;//Funciona hasta el payload = 14 inclusive mem = 3
//		xfer[2].len = 7;
////		xfer[2].delay_usecs = 200;
//
//		xfer[3].rx_buf = (__u64) cBuf+14;//Funciona hasta el payload = 21 inclusive mem = 4
//		xfer[3].len = 7;
////		xfer[3].delay_usecs = 300;
//
//		xfer[4].rx_buf = (__u64) cBuf+21;//Funciona hasta el payload = 28 inclusive mem = 5
//		xfer[4].len = 7;
////		xfer[4].delay_usecs = 400;
//
//		xfer[5].rx_buf = (__u64) cBuf+28;//Funciona hasta el payload = 32  inclusive mem = 6
//		xfer[5].len = 7;
////		xfer[5].delay_usecs = 400;

    	status = ioctl(iFd, SPI_IOC_MESSAGE(mem), xfer);

    	if (status < 0) {
    		perror("SPI_IOC_MESSAGE");
    		return;
    	}

    	for(i=0;i<len;i++)
    	{
    		cData[i]=cBuf[i];
    		//printf("cData %d: %c\n",i,cData[i]);
    	}
    	cData[len]=0;
    	//printf("cData %s\n",cData);
    	return status;
    }
}

void setChannel(uint8_t canal)//De 0 a 127
{
	channel = canal;//channel es la variable del canal, sería el atributo channel de la clase mirf, pero en c no hay POO
	configRegister(RF_CH,channel);
}

void setPayloadWidth(uint8_t anchura)//De 1 a 32 bytes
{
	payload = anchura;
	configRegister(RX_PW_P0, payload);
	configRegister(RX_PW_P1, payload);

}


