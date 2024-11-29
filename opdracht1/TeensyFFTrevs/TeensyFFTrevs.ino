// filename: TeensyFTTtest.
// Autor: J. v/d Helder
// date 27/05/2020
// program developed for Teensy3.2 on Arduino IDE with the TeensyDruino plugin
// When button SW1 is pressed, the sample table is filled and the FFT is calculated
// When button SW2 is pressed the serial output will be the samples array (when SW3 is switched up), 
// which is filled with a calculated signal or the calculated FFT-values (when SW3 is switched down) 
#define ARM_MATH_CM4
#include <arm_math.h>
const int FFT_SIZE = 256;              // Size of the FFT.  Realistically can only be at most 256
const int BUTTON1 = 4;                 // Button to start the sampling and FFT
const int BUTTON2 = 5;                 // Button to display the time domain or freq. domain
const int SWITCH3 = 6;                 // te switch dispay between freq/time domain
const int LED = 11;                    // to switch dispay between freq/time domain
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
    // fill sample array
    for (int t=0; t < FFT_SIZE; t++) {      // fill the samples array with a pure sinus
      //samples[2*t] = sin(t*0.2);  // real part
      samples[2*t] = (t%32 < 16 ?  1: -1);    // real part
      //samples[2*t] = (t%32)/16.0 -1;  // real part
      samples[2*t+1] = 0.0;          // imaginary part
    }
    // Run FFT on sample data.
    arm_cfft_radix4_instance_f32 fft_inst;
    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_f32(&fft_inst, samples);
    // Calculate magnitude of complex numbers output by the FFT.
    arm_cmplx_mag_f32(samples, freqDomain, FFT_SIZE);
    delay(500);
    
    //Calculating back from complex frequency Domain to time Domain.
    for (int t=0; t<FFT_SIZE; t++) timeDomain[t] = 0.0;
    for (int t=0; t<FFT_SIZE; t++) {
      for (int f=0; f<128; f++) {
        timeDomain[t] += samples[2*f]*cos(2*PI*t*f/FFT_SIZE)/FFT_SIZE - samples[2*f+1]*sin(2*PI*t*f/FFT_SIZE)/FFT_SIZE;
      }
    }
    digitalWrite(LED, LOW);
  }
  if (digitalRead(BUTTON2)) { // button (SW2) is pressed
    if (digitalRead(SWITCH3)) {
      for (int t=0; t<FFT_SIZE; t++) {  //print the "samples" signal
        Serial.print(t);
        Serial.print("= ");
        Serial.println(timeDomain[t]);
      }
    }
    else {
      for (int f = 1; f < FFT_SIZE/2; f++) { // print only first half, the others are imaginary
        Serial.print(f);
        Serial.print("= ");
        Serial.println(freqDomain[f]);
      }
    }
    delay(500);
  }
}
