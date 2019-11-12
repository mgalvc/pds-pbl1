#define led 7
#define pot A0
long t;  //vai de 40ms a 200ms
long p = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  p = analogRead(pot);
  t = 40 + 0.1564*p - 0.2;
  Serial.println(1000/(t + 0.2));
  
  digitalWrite(led, HIGH);
  delayMicroseconds(200);
  digitalWrite(led, LOW);
  delay(t);
}
