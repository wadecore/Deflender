// Includes:
#include <Bounce2.h>
#include <Wire.h> 
#include <RobotGeekLCD.h>

// Pins: These pins are arranged by function in Arrays
int buttonPins[26] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
int value[26]      = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

// Notes: These are keyboard keystrokes that correspond with a note on the piano, Starting from C-1, up a half step 
int key[32]   = {'z', 's', 'x', 'd', 'c', 'v', 'g', 'b', 'h', 'n', 'j', 'm', 'q', '2', 'w', '3', 'e', 'r', '5', 't', '6', 'y', '7', 'u', 'i',  '9', 'o', '0', 'p', '[', '=', ']'};
int keyoffset = 0;


//Pin Listing
//0 Skipped
//1-8 Strum Buttons
//9-23 Key Buttons
//13 Skipped
//18 SDA0 for I2C LCD
//19 SCL0 For I2C LCD
//24&25 Scale Up and Down
//26&27 Octave Up and Down
//24&25 Instrument Up and Down

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


// LCD Screen
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;           // interval at which to blink (milliseconds)

String scaleLine[8] = {"Ionian", 
                   "Dorian",
                   "Phyrigian",
                   "Lydian",
                   "Mixolydian",
                   "Aeolian",
                   "Locrian",
                   "HarmonicMin"
                   };

String keyLine[12] = {"C", 
                   "C# Db",
                   "D",
                   "D# Eb",
                   "E",
                   "F",
                   "F# Gb",
                   "G",
                   "G# Ab",
                   "A",
                   "A# Bb",
                   "B"
                   };

// Create objects
Bounce debounce[26] = Bounce(); //Debouncing Library
RobotGeekLCD lcd;               //I2C LCD Screen


void setup() {

  // Setup the button with an internal pull-up :
  for (int i = 0; i < 26; i = i + 1) 
  {
  pinMode(buttonPins[i],INPUT_PULLUP);
  debounce[i].attach(buttonPins[i]);
  debounce[i].interval(5);
  }

  // Rev up that Keyboard
  Keyboard.begin();

  // Get that screen all hot and bothered
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("deFlender");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Is go!");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void loop() 
{

  // LCD
  unsigned long currentMillis = millis(); // Update currentMillis
  if(currentMillis - previousMillis > interval) 
    {
      // save the last time you blinked the LED 
      previousMillis = currentMillis;   
      lcd.setCursor(0, 0);
      lcd.print(keyLine[keyoffset]);
      lcd.print("               ");
      lcd.setCursor(0, 1);
      lcd.print(scaleLine[scaleSelectCounter - 1]);
      lcd.print("               ");
    }
  
  // Update the Bounce instance:
  
  for (int i = 0; i < 26; i = i + 1) 
  {
    debounce[i].update();
    value[i] = debounce[i].read();
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
 










  // Scale Key Buttons:

  if ( debounce[20].fell() )
  {
    scaleSelectCounter = (scaleSelectCounter + 1);
  } 

  if ( debounce[21].fell() )
  {
    scaleSelectCounter = (scaleSelectCounter - 1);
    
  } 

  //Scales 
  if(scaleSelectCounter == 0)
  {
    scaleSelectCounter = 1;
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
    scaleSelectCounter = 8;
  }

// Change Instrument
  if ( debounce[22].fell() )
  {
    Keyboard.set_key1(KEY_RIGHT_ALT);
    Keyboard.set_key2(KEY_LEFT_ARROW);
    Keyboard.send_now();
    
    Keyboard.set_key1(0);
    Keyboard.set_key2(0);
    Keyboard.send_now();
  } 

  if ( debounce[23].fell() )
  {
    Keyboard.set_key1(KEY_RIGHT_ALT);
    Keyboard.set_key2(KEY_RIGHT_ARROW);
    Keyboard.send_now();
    
    Keyboard.set_key1(0);
    Keyboard.set_key2(0);
    Keyboard.send_now();
  } 

// Change Octave
  if ( debounce[24].fell() )
  {
    Keyboard.set_key1(KEYPAD_SLASH);
    Keyboard.send_now();
    
    Keyboard.set_key1(0);
    Keyboard.send_now();
  } 

  if ( debounce[25].fell() )
  {
    Keyboard.set_key1(KEYPAD_ASTERIX);
    Keyboard.send_now();
    
    Keyboard.set_key1(0);
    Keyboard.send_now();
  } 

}



