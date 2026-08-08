#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "presets.h"

/* The following line will create the strip and set all of the necessary
 * characteristics, I have no idea how this line works as I pulled it from
 * a sample.
 */

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LED, PIN, NEO_GRB + NEO_KHZ800);

/* We keep both the current and previous status, this is used so that way we
 * can write the serial data directly to the status while being able to revert
 * back to the previous state when using NULL characters.
 */

LEDStatus status =  LEDStatus();
char animationState, trash, inputStatus[NUM_LED];

void setup(void) {
  Serial.begin(9600);

  animationState = '@';

  strip.begin();
  strip.show();

  applyStatus(status);
}

void loop(void) {
  animationState = -1;

  /* This will only trigger if we know that there is at least one full set of
   * data for setting the strip's color. We add 1 or 0 to account for if we
   * need to handle the new line character or not.
   */

  while(Serial.available() == 0)
    delay(500);

  Serial.flush();

  if (Serial.available() == (NUM_LED + 1 + USING_NULL)) {
    Serial.readBytesUntil('\n' , inputStatus, NUM_LED);

    for (uint8_t i = 0; i < NUM_LED; i++) {
      status.setStatus(inputStatus[i] - 'A', i);

    }

    animationState = Serial.read() - 'A';

    /* This flushes the serial data, some people say that the 'Serial.flush()'
     * function will do this, however it does not. That function is designed to
     * pause while waiting for data to be transfered.
     */

    while(Serial.available() > 0)
      trash = Serial.read();
    
    animationCall(status, animationState);
    applyStatus(status);
    status.resetChanged();

    return;
  }

  else if (Serial.available() == (1 + USING_NULL)) {
    animationState = Serial.read() - 'A';

    animationCall(status, animationState);
    applyStatus(status);

    while(Serial.available() > 0)
      Serial.read();

    return;
  }

  else {
    while(Serial.available() > 0)
      trash = Serial.read();
  }

}

void applyStatus(LEDStatus status) {
  for (uint8_t i = 0; i < NUM_LED; i++) {   // Sets each led color
    extractLEDPreset(status.grabStatus(i), i);
  }


  strip.show();
}

void applyPreset(LEDPresets preset) {
  for (uint8_t i = 0; i < NUM_LED; i++) {   // Sets each led color
    extractLEDPreset(preset, i);
  }

  strip.show();
}

void extractLEDPreset(LEDPresets preset, uint8_t pixel) {
  uint8_t r,g,b;

  /* We pull from the PRESETS array and then use the proper enumeration index
   * in order to set the colors of the pixel.
   */

  if (preset == -1)
    return;
  
  r = PRESETS[preset][0];
  g = PRESETS[preset][1];
  b = PRESETS[preset][2];

  strip.setPixelColor(pixel, r,g,b);
}

/* Animations */

void animationCall(LEDStatus status, char animation) {
  if (animation == -1) {
    return;
  }

  switch (animation) {
    case 0:
      lightning();
      break;
    case 1:
      statusChange(status);
      break;
  }
  
}

void lightning(void) { 
  for (uint8_t i = 0; i < 20; i++) {
    applyPreset(PURPLE);
    delay(random(20,70));
    applyPreset(BLANK);
    delay(random(50,150));
  }
}

void statusChange(LEDStatus status) {
  LEDStatus blankedStatus = LEDStatus();

  /* The goal is to make the pixels defined in the array be set to blank so
   * that there can be a flashing like effect.
   */

  for (uint8_t i = 0; i < NUM_LED; i++) {
    if (status.hasChanged(i)) {
      blankedStatus.setStatus(i, status.grabStatus(i));
    }
  }

  for (uint8_t i = 0; i < 20; i++) {
    if (Serial.available() > 0)
      return;
    applyStatus(status);
    delay(500);
    applyStatus(blankedStatus);
    delay(500);     
  }

}
