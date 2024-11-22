/* filename: TeensyFTTtest.
 * Autor: J. v/d Helder
 * date 27/05/2020
 * program developed for Teensy3.2 on Arduino IDE with the TeensyDruino plugin
 * When button SW1 is pressed, the sample table is filled and the FFT is calculated
 * When button SW2 is pressed the serial output will be the samples array (when SW3 is switched up), 
 * which is filled with a calculated signal or the calculated FFT-values (when SW3 is switched down) 
 */
#include <arm_math.h>
#define FFT_SIZE 256              // Size of the FFT.  Realistically can only be at most 256
#define BUTTON1 4                 // Button to start the sampling and FFT
#define BUTTON2 5                 // Button to display the time domain or freq. domain
#define SWITCH3 6                 // te switch dispay between freq/time domain
#define LED 11           
float samples[FFT_SIZE * 2];
float timeDomain[FFT_SIZE];
float freqDomain[FFT_SIZE];

void setup() {
  Serial.begin(38400);   // Set up serial port.
  pinMode(BUTTON1, INPUT);   // configure switches
  pinMode(BUTTON2, INPUT);
  pinMode(SWITCH3, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON1)) { // button (SW1) is pressed
    digitalWrite(LED, HIGH);
    
    for (int t=0; t<256; t++) {      // fill the samples array 

      samples[2*t] = sin(t*0.2);               // real part of a sinus
      // samples[2*t] = (t%32 < 16 ?  1: -1);    // real part square wave signal
      // samples[2*t] = (t%32)/16.0 -1;          // real part ..... signal

      samples[2*t+1] = 0.0;          // imaginary part is zerro
      timeDomain[t] = samples[2*t];
    }
    // Run FFT on sample data.
    arm_cfft_radix4_instance_f32 fft_inst;
    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_f32(&fft_inst, samples);
    // Calculate magnitude of complex numbers output by the FFT.
    arm_cmplx_mag_f32(samples, freqDomain, FFT_SIZE);
    delay(500);
    digitalWrite(LED, LOW);
  }
  if (digitalRead(BUTTON2)) { // button (SW2) is pressed
    if (digitalRead(SWITCH3)) {
      for (int t=0; t<256; t++) {  //print the "samples" signal
        Serial.print(t);
        Serial.print("= ");
        Serial.println(timeDomain[t]);
      }
    }
    else {
      for (int f = 1; f < 127; f++) { // print only first half, the others are imaginary
        Serial.print(f);
        Serial.print("= ");
        Serial.println(freqDomain[f]);
      }
    }
    delay(500);
  }
}
