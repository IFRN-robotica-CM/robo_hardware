#ifndef PINAGEM_H
#define PINAGEM_H

#include <Arduino.h>

/*
Arduino UNO pinout

13- SONAR_ECHO_FRONTAL
12-	SONAR_TRIGGER_FRONTAL
11-	LED_SENSOR_LINHA_MAIS_DIREITO
10-	LED_SENSOR_DIREITO
09-	LED_SENSOR_ESQUERDO
08-	LED_SENSOR_LINHA_MAIS_ESQUERDO
07-	SENTIDO_RODA_DIREITA
06-	PWM_RODA_DIREITA
05- PWM_RODA_ESQUERDA
04-	SENTIDO_RODA_ESQUERDA
03-	SENSOR_COR_DIR_TCS34
02- SENSOR_COR_ESQ_TCS34
01-	Tx LED 1
00-	Rx LED 2

A0- SENSOR_LINHA_MAIS_DIREITO
A1- SENSOR_LINHA_DIREITO
A2- SENSOR_LINHA_ESQUERDO
A3- SENSOR_LINHA_MAIS_ESQUERDO
A4-	SDA							
A5-	SCL							


*/


class pinagem{
	#define PWM_RODA_ESQUERDA 		5		    //Define o pino que ligara o motor esquerdo para mudar a velocidade de rotacao
	#define SENTIDO_RODA_ESQUERDA   4		    //Define o pino que ligara o motor esquerdo para mudar o sentido de rotacao
	#define PWM_RODA_DIREITA 	    6	        //Define o pino que ligara o motor direito para mudar a velocidade de rotacao
	#define SENTIDO_RODA_DIREITA 	7		    //Define o pino que ligara o motor direito para mudar o sentido de rotacao

	#define SENSOR_LINHA_MAIS_ESQUERDO	A3	    //Define o pino do sensor de refletancia mais esquerdo
	#define SENSOR_LINHA_ESQUERDO	    A2	    //Define o pino do sensor de refletancia esquerdo
	#define SENSOR_LINHA_DIREITO	    A1	    //Define o pino do sensor de refletancia direito
	#define SENSOR_LINHA_MAIS_DIREITO	A0	    //Define o pino do sensor de refletancia mais direito

	#define LED_SENSOR_LINHA_MAIS_ESQUERDO 8    //Define o pino para ligar o sensor de refletancia mais esquerdo
	#define LED_SENSOR_LINHA_ESQUERDO      9    //Define o pino para ligar o sensor de refletancia esquerdo
	#define LED_SENSOR_LINHA_DIREITO       10   //Define o pino para ligar o sensor de refletancia direito
	#define LED_SENSOR_LINHA_MAIS_DIREITO  11   //Define o pino para ligar o sensor de refletancia mais direito

	#define SENSOR_COR_DIR_TCS34	3          //Define o pino para ligar o sensor de cor direito
	#define SENSOR_COR_ESQ_TCS34	2          //Define o pino para ligar o sensor de cor esquerdo

	#define SONAR_TRIGGER_FRONTAL	12           //Define o pino tigger do sensor sonar
	#define SONAR_ECHO_FRONTAL		13          //Define o pino echo do sensor sonar

	#define LED_1		1                       //Define o pino do led 1 da placa
	#define LED_2		0                       //Define o pino do led 2 da placa

};

#endif
