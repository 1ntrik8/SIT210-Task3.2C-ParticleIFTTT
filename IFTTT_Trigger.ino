/*
Leigh Rowell, ID: 219309149
SIT210 Embedded Systems Development
Ontrack Task 3.2C
Create an IFTTT Trigger

*/

// Define constants
#define LEDPIN  D7
#define PHOTO A0
#define POWERPIN A4

bool isShining = false;
int lightLevel;
int lightThreshold = 5; // This is the reading returned from the photosensor which seperates light from dark ie: dark < lightThreshold < light

void setup()
{
// Setup pins
pinMode (LEDPIN, OUTPUT);
pinMode (POWERPIN, OUTPUT);

// Turn on power to powerpin
digitalWrite(POWERPIN, HIGH);

// Start Serial Comms
  Serial.begin(9600);
  while (!Serial.available() && millis() < 30000) {
    Serial.println("Press any key to start.");
    Particle.process();
    delay(1000);
  }
  Serial.println("IFTTT Trigger - Ontrack Task 3.2C");
  Serial.println("#################################");
  
}

void loop() {


// obtain light level reading
lightLevel = analogRead(PHOTO);

Serial.print("Light level: ");
Serial.print(lightLevel);
Serial.print(". isShining: ");
Serial.print(isShining);
Serial.print(". Threshold: ");
Serial.println(lightThreshold);

// if light level is 'light' and isShining is false then change status and publish event.
// likewise if light level is dark and isShining is True then change status and publish event.

if (isShining == true && lightLevel < lightThreshold)
{
    // It has gone dark...
    isShining = false;
    Serial.println("Publishing status change event... sun not shining");
    // Publish sun shining event
    digitalWrite(LEDPIN, HIGH);
    Particle.publish("sun", "not_shining", PRIVATE);
    delay(1000);
    digitalWrite(LEDPIN, LOW);

}
else if (isShining == false && lightLevel > lightThreshold)
{
    // It has got light
    isShining = true;
    Serial.println("Publishing status change event... sun shining");
    // Publish sun shining event
    digitalWrite(LEDPIN, HIGH);
    Particle.publish("sun", "shining", PRIVATE);
    delay(1000);
    digitalWrite(LEDPIN, LOW);
}

// Wait 10 seconds and cycle again..
delay(10000);


}
