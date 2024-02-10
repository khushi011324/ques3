const byte LED_PIN = 13;
const byte METER_PIN = A4;
const byte POTENTIOMETER_PIN = A4;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer value and map it to the timer frequency range
  double frequency = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 0.1, 10.0);
  
  startTimer(frequency);
  delay(1000);  // Adjust delay based on your requirements
}

void startTimer(double frequency) {
  noInterrupts();
  int prescaler = 1024;  // Adjust based on your specific timer and Arduino model
  long timerValue = F_CPU / prescaler / frequency - 1;
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = timerValue;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}
