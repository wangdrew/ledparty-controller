//http://192.168.1.126/sequence?id=52&intensity=128&tempo=128


#include "LedDriver.h"
#include "LightPrograms.h"

#define PGID_MANUAL_CONTROL 99

// Program number
 int g_program = 0;

// Previous program, used to determine whether to re-init the RGB
// strips for a newly selected program
 int g_prevprogram = -1;

// Program duration, how long (sec) to run each program.
// Used only when program 10 is used (random all programs) 
 int g_programdur = 20;

// Written into by ManualCtrl. These are commands input via serial
// Format spec: 3 element array: 
// sequence ID <0-254>
// Intensity (gamma) value <0-255>
// Tempo <0-255>
byte serial_command = 0;

// Used by ManualCtrl
byte commandByte0;
byte commandByte1;
byte commandByte2;
int actionRecvd = 0;

void setup() {
  setupPins();
  turnOffAllStrips();
  setGamma(1.0);
  setLightProgram(0);
}

void loop() {
  
  /*
  if(readSerial()) {
    digitalWrite(22,HIGH);
    parseSerial();
  }*/
  readSerial();
  
  /*
    Run the current program by updating each strip then
    sleep for the duration of the step time
  */
  switch(g_program) {
    // Turn off all strips
    case 0:
      lp_all_off();
      delay(g_step);
      break;
      
    // Turn on all strips
    case 1:
      lp_all_white();
      delay(g_step);
      break;
  
    // Soft ROYGBIV fading
    case 2:
      lp_rgb_unified_fading();
      delay(g_step);
      break;
    
    // Flashy hard strobes on random strips
    case 3:
      lp_indiv_color_hard_strobe();
      delay(g_step);
      break;
    
    // Color unified soft strobing
    case 4:
      lp_unified_color_soft_strobe();
      delay(g_step);
      break;
    
    // Color independent interval soft strobing
     case 5:
       lp_indiv_diffint_color_soft_strobe();
       delay(g_step);
       break;
     
    // Moving random colors
     case 6:
       lp_indiv_single_color_soft_strobe();
       delay(g_step);
       break;
     
     case 7:
       lp_indiv_color_soft_strobe();
       delay(g_step);
       break;
     
     case PGID_MANUAL_CONTROL:
       break;
     
     case 8:
       lp_indiv_side_center_color_soft_strobe();
       delay(g_step);
       break;
       
     case 9:
       lp_soft_strobe_unified_red();
       delay(g_step);
       break;
     
       
     Serial.println("Invalid");
  }
  // Global delay
  //   delay(g_step); <---- this should work but is causing some weird linking issues
}
