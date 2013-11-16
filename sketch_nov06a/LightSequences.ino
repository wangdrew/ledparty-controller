void setLightSequence(int ls_val) {
  if (ls_val >= 40 && ls_val < 40 + NUM_LIGHT_SEQUENCES) {
    g_program = ls_val;
  } else {
    g_program = 0;
  }
}

void ls_loop_seq1() {
  g_program = 0;
  int std_duration = 2000;
  int beat_timer = 0;
  int random_variance = 0;
  int random_selection = 0;
  
  while (true) {
    if (Serial.available()) {
      break;
    }
    random_selection = random(6);
    random_variance = random(2000);
    Serial.println(random_variance + std_duration, DEC);  
    beat_timer = 0;
    
    switch(random_selection) {
      case 0:
        while (beat_timer < std_duration + random_variance) {
          lp_sequential_color_soft_strobe();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
        
      case 1:
        while (beat_timer < std_duration + random_variance) {
          lp_indiv_side_center_color_soft_strobe();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
        
      case 2:
        while (beat_timer < std_duration + random_variance) {
          lp_indiv_color_soft_strobe();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
        
      case 3:
        while (beat_timer < std_duration + random_variance) {
          lp_unified_color_soft_strobe();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
        
      case 4:
        while (beat_timer < std_duration + random_variance) {
          lp_rgb_unified_fading();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
        
      case 5:
        while (beat_timer < std_duration + random_variance) {
          lp_sequential_color_fade();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
        
      case 6:
        while (beat_timer < std_duration + random_variance) {
          lp_indiv_single_color_soft_strobe();
          if (Serial.available()) break;
          delay(g_step);
          beat_timer++;
        }
        break;
    }
  }
}
  



void ls_roar_sequence() {
  g_program = 0; // Turn off after this sequence is complete
  int beat_timer = 0;
  int random_color = 0;
  int random_strip = 0;
  delay(600);
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
