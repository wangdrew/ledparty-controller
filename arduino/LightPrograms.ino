/***********************
* LightProgram
* Contains pre-programmed light patterns
* Usage: Run from the mainloop
* each function call will only update all strips once
*
***********************/

void setLightProgram(int lp_val) {
  if (lp_val >= 0 && lp_val < NUM_LIGHT_PROGRAMS) {
    g_program = lp_val;
  } else {
    g_program = 0;
  }
}

// Program ID = 0
// Turn all strips off
void lp_all_off() {
    if (g_prevprogram != 0) {
      g_prevprogram = 0;
      turnOffAllStrips();
    }
}

// Program ID = 1
// Turn all strips to white
// TODO: Make this LP independent of number of strips
void lp_all_white() {
  if (g_prevprogram != 1) {
    g_prevprogram = 1;
    turnOffAllStrips();
    program_color = 0;
    program_prevcolor = 0;
    for (int strip = 0; strip < NUM_STRIPS; strip++) {
      startEvent(strip, 2000, BLACK, WHITE);
    }
  }
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    updateStrip(strip);
  }
}

// Program ID = 2
// Fade through ROYGBIV for all strips at the same time
// TODO: Make this LP independent of number of strips
void lp_rgb_unified_fading() {
  if (g_prevprogram != 2) {
    g_prevprogram = 2;
    turnOffAllStrips();
    program_color = 0;
    program_prevcolor = 0;
    startEvent(STRIP0, 2000, BLACK, COLORS[program_color]); //COLORS[program_color]
    startEvent(STRIP1, 2000, BLACK, COLORS[program_color]);
    startEvent(STRIP2, 2000, BLACK, COLORS[program_color]);
  }
    if (g_status[STRIP0] == READY &&
        g_status[STRIP1] == READY &&
        g_status[STRIP2] == READY) {
      startEvent(STRIP0, 2000, COLORS[program_prevcolor], COLORS[program_color]); //COLORS[program_prevcolor]
      startEvent(STRIP1, 2000, COLORS[program_prevcolor], COLORS[program_color]);
      startEvent(STRIP2, 2000, COLORS[program_prevcolor], COLORS[program_color]);
      program_prevcolor = program_color;
      if (program_color + 1 > 7) {
        program_color = 0;
      } else {
        program_color++;
      }
    }
    updateStrip(STRIP0);
    updateStrip(STRIP1);
    updateStrip(STRIP2);
}

// Program ID = 3
// Hard strobe a random color on a random strip
// TODO: Make this function independent of number of strips
void lp_indiv_color_hard_strobe() {
  if (g_prevprogram != 3) {
    g_prevprogram = 3;
    turnOffAllStrips();
    program_color = 0;
    startEvent(program_strip, 20, COLORS[program_color], COLORS[program_color]);
  }
  // Select a new random strip
  if (g_status[STRIP0] == READY &&
      g_status[STRIP1] == READY &&
      g_status[STRIP2] == READY)
   {
     turnOffAllStrips();
     program_strip = random(NUM_STRIPS);
     program_color = random(NUM_COLORS-2);
     delay(40);
     startEvent(program_strip, 50, COLORS[program_color], COLORS[program_color]); 
   }
   updateStrip(program_strip);
}

// Program ID = 4
// Soft strobe a random color on all strips
void lp_unified_color_soft_strobe() {
  if (g_prevprogram != 4) {
    g_prevprogram = 4;
    turnOffAllStrips();  // reset strips
    program_color = 0;
  }
  
  if (g_status[STRIP0] == READY && 
  g_status[STRIP1] == READY && 
  g_status[STRIP2] == READY)
  {
    program_color = random(NUM_COLORS-1);
    startEvent(STRIP0, 425, COLORS[program_color], BLACK);
    startEvent(STRIP1, 425, COLORS[program_color] ,BLACK);
    startEvent(STRIP2, 425, COLORS[program_color], BLACK);
  }
      
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
      updateStrip(strip);
  }
}

