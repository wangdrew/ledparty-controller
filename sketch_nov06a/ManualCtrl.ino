boolean readSerial() {
  if (Serial.available()) {
    commandByte0 = Serial.read(); // - '0';
    commandByte1 = Serial.read();
    commandByte2 = Serial.read();
    
    if (commandByte0 == 255 && commandByte1 == 255 && commandByte2 == 255) {
      serial_commands[0] = Serial.read(); // Event ID <0-254>
      serial_commands[1] = Serial.read(); // Gamma <0-255>
      serial_commands[2] = Serial.read(); // Tempo <0-255>
      if (serial_commands[0] <= 254) {
        return true;
      } else return false;
    }
    else {
      return false;
    }
  } else return false;
}

void parseSerial() {
  if (serial_commands[0] - '0'< NUM_LIGHT_PROGRAMS) {
    setLightProgram(serial_commands[0] - '0');
    setGamma(serial_commands[1]/255);
    // Ignoring tempo for now
  }
  else {
    setLightProgram(0);
  }
}
