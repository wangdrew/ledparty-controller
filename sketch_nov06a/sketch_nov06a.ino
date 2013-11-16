//http://192.168.1.126/sequence?id=52&intensity=128&tempo=128


#include "LedDriver.h"
#include "LightPrograms.h"
#include "LightSequences.h"

#define PGID_MANUAL_CONTROL 99

// Program number
int g_program = 0;

// Previous program, used to determine whether to re-init the RGB
// strips for a newly selected program
int g_prevprogram = -1;

// Program duration, how long (sec) to run each program.
// Used only when program 10 is used (random all programs) 
int g_programdur = 20;
 
// Color tracking used for program 13
int prog13colorindex = 0;

// Written into by ManualCtrl. These are commands input via serial
byte serial_command = 0;

boolean g_siren = false;

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
      lp_all_off(); // serial -48
      delay(g_step);
      break;
      
    // Turn on all strips
    case 1:
      lp_all_white(); // serial - 49
      delay(g_step);
      break;
  
    // Soft ROYGBIV fading
    case 2:
      lp_rgb_unified_fading(); // serial - 50
      delay(g_step);
      break;
    
    // Flashy hard strobes on random strips
    case 3:
      lp_indiv_color_hard_strobe(); // serial - 51
      delay(g_step);
      break;
    
    // Color unified soft strobing
    case 4:
      lp_unified_color_soft_strobe(); // serial 52
      delay(g_step);
      break;
    
    // Color independent interval soft strobing
     case 5:
       lp_indiv_diffint_color_soft_strobe(); //serial 53
       delay(g_step);
       break;
     
    // Moving random colors
     case 6:
       lp_indiv_single_color_soft_strobe(); // serial 54
       delay(g_step);
       break;
     
     case 7:
       lp_indiv_color_soft_strobe(); // serial 55
       delay(g_step);
       break;
     
     case 8:
       lp_indiv_side_center_color_soft_strobe(); // serial 56
       delay(g_step);
       break;
       
     case 9:
       lp_sequential_color_soft_strobe(); // serial 57
       delay(g_step);
       break;
       
     case 10:
       lp_random_color_fade(); // serial 58
       delay(g_step);
       break;
     
     case 11:
       lp_sequential_color_fade(); // serial 59
       delay(g_step);
       break;
       
     case 12:
       lp_sequential_color_hard_strobe(); // serial 60
       delay(g_step);
       break;
       
     /*case 13:
       lp_custom_solid_color(prog13colorindex); // serial 61
       delay(g_step);
       break;
        //solid*/
       
     case 40:
       ls_roar_sequence(); // serial 88
       break;
       
     case 41:
       ls_loop_seq1(); // serial 89
       break;
       
  }
  // Global delay
  //   delay(g_step); <---- this should work but is causing some weird linking issues
}
