#!/usr/bin/python

import json
from utilities.custom_led import * 
import sys

IDX_X = 0
IDX_Y = 1

TOP_LEFT_X = 1000
TOP_LEFT_Y = 1000

DEFAULT_WIDTH  = 16
DEFAULT_HEIGHT = DEFAULT_WIDTH

OUT_FILE_SUFFIX  = ".disp"
DEFAULT_OUT_FILE = "./matrix_" +               \
                   str(DEFAULT_WIDTH)  + "x" + \
                   str(DEFAULT_HEIGHT) + OUT_FILE_SUFFIX

### MAIN FN ###
def main(args=None) -> str:
    argc  = len(sys.argv)
    argc -= 1 # Remove exectuable path from counted args

    # Default values that can depend from args
    filename_set = False
    h = DEFAULT_HEIGHT
    w = DEFAULT_WIDTH

    if (argc < 0) or (argc > 4):
        print('usage: %s [-h] [display_filename] [w=<width>] [h=<height>]' % sys.argv[0])
        return

    for arg in sys.argv[1:]:
        if arg == '-h':
            print('       display_filename: Suffix needs to be \".disp\".')
            print('                         The program will add if it\'s '
                  'not the case.')
            print('                         When not specified, the default '
                  'is \"%s\"' % DEFAULT_OUT_FILE)
            print('       h=<height>      : Height of a display (in pixels)')
            print('       w=<width>       : Width  of a display (in pixels)')
            return
        elif arg.startswith("h="):
            h = int(arg[2:])
        elif arg.startswith("w="):
            w = int(arg[2:])
        else: # It's display_filename
            filename_set = True
            display_filename = arg

    # Set default filename based on defined width & height
    if not filename_set:
        display_filename = "./matrix_" + str(w) + "x" + str(h) + OUT_FILE_SUFFIX

    # Generate display
    leds = []
    for r in range(h):
        for c in range(w):
            # -50*row as Y in Qt is reverse
            # (Top -> Bottom means value increasing)
            leds.append(createLed(0, 50*c if (r % 2) == 0 else 50*(w-c-1), -50*r,
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))

    print('len(leds):', len(leds))

    # Wrapping leds array
    wrapped = {
        "leds": leds
    }

    # Serializing json
    json_object = json.dumps(wrapped, indent=4)

    # Writing to sample.json
    with open(display_filename, "w") as outfile:
        outfile.write(json_object)

    return

### ACTUAL MAIN ###
if __name__ == "__main__":
    main()

