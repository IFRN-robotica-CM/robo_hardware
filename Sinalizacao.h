#ifndef SINALIZACAO_H
#define SINALIZACAO_H

#include "pinagem.h"
class Led{
    private:
    int pino_led;
    int tempo_anterior;
    int intervalo_led;


    public:
    void config(int pino, int intervalo=500);

    inline void ligarLed(){digitalWrite(pino_led, HIGH);}
    inline void desligarLed(){digitalWrite(pino_led, LOW);}
    void piscarLed();
};

class Sinalizacao{
    private:
    Led verde;
    Led amarelo;
    Led vermelho;
    Led azul;

    // void piscarLed(const int PINO_LED, const int INTERVALO);

    public:

    Sinalizacao();
    
    void config();

    inline void ligarLedVerde(){ digitalWrite(LED_VERDE, HIGH);}
    inline void ligarLedAmarelo(){ amarelo.ligarLed();}
    inline void ligarLedVermelho(){ digitalWrite(LED_VERMELHO, HIGH);}
    inline void ligarLedAzul(){ azul.ligarLed();}

    inline void desligarLedVerde(){ digitalWrite(LED_VERDE, LOW);}
    inline void desligarAmarelo(){ digitalWrite(LED_AMARELO, LOW);}
    inline void desligarLedVermelho(){ digitalWrite(LED_VERMELHO, LOW);}

    // inline void piscarLedVerde(){ piscarLed(LED_VERDE, intervalo_led_verde);}
    // inline void piscarLedAmarelo(){ piscarLed(LED_AMARELO, intervalo_led_amarelo);}
    // inline void piscarLedVermelho(){ piscarLed(LED_VERMELHO, intervalo_led_vermelho);}

    inline void piscarLedVerde(){ verde.piscarLed();}
    inline void piscarLedAmarelo(){ amarelo.piscarLed();}
    inline void piscarLedVermelho(){ vermelho.piscarLed();}

    
};



#endif