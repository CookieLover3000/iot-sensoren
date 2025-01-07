/*  Teensy digtal filter  3 versie 2
 *  Author: J. van den Helder
 *  Date 9 juni 2023
 *  Digitale filter; een ingangs signaal wordt vergeleken met het gefilterde signaal.
 *  
 */
#define SW1 4
#define TwoPi 6.2831853072
#define TRUE 1
#define FALSE 0
int f;                    // frequentie
int i ;
int vul;
float Xmin2, Xmin1, Xmin0, X[500];
float Ymin2, Ymin1, Ymin0, Y[500];
IntervalTimer timer;
void sample();

void setup() {
  pinMode(SW1, INPUT);
  Serial.begin(38400);
  timer.begin(sample, 100); // 100usec => fs = 10kHz
}

void loop() {
    while (digitalRead(SW1)==0); delay(50);
    while (digitalRead(SW1)==1); delay(50);
    for (f = 20; f<1020; f+=2) {
      vul = TRUE;
      i=0;
      while(vul) delay(1);
      float Ymax = 0;
      for(int j = (f-20)/2.1; j < 500; j++) { // de laatste paar Y waarden voldoen
         if (Y[j] > Ymax) Ymax=Y[j];
      }
      Serial.println(Ymax);
    }
}

void sample () {
  if (vul and i>=0) {
    Xmin2 = Xmin1; Xmin1 = Xmin0;
    Ymin2 = Ymin1; Ymin1 = Ymin0;
    Xmin0 = 10.0*sin(TwoPi*f*i/10000);
    // Begin Digitale filter 
//    Ymin0 = (Xmin0 + 50*Ymin1 - 25*Ymin2)/26; 
    Ymin0 = (Xmin0 - 1.7526 * Xmin1 + 1.0000 * Xmin2) * 0.9950 + 1.7351 * Ymin1 - 0.9801 * Ymin2;
    // Eind digitale filter
    X[i]=Xmin0;
    Y[i]=Ymin0; 
    i++;
    if (i >= 500) {i = 0; vul = FALSE;}
  }
}
