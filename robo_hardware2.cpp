#include "robo_hardware2.h"
#include <math.h>

int robo_hardware::tipoSensorCor;
VL53L0X robo_hardware::sensor;

//----- construtor -----//
robo_hardware::robo_hardware():
	sonarFrontal(SONAR_TRIGGER_FRONTAL, SONAR_ECHO_FRONTAL),
	tcsD(TCS34725_INTEGRATIONTIME_614MS,TCS34725_GAIN_1X),
	tcsE(TCS34725_INTEGRATIONTIME_614MS,TCS34725_GAIN_1X){
}

//----- funções de controle dos motores -----//
void robo_hardware::tensao(float valor_por_cento,int pino){
  float k = 255/100.0;

  if(valor_por_cento < -100) 
    valor_por_cento = -100;	//se o valor passado em valor_por_cento for menor que -100 obriga-se o mmotor a ficar em -100
  if(valor_por_cento >  100) 
    valor_por_cento =  100;	//se o valor passado em valor_por_cento for maior que 100 obriga-se o mmotor a ficar em 100

  float valor_ate_255 = valor_por_cento * k;
  
  analogWrite(pino, abs(valor_ate_255)); 
}

void robo_hardware::acionarMotores(float motor1, float motor2){
 
  if(motor1 < 0){
    digitalWrite(SENTIDO_RODA_ESQUERDA, false);
    tensao(motor1,PWM_RODA_ESQUERDA);  
  }else{
    digitalWrite(SENTIDO_RODA_ESQUERDA, true);
    motor1 = 100 - motor1;
    tensao(motor1,PWM_RODA_ESQUERDA);  
  }
  
  if(motor2 < 0){
    digitalWrite(SENTIDO_RODA_DIREITA, false);
    tensao(motor2,PWM_RODA_DIREITA);  
  }else{
    digitalWrite(SENTIDO_RODA_DIREITA, true);
    motor2 = 100 - motor2;
    tensao(motor2,PWM_RODA_DIREITA);  
  }
    
}

//----- função de inicialização -----//
void robo_hardware::configurar(){
	//Com essas funcoes os sonares sao calibrados 
	sonarFrontal.setDivisor(CALIBRACAO_SONAR, Ultrasonic::CM);  

	//Configura pinos da ponte H
  	pinMode(PWM_RODA_ESQUERDA, OUTPUT); 
  	pinMode(PWM_RODA_DIREITA, OUTPUT); 
	pinMode(SENTIDO_RODA_ESQUERDA, OUTPUT); 
	pinMode(SENTIDO_RODA_DIREITA, OUTPUT);

	//Configura pinos para ligar o sensor de linha
	pinMode(LED_SENSOR_LINHA_MAIS_ESQUERDO, OUTPUT);
	pinMode(LED_SENSOR_LINHA_ESQUERDO, OUTPUT);
	pinMode(LED_SENSOR_LINHA_DIREITO, OUTPUT);
	pinMode(LED_SENSOR_LINHA_MAIS_DIREITO, OUTPUT);
	pinMode(LED_SENSOR_LINHA_CENTRAL, OUTPUT);
	pinMode(LED_SENSOR_LINHA_FRONTAL, OUTPUT);

	//Configura pinos para ligar o sensor de linha
	pinMode(SENSOR_LINHA_MAIS_ESQUERDO, INPUT);
	pinMode(SENSOR_LINHA_ESQUERDO, INPUT);
	pinMode(SENSOR_LINHA_DIREITO, INPUT);
	pinMode(SENSOR_LINHA_MAIS_DIREITO, INPUT);
	pinMode(SENSOR_LINHA_CENTRAL, INPUT);
	pinMode(SENSOR_LINHA_FRONTAL, INPUT);

	//Configura pinos para ligar os LEDS
	pinMode(LED_SMD_VERDE, OUTPUT);
	pinMode(LED_SMD_VERMELHO, OUTPUT);

	pinMode(LED_AMARELO, OUTPUT);
	pinMode(LED_AZUL, OUTPUT);
	pinMode(LED_VERMELHO, OUTPUT);
	pinMode(LED_VERDE, OUTPUT);

	//Configura o sensor de cor
	Wire.begin();
	tcsD.begin();
	tcsE.begin();

	pinMode(SEL_A, OUTPUT);
	pinMode(SEL_B, OUTPUT);
	
	digitalWrite(SEL_A, LOW);
	digitalWrite(SEL_B, HIGH);
	
	//configura sensor frontal de distância a laiser
	sensor.init();
	sensor.setTimeout(500);

	//configurar o servo do braço
	servoBraco.attach(SERVO_BRACO); // pino do braço
  	servoGarra.attach(SERVO_GARRA); // pino da garra

	servoGarra.write(0);  // fecha a garra
  	servoBraco.write(0);
}

