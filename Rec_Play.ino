// Definiranje pinova
const int micPin = 14;                                  // Mikrofon povezan na GPIO14
const int speakerPin = 25;                              // Zvučnik povezan na GPIO25
const int sampleTime = 3000;                            // Vrijeme snimanja u milisekundama
const int sampleRate = 8000;                            // Broj uzoraka u sekundi
const int numSamples = sampleTime * sampleRate / 1000;  // Ukupan broj uzoraka

int samples[numSamples];  // Niz za pohranu uzoraka

void soundRec() {
  digitalWrite(2, HIGH);        // turn the LED on
  // Snimanje zvuka
  Serial.println("Snimanje zvuka...");
  for (int i = 0; i < numSamples; i++) {
    samples[i] = analogRead(micPin);
    delayMicroseconds(1000000 / sampleRate);
  }
  Serial.println("Kraj snimanja!");
  digitalWrite(2, LOW);  // turn the LED off
}

void setup() {
  // Inicijalizacija serijske komunikacije za debugging
  Serial.begin(115200); Serial.println("Hi!");
  pinMode(2, OUTPUT);
  soundRec();
}

void loop() {
  // Reprodukcija zvuka 5 puta
  for (int j = 0; j < 5; j++) {
    Serial.println("Reprodukcija zvuka...");
    for (int i = 0; i < numSamples; i++) {
      dacWrite(speakerPin, map(samples[i], 0, 4095, 0, 255) ); // Smanjivanje amplitude za DAC
      dacWrite(speakerPin, (samples[i] / 24) + 32);  // Smanjivanje amplitude za DAC
      delayMicroseconds(1000000 / sampleRate);
      delayMicroseconds(50);
    }
    Serial.println("Kraj reprodukcije!");
  }
}
