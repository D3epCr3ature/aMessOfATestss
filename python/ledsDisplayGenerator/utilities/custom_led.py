
from math import pi

LED_DEFAULT_PITCH  = 2.5399999618530273
LED_DEFAULT_RADIUS = 50.0
LED_DEFAULT_TYPE   = "WS281x"

def createLed(angleRad, x, y,
              REF_X = 0.0, REF_Y = 0.0,
              pitch  = LED_DEFAULT_PITCH,
              radius = LED_DEFAULT_RADIUS,
              typ    = LED_DEFAULT_TYPE):
    led = {
        "angle": angleRad / pi * 180,
        "pitch": pitch, 
        "position": {
            "x": REF_X + x,
            "y": REF_Y + y
        },
        "radius": radius,
        "type": typ
    }
    return led

