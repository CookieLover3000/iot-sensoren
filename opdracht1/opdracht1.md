# Opdracht 1

1. Waar staat ARM voor?

    Advanced Risc Machines

2.  Welke micro processor zit er op de Teensy3.2?

    ARM Cortex-M4

3. Wat is de kloksnelheid en intern geheugen van deze processor?

    kloksnelheid: 72 MHz - Geheugen: 64KB

4. Pas de code nu dusdanig aan dat de speaker op de Teensy Board met een frequentie van 500 Hz gaat piepen door deze 1 ms aan en 1 ms uit te zetten. Zoek in het Schema van de Teensy Board (BrightSpace) op welke poort de speaker zit. (letop!: een pin-nummer is geen poortnummer) Zet deze code in je practicum-verslag.


    ```cpp
    void setup(){
    pinMode(3, OUTPUT);
    }

    void loop() {
    digitalWrite(3, HIGH);
    delay(1);
    digitalWrite(3, LOW);
    delay(1);
    }
    ```

5. Wat zijn de argumenten die samplingTimer meekrijgt, en verklaar dat.

    Het krijgt de functie sample en een tijdsinterval van 100ms mee.

6. Gegeven dat het lezen van een analoge waarde en omzetten naar een digitale waarde 10 microseconden duurt, wat zou de maximale sampling frequentie dan kunnen zijn?

    10*10^-6 = 0,00001

    1/0.00001 = 100.000 KHz

7. Kopieer het plaatje in je practicum verslag.

    ![alt text](image.png)

8. Het plaatje laat een laag frequent (stoor) signaal zien. Schat aan de hand van het plaatje de frequentie in van dit signaal, en verklaar hoe je aan deze schatting komt.

    $T = 500μs * 100μs = 50 ms $ 

    Het signaal gaat 7 keer. Dus $1000 ms/50ms*7=140 Hz$

9. Kopieer het plaatje in je practicum-verslag. Leg uit wat je nu ziet. Stel dat de samplefrequentie 9000 Hz is. Schat en verklaar uit dit plaatje de frequentie van het signaal.
    
    ![alt text](image-1.png)

    Er zijn 256 samples gemaakt. met een sampling frequentie van 9000 Hz betekent dat dus dat deze afbeelding is gesampled in $256 / 9000 = 0.02844444444$ seconden. De golven worden 8 keer herhaalt en dat betekent dat een frequentie van $1/(0.02844444444 / 8) = 281$ Hz wordt gebruikt.

10. Kopieer het plaatje in je practicum verslag. Leg uit wat je nu ziet.

    ![alt text](image-2.png)

Ik zie een piek aan de linkerkant van de grafiek.

11. Bij welke “f”-waarde ligt de piek?

    De piek ligt bij de “f”-waarde 8

12. Gegeven is dat de sampling frequentie 9000Hz was. Wat is dan de frequentie van de gemeten signaal? (beargumenteer je antwoord volledig)