// Program ID = 5
// Soft strobe random colors on all strips at different intervals
void lp_indiv_diffint_color_soft_strobe() {
   if (g_prevprogram != 5) {
     g_prevprogram = 5;
     turnOffAllStrips();
     startEvent(STRIP0, 250, BLACK, RED);
     startEvent(STRIP1, 250, BLACK, GREEN);
     startEvent(STRIP2, 250, BLACK, BLUE);
   }
   
   if (g_status[STRIP0] == BUSY) {
     updateStrip(STRIP0);
   } else {
     startEvent(STRIP0, 200, getRandomColor(), BLACK);
   }
   
   if (g_status[STRIP1] == BUSY) {
     updateStrip(STRIP1);
   } else {
     startEvent(STRIP1,300, getRandomColor(), BLACK);
   } 
   
   if (g_status[STRIP2] == BUSY) {
     updateStrip(STRIP2);
   } else {
     startEvent(STRIP2, 250, getRandomColor(), BLACK);
   }  
}

// Program ID = 6
// Soft strobe a random color one strip at a time in a specified order
void lp_indiv_single_color_soft_strobe() {
  //g_state = 0  rising
   //g_state = 1 falling
 
   if (g_prevprogram != 6) {
     turnOffAllStrips();
     g_prevprogram = 6;
     g_state[STRIP0] = 0;
     g_state[STRIP1] = 0;
     g_state[STRIP2] = 0;
     int program_color = 0;
     startEvent(STRIP0, 500, BLACK, COLORS[program_color]);
   }
   
   // Trigger rising edge of strip1
   if (g_timer[STRIP0] >= 400 && g_state[STRIP0] == 0) {
       g_state[STRIP1] = 0;
      startEvent(STRIP1, 500, BLACK, COLORS[program_color]);
   } 
   
   // Trigger rising edge of strip2
   if (g_timer[STRIP1] >= 400 && g_state[STRIP1] == 0) {
     g_state[STRIP2] = 0;
     startEvent(STRIP2, 500, BLACK, COLORS[program_color]);
   }
   
  if (g_status[STRIP0] == BUSY) {
     updateStrip(STRIP0);
   } else if (g_state[STRIP0] == 0){
     g_state[STRIP0] = 1;
     startEvent(STRIP0, 500, COLORS[program_color], BLACK);
     // Start entire loop again, start rising edge of strip0
   } else if (g_state[STRIP1] == 1 && g_state[STRIP2] == 1 
            && g_status[STRIP1] == READY && g_status[STRIP2] == READY)
   {
     //delay(50);
     g_state[STRIP0] = 0;
     program_color = random(9);
     startEvent(STRIP0, 500, BLACK, COLORS[program_color]);
 
   }
   
   if (g_status[STRIP1] == BUSY) {
     updateStrip(STRIP1);
   } else if (g_state[STRIP1] == 0){
     g_state[STRIP1] = 1;
     startEvent(STRIP1, 500, COLORS[program_color], BLACK);
   }
   
   if (g_status[STRIP2] == BUSY) {
     updateStrip(STRIP2);
   } else if (g_state[STRIP2] == 0){
     g_state[STRIP2] = 1;
     startEvent(STRIP2, 500, COLORS[program_color], BLACK);
   }
}

// Program ID = 7
// Hard strobe a random color on a random strip
// TODO: Make this function independent of number of strips
void lp_indiv_color_soft_strobe() {
  if (g_prevprogram != 7) {
    g_prevprogram = 7;
    turnOffAllStrips();
    program_color = 0;
    startEvent(program_strip, 425, COLORS[program_color], BLACK);
  }
  // Select a new random strip
  if (g_status[STRIP0] == READY &&
      g_status[STRIP1] == READY &&
      g_status[STRIP2] == READY)
   {
     turnOffAllStrips();
     program_strip = random(NUM_STRIPS);
     program_color = random(NUM_COLORS-2);
     startEvent(program_strip, 425, COLORS[program_color], BLACK); 
   }
   updateStrip(program_strip);
}

