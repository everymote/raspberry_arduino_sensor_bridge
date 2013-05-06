  
 void reportHumidityAndTemperature(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // check if returns are valid, if they are NaN (not a number) then something went wrong!
    if (isnan(t) || isnan(h)) 
    {
        Serial.println("Failed to read from DHT");
    } 
    else 
    {
      
        Serial.print("{\"type\":\"humidity\",\"value\":"); 
        Serial.print(h);
        Serial.println("}");
        
        Serial.print("{\"type\":\"temperature\",\"value\":"); 
        Serial.print(t);
        Serial.println("}");
    }
 }
