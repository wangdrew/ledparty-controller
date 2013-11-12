import serial
import __builtin__


'''
Valid Colors on LED strips

RED = [255,0,0]
ORANGE = [255,30,0]
YELLOW = [255, 60, 0]
L_GREEN = [0, 255, 0]
GREEN = [0, 255, 0]
AQUA = [0, 255, 128]
BLUE = [0, 0, 255]
PURPLE = [255, 0, 255]
WHITE = [255, 255, 255]
BLACK = [0, 0, 0]
'''

'''
0 turn off
1 turn on to white
2 fade between colors
'''

class ArduinoCommand(object):

    """
    Defines packets for a command that will be sent to Arduino
    """
    def __init__(self, action_code, intensity, tempo):
        if action_code < 0 or action_code >= 254:
            raise ValueError("action code must be between 1 and 254")
        elif intensity < 0 or intensity > 255:
            raise ValueError("intensity must be between 0 and 255")
        elif tempo <0 or tempo > 255:
            raise ValueError("tempo must be between 0 and 255")
        self.command_sequence = [chr(action_code)]

#        self.command_sequence = [chr(255), chr(255), chr(action_code), chr(intensity), chr(tempo)]

    def execute(self):
        for v in self.command_sequence:
            __builtin__.arduino_ser.write(v)

