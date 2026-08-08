# How To Change Colors and Animations

The ardunio accepts two formats for changing colors or triggering animations.
One format is sending a letter for each color of the strip along with an animation
letter at the end, and the other is sending a single animation letter. These values
should be sent to arduino as single byte ascii values.

# Null Color/Animation

The "@" symbol can be used when you don't want a color to change or an animation to trigger.
This symbol should be used anytime you are choosing to not change the color (although the
code will catch if you try and assign the same color twice and will automatically use it).
This symbol is important for any animations which rely on knowledge of recently changed colors.

# Preset List

* Green (A)
* Yellow (B)
* Red (C)
* Blue (D)
* Purple (E)
* Blank (F)

# Animation List

## Lightning (A)

Plays a brief series of purple flashes.

## Status Change (B)

Makes any recently changed (colors not assigned null values) blink for 30 seconds.