#include <TimerOne.h>
#include <SoftwareSerial.h>  
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial BT1 (0,1);
int speakerPin = 2, LuzVerde = 4, LuzAzul = 6, LuzRoja = 8;

LiquidCrystal_I2C lcd(0x27 ,16,2);  
String hc, ha, ma, mc, yc, oc, dc;
int hora, minuto, dia, mes, anio;
volatile int segundo;
volatile boolean actualizar;

int hora_alarma=0;
int minuto_alarma=0;
boolean alarmaOn=false;
boolean indicador=false;
int static ENTRADA_1 = 3;

int length = 14;
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2 };
int tempo = 300;

char data;
char textoH[10];
char textoA[7];
char textoF[10];
char c = 0;

int tono = 14;
int contador = 0;

void alarma(){
  
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 250L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    digitalWrite(LuzRoja, HIGH);
    digitalWrite(LuzVerde, HIGH);
    digitalWrite(LuzAzul, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    digitalWrite(LuzRoja, LOW);
    digitalWrite(LuzAzul, LOW);
    digitalWrite(LuzVerde, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {  
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  // toca el tono correspondiente al nombre de la nota
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
void setup()
{
  Serial.begin(9600); 
  BT1.begin(57600);
  pinMode(12, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(speakerPin, OUTPUT);
  pinMode(ENTRADA_1, INPUT);

  lcd.init();
  lcd.backlight();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(manejadoraTimer);
  lcd.print("Bienvenido");
 
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(manejadoraTimer);  
}

void manejadoraTimer(){
    segundo++;
    actualizar=true;    
  }

void actualizarReloj(){
  minuto += segundo / 60;
  segundo = segundo % 60;
  
  hora += minuto / 60;
  minuto = minuto % 60;

  dia += hora / 24;
  hora = hora % 24;
  
  if((mes == 1) || (mes == 3) || (mes == 5) || (mes == 7) || (mes == 8) || (mes == 10) || (mes == 12)){
    mes += dia / 32;
    dia = dia % 32;  
  }

  else if ((mes == 4) || (mes == 6) || (mes == 9) || (mes == 11)){
    mes += dia / 31;
    dia = dia % 31;
  }

  else if (mes == 2){
    mes += dia / 29;
    dia = dia % 29;
  }

  anio += mes / 12;

if (dia == 0)
    dia++;  
}
 
void loop()
{
  if(actualizar=true){
    actualizarReloj();
    mostrar();
    actualizar=false;
  }

  if(Serial.available()){
      data = Serial.read();
      //Serial.write(Serial.read());  
      switch (data)
      {
          case '2':
            digitalWrite(LuzAzul, HIGH);
            digitalWrite(LuzRoja, LOW);
            digitalWrite(LuzVerde, LOW);
            break;
  
          case '4':
            digitalWrite(LuzRoja, LOW);
            digitalWrite(LuzAzul, LOW);
            digitalWrite(LuzVerde, LOW);
            break;
  
          case '3':
            digitalWrite(LuzRoja, LOW);
            digitalWrite(LuzAzul, LOW);
            digitalWrite(LuzVerde, HIGH);
            break;
  
          case '1':
            digitalWrite(LuzRoja, HIGH);
            digitalWrite(LuzAzul, LOW);
            digitalWrite(LuzVerde, LOW);
            break;

          case 's':
            digitalWrite(LuzRoja, HIGH);
            digitalWrite(LuzAzul, HIGH);
            digitalWrite(LuzVerde, HIGH);
            break;

          case 'h':          
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hora Establecida");
          lcd.setCursor(0,1);
          lcd.print("Correctamente");
          delay(500);
          horita_LCD();
          break;

          case 't':
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Alarma Encendida");
          alarma_LCD();
          delay(2000);
          actualizar=true;
          break;

          case 'n':
          establecerTono();
          break;

          case 'p':
          lcd.backlight();
          break;

          case 'q':
          lcd.noBacklight();
          break;
      }
  }

  if(tono == 1){
    char notes[] = "ffeeccbbaabbcc";
    comprobarAlarma(notes);
  }
  
  if(tono == 2){
    char notes2[] = "abcefdefbccdff";
    comprobarAlarma(notes2);
  }
  
  if(tono == 3){
    char notes3[] = "ccccddeeeeffaa";
    comprobarAlarma(notes3);
  }
  
  if(tono == 4){ 
    char notes4[] = "ccggaagffeeddc"; 
    comprobarAlarma(notes4);
  }
  
  if(tono == 5){ 
    char notes5[] = "aaabbbfffaaacc";
    comprobarAlarma(notes5);
  }
   
  if(tono == 6){ 
    char notes6[] = "babacacafafaea";
    comprobarAlarma(notes6);
  }
  
  if(tono == 7){ 
    char notes7[] = "afbecdaecfbace";
    comprobarAlarma(notes7);
  }
  
  if(tono == 8){ 
    char notes8[] = "cacababafafafa";
    comprobarAlarma(notes8);
  }
  
  if(tono == 9){ 
    char notes9[] = "fafafaeaeababe";
    comprobarAlarma(notes9);
  }
  
  if(tono == 10){ 
    char notesA[] = "befcafbecfacfa";
    comprobarAlarma(notesA);
  }
  
  if(tono == 11){
    char notesB[] = "cbfefebacfecaa";
    comprobarAlarma(notesB);
  }
  
  if(tono == 12){ 
    char notesC[] = "cccbbbebffbeba";
    comprobarAlarma(notesC);
  }
  
  if(tono == 13){
    char notesD[] = "abefefbecafecf";
    comprobarAlarma(notesD);
  }
  
  if(tono == 14){
    char notesE[] = "aaaaaaaaaaaaaa";
    comprobarAlarma(notesE);
  }
  
  if(tono == 15){
    char notesF[] = "aaabbbfffaaacc";
    comprobarAlarma(notesF);
  }
  
}

void establecerTono(){
  delay(30);
  if(Serial.available()){
    char dato = Serial.read();
    if(dato == '1'){
      char notes[] = "ffeeccbbaabbcc";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("MARAMBA");
      for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=1;}
    if(dato == '2'){
      char notes2[] = "abcefdefbccdff";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono 1");
      lcd.setCursor(0,1);
      lcd.print("LA TECNO");
      for (int i = 0; i < length; i++) {
        if (notes2[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes2[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=2;}
    if(dato == '3'){
      char notes3[] = "ccccddeeeeffaa";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("ARQUI");
      for (int i = 0; i < length; i++) {
        if (notes3[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes3[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=3;}
    if(dato == '4'){
      char notes4[] = "ccggaagffeeddc"; 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("CUCARACHA");
      for (int i = 0; i < length; i++) {
        if (notes4[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes4[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=4;}
    if(dato == '5'){
      char notes5[] = "aaabbbfffaaacc";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("TONO 5");
      for (int i = 0; i < length; i++) {
        if (notes5[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes5[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=5;}
    if(dato == '6'){
      char notes6[] = "babacacafafaea";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("DESESPERANTE");
      for (int i = 0; i < length; i++) {
        if (notes6[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes6[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=6;}
    if(dato == '7'){
      char notes7[] = "afbecdaecfbace";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("CASUAL");
      for (int i = 0; i < length; i++) {
        if (notes7[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes7[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=7;}
    if(dato == '8'){
      char notes8[] = "cacababafafafa";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("DESPIERTE");
      for (int i = 0; i < length; i++) {
        if (notes8[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes8[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=8;}
    if(dato == '9'){
      char notes9[] = "fafafaeaeababe";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("ESTAÑO");
      for (int i = 0; i < length; i++) {
        if (notes9[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notes9[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=9;}
    if(dato == 'a'){
      char notesA[] = "befcafbecfacfa";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("DISCOS");
      for (int i = 0; i < length; i++) {
        if (notesA[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notesA[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=10;}
    if(dato == 'b'){
      char notesB[] = "cbfefebacfecaa";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("MEMORIA");
      for (int i = 0; i < length; i++) {
        if (notesB[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notesB[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=11;}
    if(dato == 'c'){
      char notesC[] = "cccbbbebffbeba";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("PASS");
      for (int i = 0; i < length; i++) {
        if (notesC[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notesC[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=12;}
    if(dato == 'd'){
      char notesD[] = "abefefbecafecf";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("FAIL");
      for (int i = 0; i < length; i++) {
        if (notesD[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notesD[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=13;}
    if(dato == 'e'){
      char notesE[] = "aaaaaaaaaaaaaa";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono 1");
      lcd.setCursor(0,1);
      lcd.print("TRUNCK");
      for (int i = 0; i < length; i++) {
        if (notesE[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notesE[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=14;}
    if(dato == 'f'){
      char notesF[] = "aaabbbfffaaacc";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Establecido Tono ");
      lcd.setCursor(0,1);
      lcd.print("ARRIBIRIJILLA");
      for (int i = 0; i < length; i++) {
        if (notesF[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notesF[i], beats[i] * tempo);          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        mostrar();
      tono=15; }   
  }
}

boolean apagarAlarma(int t){
  delay(30);
 if(Serial.available()){
      data = Serial.read();
      if (data == 'o' || (t == 10)){
            Serial.println("Señal de apagado");
            t = 0;
            alarmaOn = false;
            digitalWrite(12, LOW);
            digitalWrite(8, LOW);
            minuto_alarma = 0;
            hora_alarma = 0;
            indicador=false;
            return true;
      }
    }
}

void comprobarAlarma(char notas[]){
  if((hora == hora_alarma) && (minuto == minuto_alarma) && (hora != 0)){
    alarmaOn=true;  
  }

  if((alarmaOn == true)){
    int t = 0;
    while(t < 10){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Alarma");
      digitalWrite(12, HIGH);
      digitalWrite(8, HIGH);
      t++;

      for (int i = 0; i < length; i++) {
        if (notas[i] == ' ') {
          delay(beats[i] * tempo); 
        } else {
          playNote(notas[i], beats[i] * tempo);
          
        }
        // pausa entre notas
        delay(tempo / 2); 
        }
        if(apagarAlarma(0))
        break;
    }
  }
}

void horita_LCD(){
      hc="";
      mc="";
      segundo=45;
      yc="";
      oc="";
      dc="";
  delay(30);
  int t = 0;
  while(t < 2){
     char c = Serial.read();
     hc = hc + c;
     t++;
  }   
  if(t==2)
     t=0;
     
  while(t < 2){
     char c = Serial.read();
     mc = mc + c;
     t++;
  }
  
  if(t==2)
     t=0;
     delay(30);
 
  while(t < 2){
     char c = Serial.read();
     oc = oc + c;
     t++;
  }
  if(t==2)
     t=0;
  while(t < 2){
     char c = Serial.read();
     dc = dc + c;
     t++;
  }

   while(t < 6){
     char c = Serial.read();
     yc = yc + c;
     t++;
  }
  
  if(t==2)
     t=0;
     delay(30);

  llenar();
}

void alarma_LCD(){
      ha="";
      ma="";
  delay(30);
  int t = 0;
  while(t < 2){
     char c = Serial.read();
     ha = ha + c;
     t++;
  }   
  if(t==2)
     t=0;
     
  while(t < 2){
     char c = Serial.read();
     ma = ma + c;
     t++;
  }
  
  if(t==2)
     t=0;
     delay(30);
 
  ponerAlarma();
}

void llenar(){
  hora = hc.toInt();
  minuto = mc.toInt();
  anio = yc.toInt();
  mes = oc.toInt();
  dia = dc.toInt();
  }

void ponerAlarma(){
  hora_alarma = ha.toInt();
  minuto_alarma = ma.toInt();
  lcd.setCursor(0,1);
  sprintf(textoA, "%02d:%02d",hora_alarma,minuto_alarma); 
  lcd.print("A las: ");
  lcd.print(textoA);
  }

void mostrar(){
  delay(1000);
  if (hc.length() > 0){
      lcd.clear();
      lcd.setCursor(0,0);
      sprintf(textoH, "%02d:%02d:%02d",hora,minuto,segundo - 1); 
      lcd.print(textoH);
      lcd.setCursor(0,1);
      sprintf(textoF, "%02d/%02d/%04d",dia,mes,anio); 
      lcd.print(textoF);
  }
}
