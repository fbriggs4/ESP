int led = 2;  //built in LED on pins 2 and 16


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT); //define the pin as an input
  

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  

}
