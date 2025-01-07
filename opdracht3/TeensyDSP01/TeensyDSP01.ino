/*  Teensy Digital Signal Processing 01
 *  Author: J. van den Helder
 *  Date 9 maart 2021
 *  DSP reactie op heaviside functie van een eerste orde filter.
 * 
 */
#define SW1 4
float X[500], Y[500];
int n = 0, klaar = 0;
int k = 1;

void setup() {
  pinMode(SW1, INPUT);
  Serial.begin(38400);
}

void loop() {
  while(digitalRead(SW1)==0); delay(50);
  while(digitalRead(SW1)==1); delay(50);     // wacht to SW1 wordt losgelaten
  X[0] = 0.0;   Y[0] = 0.0;                  // vul X0 en Y0 omdat [n-1] niet fout mag gaan
  for (int n = 1; n <500; n++){
    if (n<25) X[n] = 0.0; else X[n] = 10.0;  // Heavisidefunction
    //Digitale Filter
//    Y[n] = 0.15*X[n] + 0.85*Y[n-1];  // integrator, low pass
    float C = 0.95123;
    Y[n] = X[n]-X[n-1]+C*Y[n-1];
  } 

  for (int n = 0; n< 500; n++){
    Serial.print( X[n]);
    Serial.print( " ; ");
    Serial.println(Y[n]);
  }
}
