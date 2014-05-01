//----------------------------------------------------------------------------------------------------------------------
// TinyPCRemote 
// Original code by Nathan Chantrell http://nathan.chantrell.net
// Modified by Electro_Phunk. Email me for questions or comments at ubuildpc@gmail.com, alternatively discus your issues on Nathan's forum
// Receives infra red codes and turns on or off the output pin
//
// Licenced under the Creative Commons Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0) licence:
// http://creativecommons.org/licenses/by-sa/3.0/
//----------------------------------------------------------------------------------------------------------------------

#define IRpin_PIN      PINB
# define IRpin          2

#define MAXPULSE 5000 // max IR pulse length
#define NUMPULSES 100 // max IR pulse pairs to sample
#define RESOLUTION 2 // time between IR measurements

uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing



void setup() {

  pinMode(2, INPUT); // Make sure IR pin is set as input
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

}

void loop() {

  unsigned long irCode=listenForIR(); // Wait for an IR Code

  // Process the pulses to get our code
  for (int i = 0; i < 32; i++) {
    irCode=irCode<<1;
    if((pulses[i][0] * RESOLUTION)>0&&(pulses[i][0] * RESOLUTION)<500) {
      irCode|=0; 
    } 
    else {
      irCode|=1;
    }
  }

  /*----------------------------------------------------------------------------------------
   // execute function when button is pushed-------------------------------------------------
   -----------------------------------------------------------------------------------------*/
// The code below will turn on the led when the button is pushed and turn off the led if the other button is pushed

 /*3354975012
 - up arrow
3354981132
 - Down arrow
3354977052
 - left arrow
3354979092
 - right arrow

3354920952 - 1
3354921972
 - 2
3354922992
 - 3
3354924012
 - 4
3354978072
 - OK
 */
 
  if (irCode==3354920952) { // Paste the decoded remote button code like this: if (irCode== decoded code) 
    digitalWrite(0, HIGH); // switch on led
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    
    listenForIR(); // listen for new instructions
  }   

  else if (irCode==3354921972){ // this allows for a second function. You may use this as many times as required

    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    listenForIR(); // listen for new instructions 

  }
  
  else if (irCode==3354922992){ // this allows for a second function. You may use this as many times as required

    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    listenForIR(); // listen for new instructions 

  }
  
  else if (irCode==3354924012){ // this allows for a second function. You may use this as many times as required

    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    listenForIR(); // listen for new instructions 

  }
  
  else if (irCode==3354978072){ // this allows for a second function. You may use this as many times as required

    digitalWrite(0, HIGH); // switch off led 
    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    delay(500);
    //
    digitalWrite(0, HIGH); // switch off led 
    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    delay(500);
    //
    digitalWrite(0, HIGH); // switch off led 
    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    delay(500);
    //
    digitalWrite(0, HIGH); // switch off led 
    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    delay(500);
    //
    digitalWrite(0, HIGH); // switch off led 
    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(500);
    digitalWrite(0, LOW); // switch off led 
    digitalWrite(1, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    delay(500);
    listenForIR(); // listen for new instructions 

  }

} // loop end

/*----------------------------------------------------------------------------------------
 IR receive code---------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------*/

int listenForIR() {  
  currentpulse = 0;
  while (1) {
    unsigned int highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length 

    while (IRpin_PIN & _BV(IRpin)) { // got a high pulse
      //UsbKeyboard.update(); // needs to be called often
      highpulse++; 
      delayMicroseconds(RESOLUTION);
      if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
        return currentpulse; 
      }
    }
    pulses[currentpulse][0] = highpulse;

    while (! (IRpin_PIN & _BV(IRpin))) { // got a low pulse
      // UsbKeyboard.update(); // needs to be called often
      lowpulse++; 
      delayMicroseconds(RESOLUTION);
      if (((lowpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
        return currentpulse; 
      }
    }
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
  }
}







