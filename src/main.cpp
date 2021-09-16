#include <Arduino.h>
/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string>

// Update these with values suitable for your network.

const char* ssid = "MEGACABLE-979F";
const char* password = "8eAYgaeY";
const char* mqtt_server = "192.168.100.32";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
/*Salidas para los motores*/ 
int Left_IN1 = D0; 
int Left_IN2 = D1;
int pwm1 = D2;  
int RIGH_IN3 = D3; 
int RIGH_IN4 = D4; 
int pwm2 = D5; 
int slider2_int = 50; 
int slider1_int = 50;  

int get_velocidad_adelante(int vel){
int velocidad; 
velocidad = (vel - 49.98038446449588 )/ 0.1961553550411926; 
return velocidad ;  
}

int get_velocidad_back(int vel){
int velocidad; 
velocidad = (vel -39.01490780698313 )/ -0.1490780698313064;
return velocidad ;  
}

int get_sentido_adelante_derecha(int slider2_int){
 int sentido_der = 0; 
 sentido_der = (slider2_int - 50.98077677520596 )/ 0.19223224794036878; 
 return sentido_der;
}

int  get_sentido_adelante_izquierda(int slider2_int){
 int sentido = 0; 
 sentido = (slider2_int - 40.153543307086615 )/ -0.15354330708661418; 
 return sentido;
}

void move_back(int vel, int sentido_derecha, int sentido_izquierda){
  digitalWrite(Left_IN1,HIGH);
  digitalWrite(Left_IN2,LOW);
  digitalWrite(RIGH_IN3,LOW);
  digitalWrite(RIGH_IN4,HIGH);
  analogWrite(pwm1,vel - sentido_derecha);
  analogWrite(pwm2,vel - sentido_izquierda);
}

void stop(){
  digitalWrite(Left_IN1,LOW);
  digitalWrite(Left_IN2,LOW);
  digitalWrite(RIGH_IN3,LOW);
  digitalWrite(RIGH_IN4,LOW);
}

void tatakae(int vel, int sentido_derecha, int sentido_izquierda){
  digitalWrite(Left_IN1,LOW);
  digitalWrite(Left_IN2,HIGH);
  digitalWrite(RIGH_IN3,HIGH);
  digitalWrite(RIGH_IN4,LOW);
  analogWrite(pwm1,vel - sentido_derecha);
  analogWrite(pwm2,vel - sentido_izquierda);
}

int move_righ(){
  int sentido_derecha = get_sentido_adelante_derecha(slider2_int);  
  Serial.print("Move righ"); 
  return sentido_derecha; 
}

int move_left(){  
  int sentido_izquierda = get_sentido_adelante_izquierda(slider2_int); 
  Serial.print("Move izda"); 
  return sentido_izquierda;
}

void move_forward(){
    int sentido_derecha = 0;
    int sentido_izquierda = 0; 
    int velocidad1 = get_velocidad_adelante(slider1_int);  
    tatakae(velocidad1, sentido_derecha,sentido_izquierda);  
    Serial.print("Move forward"); 
}

void move_back1 ( ){
    int sentido_derecha = 0;
    int sentido_izquierda = 0; 
    int velocidad1 = get_velocidad_back(slider1_int);  
    move_back(velocidad1, sentido_derecha,sentido_izquierda);  
    Serial.print("Move back"); 
}


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.println((char)payload[i]);
  }
  
  /*Se inicia la conversión de char a un número entero */
 
  
  String topic_string = topic; 

/*Se conveierte cada caracter a una cadena */
  if (topic_string == "Coche"){
   String  concatenacion = "";  // Inicialización de variables String
   String s1 = "123";
   for (int i = 0; i < length; i++){
      s1 = String((char)payload[i]) ; 
      concatenacion = concatenacion + s1;  
      Serial.print("String concatenación: ");
      Serial.println(concatenacion); 
    }
    //Convierte el numero en int 
    slider1_int = concatenacion.toInt();
  }

  if(topic_string == "Coche/Sentido"){ 
   String concatenacion_2 = "";
   String s2 = "123";  
   for (int i = 0; i < length; i++){
      s2 = String((char)payload[i]) ; 
      concatenacion_2 = concatenacion_2 + s2;  
      Serial.print("String concatenación_2: ");
      Serial.println(concatenacion_2); 
    }
    slider2_int = concatenacion_2.toInt();
  }
  /*Pritn*/
  Serial.print("Slider2_int:");
  Serial.println(slider2_int);
  Serial.print("Slider1_int:"); 
  Serial.println(slider1_int); 
  /**/
    //Move righ
  if (slider1_int > 50 && slider2_int > 50 ){
    int sentido_izquierda = 0; 
    int sentido_derecha = move_righ();
    int velocidad1 = get_velocidad_adelante(slider1_int);   
    tatakae(velocidad1, sentido_derecha, sentido_izquierda);
  }  //Move left
  else if (slider1_int > 50 && slider2_int < 40){
    int sentido_derecha = 0;     
    int sentido_izquierda = move_left();
    int velocidad1 = get_velocidad_adelante(slider1_int);  
    tatakae(velocidad1, sentido_derecha,sentido_izquierda); 
  } //Back and righ
  else if (slider1_int < 40 && slider2_int > 50 ){
    int sentido_izquierda = 0; 
    int sentido_derecha = move_righ(); 
    int velocidad1 = get_velocidad_back(slider1_int); 
    move_back(velocidad1, sentido_derecha, sentido_izquierda); 
  }//Back and lefth
  else if ( slider1_int < 40 && slider2_int < 40 ) {
    int sentido_derecha = 0; 
    int sentido_izquierda = move_left(); 
    int velocidad1 = get_velocidad_back(slider1_int); 
    move_back(velocidad1, sentido_derecha, sentido_izquierda); 
    }
  else if(slider1_int < 40 ){
    move_back1(); 
  }
  else{
   move_forward(); 
  }
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("hi", "hello world");
      // ... and resubscribe
      client.subscribe("Coche");
      client.subscribe("Coche/Sentido");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  /*Pines de salida*/
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  /*PWM*/
  pinMode(D2,OUTPUT); 
  pinMode(D5,OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // unsigned long now = millis();
  // if (now - lastMsg > 2000) {
  //   lastMsg = now;
  //   ++value;
  //   snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
  //   Serial.print("Publish message: ");
  //   Serial.println(msg);
  //   client.publish("coche", msg);
  // }
}