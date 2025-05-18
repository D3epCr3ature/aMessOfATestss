
from math import pi

def createLed(angleRad, x, y,
              REF_X = 0.0, REF_Y = 0.0,
              pitch=2.5399999618530273,
              radius=50.0,
              typ="WS281x"):
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

