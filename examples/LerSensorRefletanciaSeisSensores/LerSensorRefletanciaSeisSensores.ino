#include <robo_hardware2.h> 
#include <Servo.h>

//********ESTE EXEMPLO É EXCLUSIVO PARA O ARDUINO MEGA***********//

float valorSensorMaisEsq;
float valorSensorEsq;
float valorSensorDir;
float valorSensorMaisDir;
float valorSensorCentral;
float valorSensorFrontal;

void setup(){
	Serial.begin(9600);
	robo.configurar(false);
}

void loop(){
	valorSensorMaisEsq = robo.lerSensorLinhaMaisEsq(); //le um valor do sensor. O sensor retornar um valor de 0 100
	valorSensorEsq = robo.lerSensorLinhaEsq(); //le um valor do sensor. O sensor retornar um valor de 0 100
	valorSensorDir = robo.lerSensorLinhaDir(); //le um valor do sensor. O sensor retornar um valor de 0 100
	valorSensorMaisDir = robo.lerSensorLinhaMaisDir(); //le um valor do sensor. O sensor retornar um valor de 0 100
        valorSensorCentral = robo.lerSensorLinhaCentral(); //le um valor do sensor. O sensor retornar um valor de 0 100
        valorSensorFrontal = robo.lerSensorLinhaFrontal(); //le um valor do sensor. O sensor retornar um valor de 0 100

	//Impressão dos valores dos sensores
	Serial.print("Sensores refletancia: +esq; esq; dir; +dir; central; frontal");
	Serial.print(valorSensorMaisEsq); //Imprime o valor do sensor pela porta serial
	Serial.print("; ");
	Serial.print(valorSensorEsq); //Imprime o valor do sensor pela porta serial
	Serial.print("; ");
	Serial.print(valorSensorDir); //Imprime o valor do sensor pela porta serial
	Serial.print("; ");
	Serial.print(valorSensorMaisDir); //Imprime o valor do sensor pela porta serial
 	Serial.print("; ");
 	Serial.print(valorSensorCentral); //Imprime o valor do sensor pela porta serial
 	Serial.print("; ");
 	Serial.println(valorSensorFrontal); //Imprime o valor do sensor pela porta serial

	delay(1000);

}

