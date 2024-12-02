#define NOTA_1  250
#define NOTA_2  300
#define NOTA_3  350
#define NOTA_4  400
#define NOTA_5  450

// Notas da música do Mario
#define E7 2637
#define G7 3136
#define A7 3520
#define F7 2794
#define F6 1397
#define D7 2349
#define G6 1568
#define C7 2093

int melody1[] = { // Música 1 (original)
  NOTA_2, NOTA_3, NOTA_4, NOTA_5, NOTA_4, NOTA_3, NOTA_2
};

int noteDurations1[] = {
  4, 4, 4, 4, 4, 4, 4
};

int melody2[] = { // Música 2 (Mario)
  E7, E7, 0, E7, 0, C7, E7, 0, G6, 0, 0, 0, G7, 0, 0, 0
};

int noteDurations2[] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

// Configuração dos botões
const int startButtonPin = 3;  // Botão para iniciar a música
const int stopButtonPin = 4;   // Botão para parar a música
const int switchButtonPin = 5; // Botão para alternar entre as músicas
const int tonePin = 8;         // Pino do buzzer

bool playMusic = false;      // Variável para controlar o estado da música
bool musicPlaying = false;   // Indica se a música está tocando
int currentMelody = 1;       // 1 para a música original, 2 para a música do Mario
unsigned long musicStartTime = 0; // Tempo em que a música começou a tocar

void playMelody(int* melody, int* noteDurations, int length) {
  for (int thisNote = 0; thisNote < length; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(tonePin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(tonePin);

    // Interrompe a música após 5 segundos
    if (millis() - musicStartTime >= 5000) {
      break;
    }
  }
}

void setup() {
  pinMode(startButtonPin, INPUT_PULLUP);  // Botão para iniciar a música
  pinMode(stopButtonPin, INPUT_PULLUP);   // Botão para parar a música
  pinMode(switchButtonPin, INPUT_PULLUP); // Botão para alternar entre as músicas
  pinMode(tonePin, OUTPUT);               // Configura o pino do buzzer como saída
}

void loop() {
  int startButtonState = digitalRead(startButtonPin);
  int stopButtonState = digitalRead(stopButtonPin);
  int switchButtonState = digitalRead(switchButtonPin);

  // Verifica se o botão de iniciar foi pressionado
  if (startButtonState == LOW) {
    playMusic = true; // Ativa a música
  }

  // Verifica se o botão de parar foi pressionado
  if (stopButtonState == LOW) {
    playMusic = false;  // Para a música
    musicPlaying = false;
  }

  // Verifica se o botão de alternar foi pressionado
  if (switchButtonState == LOW) {
    delay(200); // Pequeno debounce
    currentMelody = (currentMelody == 1) ? 2 : 1; // Alterna entre as músicas
    playMusic = true;  // Ativa a música imediatamente
    musicPlaying = false; // Reinicia o estado de reprodução
  }

  // Gerencia o ciclo da música
  if (playMusic) {
    if (!musicPlaying) {
      musicStartTime = millis(); // Registra o tempo de início
      musicPlaying = true;
    }

    if (musicPlaying) {
      if (currentMelody == 1) {
        playMelody(melody1, noteDurations1, sizeof(melody1) / sizeof(melody1[0]));
      } else {
        playMelody(melody2, noteDurations2, sizeof(melody2) / sizeof(melody2[0]));
      }

      if (millis() - musicStartTime >= 5000) { // Após 5 segundos
        musicPlaying = false;   // Para a música
        delay(15000);           // Aguarda 15 segundos
      }
    }
  }
}