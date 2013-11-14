
// Raspberry Pi interface
void readSerial() {
  // Commands:
    // 48-60 Light Patterns
    // 88 - 100 Light Sequences
    // 128-136 Gamma Control
  if (Serial.available() > 0) {
      
      serial_command = Serial.read();
      if (serial_command < 128) {
        if (serial_command < 88) {
          setLightProgram(serial_command - '0');
        } else {
          setLightSequence(serial_command - '0');
        }
      }
      else if (serial_command >= 128) {
       if (serial_command == 128) {
         setGamma(.05);
       } else if (serial_command == 129) {
         setGamma(.10);
       } else if (serial_command == 130) {
         setGamma(.15);
       } else if (serial_command == 131) {
         setGamma(.20);
       } else if (serial_command == 132) {
         setGamma(.25);
       } else if (serial_command == 133) {
         setGamma(.35);
       } else if (serial_command == 134) {
         setGamma(.50);
       } else if (serial_command == 135) {
         setGamma(.75);
       } else if (serial_command == 136) {
         setGamma(1.00);
       } else if (serial_command == 147) {
          if (g_siren) turnOffSiren();
          else turnOnSiren();
       }
       
      }
   }
}

/*
//Arduino testing interface
boolean readSerial() {
  if (Serial.available()) {
      Serial.println(commandByte0, DEC);
      commandByte0 = Serial.read();
    if (commandByte0 >= '0' && commandByte0 < '0' + NUM_LIGHT_PROGRAMS) {
      g_program = commandByte0 - '0';
    }
  }
}
*/

/*
// Arduino testing interface
void parseSerial() {
} */

/*

// Raspberry Pi interface
void parseSerial() {
  if (int(serial_commands[0] - '0') < NUM_LIGHT_PROGRAMS) {
    setLightProgram(serial_commands[0] - '0');
    setGamma(int(serial_commands[1])/255);
    // Ignoring tempo for now
  }
  else {
    setLightProgram(0);
  }
}
*/

