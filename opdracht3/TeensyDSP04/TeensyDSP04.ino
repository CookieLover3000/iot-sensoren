/*  Teensy digtal filter 2
 *  Author: J. van den Helder
 *  Date 9 maart 2021
 *  Audio Notch filter
 */

#define LED1 11
#define LED2 12
#define LED3 13
#define LED4 14
#define AUDIO_INPUT_PIN 23        // Input ADC pin for audio data. (A9)

IntervalTimer timer;
void sample();
int Xmin2, Xmin1, Xmin0;
float Ymin2, Ymin1, Ymin0;
float Ymax = 0;

void setup() {
  pinMode(LED1, OUTPUT); pinMode(LED2, OUTPUT); pinMode(LED3, OUTPUT); pinMode(LED4, OUTPUT);
  pinMode(AUDIO_INPUT_PIN, INPUT);
  Serial.begin(38400);
  timer.begin(sample, 100);
}

void loop() {
  digitalWrite(LED1, LOW); digitalWrite(LED2, LOW); digitalWrite(LED3, LOW); digitalWrite(LED4, LOW);
  if (Ymax>400)  digitalWrite(LED1, HIGH);
  if (Ymax>435)  digitalWrite(LED2, HIGH);
  if (Ymax>470)  digitalWrite(LED3, HIGH);
  if (Ymax>500)  digitalWrite(LED4, HIGH);
  delay(100);
  Ymax = 0.9*Ymax;
}

void sample () {
  Xmin2 = Xmin1; Xmin1 = Xmin0;
  Xmin0 = analogRead(AUDIO_INPUT_PIN);
  Ymin2 = Ymin1; Ymin1 = Ymin0;
unsigned long BeginMicro = 0;
unsigned long EindMicro = 0;
// Begin Digitale filter 
  BeginMicro = micros();
  Ymin0 = (Xmin0 - 1.7526 * Xmin1 + 1.0000 * Xmin2) * 0.9950 + 1.7351 * Ymin1 - 0.9801 * Ymin2;
  EindMicro = micros();
  Serial.print(BeginMicro); 
  Serial.print("-"); 
  Serial.print(EindMicro); 
  Serial.print("="); 
  Serial.println(EindMicro-BeginMicro);
  // Eind digitale filter
  if (Ymin0 > Ymax) Ymax = Ymin0;
}
