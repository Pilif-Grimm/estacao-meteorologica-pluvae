void medir_velVento() {
  static unsigned long timeOld;
  detachInterrupt(digitalPinToInterrupt(pinAnemo));
  float segundos = (millis() - timeOld)/1000;
  velVento = (pulsos_anemo/segundos) * 0.34;
  velVento_kmh = velVento*3.6;
  timeOld = millis();
  pulsos_anemo = 0;
  /*
  Serial.print("Velocidade do Vento (m/s): ");
  Serial.println(velVento);
  */
  attachInterrupt(digitalPinToInterrupt(pinAnemo), contador_anemo, RISING);
}

byte medir_direVento(byte pino) {
  delay(1);
  int valorSensor = analogRead(pino);
  byte val_direcaoVento;
  if (valorSensor <= 100) {
    val_direcaoVento = 2;
  }
  else if (valorSensor <= 200) {
    val_direcaoVento = 3;
  }
  else if (valorSensor <= 300) {
    val_direcaoVento = 4;
  }
  else if (valorSensor <= 500) {
    val_direcaoVento = 1;
  }
  else if (valorSensor <= 700) {
    val_direcaoVento = 5;
  }
  else if (valorSensor <= 800) {
    val_direcaoVento = 0;
  }
  else if (valorSensor <= 900) {
    val_direcaoVento = 7;
  }
  else {
    val_direcaoVento = 6;
  }
  return val_direcaoVento;
}