// Program ID = 8
// Soft strobe strips 1 and 3, then 2
void lp_indiv_side_center_color_soft_strobe() {
  if (g_prevprogram != 8) {
    
    g_prevprogram = 8;
    turnOffAllStrips();
    program_color = 0;
    g_state[STRIP0] = 0;
    g_state[STRIP1] = 0;
    g_state[STRIP2] = 0; 
    startEvent(STRIP0, 1000, BLACK, COLORS[program_color]); //425
    startEvent(STRIP2, 1000, BLACK, COLORS[program_color]); 
  }
     // Trigger rising edge of strip1
   if (g_timer[STRIP0] >= 400 && g_state[STRIP0] == 0) {
     g_state[STRIP1] = 0;
     startEvent(STRIP1, 500, BLACK, COLORS[program_color]);
   }
   
  if (g_status[STRIP0] == BUSY) {
     updateStrip(STRIP0);
     updateStrip(STRIP2);
   } else if (g_state[STRIP0] == 0){
     g_state[STRIP0] = 1;
     g_state[STRIP2] = 1;
     startEvent(STRIP0, 500, COLORS[program_color], BLACK);
     startEvent(STRIP2, 500, COLORS[program_color], BLACK);
     // Start entire loop again, start rising edge of strip0
   } else if (g_status[STRIP0] == READY && g_status[STRIP1] == READY && g_status[STRIP2] == READY) {;
     //delay(1000);
     g_state[STRIP0] = 0;
     g_state[STRIP2] = 0;
     program_color = random(9);
     startEvent(STRIP0, 500, BLACK, COLORS[program_color]);
     startEvent(STRIP2, 500, BLACK, COLORS[program_color]);
   }
   
   if (g_status[STRIP1] == BUSY) {
     updateStrip(STRIP1);
   } else if (g_state[STRIP1] == 0){
     g_state[STRIP1] = 1;
     startEvent(STRIP1, 500, COLORS[program_color], BLACK);
   }
}

// Program ID = 9
// Soft strobe a color sequentially on all strips
void lp_sequential_color_soft_strobe() {
  if (g_prevprogram != 9) {
    g_prevprogram = 9;
    turnOffAllStrips();  // reset strips
    program_color = 0;
    program_strip = 0;
    startEvent(STRIP0, 425, COLORS[program_color], BLACK);
  }
  
  if (g_status[STRIP0] == READY && program_strip == 0) {
    program_strip = 1;
    startEvent(STRIP1, 425, COLORS[program_color], BLACK);
  } 
  if (g_status[STRIP1] == READY && program_strip == 1) {
    program_strip = 2;
    startEvent(STRIP2, 425, COLORS[program_color], BLACK);
  }
  if (g_status[STRIP2] == READY && program_strip == 2) {
    program_color = random(NUM_COLORS-1);
    program_strip = 0;
    startEvent(STRIP0, 425, COLORS[program_color], BLACK);
  }
      
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
      updateStrip(strip);
  }
}

// PROGRAM ID = 10
// Fade to a random color on random strips
void lp_random_color_fade() {
    if (g_prevprogram != 10) {
    g_prevprogram = 10;
    turnOffAllStrips();  // reset strips
    program_strip = 0;
    for (int strip = 0; strip < NUM_STRIPS; strip++) {
      program_color = random(NUM_COLORS-2);
      program_prevcolors[strip] = COLORS[program_color];
      startEvent(strip, 425, BLACK, COLORS[program_color]);
    }
  }
  if (g_status[STRIP0] == READY &&
      g_status[STRIP1] == READY &&
      g_status[STRIP2] == READY){
        program_strip = random(NUM_STRIPS);
        program_color = random(NUM_COLORS-2);
        startEvent(program_strip, 425, program_prevcolors[program_strip], COLORS[program_color]);
        program_prevcolors[program_strip] = COLORS[program_color];
      }
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    updateStrip(strip);
  }
}

