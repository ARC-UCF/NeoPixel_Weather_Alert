#ifndef SETPRESETS

#define NUM_PRESETS 6

/* This enumeration is only used in order to index the preset arrays which
 * follow. They are formatted so that each weather status is on a separate
 * line.
 */

typedef enum LEDPresets: char {
  GREEN, YELLOW, RED,
  BLUE,
  PURPLE, BLANK
} LedPresets;

/* The preset colors are stored as 3 element long arrays with each element
 * representing the value of the color. They are ligned up to match the
 * previous enumeration.
 */

extern uint8_t PRESETS[NUM_PRESETS][3] 
{{0,128,0},{128,128,0},{128,0,0},
{0,0,128},
{64,0,128},{0,0,0}};

class LEDStatus {
  private:
    LEDPresets colorState[NUM_LED];   // Tracks the static state of the LEDs
    LEDPresets prevState[NUM_LED];    // Tracks the previous status
    bool changed[NUM_LED];            // Tracks if color was changed
  public:
    LEDStatus()
    {
      for (uint8_t i = 0; i < NUM_LED; ++i)
      {
        colorState[i] = BLANK;
        prevState[i] = BLANK;
      }
    }
    void setStatus(LEDPresets preset, uint8_t i)
    {
      if (colorState != -1) {
        prevState[i] = colorState[i];
        colorState[i] = preset;
        setChanged(i);
        return;
      }
      colorState[i] = prevState[i];
    }
    LEDPresets grabStatus(uint8_t i)
    {
      return colorState[i];
    }
    LEDPresets grabPrevStatus(uint8_t i)
    {
      return prevState[i];
    }
    bool hasChanged(uint8_t i)
    {
      return changed[i];
    }
    void setChanged(uint8_t i)
    {
      changed[i] = true;
    }
    void resetChanged()               // Ideally this function is called after every serial input
    {
      for (uint8_t i = 0; i < NUM_LED; ++i)
      {
        changed[i] = false;
      }
    }
};

#define SETPRESETS

#endif
