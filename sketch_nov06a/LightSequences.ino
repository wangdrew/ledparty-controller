void setLightSequence(int ls_val) {
  if (ls_val >= 40 && ls_val < 40 + NUM_LIGHT_SEQUENCES) {
    g_program = ls_val;
  } else {
    g_program = 0;
  }
}


void ls_roar_sequence() {
  g_program = 0; // Turn off after this sequence is complete
  int beat_timer = 0;
  int random_color = 0;
  int random_strip = 0;

  beat_timer = 0;
  while (beat_timer < 32) {
    lp_custom_soft_strobe(RED,448,STRIP1);
    while (g_status[STRIP1] == BUSY) {
      updateStrip(STRIP1);
      delay(g_step);
    }
    beat_timer++;
  } 
  
  beat_timer = 0;
  while (beat_timer < 32) {
    lp_custom_soft_strobe(RED,395, STRIP0);
    lp_custom_soft_strobe(RED,395, STRIP1);
    lp_custom_soft_strobe(RED,395, STRIP2);
    while (g_status[STRIP2] == BUSY) {
      updateStrip(STRIP0);
      updateStrip(STRIP1);
      updateStrip(STRIP2);
      delay(g_step);
      }
    beat_timer++;
  }
  
  beat_timer = 0;
  while (beat_timer < 32) {
    random_color = random(NUM_COLORS-2);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP0);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP1);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP2);
    while (g_status[STRIP2] == BUSY) {
      updateStrip(STRIP0);
      updateStrip(STRIP1);
      updateStrip(STRIP2);
      delay(g_step);
      }
    beat_timer++;
  }
  
  beat_timer = 0;
  while (beat_timer < 32) {
    random_color = random(NUM_COLORS-2);
    lp_custom_soft_strobe(COLORS[random_color],448,STRIP1);
    while (g_status[STRIP1] == BUSY) {
      updateStrip(STRIP1);
      delay(g_step);
    }
    beat_timer++;
  } 
  
  while (beat_timer < 1155) {
    lp_indiv_diffint_color_soft_strobe();
    delay(g_step);
    beat_timer++;
  }
  delay(170);
  
  beat_timer = 0;
  while (beat_timer < 18) {
    random_color = random(NUM_COLORS-2);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP0);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP1);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP2);
    while (g_status[STRIP2] == BUSY) {
      updateStrip(STRIP0);
      updateStrip(STRIP1);
      updateStrip(STRIP2);
      delay(g_step);
      }
    beat_timer++;
  }
  
    beat_timer = 0;
    while (beat_timer < 32) {
    random_color = random(NUM_COLORS-2);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP0);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP1);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP2);
    while (g_status[STRIP2] == BUSY) {
      updateStrip(STRIP0);
      updateStrip(STRIP1);
      updateStrip(STRIP2);
      delay(g_step);
      }
    beat_timer++;
  }
  
  beat_timer = 0;
  while (beat_timer < 64 ) {
   random_strip = random(NUM_STRIPS);
   random_color = random(NUM_COLORS-2);
   startEvent(random_strip, 445, COLORS[random_color], BLACK);
    // Select a new random strip
    while (g_status[random_strip] == BUSY) {
       updateStrip(random_strip);
       delay(g_step);
    }
    beat_timer++;
  }
  
  beat_timer = 0;
  while (beat_timer < 32) {
    random_color = random(NUM_COLORS-2);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP0);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP1);
    lp_custom_soft_strobe(COLORS[random_color],393, STRIP2);
    while (g_status[STRIP2] == BUSY) {
      updateStrip(STRIP0);
      updateStrip(STRIP1);
      updateStrip(STRIP2);
      delay(g_step);
      }
    beat_timer++;
  }
  delay(40);

  beat_timer = 0;
  while (beat_timer < 64 ) {
   random_strip = random(NUM_STRIPS);
   random_color = random(NUM_COLORS-2);
   startEvent(random_strip, 445, COLORS[random_color], BLACK);
    // Select a new random strip
    while (g_status[random_strip] == BUSY) {
       updateStrip(random_strip);
       delay(g_step);
    }
    beat_timer++;
  }
  
  beat_timer = 0;
  lp_custom_soft_strobe(WHITE,2000, STRIP0);
  lp_custom_soft_strobe(WHITE,2000, STRIP1);
  lp_custom_soft_strobe(WHITE,2000, STRIP2);
  while (g_status[STRIP2] == BUSY) {
    updateStrip(STRIP0);
    updateStrip(STRIP1);
    updateStrip(STRIP2);
    delay(g_step);
  } 
  turnOffAllStrips();
  g_program = 0;
}
