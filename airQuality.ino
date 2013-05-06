
void reportAirQuality(){
    current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
      /*  if (current_quality==0)
            Serial.println("High pollution! Force signal active");
        else if (current_quality==1)
            Serial.println("High pollution!");
        else if (current_quality==2)
            Serial.println("Low pollution!");
        else if (current_quality ==3)
            Serial.println("Fresh air");
         */   
       Serial.print("{\"type\":\"airquality\",\"value\":"); 
       Serial.print(current_quality);
       Serial.println("}");
    }
}


ISR(TIMER2_OVF_vect)
{
	if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
	{

			airqualitysensor.last_vol=airqualitysensor.first_vol;
			airqualitysensor.first_vol=analogRead(A1);
			airqualitysensor.counter=0;
			airqualitysensor.timer_index=1;
			PORTB=PORTB^0x20;
	}
	else
	{
		airqualitysensor.counter++;
	}
}
