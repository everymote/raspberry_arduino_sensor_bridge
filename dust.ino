unsigned long time_rise=0;
unsigned long time_fall=0;
unsigned long time_mus=0;
unsigned int ov_counter=0;
int quantity=0;//2011/12/29 change by bruce
//double quantity=0;
float time_sum=0;
float rate=0;
boolean newValue = false; 

void setupDust(){
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  pinMode(6,OUTPUT);
  //set 16bit counter for measure the wide of sensor
  TCCR1A = 0;
  TCCR1B |=1<<(CS12)|0<<(CS11)|1<<(CS10);//Set clock 1024/16MHz,unit is 6.4us
  TIMSK1 |=1<<(ICIE1)|1<<(TOIE1); //enable capture interrupt and overflow interrupt
  TCNT1 = 0;
  sei();
}

void reportDust(){

  if(newValue){
    Serial.print("{\"type\":\"dust\",\"quantity\":"); 
    Serial.print(quantity);
    Serial.print(",\"rate\":");
    Serial.print(rate,8);
    Serial.println("}");
    newValue = false;
  }
}

ISR(TIMER1_OVF_vect)
{
  if(ov_counter==7)
    {
      PORTD^=0x40;
      ov_counter=0;
      rate=(float)(time_sum/336000);
      if(rate<=8)
      {
	quantity=rate*562.5;//8 equal 4500 pcs Particle according to the datasheet.
        newValue = true;
      }
      else
	quantity=4500+(rate-8)*750;
        time_sum=0;
      }
  else
    {
	ov_counter++;
    }
}


ISR(TIMER1_CAPT_vect)
{
	
	if((PORTB^0x01)==1)
		{
			//time_fall=ICR1;	
			time_fall=micros();			
			TCCR1B=0x45; //change to rising capture and with 1024 prescaler
			digitalWrite(13,HIGH);
			//TIFR1|=1<<(TOV1);//reset the flag
			}
	else
		{
			time_rise=micros();
			TCCR1B=0x05; //change to negative and with 1024 prescaler
			digitalWrite(13,LOW);
			//TIFR1|=1<<(TOV1);//reset the flag
			if(time_rise>time_fall)
			time_mus=20000+(time_rise-time_fall);//20000 is countervail for program run
			time_sum+=+time_mus;
		}		

}; 

