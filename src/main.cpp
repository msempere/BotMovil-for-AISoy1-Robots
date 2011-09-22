
#include <aisoy1/bot.h>
#include <aisoy1/log.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <stddef.h>

extern "C"{
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
	#include "mirf.h"
	#include "nRF24L01.h"
	#include "AISoyAPI.h"
	#include <unistd.h>
	typedef unsigned char byte;
}


//photo every intevarPhoto miliseconds. (default 1000=1 second)
const int intervalPhoto=500;

//set payload
const int payloadSize=1;

//set channel
const int channelNumber=64;

//photoTimer pid
int PTpid;

//Bot global vars
AISoy1::Image img;
AISoy1::Bot bot;


//take photos every second
void photoTimer() {
	
	while(1){
		//take photo
		img=bot.captureImage();
		
		//save it & unlik
		unlink("html/captured2.jpg");
		img.save("html/captured2.jpg");
		unlink("html/captured.jpg");
		
		//linking
		link("html/captured2.jpg", "html/captured.jpg");
	}
}


//configure radio for TX mode
void Config(){
	init(); //initializing radio
	uint8_t rx_addr[5] = {0x41, 0x49, 0x53, 0x4F, 0x59}; //AISOY
  	setTADDR(rx_addr); //set TX address
  	configRegister(RF_SETUP, 0x07); //Air data rate 1Mbit, 0dBm, Setup LNA
  	configRegister(EN_AA, 0x00); //Disable auto-acknowledge
  	configRegister(SETUP_RETR, 0x00); //Disable retransmision
    configRegister(CONFIG, 0x2A); //Mode TX
	payload = payloadSize; //1 byte payload
	channel = channelNumber; // channel 64

	config(channel,payload); //configure with payload & channel

	configRegister(RF_SETUP, 0x07); //Air data rate 1Mbit, 0dBm, Setup LNA
  	configRegister(EN_AA, 0x00); //Disable auto-acknowledge
  	configRegister(SETUP_RETR, 0x00); //Disable retransmision
	configRegister(CONFIG, 0x2A); //Mode TX
	setRADDR(rx_addr); //set RX address
	setTADDR(rx_addr); //set TX address
	

	fprintf(stderr,"OK. Setup radio RX mode completed.\n\r");
}

//convert char* to int
int Chartoint(char str[]) {

	int i,no=0;
	int len = strlen(str);
	
	for(i = 0; i < len; i++)              
      if(str[i]>='0' && str[i]<='9')  
		no=no*10+str[i]-48;          
	return no; 
}

float GetHeadAngle(char str[]){
	return (float)Chartoint(str)/(float)10;
}


//send first character (new side) from char*
void Send(char *ch){
	byte c=0;
	c=(byte)ch[0];
	send(&c);
	while(isSending()){}
}

//send new velocity
void SendVelocity(char str[]){
	int vel=Chartoint(str);
	byte c=0;
	c=(byte)vel;
	send(&c);
	while(isSending()){}
}


//cancel photoTimer proc
void CancelProc(int sig){
	
	if(kill(PTpid, SIGKILL))
		fprintf(stderr,"OK. PhotoTimer terminated. \n\r");
	else
	    fprintf(stderr,"Error. Coul not kill photoTimer or proc had already been killed. \n\r");
	exit(0);
}


//preparing killing signals
void PrepareSignals(){
	
	void (*signal_term)(int);
	void (*signal_int)(int);
	
	signal_term = signal (SIGTERM,CancelProc);
	signal_int = signal (SIGINT,CancelProc);
}


void PrepareServos(){
	
	//open bot eyes
	bot.moveServo(AISoy1::Eyes,0.5);
	
	//center head
	//bot.moveServo(AISoy1::HeadVertical,0.5);
	bot.moveServo(AISoy1::HeadHorizontal,0.5);
}


//Do all
void start() {
	
	//child will capture images, father continues
   int pid = fork();
   
   
   //If Im a child
   if(pid==0){
	   photoTimer();
	}
	//could not create a child. Maybe we need some viagra, xD
	else if(pid<0){
		fprintf(stderr,"Error. Fork failed.\n\r");
		exit(-1);
	}
	
	//If not child
	else{
	   PTpid=pid;
       std::string option;
       char *selected;
	   char *optionSelected;

	   Config();                 
	   
	   fprintf(stderr,"OK. Ready for options.\n\r");
	   
	   while(1){
		   
			//getting string option
			std::getline (std::cin,option);
						 
			//string to char*
			selected=strdupa(option.c_str());
			
			fprintf(stderr,"OK. We received %s\n\r",selected);
			
			//empty option, nothing to do
			optionSelected=strsep(&selected,"#");
			
			//first selected option (first argument)
			optionSelected=strsep(&selected,"#");
						

			fprintf(stderr,"OK. Option selected:%s.\n\r",optionSelected );
			
			
			//if "botsay", bot has a new phrase to say
			if(strcmp(optionSelected,"botsay")==0){
				char* what = strsep(&selected,"#");
				fprintf(stderr,"OK. %s, I say.\n\r",what);
				bot.say(what);
			}	
			
			//if "botvelocity", we must send new velocity to botmovil
			else if(strcmp(optionSelected,"botvelocity")==0){
				char* newVelocity = strsep(&selected,"#");
				fprintf(stderr,"OK. We have a new velocity: %s .\n\r",newVelocity);
				SendVelocity(newVelocity);
			}	
			
			//if "change", we send a motor movement
			else if(strcmp(optionSelected,"change")==0){
				char* side = strsep(&selected,"#");
				fprintf(stderr,"OK. %s motor movement.\n\r",side);
				Send(side);
			} 	
			
			//if "head", we apply a head movement
			else if(strcmp(optionSelected,"head")==0){
				
				char* headOption = strsep(&selected,"#");
				char* angle = strsep(&selected,"#");
				
				if(strcmp(headOption,"horizontal")==0){
					fprintf(stderr,"OK. %s horizontal head movement.\n\r",angle);
					bot.moveServo(AISoy1::HeadHorizontal,GetHeadAngle(angle));
				}
				else if(strcmp(headOption,"vertical")==0){
					fprintf(stderr,"OK. %s vertical head movement.\n\r",angle);
					bot.moveServo(AISoy1::HeadVertical,GetHeadAngle(angle));
				} else
					fprintf(stderr,"Error. Incorrect selection for head movement.\n\r");
				
			}
			else
				fprintf(stderr,"Error. Selected option.\n\r");		
	   }
	}
	
}


int main(int argc, char **argv){
	

	//initializing servo to default position
	PrepareServos();
	
	//kill signals
	PrepareSignals();
	
	//start bot movil control
	start();
	
	return 0;
}
