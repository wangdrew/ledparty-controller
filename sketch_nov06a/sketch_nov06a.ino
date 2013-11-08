#define RED 0
#define GREEN 1
#define BLUE 2

#define NUM_STRIPS 3
#define RGB_COLORS 3
/* Globals */

// PWM pins on Arduino [strip][RGB]
int g_pin[3][3] = {
  {2,3,4},  //strip 0 RGB
  {5,6,7},  //strip 1 RGB
  {8,9,10}  //strip 2 RGB
};

// current RGB state of each strip, range 0-255 [strip][RGB]
int g_strip[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

// init RGB state of each strip, range 0-255 [strip][RGB]
// This is set at the beginning of each event
// These hold the initial RGB values to decay from for each event
int g_initstrip[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

// 1 - strip is ready for reinit and a new event
// 0 - strip is running an event
int stripStatus[3] = {1,1,1};

// Event timers, measure how much time progress(in ms) of an event
// Array of 3 elements -> 3 LED strips
int g_timer[3] = {0,0,0};

// Beats per minute, how many LED events occur every minute, 
// try to match it with BPM of music playing
int g_bpm = 120;

// Global gamma value, range 0.01 - 1.00
float gamma = 1.0;

// Event duration (in ms)
int g_duration = 200;

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
  adjustGamma();
}

void loop() {
  /*
    for each strip, update
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
      
    case 1:
      break;
  
    case 2:
      break;
      
    case 3:
      break;
    
    case 4:
      if (g_prevprogram != 4) {
        g_prevprogram = 4;
        turnOffAllStrips();  // reset strips
      }
      for (int strip = 0; strip < NUM_STRIPS; strip++) {
        // if strip has completed, reinit all strips and update
        // reinit by pulling a random color and setting all strips to it
        // otherwise update
        updateStrip(strip);
      }
  
}

void setInitStrip(int strip_id, int R, int G, int B) {
  g_initstrip[strip_id][RED] = R;
  g_initstrip[strip_id][GREEN] = G;
  g_initstrip[strip_id][BLUE] = B;
}

void updateStrip(int strip_id) {
  int currTime = g_timer[strip_id];
  int initRGB[3] = g_initstrip[strip_id];
  int currRGB[3] = g_strip[strip_id];
  
  // End event if the timer is up
  if (currTime + g_step >= g_duration) {
    g_strip[strip_id][RED] = 0;  // Turn off RGB
    g_strip[strip_id][GREEN] = 0;
    g_strip[strip_id[BLUE] = 0; 
    output(strip_id);
  } else {
    // Update the timer
    g_timer[strip_id] = currTime + g_step;
    
    // Calculate new RGB values
    for (int color = 0; color < RGB_COLORS; color++) {
    g_strip[strip_id][color] = 
      max(currRGB[color] - (initRGB[color]/(g_duration/g_step)), 0);
    }
    output(strip_id);
  }
}

void output(int strip_id) {
//analogWrite - Used to control PWM duty cycle on a pin
//Usage - analogWrite(pin,value)
//value: duty cycle between 0 - 255
  for (int color = 0; color < RGB_COLORS; color++) {
    if (g_strip[strip_id][color] > 255) g_strip[strip_id][color] = 255;
    if (g_strip[strip_id][color] < 0) g_strip[strip_id][color] = 0;
    analogWrite (g_pin[strip_id][color], int(gamma * g_strip[strip_id][color]));
  }
}

void turnOffAllStrips() {
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    for (int color = 0; color < RGB_COLORS; color++) {
      g_initstrip[strip][color] = 0;
      g_strip[strip][color] = 0;
    }
    output(strip);
  }
}

void adjustGamma() {
    // TODO: Make this adjustable via keypad or pot rotations
    // set to 1.0 for testing
    gamma = 1.0; 
}

long HSV_to_RGB( float h, float s, float v ) {
  /* modified from Alvy Ray Smith's site: http://www.alvyray.com/Papers/hsv2rgb.htm */
  // H is given on [0, 6]. S and V are given on [0, 1].
  // RGB is returned as a 24-bit long #rrggbb
  int i;
  float m, n, f;
 
  // not very elegant way of dealing with out of range: return black
  if ((s<0.0) || (s>1.0) || (v<1.0) || (v>1.0)) {
    return 0L;
  }
 
  if ((h < 0.0) || (h > 6.0)) {
    return long( v * 255 ) + long( v * 255 ) * 256 + long( v * 255 ) * 65536;
  }
  i = floor(h);
  f = h - i;
  if ( !(i&1) ) {
    f = 1 - f; // if i is even
  }
  m = v * (1 - s);
  n = v * (1 - s * f);
  switch (i) {
  case 6:
  case 0: 
    return long(v * 255 ) * 65536 + long( n * 255 ) * 256 + long( m * 255);
  case 1: 
    return long(n * 255 ) * 65536 + long( v * 255 ) * 256 + long( m * 255);
  case 2: 
    return long(m * 255 ) * 65536 + long( v * 255 ) * 256 + long( n * 255);
  case 3: 
    return long(m * 255 ) * 65536 + long( n * 255 ) * 256 + long( v * 255);
  case 4: 
    return long(n * 255 ) * 65536 + long( m * 255 ) * 256 + long( v * 255);
  case 5: 
    return long(v * 255 ) * 65536 + long( m * 255 ) * 256 + long( n * 255);
  }
}
