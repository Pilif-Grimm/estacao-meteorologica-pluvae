# Estação Meteorológica Pedagógica – Pluvae

Projeto desenvolvido originalmente em 2022 com o objetivo de demonstrar, em ambiente educacional, o funcionamento real de uma estação meteorológica, integrando sensores físicos, processamento embarcado e visualização de dados em aplicativo móvel.

O sistema combina coleta de dados ambientais com um modo de simulação pedagógica que permite a compressão do tempo e interação física com os sensores para fins demonstrativos.

---

## 🎯 Objetivo

Criar uma plataforma didática que permitisse aos professores demonstrar, na prática:

- Conversão de fenômenos físicos em sinais elétricos
- Diferença entre entradas digitais e analógicas
- Processamento matemático de dados ambientais
- Comunicação serial via Bluetooth
- Registro estruturado de observações meteorológicas
- Análise de dados ao longo de um “dia” simulado

---

## 🏗 Arquitetura do Sistema

Sensores → Arduino → Bluetooth → Aplicativo Pluvae

### Sensores Utilizados

- Anemômetro (velocidade do vento – saída por pulsos)
- Sensor de direção do vento (leitura analógica por divisor resistivo)
- Pluviômetro de báscula (contagem de acionamentos via reed switch)
- Sensor DHT (temperatura e umidade)

### Unidade de Processamento

- Arduino
- Contagem de pulsos para velocidade do vento e precipitação
- Conversão de frequência (Hz → m/s)
- Acumulação de chuva (mm)
- Leitura analógica para direção do vento
- Estruturação e envio de dados via serial Bluetooth

### Comunicação

- Módulo Bluetooth HC-05
- Transmissão serial estruturada para o aplicativo móvel

---

## 📲 Aplicativo *Pluvae*

Aplicativo desenvolvido no MIT App Inventor para visualização e simulação pedagógica da estação meteorológica.

### 🕒 Simulação de Dia Meteorológico

O sistema implementa um modo de simulação temporal acelerada:

- Cada minuto real equivale a uma hora simulada.
- Um ciclo completo representa um “dia meteorológico”.

Durante a simulação, o apresentador pode interagir fisicamente com os sensores:

- Aquecer o sensor de temperatura
- Adicionar água ao pluviômetro
- Soprar o anemômetro
- Alterar manualmente a direção do vento

As alterações físicas impactam diretamente os dados registrados, permitindo demonstração prática e dinâmica em sala de aula.

### 📊 Registro e Geração de Tabela

Ao final do dia simulado, o aplicativo gera automaticamente uma tabela com os registros horários das variáveis:

- Velocidade do vento
- Direção do vento
- Temperatura
- Umidade
- Precipitação acumulada

Essa funcionalidade permite análise comparativa das variações ao longo do período simulado.

---

## 🧠 Conceitos Técnicos Aplicados

- Leitura de sinais digitais e analógicos
- Contagem de pulsos por evento
- Conversão matemática baseada em frequência
- Acumulação de dados ao longo do tempo
- Modelagem de tempo lógico (simulação acelerada)
- Amostragem periódica
- Estruturação tabular de dados
- Comunicação serial Bluetooth
- Integração hardware + software

---

## 📚 Aplicação Educacional

O projeto foi utilizado como ferramenta pedagógica para demonstrar:

- Funcionamento interno de estações meteorológicas
- Processamento digital de dados ambientais
- Relação entre fenômeno físico e dado numérico
- Interpretação de registros meteorológicos

A compressão temporal permitiu simular um dia completo de observações em poucos minutos, facilitando a análise em contexto de aula.

---

## 🧩 Projetos Relacionados

Este repositório documenta a versão pedagógica e portátil da estação meteorológica, desenvolvida com foco demonstrativo.

Foi posteriormente desenvolvido um segundo projeto com proposta distinta:

### 🌐 Estação Meteorológica com ESP e Wi-Fi

Características:

- Baseada em ESP8266 (Wi-Fi integrado)
- Envio de dados para a internet
- Hospedagem temporária no ThingSpeak
- Foco em monitoramento funcional contínuo

Enquanto esta versão (Pluvae) prioriza simulação, interação física e didática,
a versão com ESP prioriza conectividade e aplicação prática.

---

## 📂 Estrutura do Repositório

/firmware  → Código-fonte Arduino  
/app       → Arquivo do aplicativo Pluvae (.aia)  
/docs      → Imagens, diagramas e capturas de tela  

---

## 📄 Licença

Este projeto está licenciado sob a MIT License.