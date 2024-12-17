/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */
 // Modified to smooth sensor readings and turn a relay on or off. 

const int trigPin = 9;
const int echoPin = 10;
const int relayTrigger = 7;

float duration, distance;

int TriggerDistance = 10; //Roughly inches. GH 2024-11-19. 

int sensorOutputSmoothing = 0; 

float  smoothDistance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayTrigger, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (sensorOutputSmoothing < 5){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;

    smoothDistance = distance + smoothDistance;
    sensorOutputSmoothing++; 
  }

// Serial print for testing distance. 
  //Serial.print("Distance: ");
  //Serial.println(smoothDistance);

  if (smoothDistance/5 < TriggerDistance){
    digitalWrite(relayTrigger, LOW);
    smoothDistance = 0;
    sensorOutputSmoothing = 0;
  }
  else{
    digitalWrite(relayTrigger, HIGH);
    smoothDistance = 0; 
    sensorOutputSmoothing = 0;
  }
}