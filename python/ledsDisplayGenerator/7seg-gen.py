#!/usr/bin/python

import json
from utilities.custom_led import * 
import sys

IDX_X = 0
IDX_Y = 1

TOP_LEFT_X = 2570
TOP_LEFT_Y = 2470

OUT_FILE_SUFFIX  = ".disp"
DEFAULT_OUT_FILE = "./7Seg_L3" + OUT_FILE_SUFFIX

### MAIN FN ###
def main(args=None) -> str:
    argc  = len(sys.argv)
    argc -= 1 # Remove exectuable path from counted args

    # Default values that can depend from args
    filename_set = False

    if (argc < 0) or (argc > 2):
        print('usage: %s [-h] [display_filename]' % sys.argv[0])
        return

    for arg in sys.argv[1:]:
        if arg == '-h':
            print('       display_filename: Suffix needs to be \".disp\".')
            print('                         The program will add if it\'s '
                  'not the case.')
            print('                         When not specified, the default '
                  'is \"%s\"' % DEFAULT_OUT_FILE)
            return
        else: # It's display_filename
            filename_set = True
            display_filename = arg

    # Set default filename based on defined width & height
    if not filename_set:
        display_filename = DEFAULT_OUT_FILE

    spacing = LED_DEFAULT_RADIUS + 7.5

    # Generate display
    leds = []
    # Segment: 0 #
    for x in range(3):
            leds.append(createLed(0, spacing*(1+x), 0,
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))
    # Segment: 1 #
    for y in range(3):
            leds.append(createLed(0, spacing*(4), spacing*(1+y), 
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))
    # Segment: 2 #
    for y in range(3):
            leds.append(createLed(0, spacing*(4), spacing*(5+y), 
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))
    # Segment: 3 #
    for x in range(2, -1, -1):
            leds.append(createLed(0, spacing*(1+x), spacing*(8),
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))
    # Segment: 4 #
    for y in range(2, -1, -1):
            leds.append(createLed(0, 0, spacing*(5+y), 
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))
    # Segment: 5 #
    for y in range(2, -1, -1):
            leds.append(createLed(0, 0, spacing*(1+y), 
                                  REF_X = TOP_LEFT_X, REF_Y = TOP_LEFT_Y))
    # Segment: 6 #
    for x in range(3):
            leds.append(createLed(0, spacing*(1+x), spacing*(4),
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

