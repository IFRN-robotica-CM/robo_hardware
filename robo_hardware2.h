#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H
#include <Arduino.h>
#include <robo_hardware2.h>
#include "Motores.h"
#include "Refletancia.h"
#include "Laiser.h"
#include "MeuSensorCor.h"
#include "Garra.h"

class Estrategia {
  public:
      void seguirLinha();
      void fazerVerde();
      void desviarObstaculoDir();
      void desviarObstaculoEsq();
      void executar();
      void alinhar();
      void resgatar();
      void iniciar();
    
  private:
    Garra garra;
    Refletancia refletancia;
    Motores motores;
    MeuSensorCor cor;
    Laiser dist;

    bool estadoDeObstaculo = true;
};

#endif
