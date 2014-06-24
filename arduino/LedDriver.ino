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
  // If strip is running an event
  if (g_status[id] == BUSY) {
    
    //Update the timer
    int currTime = g_timer[id];
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

    analogWrite(g_pin[id][color], int(g_gamma * g_current[id][color]));
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
      endEvent(id);
    }
    output(id);
}


void turnOnSiren() {
   g_siren = true;
   digitalWrite(g_siren_pin, HIGH);
}

void turnOffSiren() {
   g_siren = false;
   digitalWrite(g_siren_pin, LOW);
}

// Returns a random color from the color wheel excluding black
int* getRandomColor() {
  return COLORS[random(NUM_COLORS-1)];
}


void setGamma(float l_gamma) {
    // TODO: Make this adjustable via keypad or pot rotations
    // set to 1.0 for testing
    g_gamma = l_gamma; 
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

