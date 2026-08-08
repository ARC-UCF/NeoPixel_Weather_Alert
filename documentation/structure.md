# LEDStatus Class

This class holds the current color state of each of the leds, an indication if
the led has been changed since the last "resetChanged" call, and the previous
color status.

## Functions

### "setStatus"

This function will take a LED preset color and assign it to the "i" pixel. In
the event that we attempt to assign the -1 "null" color we skip over setting
the previous color and will instead set the color to the previous state used,
technically there is no need for assigining this color again.

### "grabStatus"

This function simply returns the LED preset of the "i" color in the LED strip.

### "grabPrevStatus"

Identical to the "grabStatus" function but for the "prevState" instead.

### "hasChanged"

Returns the value of the "i" element in the "changed" array to indicate if the
"i" color was changed since the last "resetChanged" call.

### "getChanged"

Sets the "i" value in the "changed" array to true.

### "resetChanged"

Sets all of the values in the "changed" array back to false.

## Variables

### "colorState"

This array tracks the color state of each individual led, the numbered led
corrosponds to the space within the array.

### "prevState"

Identical to "colorState" but now keeps track of the previous "colorState",
this allows us to have a way of tracking changed colors and their previous
color.

### "changed"

This boolean array tracks if a color has been changed since the last call of
"resetChanged". This variable is useful to animations used to indicate changes
in colors.
