#include <robo_hardware2.h> 
#include <Servo.h>


int ValorSensorLaizer;

void setup(){
  Serial.begin(9600);
  robo.configurar();
}

void loop(){
   ValorSensorLaizer = robo.lerSensorLaiserFrontal();
   Serial.print("Valor Laise Frontal em mm: ");
   Serial.println(ValorSensorLaizer);

   delay(500);
}