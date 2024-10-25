include <Servo.h>

Servo servoMotor;

// Pinos do sensor ultrassônico
const int trigPin = 8;
const int echoPin = 7;

// Pino do servo motor
const int servoPin = 9;

void setup() {
  Serial.begin(9600);
  
  // Configuração dos pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicializa o servo motor
  servoMotor.attach(servoPin);
  servoMotor.write(0);  // Posição inicial do servo (fechado)
}

void loop() {
  long duration, distance;
  
  // Envia pulso do sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcula o tempo de retorno do pulso
  duration = pulseIn(echoPin, HIGH);
  
  // Converte o tempo em distância (em cm)
  distance = duration * 0.034 / 2;

  // Se a distância for menor que 15 cm (ajuste conforme necessário)
  if (distance < 15) {
    // Abre o dispenser
    servoMotor.write(90);  // Posiciona o servo para liberar o material
    delay(1000);  // Espera um tempo para garantir a liberação
  } else {
    // Fecha o dispenser
    servoMotor.write(0);  // Volta à posição inicial
  }

  delay(500);  // Aguarda um pouco antes de fazer a próxima leitura
}
