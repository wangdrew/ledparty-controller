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
float g_gamma = 0.0;

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


