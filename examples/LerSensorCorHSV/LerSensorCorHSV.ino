#include <robo_hardware2.h> 
#include <Servo.h>

//-----PINOS PARA SENS/ORES DE COR I2C-----//
//SENSOR DIREITO
//VIN  3
//SENSOR ESQUERDO
//VIN  2
//-----PINOS PARA SENSORES DE COR I2C-----//


//  O tipo HSV e formado por tres valores: 
//  float h   //valor varia de 0 ate 359
//  float s   //valor varia de 0 ate 1. Isso inclui: 0.1 0.34 0.73
//  int v     //valor vaira de 0 ate 255
HSV leituraSensorCor; //Declaração de uma variável do tipo RGB

void setup(){
  Serial.begin(9600);
  robo.configurar();
}

void loop(){
  leituraSensorCor = robo.getHSVEsquerdo(); //FUNCAO PARA LER VALOR DO SENSOR DE COR ESQUERDO


  //imprime os 3 valores retornardos pelo sensor cor
  Serial.print("Valor do sensor de cor: ");
  Serial.print(leituraSensorCor.h);
  Serial.print(", ");
  Serial.print(leituraSensorCor.s);
  Serial.print(", ");
  Serial.print(leituraSensorCor.v);
  
  Serial.println();
  
  delay(500);
}
