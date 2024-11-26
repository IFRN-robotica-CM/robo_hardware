#include "robo_hardware2.h"
#include <math.h>

int robo_hardware::tipoSensorCor;

//----- construtor -----//
robo_hardware::robo_hardware():sonarFrontal(SONAR_TRIGGER_FRONTAL, SONAR_ECHO_FRONTAL){
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

	//Configura pinos para ligar o sensor de linha
	pinMode(SENSOR_LINHA_MAIS_ESQUERDO, INPUT);
	pinMode(SENSOR_LINHA_ESQUERDO, INPUT);
	pinMode(SENSOR_LINHA_DIREITO, INPUT);
	pinMode(SENSOR_LINHA_MAIS_DIREITO, INPUT);

	//Configura pinos para ligar os LEDS
	pinMode(LED_SMD_VERDE, OUTPUT);
	pinMode(LED_SMD_VERMELHO, OUTPUT);

	pinMode(LED_AMARELO, OUTPUT);
	pinMode(LED_AZUL, OUTPUT);
	pinMode(LED_VERMELHO, OUTPUT);
	pinMode(LED_VERDE, OUTPUT);

	//Configura o sensor de cor
	Serial.begin(9600);
  	if (tcsE.begin() && tcsE.begin() ) {
     	tcsD.enable();
		tcsE.enable();
		ligarLedSmdVerde();
		delay(500);
		desligarLedSmdVerde();
  	}
  	else{
    	ligarLedSmdVermelho();
		delay(500);
		desligarLedSmdVermelho();
     }

  	pinMode(LED_SENSOR_COR_DIREITO,  OUTPUT);
  	pinMode(LED_SENSOR_COR_ESQUERDO, OUTPUT);

  	digitalWrite(LED_SENSOR_COR_DIREITO,  HIGH);
  	digitalWrite(LED_SENSOR_COR_ESQUERDO, HIGH);

	//configura sensor frontal de distância a laiser
	if (!lox.begin()) {
    Serial.println(F("Failed"));
	}
	lox.startRangeContinuous();
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
	delay(100);
	valorLedLigado    = lerSensorDeLinha(sensor);

	if((valorLedLigado -  valorLedDesligado) < 1){
		return valorLedDesligado;
	}
	else{
		return valorLedLigado -  valorLedDesligado;
	}
	
}

//----- função para ler o sensor sonar -----//
float robo_hardware::lerSensorSonarFrontal(){
	long microsec = sonarFrontal.timing();
	return sonarFrontal.convert(microsec, Ultrasonic::CM);  //retorna a distância do sensor ao obstáculo em cm.
}

//----- funções para sensor de cor -----//
RGBC robo_hardware::getRGBSensorDireito() const{
	int red, green, blue, clear;
	tcsD.getRawData(&red, &green, &blue, &clear);
	return {red, green, blue, clear};
}

RGBC robo_hardware::getRGBSensorEsquerdo() const{
	int red, green, blue, clear;
	tcsE.getRawData(&red, &green, &blue, &clear);
	return {red, green, blue, clear};
}

//----- funções para sensor Laiser-----//
int robo_hardware::lerSensorLaiserFrontal(){
	if (lox.isRangeComplete()) {
    	 valorLaiser = lox.readRange();
  	}

	return valorLaiser;
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