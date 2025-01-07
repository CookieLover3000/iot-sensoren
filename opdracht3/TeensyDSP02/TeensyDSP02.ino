/*  Teensy digtal filter 2 versie
 *  Author: J. van den Helder
 *  Date 9 juni 2023
 *  Een ingangssignaal (sinus) Met variable frequentie [20..1000Hz] wordt  
 *  middels DSP gefilterd.
 *  
 */
#define SW1 4
#define PM1 15        // Input ADC pin for potentiometer)
#define TwoPi 6.2831853072
#define TRUE 1
#define FALSE 0
unsigned long int n =0;
int f;   // frequentie in Hz
int i;
int vul = FALSE;
float Xmin2, Xmin1, Xmin0, X[500];
float Ymin2, Ymin1, Ymin0, Y[500];
IntervalTimer timer;
void sample();

void setup() {
  pinMode(PM1, INPUT);
  pinMode(SW1, INPUT);
  Serial.begin(38400);
  timer.begin(sample, 100); // Ts =  100 usec => fs = 10 Khz
}

void loop() {
    while (digitalRead(SW1)==0); delay(50);
    while (digitalRead(SW1)==1); delay(50);
    f = 20 + int(980*analogRead(PM1)/1023);  // 20 < f < 1000 Hz
    vul = TRUE;
    i=0;
    while(vul){delay(20);};
    for(int j = 0; j < 500; j++) {
      Serial.print(X[j]);
      Serial.print(" ; ");
      Serial.println(Y[j]);
    }
}

void sample () {
  if (vul) {
    Xmin2 = Xmin1;   Xmin1 = Xmin0; // bewaar de vorige waarden van X
    Ymin2 = Ymin1;   Ymin1 = Ymin0; // bewaar de vorige waarden van Y
    Xmin0 = 10.0*sin(TwoPi*f*i/10000);
    // Begin Digitale filter
//    Ymin0 = 0.5*Xmin0;
//    Ymin0 = 0.35 * Xmin0 + 0.65 * Ymin1;
//    Ymin0 = Xmin0 - Xmin1 + 0.65*Ymin1;
    Ymin0 = ( Xmin0  + 50*Ymin1 - 25*Ymin2)/26;
    // Eind digitale filteer
  
    X[i]=Xmin0;
    Y[i]=Ymin0; 
    i++;
    if (i == 500) {i = 0; vul = FALSE;}
  }
}
