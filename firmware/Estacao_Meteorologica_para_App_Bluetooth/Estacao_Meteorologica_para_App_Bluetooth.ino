/*
 * CMID 2022
 * Projeto de Estação meteorológica Pedagógica
 * que envia dados via bluetooth para app.
 * Autor: Filipi Prado Grimm
 */
// Incluir as bibliotecas para comunicação Serial (Bluetooth), e sensor DHT22
#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// --- Definições dos pinos ---
#define pinAnemo 2
#define pinChuva 3
#define pinGND   4
#define DHTPIN 10
#define pinBT_RX 8 //Conectar ao TX do Bluetooth
#define pinBT_TX 9 //Conectar ao RX do Bluetooth
#define pin_direVento A0

// --- declaração dos objetos ---
SoftwareSerial serialBT(pinBT_RX, pinBT_TX);
DHT dht(DHTPIN, DHTTYPE);

// --- Variaveis Globais ---
volatile int pulsos_anemo; //Contador Interrupção Anemômetro
volatile float chuva;      //Contador Interrupção Pluvômetro
float velVento;            //Velocidade do vento em m/s
float velVento_kmh;        //Velocidade do vento em km/h
int vetor_direVento[10]; //Armazena as leituras da direção do vento
byte direVento;         //Armazena a moda das 10 leituras de direção do vento
float vetor_t[10];      //Armazena as leituras da temperatura para mediana
float vetor_h[10];      //Armazena as leituras da umidade para mediana

// Variaveis para armazenar o histórico das leituras:
int hist_velVento[24];
byte hist_direVento[24];
float hist_chuva[24];
float hist_t[24];
float hist_h[24];
float hist_hic[24];
float hist_ST[24];
int hist_index;

String comando; //Usando na função para receber comando do app

// --- Funções de Interrupções ---
void contador_anemo() {
  pulsos_anemo++;
}
void contador_chuva() {
  chuva+= 0.33;
}

void setup() {
  pinMode(pinAnemo, INPUT);
  digitalWrite(pinAnemo, HIGH); // Ativa pull-up interno
  pinMode(pin_direVento, INPUT);
  pinMode(pinChuva, INPUT_PULLUP);
  pinMode(pinGND, OUTPUT);
  digitalWrite(pinGND, LOW);

  Serial.begin(9600);
  serialBT.begin(9600);
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(pinAnemo), contador_anemo, RISING);
  attachInterrupt(digitalPinToInterrupt(pinChuva), contador_chuva, RISING);

  chuva = 0;
}

void loop() {
  static unsigned long timeOld;
  static byte contador;
  if(millis() - timeOld >= 6000) {
    timeOld = millis();
    vetor_direVento[contador] = medir_direVento(pin_direVento);
    // Medir Temperatura e umidade
    vetor_h[contador] = dht.readHumidity();
    vetor_t[contador] = dht.readTemperature();
    contador++;
    if(contador >= 10) {
      // Medir velocidade do vento no intervalo de 1 Minuto
      medir_velVento();
      
      // calcular Moda da direção do vento
      isort(vetor_direVento, 10);
      direVento = calculateMode(vetor_direVento, 10);
      
      // contar mm de chuva
      detachInterrupt(digitalPinToInterrupt(pinChuva));
      float temp_chuva = chuva;
      chuva = 0;
      attachInterrupt(digitalPinToInterrupt(pinChuva), contador_chuva, RISING);
      
      // calcular mediana da temperatura e umidade
      isort_f(vetor_h, 10);
      isort_f(vetor_t, 10);
      float h = vetor_h[4];
      float t = vetor_t[4];
      // Compute heat index in Celsius (isFahreheit = false)
      float hic = dht.computeHeatIndex(t, h, false);

      // Calcular sensação termica
      float ST = sensT(t,velVento);

      // Gravar dados na memoria e enviar por bluetooth:
      if(hist_index < 24) {
        hist_velVento[hist_index] = velVento_kmh;
        hist_direVento[hist_index] = direVento;
        hist_chuva[hist_index] = temp_chuva;
        hist_t[hist_index] = t;
        hist_h[hist_index] = h;
        hist_hic[hist_index] = hic;
        hist_ST[hist_index] = ST;
        hist_index++;
        
        enviarBT();
        Serial.println("Tabela com as leituras enviados para o app");
      }
      else {
        serialBT.println("!;");
        Serial.println("Alerta de fim de simulacao enviado para o app");
      }
      
      contador = 0;
    }
  }
  receberDados();
}
