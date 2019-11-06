volatile byte half_revolutions;
unsigned int rpm;
unsigned long timeold;

int fan = 3;
double p = 50;
double value;

int led = 4;

void setup() {
  digitalWrite(2, HIGH);
  Serial.begin(9600);
  attachInterrupt(0, rpm_fun, RISING);
  half_revolutions = 0;
  rpm = 0;
  timeold = 0;

  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  readTach();
  controlFan();
  blinkLed();
}

void blinkLed() {
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
}

void controlFan() {
  value = Serial.parseFloat();
  if(Serial.available() > 0) {
    p = value;
  }
  
  double s = p*2.55;
  analogWrite(fan, s); 
  Serial.println(String(p) + "% da rotação do motor");
  //delay(2000);  
}

void readTach() {
  if (half_revolutions >= 20) { 
    //Update RPM every 20 counts, increase this for better RPM resolution,
    //decrease for faster update
    rpm = 30*1000/(millis() - timeold)*half_revolutions;
    timeold = millis();
    half_revolutions = 0;
    Serial.println(String(rpm) + " RPM => " + String(rpm/60) + "Hz");
  }
}

void rpm_fun() {
  half_revolutions++;
  //Each rotation, this interrupt function is run twice
}
