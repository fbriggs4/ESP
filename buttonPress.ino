

int door = 16; //top right labeled D0
int led = 2; // second LED is on GPIO2

int sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(door, INPUT);  //set the pin to be an input so we can read it
  digitalWrite(door, LOW); //set it to low (i.e. o volts)
}

void loop() {
  // put your main code here, to run repeatedly:

  sensor = digitalRead(door);  //read the state of the pin
  Serial.print("the door reading = ");  //print the state to the serial monitor
  Serial.println(sensor);
  delay(500);  //wait a little so we dont go to fast for the serial
 
  


  
  
}
