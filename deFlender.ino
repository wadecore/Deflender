#include <Bounce2.h>

// Pins: These pins are arranged by function in Arrays
int buttonPins[21] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 20, 21, 22, 23, 24};
int value[21]      = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 20, 21, 22, 23, 24};

// Notes: These are keyboard keystrokes that correspond with a note on the piano, Starting from C-1, up a half step 
int key[32]   = {'z', 's', 'x', 'd', 'c', 'v', 'g', 'b', 'h', 'n', 'j', 'm', 'q', '2', 'w', '3', 'e', 'r', '5', 't', '6', 'y', '7', 'u', 'i',  '9', 'o', '0', 'p', '[', '=', ']'};
int keyoffset = 0;

//pin 13 is a jerk
//pin 18 SDA0
//pin 19 SCL0

// Scale Select Counter Values
int scaleSelectCounter = 1;
//int scaleSelectMin = 1;
//int scaleSelectMax = 8;


// Scales: These arrays reference a position in the noteArray to map to a strum button pin

// Placeholder. Overwritten by scales.
int scaleStrum[8]        = {0, 0, 0, 0, 0, 0, 0, 0};
// Canonical
int scaleIonian[8]       = {0, 2, 4, 5, 7, 9, 11, 12}; //Major
int scaleDorian[8]       = {0, 2, 3, 5, 7, 9, 10, 12};
int scalePhyrigian[8]    = {0, 1, 3, 5, 7, 8, 10, 12};
int scaleLydian[8]       = {0, 2, 4, 6, 7, 9, 11, 12};
int scaleMixolydian[8]   = {0, 2, 4, 5, 7, 9, 10, 12};
int scaleAeolian[8]      = {0, 2, 3, 5, 7, 8, 10, 12}; //Natural Minor
int scaleLocrian[8]      = {0, 1, 3, 5, 6, 8, 10, 11};
// Extended
int scaleHarmonicMinor[8]= {0, 2, 3, 5, 7, 8, 11, 12};


// Instantiate Bounce objects for button debouncing
Bounce debounce[21] = Bounce();


void setup() {

  // Setup the button with an internal pull-up :
  for (int i = 0; i < 21; i = i + 1) 
  {
  pinMode(buttonPins[i],INPUT_PULLUP);
  debounce[i].attach(buttonPins[i]);
  debounce[i].interval(5);
  }

  // Rev up that Keyboard
  Keyboard.begin();



}

void loop() 
{
  // Update the Bounce instance:
  
  for (int i = 0; i < 21; i = i + 1) 
  {
    debounce[i].update();
    value[i] = debounce[i].read();
  }


  // Scale Key Buttons:

  if ( value[20] == LOW ) 
  {
    scaleSelectCounter++;
  } 

  
  if(scaleSelectCounter == 0)
  {
    scaleSelectCounter = 8;
  } 

  else if(scaleSelectCounter == 1)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleIonian[i];
    }
  }
  
  else if(scaleSelectCounter == 2)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleDorian[i];
    }
  }

  else if(scaleSelectCounter == 3)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scalePhyrigian[i];
    }
  }
  
  else if(scaleSelectCounter == 4)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleLydian[i];
    }
  }

  else if(scaleSelectCounter == 5)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleMixolydian[i];
    }
  }

  else if(scaleSelectCounter == 6)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleAeolian[i];
    }
  }

  else if(scaleSelectCounter == 7)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleLocrian[i];
    }
  }

  else if(scaleSelectCounter == 8)
  {
    for (int i = 0; i < 8; i = i + 1) 
    {
      scaleStrum[i] = scaleHarmonicMinor[i];
    }
  }

  else if(scaleSelectCounter == 9)
  {
    scaleSelectCounter = 1;
  }



  
  // Beginning Note Buttons:  

  for (int i = 8; i < 20; i = i + 1) 
  {
    if ( value[i] == LOW ) 
    {
      keyoffset = i - 8;
    } 
  }


  
  // Strum Buttons:  

  for (int i = 0; i < 8; i = i + 1) 
  {
    if ( value[i] == LOW ) 
    {
      Keyboard.press(key[scaleStrum[i]+keyoffset]);
    } 
    else if (value[i] == HIGH) 
    {
      Keyboard.release(key[scaleStrum[i]+keyoffset]);
    }
  }
 
}