//PROGRAM ID = 11
//Fade to a random color on sequential strip order
void lp_sequential_color_fade() {
    if (g_prevprogram != 11) {
    g_prevprogram = 11;
    turnOffAllStrips();  // reset strips
    program_strip = 0;
    for (int strip = 0; strip < NUM_STRIPS; strip++) {
      program_color = random(NUM_COLORS-2);
      program_prevcolors[strip] = COLORS[program_color];
      startEvent(strip, 425, BLACK, COLORS[program_color]);
    }
  }
  if (g_status[STRIP0] == READY &&
      g_status[STRIP1] == READY &&
      g_status[STRIP2] == READY){
        prev_program_strip = program_strip;
        if (prev_program_strip == 2) {
          program_strip = 0;
        } else {
          program_strip = prev_program_strip + 1; 
        }
        program_color = random(NUM_COLORS-2);
        startEvent(program_strip, 425, program_prevcolors[program_strip], COLORS[program_color]);
        program_prevcolors[program_strip] = COLORS[program_color];
      }
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    updateStrip(strip);
  }
}

// Program ID = 12
// Hard strobe a random color sequentially strip
// TODO: Make this function independent of number of strips
void lp_sequential_color_hard_strobe() {
  if (g_prevprogram != 12) {
    g_prevprogram = 12;
    turnOffAllStrips();
    program_color = 0;
    program_strip = 0;
    startEvent(program_strip, 20, COLORS[program_color], COLORS[program_color]);
  }
  // Select a new random strip
  if (g_status[STRIP0] == READY &&
      g_status[STRIP1] == READY &&
      g_status[STRIP2] == READY)
   {
     
     turnOffAllStrips();
     prev_program_strip = program_strip;
     if (prev_program_strip == 2) program_strip = 0;
     else {
       program_strip = prev_program_strip + 1;
     }
     program_color = random(NUM_COLORS-2);
     delay(40);
     startEvent(program_strip, 50, COLORS[program_color], COLORS[program_color]); 
   }
   updateStrip(program_strip);
}
  
// Program ID = 13
// Hold a solid color on all strips
void lp_custom_solid_color(int colorindex) {
   if (g_prevprogram != 13) {
    g_prevprogram = 13;
  }
  for (int strip = 0; strip < NUM_COLORS-2; strip++) {
    startEvent(strip, 10, COLORS[colorindex], COLORS[colorindex]);
    updateStrip(strip);
  }
} 

// Custom light program called by a sequence
void lp_custom_soft_strobe(int* color, int dur, int strip) {
  startEvent(strip, dur, color, BLACK);
}

// Soft strobe set to the tempo of ROAR
// TODO: Make this function independent of number of strips
void lp_indiv_color_soft_strobe_roar() {
  if (g_prevprogram != 14) {
    g_prevprogram = 14;
    turnOffAllStrips();
    program_color = 0;
    startEvent(program_strip, 444, COLORS[program_color], BLACK);
  }
  // Select a new random strip
  if (g_status[STRIP0] == READY &&
      g_status[STRIP1] == READY &&
      g_status[STRIP2] == READY)
   {
     turnOffAllStrips();
     program_strip = random(NUM_STRIPS);
     program_color = random(NUM_COLORS-2);
     startEvent(program_strip, 444, COLORS[program_color], BLACK); 
   }
   updateStrip(program_strip);
}

/*   
// Program ID = 9
// Soft strobe a random color on all strips
void lp_soft_strobe_unified_blue() {
  if (g_prevprogram != 9) {
    g_prevprogram = 9;
    turnOffAllStrips();  // reset strips
  }
  
  if (g_status[STRIP0] == READY && 
  g_status[STRIP1] == READY && 
  g_status[STRIP2] == READY)
  {
    startEvent(STRIP0, 461, BLUE, DBLUE);
    startEvent(STRIP1, 461, BLUE ,DBLUE);
    startEvent(STRIP2, 461, BLUE ,DBLUE);
  }
      
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
      updateStrip(strip);
  }
}

// Program ID = 10
// Soft strobe a random color on all strips
void lp_soft_strobe_unified_red() {
  if (g_prevprogram != 10) {
    g_prevprogram = 10;
    turnOffAllStrips();  // reset strips
  }
  
  if (g_status[STRIP0] == READY && 
  g_status[STRIP1] == READY && 
  g_status[STRIP2] == READY)
  {
    startEvent(STRIP0, 461, RED, DRED);
    startEvent(STRIP1, 461, RED ,DRED);
    startEvent(STRIP2, 461, RED ,DRED);
  }
      
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
      updateStrip(strip);
  }
}

*/