//----- função para ler o sensor de linha com ruido -----//
const float robo_hardware::lerSensorDeLinha(const int sensor, bool ledLigado=true){
	int pino;
	float val=0;
	switch(sensor){
		case SENSOR_LINHA_MAIS_ESQUERDO:
			pino = LED_SENSOR_LINHA_MAIS_ESQUERDO;
		break;
			
		case SENSOR_LINHA_ESQUERDO:
			pino = LED_SENSOR_LINHA_ESQUERDO;
		break;

		case SENSOR_LINHA_DIREITO:
			pino = LED_SENSOR_LINHA_DIREITO;
		break;

		case SENSOR_LINHA_MAIS_DIREITO:
			pino = LED_SENSOR_LINHA_MAIS_DIREITO;
		break;

		case SENSOR_LINHA_CENTRAL:
			pino = LED_SENSOR_LINHA_CENTRAL;
		break;

		case SENSOR_LINHA_FRONTAL:
			pino = LED_SENSOR_LINHA_FRONTAL;
		break;
	}

	digitalWrite(pino, ledLigado);

	delay(1);
	
	val = ( 100 - 100.0 * ( analogRead(sensor) )/1023.0);

	digitalWrite(pino, LOW);

	return val;
}

//----- função para ler o sensor de linha sem ruido -----//
const float robo_hardware::lerDadosSensorDeLinha(const int sensor){
	float valorLedDesligado = 0;
	float valorLedLigado    = 0;

	valorLedDesligado = lerSensorDeLinha(sensor, LOW);
	valorLedLigado    = lerSensorDeLinha(sensor);
	
	return valorLedLigado -  valorLedDesligado;
	
	
}

//----- função para ler o sensor sonar -----//
float robo_hardware::lerSensorSonarFrontal(){
	long microsec = sonarFrontal.timing();
	return sonarFrontal.convert(microsec, Ultrasonic::CM);  //retorna a distância do sensor ao obstáculo em cm.
}

//----- funções para sensor de cor -----//
RGBC robo_hardware::getRGBSensorEsq() const{
	int red, green, blue, clear;
	tcsE.getRawData(&red, &green, &blue, &clear);
	return {red, green, blue, clear};
}

RGBC robo_hardware::getRGBSensorDir() const{
	int red, green, blue, clear;
	tcsD.getRawData(&red, &green, &blue, &clear);
	return {red, green, blue, clear};
}

void robo_hardware::canal00() const{
	digitalWrite(SEL_A, LOW);
	digitalWrite(SEL_B, LOW);
}

void robo_hardware::canal01() const{
	digitalWrite(SEL_A, LOW);
	digitalWrite(SEL_B, HIGH);
}

void robo_hardware::canal10() const{
	digitalWrite(SEL_A, HIGH);
	digitalWrite(SEL_B, LOW);
}

RGBC robo_hardware::lerSensorDeCorEsq(){
	canal00();
	delay(100);
	return getRGBSensorEsq();
	delay(100);	
}

RGBC robo_hardware::lerSensorDeCorDir(){
	canal10();
	delay(100);
	return getRGBSensorDir();
	delay(100);
}

//----- funções para sensor Laiser-----//
int robo_hardware::lerSensorLaserFrontal() const{
	canal01();
	delay(1);

	int valDist;
	valDist =sensor.readRangeSingleMillimeters();
	return valDist;
}

//----- funções para os leds -----//
void robo_hardware::ligarLed(const int led)const{
	digitalWrite( led, HIGH);
}

void robo_hardware::desligarLed(const int led)const{
	digitalWrite( led, LOW);
}

void robo_hardware::ligarTodosLeds()const{
	ligarLedSmdVerde();
	ligarLedSmdVermelho();
	ligarLedAmarelo(); 
	ligarLedAzul();     
	ligarLedVermelho();
	ligarLedVerde();
}

void robo_hardware::desligarTodosLeds()const{
	desligarLedSmdVerde();
	desligarLedSmdVermelho();
	desligarLedAmarelo(); 
	desligarLedAzul();     
	desligarLedVermelho();
	desligarLedVerde();
}