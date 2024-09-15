// Define pin connections
const int motionSensorPin = 2; // Pin connected to SR602 output
const int transistorPin = 4;   // Pin connected to transistor base
const int ledPin = 1;         // Pin connected to onboard LED
const int activeTimeSec = 300; // Active time in seconds
const int coolDownSec = 120;   // Cooldown time in seconds 
void setup() {
    // Initialize the motion sensor pin as an input
    pinMode(motionSensorPin, INPUT);
    
    // Initialize the transistor pin as an output
    pinMode(transistorPin, OUTPUT);
    
    // Initialize the onboard LED pin as an output
    pinMode(ledPin, OUTPUT);
    // Ensure the transistor is off initially
    digitalWrite(transistorPin, LOW);
    // Ensure the onboard LED is off initially
    digitalWrite(ledPin, LOW);
}



void loop() {
    // Read the state of the motion sensor
    int motionDetected = digitalRead(motionSensorPin);
    
    // If motion is detected, activate the transistor
    if (motionDetected == HIGH) {
        
        // activate transistor and led 
        digitalWrite(ledPin, HIGH);
        digitalWrite(transistorPin, HIGH);
        cdel(activeTimeSec);
        
        // deactivate transistor and enter a cooldown and turn off led
        digitalWrite(ledPin, LOW);
        digitalWrite(transistorPin, LOW);
        cdel(coolDownSec);
        int motionDetected = digitalRead(motionSensorPin);
    }

    
    // Small delay to debounce the sensor reading
    delay(100);
}


void cdel(int sec) {
    // Delay in the attiny85 is a bit fucked, it seems like only can handle delays up to 30 seconds or 30000 ms otherwise becomes infinite
    // so i need to use a for and stop using numbers so big, second try: changed ms to s so i need 2 delays of 30 secconds per minute
    for (int i = 0; i < sec; i++) {
        delay(1000);
    }
    //worked at second try, according to a real clock 60 seconds in code are aprox 58 seconds in real life
}