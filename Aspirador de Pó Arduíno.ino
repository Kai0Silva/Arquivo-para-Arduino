int trig = 3;
int echo = 5;
int duration;
int dist;


void setup()
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(9, OUTPUT); // O pino 9 será usado para o buzzer
}


void loop()
{
  digitalWrite(trig, HIGH);
  delay(10); // Pequeno atraso para evitar leituras incorretas
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  dist = (duration / 2) / 29.1;


  if (dist < 30)
  {
    Serial.println("on");
    playMarioTune();
  }
  else
  {
    Serial.println("off");
    noTone(9); // Para o som se a distância for maior que 300 cm
  }


  delay(1000); // Atraso para evitar leituras rápidas demais
}


void playMarioTune()
{
  // Notas e durações para a música do Mario
  int melody[] = {
      330, 330, 0, 330, 0, 262, 330, 0, 392, 0, 0,
      262, 0, 196, 0, 164, 0, 220, 0, 247, 0, 233, 220, 0,
      196, 330, 0, 392, 0, 440, 0, 349, 392, 0, 330, 0, 262, 294, 247, 0};


  int noteDurations[] = {
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
      100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};


  for (int thisNote = 0; thisNote < 39; thisNote++)
  {
    int noteDuration = noteDurations[thisNote];
    if (melody[thisNote] != 0)
    {
      tone(9, melody[thisNote], noteDuration);
    }
    delay(noteDuration * 1.30); // Pausa entre as notas
    noTone(9); // Para o som entre as notas
  }
}
