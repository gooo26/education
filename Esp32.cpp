#include <SD.h>
#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"

#define SD_CS 5

AudioGeneratorWAV *wav;
AudioFileSourceSD *file = nullptr;
AudioOutputI2S *out;

void playSound(const char *name) {
  if (wav->isRunning()) wav->stop();
  if (file) delete file;
  file = new AudioFileSourceSD(name);
  wav->begin(file, out);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  if (!SD.begin(SD_CS)) {
    Serial.println("SD card nahi mila!");
    while (1);
  }
  Serial.println("SD card OK");

  out = new AudioOutputI2S(0, 1);   // internal DAC, GPIO25
  out->SetGain(0.8);
  wav = new AudioGeneratorWAV();
}

void loop() {
  Serial.println("Unlock sound bajao");
  playSound("/unlock.wav");
  while (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  }
  delay(3000);

  Serial.println("Wrong sound bajao");
  playSound("/wrong.wav");
  while (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  }
  delay(3000);
}
