float sensT(float t, float v) { // t: °C, v: m/s
  float ST;
  float rv;
  rv = sqrt(v);
  ST = 33 + (10 * rv + 10.45 - v) * (t - 33) / 22;
  return ST;
}

void enviarBT1() {
  serialBT.print("Horario,Temperatura,Sensacao Termica,Umidade,Indice de Calor,Direcao do Vento,Velocidade do Vento,Precipitacao\n");
  for(int i = 0; i < hist_index; i++) {
    serialBT.print(i); serialBT.print(",");
    serialBT.print((int)hist_t[i]); serialBT.print(",");
    serialBT.print((int)hist_ST[i]); serialBT.print(",");
    serialBT.print((int)hist_h[i]); serialBT.print(",");
    serialBT.print((int)hist_hic[i]); serialBT.print(",");
    serialBT.print(DireVentoToCardeal(hist_direVento[i])); serialBT.print(",");
    serialBT.print(hist_velVento[i]); serialBT.print(",");
    serialBT.print(hist_chuva[i]);
    if(i != hist_index-1) {
      serialBT.print("\n");
    }
  }
  serialBT.println(";");
}

void enviarBT() {
  serialBT.print("Horario,Temperatura,Sensacao Termica,Umidade,Indice de Calor,Direcao do Vento,Velocidade do Vento,Precipitacao\n");
  for(int i = hist_index-1; i >= 0; i--) {
    serialBT.print(convertToTime(i)); serialBT.print(",");
    serialBT.print((int)hist_t[i]); serialBT.print(",");
    serialBT.print((int)hist_ST[i]); serialBT.print(",");
    serialBT.print((int)hist_h[i]); serialBT.print(",");
    serialBT.print((int)hist_hic[i]); serialBT.print(",");
    serialBT.print(DireVentoToCardeal(hist_direVento[i])); serialBT.print(",");
    serialBT.print(hist_velVento[i]); serialBT.print(",");
    serialBT.print(hist_chuva[i],1);
    if(i != 0) {
      serialBT.print("\n");
    }
  }
  serialBT.println(";");
}

String DireVentoToCardeal(int x) {
  String cardeal;
  switch (x) {
    case 0:
      cardeal = "N";
      break;
    case 1:
      cardeal = "NE";
      break;
    case 2:
      cardeal = "E";
      break;
    case 3:
      cardeal = "SE";
      break;
    case 4:
      cardeal = "S";
      break;
    case 5:
      cardeal = "SO";
      break;
    case 6:
      cardeal = "O";
      break;
    case 7:
      cardeal = "NO";
      break;
  }
  return cardeal;
}

String convertToTime(int x) {
  String val;
  if (x <10) {
    val = "0";
    val += String(x);
    val += ":00";
  }
  else {
    val = String(x);
    val += ":00";
  }
  return val;
}

void receberDados() {
  while (serialBT.available()) {
    char byteRec = serialBT.read();
    comando += byteRec;
    if (byteRec == ';') {
      Serial.print("Comando Recebido: ");
      Serial.println(comando); 

      if (comando.substring(0,1) == "R") {
        hist_index = 0;
      }
      if (comando.substring(0,1) == "S" && hist_index > 0) {
        enviarBT();
      }
      comando = "";
    }
  }
}
