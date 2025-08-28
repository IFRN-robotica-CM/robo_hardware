#include "../include/Estrategia.h"

void Estrategia::seguirLinha(){
  //lê sensores de linha
  refletancia.atualizarSensoresRefletancia();
  
  if (refletancia.frente()){
    motores.emFrente();
  }
  else if(refletancia.direita()){
    motores.direita();
  }
  else if(refletancia.esquerda()){
    motores.esquerda();
  }
  else if(refletancia.bbpp()){
    if(refletancia.pp() || refletancia.bp()){
      motores.parar(1000);
      fazerVerde();
    }else{
      motores.direita();
    }
  }

  else if(refletancia.ppbb()){
    if(refletancia.pp() || refletancia.bp()){
      motores.parar(1000);
      fazerVerde();
    }else{
      motores.esquerda();
    }
  }
  else if(refletancia.pppp()){
    motores.parar(500);
    robo.ligarTodosLeds();
    delay(100);
    robo.desligarTodosLeds();
    delay(100);
    fazerVerde();
    estadoDeObstaculo = true;
  }
}

void Estrategia::fazerVerde(){
  cor.lerSensoresCor();
  MeuSensorCor::CORES corDir = cor.verificaCorDir();
  MeuSensorCor::CORES corEsq = cor.verificaCorEsq();

  if(corDir == cor.VERDE && corEsq == cor.VERDE){
    robo.ligarLedVerde();

    motores.emFrente();
    delay(300);
    robo.acionarMotores(80, -80);
    delay(2200);
    motores.emFrente();
    delay(200);

    robo.desligarLedVerde();
  }

  else if(!(corDir == cor.VERDE) && corEsq == cor.VERDE){
    robo.ligarLedAmarelo();

    motores.emFrente();
    delay(100);
    motores.girar90Esq();

    robo.desligarLedAmarelo();
  }

  else if(corDir == cor.VERDE && !(corEsq == cor.VERDE)){
    robo.ligarLedAzul();

    motores.emFrente();
    delay(100);
    motores.girar90Dir();

    robo.desligarLedAzul();
  }
  else{
    motores.emFrente();
    delay(300);
  }
}

void Estrategia::executar(){
  dist.atualizarSensorLaiser();
  refletancia.atualizarSensoresRefletancia();

  if (dist.identificouObstaculo() && estadoDeObstaculo){
    desviarObstaculoEsq();
  }
  else if (refletancia.IdentificaArea()){
    motores.emFrente();
    delay(100);
    motores.parar(1000);

    cor.lerSensoresCor();
    MeuSensorCor::CORES corDir = cor.verificaCorDir();
    MeuSensorCor::CORES corEsq = cor.verificaCorEsq();

    if(corDir == cor.CINZA && corEsq == cor.CINZA){
      robo.ligarTodosLeds();
      resgatar();
      robo.desligarTodosLeds();
    }
    else{
      motores.emFrente();
      delay(100);
    }
  }
  else{
    seguirLinha();
  }
}

void Estrategia::alinhar(){
  refletancia.atualizarSensoresRefletancia();
  while(!(refletancia.pppp())){
    refletancia.atualizarSensoresRefletancia();
    if(refletancia.desalinhou_direita()){
      motores.esquerda();
    }
    else if(refletancia.desalinhou_esquerda()){
      motores.direita();
    }
    else{
      motores.paraTras();
    }
  }
  motores.parar(500);

}

void Estrategia::desviarObstaculoEsq(){
  robo.ligarLedSmdVermelho();
  motores.parar(500);
  motores.girar90Esq();
  alinhar();
  motores.emFrente();
  delay(1500);
  motores.girar90Dir();
  motores.emFrente();
  delay(2000);
  motores.girar90Dir();
  motores.emFrente();
  delay(1500);
  alinhar();
  motores.emFrente();
  delay(300);
  motores.girar90Esq();
  refletancia.atualizarSensoresRefletancia();
  while(!(refletancia.bbbb())){
    refletancia.atualizarSensoresRefletancia();
    if(refletancia.desalinhou_direita()){
      motores.direita();
    }
    else if(refletancia.desalinhou_esquerda()){
      motores.esquerda();
    }
    else{
      motores.emFrente();
    }
  }
  robo.desligarLedSmdVermelho();
  estadoDeObstaculo = false;
}

void Estrategia::resgatar(){
  motores.emFrente();
  delay(250);
  garra.descerBraco();
  garra.abrirGarra();
  motores.emFrente();
  delay(1000);
  // motores.parar(5000);
  garra.fecharGarra();
  delay(900);
  garra.levantarBraco();
  // motores.emFrente();
  motores.paraTras();
  delay(1200);
  motores.girar90Esq();
  motores.emFrente();
  delay(2200);
  motores.direita();
  delay(450);
  motores.emFrente();
  // garra.levantarBraco();
  delay(1100);
  motores.parar(1000);
  garra.medianaBraco();
  delay(500);
  garra.abrirGarra();
  delay(1000);
  garra.levantarBraco();
  motores.paraTras();
  delay(1000);
  motores.parar(500);
  motores.esquerda();
  delay(500);
  // motores.girar90Esq();
  garra.descerBraco();
  garra.abrirGarra();
  motores.emFrente();
  delay(500);
  garra.fecharGarra();
  garra.levantarBraco();
  motores.paraTras();
  delay(500);
  motores.girar90Dir();
}

void Estrategia::iniciar(){
  garra.begin();
  garra.fecharGarra();
  garra.levantarBraco();
  delay(1000);
}