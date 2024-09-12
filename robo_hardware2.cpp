#include "robo_hardware2.h"
#include <math.h>

int robo_hardware::tipoSensorCor;

robo_hardware::robo_hardware():	corDireita34(SENSOR_COR_DIR_TCS34),
																corEsquerda34(SENSOR_COR_ESQ_TCS34),
																sonarFrontal(SONAR_TRIGGER_FRONTAL, SONAR_ECHO_FRONTAL),
																led1(LED_1), led2(LED_2)
{
	tipoSensorCor = TCS23;
}

void robo_hardware::tensao(float valor_por_cento,int pino){
  float k = 255/100.0;

  if(valor_por_cento < -100) 
    valor_por_cento = -100;	//se o valor passado em valor_por_cento for menor que -100 obriga-se o mmotor a ficar em -100
  if(valor_por_cento >  100) 
    valor_por_cento =  100;	//se o valor passado em valor_por_cento for maior que 100 obriga-se o mmotor a ficar em 100

  float valor_ate_255 = valor_por_cento * k;
  
  analogWrite(pino, abs(valor_ate_255)); 
}

void robo_hardware::habilitaTCS34(){
	tipoSensorCor = TCS34;
}

void robo_hardware::configurar(bool habilitar_garra){
//  Serial.begin(9600);

	//Com essas funcoes os sonares sao calibrados 
	//Quanto maior o valor de CALIBRACAO_SONAR menor a inclinacao da curva de calibracao 
	sonarFrontal.setDivisor(CALIBRACAO_SONAR, Ultrasonic::CM);  

  pinMode(PWM_RODA_ESQUERDA, OUTPUT); 
  pinMode(PWM_RODA_DIREITA, OUTPUT); 
  pinMode(SENTIDO_RODA_ESQUERDA, OUTPUT); 
  pinMode(SENTIDO_RODA_DIREITA, OUTPUT);

  pinMode(LED_SENSOR_LINHA_MAIS_ESQUERDO, OUTPUT);
  pinMode(LED_SENSOR_LINHA_ESQUERDO, OUTPUT);
  pinMode(LED_SENSOR_LINHA_DIREITO, OUTPUT);
  pinMode(LED_SENSOR_LINHA_MAIS_DIREITO, OUTPUT);

	led1.config();
	led2.config();

	corDireita34.config();
	corEsquerda34.config();
}

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

float robo_hardware::lerSensorSonarFrontal(){
	long microsec = sonarFrontal.timing();
	return sonarFrontal.convert(microsec, Ultrasonic::CM);  //retorna a distância do sensor ao obstáculo em cm.
}

HSV robo_hardware::getHSVEsquerdo(){
  return corEsquerda34.getHSV();
}

HSV robo_hardware::getHSVDireito(){
  return corDireita34.getHSV();
}

RGB robo_hardware::getRGBEsquerdo(){
  return corEsquerda34.getRGB();
}

RGB robo_hardware::getRGBDireito(){
      return corDireita34.getRGB();
}

void  robo_hardware::salvarCalibracao(calibracao_dados calibraca_val){
	//EEPROM.put(ENDERECO_EEPROM, calibraca_val);
}

void robo_hardware::lerCalibracao(calibracao_dados &cal){
	//EEPROM.get(ENDERECO_EEPROM, cal);
}

void robo_hardware::ligarLed(const int led)const{
	switch(led){
		case 1:
			led1.ligar();
		break;
		case 2:
			led2.ligar();
		break;
		default:
		break;	
	}
}

void robo_hardware::desligarLed(const int led)const{
	switch(led){
		case 1:
			led1.desligar();
		break;
		case 2:
			led2.desligar();
		break;
		default:
		break;	
	}
}

void robo_hardware::ligarTodosLeds()const{
	led1.ligar();
	led2.ligar();
}

void robo_hardware::desligarTodosLeds()const{
	led1.desligar();
	led2.desligar();
}

const float robo_hardware::lerDadosSensorDeLinha(const int sensor){
	float valorLedDesligado = 0;
	float valorLedLigado    = 0;

	valorLedDesligado = lerSensorDeLinha(sensor, OFF);
	valorLedLigado    = lerSensorDeLinha(sensor);
	

	return valorLedLigado -  valorLedDesligado;
}

