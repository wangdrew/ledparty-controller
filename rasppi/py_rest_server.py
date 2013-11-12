from flask import Flask
from flask import request
from arduino_api import ArduinoCommand
import serial
import __builtin__
import json
import mimerender

# Return 
mimerender = mimerender.FlaskMimeRender()

render_xml = lambda message: '<message>%s</message>'%message
render_json = lambda **args: json.dumps(args)
render_html = lambda message: '<html><body>%s</body></html>'%message
render_txt = lambda message: message

app = Flask(__name__)

@app.route('/fade', methods=['GET'])
@mimerender(
    default = 'html',
    html = render_html,
    xml  = render_xml,
    json = render_json,
    txt  = render_txt
)
def fade():

    '''
    Takes urls of form /fade?from=RRGGBB&to=RRGGBB&time=N 
    Color in hex, color will fade over N milliseconds
    '''
    # TODO: Call fade api

    return {'message': 'fade from color: ' + request.args.get('from') + 
        ' to: ' + request.args.get('to') + ' over ' + request.args.get('time') + ' ms'}

@app.route('/flash', methods=['GET'])
@mimerender(
    default = 'html',
    html = render_html,
    xml  = render_xml,
    json = render_json,
    txt  = render_txt
)
def flash():

    '''
    Takes URLs in form /flash?color=RRGGBB&on=M&off=N
    Color in hex. Lights will be ON for M milliseconds and OFF for N milliseconds
    '''
    # TODO: Call flash API
    # TODO: limit flash time to prevent siezures
    # TODO: Stop flashing after some time

    return {'message': 'Flashing ' + request.args['color'] + ' for on time ' + request.args['on'] + 
        'ms and OFF time ' + request.args['off'] + 'ms'}

@app.route('/solid', methods=['GET'])
@mimerender(
    default = 'html',
    html = render_html,
    xml  = render_xml,
    json = render_json,
    txt  = render_txt
)
def solid():

    '''
    Takes URLS in form /solid?color=RRGGBB
    '''
    # TODO: Call display solid color api

    return {'message': ' LEDs at color: ' + request.args['color']}


@app.route('/sequence', methods=['GET'])
@mimerender(
    default = 'html',
    html = render_html,
    xml  = render_xml,
    json = render_json,
    txt  = render_txt
)
def sequence():

    '''
    URL form: /sequence?id=N&intensity=O&tempo=P
    '''

    # TODO: Call a flash sequence

    cmd = ArduinoCommand(int(request.args['id']), int(request.args['intensity']), int(request.args['tempo']))
    cmd.execute()
    return {'message': 'using sequence id ' + request.args['id']}

if __name__ == "__main__":
    __builtin__.arduino_ser = serial.Serial("/dev/ttyACM0",9600)
    try:
        app.run(host='0.0.0.0', port=80)
    except:
        pass
    __builtin__.arduino_ser.close()
