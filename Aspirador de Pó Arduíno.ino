#include <IRremote.h>

// Definições dos pinos
const int motor1Pin1 = 5;  // Motor 1: pino 1
const int motor1Pin2 = 6;  // Motor 1: pino 2
const int motor2Pin1 = 9;  // Motor 2: pino 1
const int motor2Pin2 = 10; // Motor 2: pino 2
const int echoPin = 7;      // Pino do sensor ultrassônico: echo
const int trigPin = 8;      // Pino do sensor ultrassônico: trig

IRrecv irrecv(2); // Pino do receptor IR
decode_results results;

// Define a velocidade dos motores (0 a 255)
int motorSpeed = 255; // Velocidade máxima

void setup() {
    Serial.begin(9600);
    
    // Configuração dos pinos dos motores
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    
    // Configuração dos pinos do sensor ultrassônico
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    // Inicializa o receptor IR
    irrecv.enableIRIn();
}

void loop() {
    if (irrecv.decode(&results)) {
        switch(results.value) {
            case 0xFFA25D: // Código do botão "cima"
                moveForward();
                break;
            case 0xFF629D: // Código do botão "baixo"
                moveBackward();
                break;
            case 0xFF22DD: // Código do botão "esquerda"
                turnLeft();
                break;
            case 0xFFC23D: // Código do botão "direita"
                turnRight();
                break;
            case 0xFFFFFFFF: // Código do botão "stop"
                stopMovement();
                break;
            default:
                break;
        }
        irrecv.resume(); // Recebe o próximo valor
    }
    
    // Lógica do sensor ultrassônico
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.034) / 2; // Converte para cm

    if (distance < 20) { // Se um obstáculo estiver a menos de 20 cm
        stopMovement();
        delay(500);
        turnLeft(); // Gira para a esquerda quando encontra um obstáculo
    }
}

void moveForward() {
    analogWrite(motor1Pin1, motorSpeed);
    analogWrite(motor1Pin2, LOW);
    analogWrite(motor2Pin1, motorSpeed);
    analogWrite(motor2Pin2, LOW);
}

void moveBackward() {
    analogWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, motorSpeed);
    analogWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, motorSpeed);
}

void turnLeft() {
    analogWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, motorSpeed);
    analogWrite(motor2Pin1, motorSpeed);
    analogWrite(motor2Pin2, LOW);
}

void turnRight() {
    analogWrite(motor1Pin1, motorSpeed);
    analogWrite(motor1Pin2, LOW);
    analogWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, motorSpeed);
}

void stopMovement() {
    analogWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, LOW);
    analogWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, LOW);
}