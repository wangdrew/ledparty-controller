#define R 0
#define G 1
#define B 2

#define STRIP0 0
#define STRIP1 1
#define STRIP2 2

#define NUM_STRIPS 3
#define NUM_COLORS 10
#define RGB_COLORS 3

#define BUSY 1
#define READY 0

#define PROGRAM_TEST_A 99
#define PROGRAM_TEST_B 100
/* Globals */

// Colors
  int RED[3] = {255,0,0};
  int ORANGE[3] = {255,30,0};
  int YELLOW[3] = {255,60,0};
  int LGREEN[3] = {255,255,0};
  int GREEN[3] = {0,255,0};
  int AQUA[3] = {0,255,128};
  int BLUE[3] = {0,0,255};
  int PURPLE[3] = {255,0,255};
  int WHITE[3] = {255,255,255};
  int BLACK[3] = {0,0,0};

// Color wheel - used for random selection of colors
int* COLORS[10] = {RED, ORANGE, YELLOW, LGREEN, GREEN, AQUA, BLUE, PURPLE, WHITE, BLACK};

// PWM pins on Arduino [strip][RGB]
int g_pin[3][3] = {
  {4,3,2},  //strip 0 RGB
  {7,6,5},  //strip 1 RGB
  {10,9,8}  //strip 2 RGB
};

// Digital out on Party siren
int g_siren_pin = 22;

