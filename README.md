# Deflender
A controller for DefleMask. Dynamically arranges note structure by key and scale. Most definitely not a MIDI controller.

# What works right now:
Scale Selection Button - Scrolls through the canon scales and wraps around to first.
Key Selection Buttons - Starts the scale at the key selected from the pad
Play Buttons - Plays 8 notes, starting at the key selected, and progressing through the selected scale
Scale Selection Buttons - Scroll through a list of scales without wrapping around, by adding a decrement button
Octave Selection Buttons - Raise and lower the octave in Deflemask through a set of buttons
Instrument Selection Buttons - Scroll through a list of instruments in Deflemask through a set of buttons
LCD Screen - Display the selected Scale and Key for less ambiguous usage

# What's next:
Maybe a chord mode, further complicating the stack of arrays?
Maybe a SoftPot for playing chords?
Maybe make a Teensy breakout board?

# Parts:
Teensy 3.1
26 buttons
RobotGeek LCD screen
Bi-Directional Logic Level Converter (to make the screen work)