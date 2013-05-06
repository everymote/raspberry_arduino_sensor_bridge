#define SOUND_SENSOR A0

#define THRESHOLD_VALUE 400//The threshold to turn the led on 400.00*5/1024 = 1.95v
void setupSound() 
{
    pinMode(SOUND_SENSOR, INPUT); 
}
 
void reportSound() 
{
	int sensorValue = analogRead(SOUND_SENSOR);//use A0 to read the electrical signal

        Serial.print("{\"type\":\"sound\",\"value\":"); 
        Serial.print(sensorValue);
        Serial.println("}");
}


