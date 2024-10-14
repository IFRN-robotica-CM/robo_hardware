#include <robo_hardware2.h> 
#include <Servo.h>

//-----PINOS PARA SENS/ORES DE COR I2C-----//
//SENSOR DIREITO
//VIN  3
//SENSOR ESQUERDO
//VIN  2
//-----PINOS PARA SENSORES DE COR I2C-----//


//O tipo RGB e formado por tres inteiros: vermelho, verde, azul
RGB leituraSensorCor; //Declaração de uma variável do tipo RGB

void setup(){
  Serial.begin(9600);
  robo.configurar();
}

void loop(){
  leituraSensorCor = robo.getRGBEsquerdo(); //FUNCAO PARA LER VALOR DO SENSOR DE COR ESQUERDO

  //imprime os 3 valores retornardos pelo sensor cor
  Serial.print("Valor do sensor de cor: ");
  Serial.print(leituraSensorCor.vermelho);
  Serial.print(", ");
  Serial.print(leituraSensorCor.verde);
  Serial.print(", ");
  Serial.print(leituraSensorCor.azul);
  
  Serial.println();
  
  delay(500);
}