// current RGB state of each strip, range 0-255 [strip][RGB]
float g_current[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

// initial RGB state of each strip, range 0-255 [strip][RGB]
// This is set at the beginning of each event
// These hold the initial RGB values to progress from for each event
float g_begin[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

// end RGB state of each strip, range 0-255 [strip][RGB]
// This is set at the beginning of each event
// These hold the end RGB values to progress to for each event
float g_end[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

// 0 - strip is ready for reinit and a new event
// 1 - strip is running an event
int g_status[3] = {READY,READY,READY};

// PWM amount to increment or decrement by per step. range -255 to 255 [strip][RGB]
// Computed at the beginning of each event
float g_steps[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

// Event timers, measure how much time progress(in ms) of an event
// Array of 3 elements -> 3 LED strips
int g_timer[3] = {0,0,0};

// Global gamma value, range 0.00 - 1.00
float gamma = 0.0;

// Event duration (in ms)
int g_duration[3] = {200,200,200};

// Used for misc. state handling for specific programs
int g_state[3] = {0,0,0};
//Used for PROGRAM_TEST_B
int program_color = 0;
int program_strip = 0;
int program_prevcolor = 0;

// Step duration, amount of time between RGB output adjustments (in ms)
int g_step = 5;

// Program number
int g_program = 0;

// Previous program, used to determine whether to re-init the RGB
// strips for a newly selected program
int g_prevprogram = -1;

// Program duration, how long (sec) to run each program.
// Used only when program 10 is used (random all programs) 
int g_programdur = 20;



/* End Globals */

/* Programs */
// 0 - all off
// 1 - RGB fade together (HSV)
// 2 - Single color fade across strips moving left (RGB)
// 3 - Single color fade across strips moving right (RGB)
// 4 - Soft strobe in unison (RGB)
// 5 - Soft strobe different colors (RGB)
// 6 - Discreet color changes in unison (RGB)
// 7 - Discreet color changes different colors (RGB)
// 8 - custom functions, programmable colors per strip
// 9 - all white
// 10 - cycle between programs 1-7

void setup() {
  setupPins();
  turnOffAllStrips();
  setGamma();

  // Debugging
  g_program = 6;
}

void loop() {
  /*
    for each strip, upda6e
    sleep for step - processing time duration
  */
  switch(g_program) {
    // Program 1: All strips OFF
    case 0:
      if (g_prevprogram != 0) {
        g_prevprogram = 0;
        turnOffAllStrips();
      }
      break;
      
    // all white  
    case 1:
      if (g_prevprogram != 2) {
        g_prevprogram = 2;
        turnOffAllStrips();
        program_color = 0;
        program_prevcolor = 0;
        gamma = .1;
        startEvent(STRIP0, 2000, BLACK, WHITE); //COLORS[program_color]
        startEvent(STRIP1, 2000, BLACK, WHITE);
        startEvent(STRIP2, 2000, BLACK, WHITE);
      }
      break;
  
    // RGB unified fading
    case 2:
      if (g_prevprogram != 2) {
        g_prevprogram = 2;
        turnOffAllStrips();
        program_color = 0;
        program_prevcolor = 0;
        gamma = .1;
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
        delay(g_step);
        
      break;
    
    // color strobing (headache inducing - use with caution!!!!)  
    case 3:
      if (g_prevprogram != 3) {
        g_prevprogram = 3;
        turnOffAllStrips();
        program_color = 0;
        gamma = .5;
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
       delay(g_step);
      break;
    
    // Color unified soft strobing
    case 4:
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
      delay(g_step);
      break;
    
    // Color individual soft strobing
     case 5:
       if (g_prevprogram != PROGRAM_TEST_A) {
         g_prevprogram = PROGRAM_TEST_A;

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
        
       delay(g_step); // debug
       break;
     
     // Moving random colors
     case 6:
       //g_state = 0  rising
       //g_state = 1 falling
     
       if (g_prevprogram != PROGRAM_TEST_B) {
         turnOffAllStrips();
         g_prevprogram = PROGRAM_TEST_B;
         g_state[STRIP0] = 0;
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
         delay(500);
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

       delay(g_step); // debug
       break;
       
  }
}


// Returns a random color from the color wheel excluding black
int* getRandomColor() {
  return COLORS[random(NUM_COLORS-1)];
}

// Call this function on a strip to start a single event.
//void startEvent(int id, int duration, int R_start, int G_start, int B_start, int R_end, int G_end, int B_end) {
void startEvent(int id, int duration, int *start_color, int *end_color) {  
  g_status[id] = BUSY;
  g_duration[id] = duration;
  
  g_begin[id][R] = start_color[R];
  g_current[id][R] = start_color[R];
  g_end[id][R] = end_color[R];
  g_begin[id][G] = start_color[G];
  g_current[id][G] = start_color[G];
  g_end[id][G] = end_color[G];
  g_begin[id][B] = start_color[B];
  g_current[id][B] = start_color[B];
  g_end[id][B] = end_color[B];
  
  for (int color = 0; color < RGB_COLORS; color++) {
    g_steps[id][color] = (g_end[id][color] - g_begin[id][color]) / (g_duration[id]/g_step);
  }
}

// Call this function on the end of every event to reset the strip state
void endEvent(int id) {
  g_timer[id] = 0;
  g_status[id] = READY;
}

void updateStrip(int id) {
  int currTime = g_timer[id];

  // Update the timer if strip is running an event
  if (g_status[id] == BUSY) {
    g_timer[id] = currTime + g_step;
    
    // Calculate new RGB values and output
    for (int color = 0; color < RGB_COLORS; color++) {
      g_current[id][color] = 
        max(g_current[id][color] + g_steps[id][color], 0);
      output(id);
    }
    
    // End event if timer is up
    if (currTime + g_step > g_duration[id]) {
      endEvent(id);
    }
  }
}


void output(int id) {
//analogWrite - Used to control PWM duty cycle on a pin
//Usage - analogWrite(pin,value)
//value: duty cycle between 0 - 255
  for (int color = 0; color < RGB_COLORS; color++) {
    if (g_current[id][color] > 255) g_current[id][color] = 255;
    if (g_current[id][color] < 0) g_current[id][color] = 0;

    analogWrite(g_pin[id][color], int(gamma * g_current[id][color]));
  }
}

void turnOffAllStrips() {
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    turnOffStrip(strip);
  }
}

void turnOffStrip(int id) {
    for (int color = 0; color < RGB_COLORS; color++) {
      g_begin[id][color] = BLACK[color];
      g_current[id][color] = BLACK[color];
      g_end[id][color] = BLACK[color];
    }
    output(id);
}


void turnOnSiren() {
   digitalWrite(g_siren_pin, HIGH);
}

void turnOffSiren() {
   digitalWrite(g_siren_pin, LOW);
}

void setGamma() {
    // TODO: Make this adjustable via keypad or pot rotations
    // set to 1.0 for testing
    gamma = 1; 
}

void setupPins() {
  // diagnostic LED
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  //Serial console
  Serial.begin(9600);
  
  // Initialize Party siren pin
  pinMode(g_siren_pin, OUTPUT);
  
  // Setup pins for RGB strips
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    for (int color = 0; color < RGB_COLORS; color++) {
      pinMode(g_pin[strip][color],OUTPUT);
    } 
  }
  
  // Random Seed for our random color generator
  randomSeed(analogRead(0));
}
