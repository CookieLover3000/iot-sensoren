/*  Teensy sample  
 *  Author: J. van den Helder
 *  Date 22 april 2021
 *  Dit programma is geschreven voor een Teensy 3.2 in combinatie met een Teensy Board
 *  Het meet de uitgang van de microfoon op de Teensyboard
 *  door 500 samples van het signaal te meten en om te zetten in een digitale waarde.
 */

#define LED1 11
#define AUDIO_INPUT_PIN 23        // Input ADC pin for audio data. (A9)
#define SW1 4
#define SW2 5
float samples[500];
int counter;
IntervalTimer timer;
void sample();

void setup() {
  pinMode(LED1, OUTPUT); 
  pinMode(AUDIO_INPUT_PIN, INPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  Serial.begin(38400);
}

void loop() {
  while(digitalRead(SW1)==0); 
  delay(50);
  while(digitalRead(SW1)==1); 
  delay(50);     // wacht to SW1 wordt losgelaten
  digitalWrite(LED1, HIGH);
  counter = 0;
  timer.begin(sample, 100);
  while (counter < 500){delay(5);}
  timer.end();
  digitalWrite(LED1, LOW);
  while(digitalRead(SW2)==0); delay(50);     // wacht tot SW2 wordt ingedrukt 
  while(digitalRead(SW2)==1); delay(50);     // wacht tot SW2 wordt losgelaten
  for (int t=0; t<500; t++) {  //print the "samples" signal
     Serial.print(t);
     Serial.print("= ");
     Serial.println(samples[t]);
   }
}

void sample () {
  samples[counter] = analogRead(AUDIO_INPUT_PIN);
  counter++;
}
