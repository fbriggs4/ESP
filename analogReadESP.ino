int pot = A0;  //pin used for reading the 10k pot
int input; //stores the analog reading from the pot

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot, INPUT); //define the pin as an input
  digitalWrite(pot, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  input = analogRead(pot);
  Serial.print("alalog reading = ");
  Serial.println(input);
  

}
