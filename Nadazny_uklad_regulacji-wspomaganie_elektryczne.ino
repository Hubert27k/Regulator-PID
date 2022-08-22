 #define sensor_bez_zasi A0
    #define sensor_z_zasi A1

 
    unsigned int hits_zasilane ;
    unsigned int hits_niezasilane ;
 
    unsigned int ti_zasilane;
    unsigned int ti_niezasilane;
   
    float roznica_czestotliwosci;
float herz_zasilane=0;
float herz_niezasilane=0;
    
    
unsigned int now1;
unsigned int now2;

    float Kd = 0.1;
    float P;
    float I;
    float D;
    volatile  float uchyb;
    float ostatniuchyb;
    float calkujaca;
    int sygnal_pwm=0;
 void pulse_zasilane();
 void pulse_niezasilane();
 
 
 
   
void setup()
{
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  digitalWrite(7, HIGH);
 attachInterrupt(0, pulse_niezasilane, RISING); //aktywowanie pomiaru na kole niezasilanym 
 attachInterrupt(1, pulse_zasilane, RISING); //aktywowanie pomiaru na kole zasilanym

}
 
void loop()
{
 
 
 
         int odczyt1 = analogRead(sensor_bez_zasi);
  if(odczyt1 >= 900)          
  {
  digitalWrite(12, HIGH);
 }
 else                      
 {
 digitalWrite(12, LOW);
  }
 
        int odczyt2 = analogRead(sensor_z_zasi);
  if(odczyt2 >= 900)          
  {
 digitalWrite(13, HIGH);
 }
 else                      
 {
  digitalWrite(13, LOW);
  }


 

  
 if (sygnal_pwm > 255)
  {
  sygnal_pwm = 255;
  }
   if (sygnal_pwm < 0)
  {
  sygnal_pwm = 0;
  }
  
   analogWrite(10, sygnal_pwm);

  

Serial.flush();


}

void pulse_niezasilane()
    {
      now1=millis();  //aktualny czas
     hits_niezasilane=now1-ti_niezasilane; // roznica czasu zdarzen
     ti_niezasilane=now1; // czas ostatniego zdarzenia
     herz_niezasilane=((1000/hits_niezasilane)); //częstotliwość koła niezasilanego
    ostatniuchyb = uchyb;
    uchyb =   herz_niezasilane -  herz_zasilane;
      
  
 P=uchyb*(4.8664121)*0.05;
 //D=(uchyb - ostatniuchyb)*Kd*(4.8664121);
 sygnal_pwm = sygnal_pwm + P ;
if (uchyb>0)
  {
  sygnal_pwm=sygnal_pwm+1;

  }
  else
  {
    if(uchyb<0)
    {
      
    sygnal_pwm=sygnal_pwm-1;
 
    }
  }
  Serial.print(now1);
  Serial.print(" ");
  Serial.print(sygnal_pwm);
  Serial.print(" ");
  Serial.println(uchyb);
  herz_zasilane=0;
      
     
 
  }
 
 void pulse_zasilane()
   {
     now2=millis();  //aktualny czas
     hits_zasilane=now2-ti_zasilane; // roznica czasu zdarzen
     ti_zasilane=now2; // czas ostatniego zdarzenia
     herz_zasilane=((1000/hits_zasilane));
 

   }

 
