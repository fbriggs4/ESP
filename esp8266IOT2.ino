//modified by Fred Briggs for IoT class 2018


//#include &lt; OneWire.h &gt;
//#include  &lt; DallasTemperature.h &gt;
#include "ESP8266WiFi.h"
const char* ssid       = "3MFGF";  //put your wifi SSID here
const char* password   = "HJVGDPNB6FNQWJM4";  //password

//const char* ssid       = "novalabs";  //put your wifi SSID here
//const char* password   = "robots4u";  //password
const char* server = "insecure-groker.initialstate.com";
 

WiFiClient client;
////////////////////////////
// Initial State Streamer //
////////////////////////////
 
// Data destination
// https can't be handled by the ESP8266, thus "insecure"
#define ISDestURL "insecure-groker.initialstate.com"
// Bucket key (hidden reference to your bucket that allows appending):
#define bucketKey "R6SWSBLEM7S3"
// Bucket name (name your data will be associated with in Initial State):
#define bucketName "ESP8266"
// Access key (the one you find in your account settings):
#define accessKey "PAUI6cBPBCNE68CI86WqFq28WZKSLhfl"
// How many signals are in your stream? You can have as few or as many as you want

const int NUM_SIGNALS = 2;

String signalName[NUM_SIGNALS] = {"Temp", "Door"}; // What are the names of your data types

String signalData[NUM_SIGNALS];  // This array is to store our signal data later
String doorState[2] = {"OPEN", "CLOSED"}; 

int temp; //reads a temp
 
//////////////////////
// Network Settings //
/////////////////////
void setup() {
 

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  // start wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // The postBucket() function creates a bucket 
  // (unnecessary if the bucket already exists)
  while (!postBucket()) {};
}




void loop() {
  //read your sensors and make decisions here: 
  temp = 72; //read a temp sensor
  
  signalData[0] = String(temp); //put the temp sensor reading into the data array 
  signalData[1] = doorState[1]; //door state information
  
  while(!postData());     // The postData() function streams our events
  
  delay(7000); // Wait before collecting and sending the next batch
}



 
// this method makes a HTTP connection to the server and creates a bucket is it does not exist:
bool postBucket() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
 
  // if there's a successful connection:
  if (client.connect(ISDestURL, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    // Build HTTP request.
    String toSend = "POST /api/buckets HTTP/1.1\r\n";
    toSend += "Host:";
    toSend += ISDestURL;
    toSend += "\r\n" ;
    toSend += "User-Agent:Arduino\r\n";
    toSend += "Accept-Version: ~0\r\n";
    toSend += "X-IS-AccessKey: " accessKey "\r\n";
    toSend += "Content-Type: application/json\r\n";
    String payload = "{\"bucketKey\": \"" bucketKey "\","; 
    payload += "\"bucketName\": \"" bucketName "\"}";
    payload += "\r\n"; 
    toSend += "Content-Length: "+String(payload.length())+"\r\n";
    toSend += "\r\n";
    toSend += payload;
    
    client.println(toSend);
    Serial.println(toSend);  
    return true;
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    return false;
  }
}
// this method makes a HTTP connection to the server and sends the signals measured:
bool postData() {
  // close any connection before send a new request.
  client.stop();  // This will free the socket on the WiFi shield
 
  // if there's a successful connection:
  if (client.connect(ISDestURL, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    // Build HTTP request.
 
    String toSend = "POST /api/events HTTP/1.1\r\n";
    toSend += "Host:";
    toSend += ISDestURL;
    toSend += "\r\n" ;
    toSend += "Content-Type: application/json\r\n";
    toSend += "User-Agent: Arduino\r\n";
    toSend += "Accept-Version: ~0\r\n";
    toSend += "X-IS-AccessKey:  " accessKey "\r\n";
    toSend += "X-IS-BucketKey:  " bucketKey "\r\n";
    
//    String payload = "[{\"key\": \"" + ValueName + "\", "; 
//    payload +="\"value\": \"" + ValueData + "\"}]\r\n";

String payload;  // Initialize a string to hold our signal data

  payload = "[";

  for (int i = 0; i < NUM_SIGNALS; i++)
  {
    payload += "{\"key\": \"" + signalName[i] + "\", \"value\": \"" + signalData[i] + "\"}";

    if (i != NUM_SIGNALS - 1)
    {
      payload += ",";
    }
  }

  payload += "]";

    
    toSend += "Content-Length: "+String(payload.length())+"\r\n";
    toSend += "\r\n";
    toSend += payload;
 
    Serial.println(toSend);
    client.println(toSend);
 
  return true;
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    return false;
  }
}
