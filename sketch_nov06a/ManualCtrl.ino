
// Raspberry Pi interface
void readSerial() {
  if (Serial.available() > 0) {
    //commandByte0 = Serial.read(); // - '0';
    //commandByte1 = Serial.read();
    
    //if (commandByte0 == 255 && commandByte1 == 255) {
      
      serial_command = Serial.read(); // Event ID <0-254>
      if (serial_command - '0' < NUM_LIGHT_PROGRAMS) {
        actionRecvd = 1;
        setLightProgram(serial_command - '0');
      }
      else if (actionRecvd == 1) {
        if (serial_command > 0  &&  serial_command < 256)
        {
          actionRecvd = 0;
          setGamma(int(serial_command)/255);
        }
      }
    }
    /*
      serial_commands[1] = Serial.read(); // Gamma <1-255>
      //serial_commands[2] = Serial.read(); // Tempo <0-255>
      if (serial_commands[0] <= 254) {
        return true;
      } else return false;
    //}
    //else {
    //  return false;
    //}
  } else return false; */
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

