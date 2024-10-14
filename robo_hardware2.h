#ifndef ROBO_HARDWARE_H
#define ROBO_HARDWARE_H


#include <Arduino.h>

#include "cor.h"
#include "pinagem.h"
#include "Ultrasonic.h"
#include "CorTcs34.h"
#include "led_botoes/Led.h"

enum{
	TCS23,
	TCS34
};

struct calibracao_dados{
	HSV brancoDir;
	HSV brancoEsq;
	HSV pretoDir;
	HSV pretoEsq;
	HSV verdeDir;
	HSV verdeEsq;
	HSV cinzaDir;
	HSV cinzaEsq;

	int refletanciaDir;
	int refletanciaMaisDir;
	int refletanciaEsq;
	int refletanciaMaisEsq;
	

};

struct refletancia_dados{
	float valorLedLigado;
	float valorLedDesligado;
	float valorDiferenca;
};

class robo_hardware:private pinagem{
private:

	#define AJUSTE_PINO_SENSOR 36
	#define OFF 0
	#define AJUSTE_MOTOR 0.65
	#define MAX_10_BITS 1023.0				//Maior valor que um numero de 10 bits pode obter
	
	#define CALIBRACAO_SONAR  40.4	       //Valor para calibrar os sonares. Quanto maior esse valor menor a inclinação da reta de calibracao

	#define ENDERECO_EEPROM 0

public: 
	//construtor 
	robo_hardware();

  	void configurar();

	//A função para acionar os motores de locomoção do robô
  	void acionarMotores(float percetualMotorEsquerdo, float percetualMotorDireito);

	//As funções retornam o valor lido do sensor refletância
    const float lerSensorDeLinha(const int sensor, bool ledLigado=true); //recebe um pino analogico (A0, A1, A2 e etc) e retorna um valor de 0 a 100 
	
	inline const float lerSensorLinhaEsq(){			return lerSensorDeLinha(SENSOR_LINHA_ESQUERDO);} //retorna um valor de 0 a 100 
	inline const float lerSensorLinhaMaisEsq(){	return lerSensorDeLinha(SENSOR_LINHA_MAIS_ESQUERDO);} //retorna um valor de 0 a 100 
	inline const float lerSensorLinhaDir(){			return lerSensorDeLinha(SENSOR_LINHA_DIREITO);} //retorna um valor de 0 a 100
	inline const float lerSensorLinhaMaisDir(){	return lerSensorDeLinha(SENSOR_LINHA_MAIS_DIREITO);} //retorna um valor de 0 a 100

	const float lerDadosSensorDeLinha(const int sensor);

  	inline const float lerSensorLinhaEsqSemRuido(){			return lerDadosSensorDeLinha(SENSOR_LINHA_ESQUERDO);} //retorna um valor de 0 a 100  
	inline const float lerSensorLinhaMaisEsqSemRuido(){return lerDadosSensorDeLinha(SENSOR_LINHA_MAIS_ESQUERDO);} //retorna um valor de 0 a 100 
	inline const float lerSensorLinhaDirSemRuido(){			return lerDadosSensorDeLinha(SENSOR_LINHA_DIREITO);} //retorna um valor de 0 a 100
	inline const float lerSensorLinhaMaisDirSemRuido(){	return lerDadosSensorDeLinha(SENSOR_LINHA_MAIS_DIREITO);} //retorna um valor de 0 a 100


	//A função retorna o valor lido do sensor sonar
	float lerSensorSonarFrontal();
  
	//funcoes para trabalhar com os sensores de Cor
  	HSV getHSVEsquerdo(); //realiza a leitura do sensor de cor esquerdo e retorna uma estrutura HSV. Ver cor.h
  	RGB getRGBEsquerdo(); //realiza a leitura do sensor de cor esquerdo e retorna uma estrutura RGB. Ver cor.h
  	HSV getHSVDireito(); 	//realiza a leitura do sensor de cor direito e retorna uma estrutura HSV. Ver cor.h
 	RGB getRGBDireito(); 	//realiza a leitura do sensor de cor direito e retorna uma estrutura RGB. Ver cor.h

	void salvarCalibracao(calibracao_dados cal);  
	void lerCalibracao(calibracao_dados &cal);

	void ligarLed(const int led)const;
	void desligarLed(const int led)const;
	void ligarTodosLeds()const;
	void desligarTodosLeds()const;

private:

  	static int tipoSensorCor;

  	void tensao(float valor_por_cento,int pino);

  	CorTcs34 corDireita34;
  	CorTcs34 corEsquerda34;


	Ultrasonic sonarFrontal;
	
	Led	led1, led2;
};

static robo_hardware robo;

#endif
