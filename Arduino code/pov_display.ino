#include <avr/pgmspace.h>
#include "fonts.h"
//Definicion de constantes
# define izquierda 0
# define derecha 255
# define parado 128
# define nleds 7
//Definicion de variables
int  accelPin = 0;
int  acelerometro = 0;
int movimiento;
const int leds[] = {7,8,9,10,11,12,13};
const char texto1[] = "Feliz";
const char texto2[] = "Navidad";
const char texto3[] = "Bricogeek";
int cadena1[80];
int cadena2[80];
int cadena3[80];
int longitud1;
int longitud2;
int longitud3;
int texto=1;
int indice=0;
int ini=0,fin=25;


//Rutina de setup
void setup() 
{ 
  
  int z,x,y;
  int ch;
  DDRB=B11111111;
  DDRD=B10000000;
 // for (z = 0; z < nleds; ++z) { //Iniciamos los pines de salida
 //   pinMode(leds[z], OUTPUT);
 // }
 // pinMode (3, OUTPUT);
  Serial.begin(9600);
  Serial.write("PoV bricogeek");
  Serial.println(""); 
  longitud1=sizeof(texto1);
  longitud2=sizeof(texto2);
  longitud3=sizeof(texto3);
  y=0;
  for (z=0;z<longitud1-1;z++){
     for(x=0;x<5;x++){
        ch=texto1[z]-32;
        cadena1[y]=font[ch][x];
    //    Serial.print(cadena1[y],DEC);
    //    Serial.println(""); 
        y++;
     } 
  }
  longitud1=y;
  y=0;
  for (z=0;z<longitud2-1;z++){
     for(x=0;x<5;x++){
        ch=texto2[z]-32;
        cadena2[y]=font[ch][x];
    //    Serial.print(cadena1[y],DEC);
    //    Serial.println(""); 
        y++;
     } 
  }
  longitud2=y;
  y=0;
  for (z=0;z<longitud3-1;z++){
     for(x=0;x<5;x++){
        ch=texto3[z]-32;
        cadena3[y]=font[ch][x];
    //    Serial.print(cadena1[y],DEC);
    //    Serial.println(""); 
        y++;
     } 
  }
  longitud3=y;
 // delay(2000);
}

// To Do All
void loop() 
{
  int x;
  leeAcelerometro();
 
  if (texto<20){
      if (movimiento==izquierda) {
        for (x=0;x<longitud1;x++){
         ponLeds(cadena1[x]);
        }
      }
      else if (movimiento==derecha){
        for(x=longitud1; x>=0; --x){
         ponLeds(cadena1[x]);
        }  
      }
  }
  else if (texto<40){
      if (movimiento==izquierda) {
        for (x=0;x<longitud2;x++){
         ponLeds(cadena2[x]);
        }
      }
      else if (movimiento==derecha){
        for(x=longitud2; x>=0; --x){
         ponLeds(cadena2[x]);
        }  
      }
  }
  else if (texto<60){
      if (movimiento==izquierda) {
        for (x=0;x<longitud3;x++){
         ponLeds(cadena3[x]);
        }
      }
      else if (movimiento==derecha){
        for(x=longitud3; x>=0; --x){
         ponLeds(cadena3[x]);
        }  
      }
  }
 // while (movimiento==izquierda) leeAcelerometro();
  delay(20);
  texto++;
  if (texto==60) texto=1;

}



void ponLeds(int data)
{
  int tmp;
  PORTD=data<<7;
  //tmp=(data && B00000001);
 // if (tmp==B0000001) PORTD = (B10000000);
  
PORTB=(data >> 1);
//delay(1);
delayMicroseconds(800);
PORTB = B00000000;
PORTD = B00000000;
delay(1);
}


//Funcion lectura acelerómetro con filtrado por integracion
//simple de 10 muestras
void leeAcelerometro(){
  int tmp = 0, x;
  for (x=0;x<20;x++){
    tmp += analogRead(accelPin);
  }
  tmp = tmp/20;
  if (tmp<200) movimiento = izquierda;
  else if (tmp>740)movimiento = derecha;
  else movimiento = parado;
 // return tmp; 
}


