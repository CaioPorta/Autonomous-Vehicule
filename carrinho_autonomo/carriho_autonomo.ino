//bibliotecas: 
#include <Servo.h>

// DEFINIÇAO DE PORTAS:
#define trig1 4
#define echo1 7
#define trig2 5
#define echo2 8
#define trig3 6
#define echo3 9
#define LEDe 2
#define LEDd 10
#define MOTOR 13
#define BUZZ 3
#define pisca 60
#define S 11
Servo servo; 

//DEFINIÇÕES DE DISTANCIA LIMITE (K):
#define K1 40 //distancia limite para começar a ler os "ifs"
#define K2 K1+20
#define K3 K2+20

//DEFINIÇÕES DE ANGULOS:
#define ET 50
#define ep 70
#define C 90
#define dp 110
#define DT 130



void setup() 
{
  ///*
  Serial.begin(9600);
  Serial.flush();
  Serial.println("INICIANDO...");
  //*/
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT); 
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(LEDe, OUTPUT);
  pinMode(LEDd, OUTPUT);
  servo.attach(S);
  digitalWrite(LEDe, HIGH);
  digitalWrite(LEDd, HIGH);
  pinMode(MOTOR, OUTPUT);
  digitalWrite(MOTOR, HIGH);  
  servo.write (C);
  delay(500);
 
  

}

void loop() 
{
  //leitura das distâncias:
  long duration1, distance1;
  digitalWrite(trig1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1/2) / 29.1;
  
  long duration2, distance2;
  digitalWrite(trig2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2/2) / 29.1;
 
  long duration3, distance3;
  digitalWrite(trig3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = (duration3/2) / 29.1;
    
 // /*  
  Serial.print("distance1:");  // indicador de distancias via serial
  Serial.println(distance1);
  delay(50);
  Serial.print("distance2:");
  Serial.println(distance2);
  delay(50);
  Serial.print("distance3:");
  Serial.println(distance3);
  delay(50);
 // */
  
  if (distance1<K1 || distance2<K1 || distance3<K1) // SE ALGUMA SENSOR TIVER MENOS QUE K1(distancia limite)cm, faça a leitura:  
   {
    
    
    if (distance1<distance2 && distance1<distance3) //COMANDOS PARA IR PRA "ESQUERDA TOTAL"  se distance1 for a menor
    {
      for(int x=0; x<2; x++) //COMANDO DE INDICADOR LED
      {
      digitalWrite (LEDe, LOW);
      digitalWrite (BUZZ, LOW);
      delay(pisca);
      digitalWrite (LEDe, HIGH);
      digitalWrite (BUZZ, HIGH);
      delay(pisca);
      }  
      servo.write (ET);
      delay (15);
      if (distance1<distance2 && distance1<distance3){} // o que volta ao normal ou não
      else
      {
        servo.write (C);
        delay (15);
      }

    if (distance3<distance1 && distance3<distance2) //COMANDOS PARA IR PRA "DIREITA TOTAL"   se distance3 for a menor//perfeito!
    {
      for(int x=0; x<2; x++) //COMANDO DE INDICADOR LED
      {
      digitalWrite (LEDd, LOW);
      digitalWrite (BUZZ, LOW);
      delay(pisca);
      digitalWrite (LEDd, HIGH);
      digitalWrite (BUZZ, HIGH);
      delay(pisca);
      }  
      servo.write (DT);
      delay (15);
      if (distance3<distance1 && distance3<distance2) {} // o que volta ao normal ou não
      else
      {
        servo.write (C);
        delay (15);
      }
    }
    }
   }

   
    else if (distance1<K2 || distance2<K2 || distance3<K2) //K2 direções parciais
   {
     
    if (distance1<distance2 && distance1<distance3) // ir pra esquerda parcial
    { 
      for(int x=0; x<2; x++) //COMANDO DE INDICADOR LED
      {
      digitalWrite (LEDe, LOW);
      digitalWrite (BUZZ, LOW);
      delay(pisca);
      digitalWrite (LEDe, HIGH);
      digitalWrite (BUZZ, HIGH);
      delay(pisca);
      }  
      servo.write (ep);
      delay (15);
      if (distance1<distance2 && distance1<distance3){}
      else
      {
        servo.write (C);
        delay (15);
      }
    }

      if (distance3<distance1 && distance3<distance2) // ir pra direita parcial
      { 
      for(int x=0; x<2; x++) //COMANDO DE INDICADOR LED
      {
      digitalWrite (LEDd, LOW);
      digitalWrite (BUZZ, LOW);
      delay(pisca);
      digitalWrite (LEDd, HIGH);
      digitalWrite (BUZZ, HIGH);
      delay(pisca);
      }  
      servo.write (dp);
      delay (15);
      if (distance3<distance1 && distance3<distance2) {}
      else 
      {
        servo.write (C);
        delay (15);
      }
      }
    }
    else 
    {
      servo.write (C);
      delay (15);
    }
}

