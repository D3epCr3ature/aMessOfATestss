#!/usr/bin/python

import json
from math import atan, cos, pi
from utilities.custom_led import * 
from utilities.float_ranges import * 
import sys

# 2D array access index: [X = 0, Y = 1]
IDX_X = 0
IDX_Y = 1

# Center display position
CENTER_X = 2500
CENTER_Y = 2500

# Output file default
OUT_FILE_SUFFIX  = ".disp"
DEFAULT_OUT_FILE = "./BMTH-LudensStar" + OUT_FILE_SUFFIX

def slopeFn(x, m, b):
    return m*x + b

def computeSlopeFromPoints(p1, p2):
    return (p2[IDX_Y] - p1[IDX_Y]) / (p2[IDX_X] - p1[IDX_X])

def createOffsetsAndRanges_branch01(step):
    ofst_rgs = []
    ofst_rgs.append([ 0,  -80, float_range(-( 1)*step, -(32+1)*step, -step)])
    ofst_rgs.append([ 0,    0, float_range(-(33)*step,            0,  step)])
    ofst_rgs.append([ 0,  +80, float_range(-( 3)*step, -(26+3)*step, -step)])
    return ofst_rgs

def createOffsetsAndRanges_branch11(step):
    ofst_rgs = []
    ofst_rgs.append([ 0,  +80, float_range( ( 1)*step,  (32+1)*step,  step)])
    ofst_rgs.append([ 0,    0, float_range( (33)*step,            0, -step)])
    ofst_rgs.append([ 0,  -80, float_range( ( 2)*step,  (28+2)*step,  step)])
    return ofst_rgs

def createOffsetsAndRanges_branch06(step):
    ofst_rgs = []
    ofst_rgs.append([ 0,  +80, float_range( (26+2)*step,     (2)*step, -step)])
    ofst_rgs.append([ 0,    0, float_range(        step,  (33+1)*step,  step)])
    ofst_rgs.append([ 0,  -80, float_range( (32+0)*step,     (0)*step, -step)])
    return ofst_rgs

def createOffsetsAndRanges_branch10(step):
    ofst_rgs = []
    ofst_rgs.append([ 0,  -80, float_range(-(28+1)*step,    -(1)*step,  step)])
    ofst_rgs.append([ 0,    0, float_range(-       step, -(33+1)*step, -step)])
    ofst_rgs.append([ 0,  +80, float_range(-(32)*step,    0,  step)])
    return ofst_rgs

def createOffsetsAndRanges_branch02(step):
    ofst_rgs = []
    ofst_rgs.append([-700, -80+280, float_range(-(20-1)*step, step,  step)])
    ofst_rgs.append([-700,    +280, float_range(-step, -(25+1)*step,  -step)])
    ofst_rgs.append([-700, +80+280, float_range(-(27+1)*step, -step,  step)])
    return ofst_rgs

def createOffsetsAndRanges_branch12(step):
    ofst_rgs = []
    #ofst_rgs.append([ 700, +80-280, float_range_list( (15+3+3-1)*step, -step, -step)])
    #del ofst_rgs[0][2][15:18]
    ofst_rgs.append([ 700, +80-280, float_range_list( (15+3+3-1)*step, (3+3-1)*step, -step)])
    ofst_rgs.append([ 700, +80-280, float_range_list( (2)*step, -step, -step)])

    #ofst_rgs.append([ 700,    -280, float_range_list( step,  (20+3+3+1)*step,  step)])
    #del ofst_rgs[1][2][3:6]
    ofst_rgs.append([ 700,    -280, float_range_list( step,  (3+1)*step,  step)])
    ofst_rgs.append([ 700,    -280, float_range_list( (3+4)*step,  (20+3+3+1)*step,  step)])

    #ofst_rgs.append([ 700, -80-280, float_range_list( (22+3+3+1)*step,  step, -step)])
    #del ofst_rgs[2][2][22:25]
    ofst_rgs.append([ 700, -80-280, float_range_list( (22+3+3+2-1)*step, (3+3+2-1)*step, -step)])
    ofst_rgs.append([ 700, -80-280, float_range_list( (2+2)*step, step, -step)])
    return ofst_rgs

def createOffsetsAndRanges_branch05(step):
    ofst_rgs = []
    ofst_rgs.append([ 700, +80+280, float_range( (2)*step,  (27+2)*step,  step)])
    ofst_rgs.append([ 700,    +280, float_range( 25*step,  0, -step)])
    ofst_rgs.append([ 700, -80+280, float_range( 0,  20*step, step)])
    return ofst_rgs

def createOffsetsAndRanges_branch09(step):
    ofst_rgs = []
    ofst_rgs.append([-700, -80-280, float_range_list( -(2)*step,  -(2+2+1)*step, -step)])
    ofst_rgs.append([-700, -80-280, float_range_list( -(3+3+1+2-1)*step, -(22+3+3+1+2-1)*step, -step)])

    ofst_rgs.append([-700,    -280, float_range_list(-(20+3+3)*step, -(3+3)*step,  step)])
    ofst_rgs.append([-700,    -280, float_range_list(-(3)*step,     0,  step)])

    ofst_rgs.append([-700, +80-280, float_range_list(0, -(3)*step, -step)])
    ofst_rgs.append([-700, +80-280, float_range_list(-(3+3)*step, -(15+3+3)*step, -step)])
    return ofst_rgs

def createOffsetsAndRanges_branch03(step):
    ofst_rgs = []
    ofst_rgs.append([-760, +80+280, float_range( (2)*step,  (25+2)*step,  step)])
    ofst_rgs.append([-700,    +280, float_range( (25+1+2)*step,  (2)*step, -step)])
    ofst_rgs.append([-640, -80+280, float_range( (3)*step,  (23+3)*step, step)])
    return ofst_rgs

def createOffsetsAndRanges_branch07(step):
    ofst_rgs = []
    ofst_rgs.append([ 760, -80-280, float_range(-(2)*step, -(25+2)*step, -step)])
    ofst_rgs.append([ 700,    -280, float_range(-(25+1+2)*step, -(2)*step,  step)])
    ofst_rgs.append([ 640, +80-280, float_range(-(3)*step, -(23+3)*step, -step)])
    return ofst_rgs

def createOffsetsAndRanges_branch04(step):
    ofst_rgs = []
    ofst_rgs.append([ 640, -80+280, float_range(-(23+3)*step, -(2)*step,  step)])
    ofst_rgs.append([ 700,    +280, float_range(-(3)*step, -(25+1+2)*step, -step)])
    ofst_rgs.append([ 760, +80+280, float_range(-(25+1)*step, -(1)*step,  step)])
    return ofst_rgs

def createOffsetsAndRanges_branch08(step):
    ofst_rgs = []
    ofst_rgs.append([-640, +80-280, float_range( (23+3)*step,  (2)*step, -step)])
    ofst_rgs.append([-700,    -280, float_range( (3)*step,  (25+1+2)*step,  step)])
    ofst_rgs.append([-760, -80-280, float_range( (25+1)*step,  (1)*step, -step)])
    return ofst_rgs

def createBranch(leds, slope,
                 pitch=1.65,
                 branch_01=False, branch_02=False,
                 branch_03=False, branch_04=False,
                 branch_05=False, branch_06=False,
                 branch_07=False, branch_08=False,
                 branch_09=False, branch_10=False,
                 branch_11=False, branch_12=False):
    angleRad = atan(slope)
    step     = pitch * cos(angleRad)

    if branch_01:
        offsets_ranges = createOffsetsAndRanges_branch01(step)
    elif branch_02:
        offsets_ranges = createOffsetsAndRanges_branch02(step)
    elif branch_03:
        offsets_ranges = createOffsetsAndRanges_branch03(step)
    elif branch_04:
        offsets_ranges = createOffsetsAndRanges_branch04(step)
    elif branch_05:
        offsets_ranges = createOffsetsAndRanges_branch05(step)
    elif branch_06:
        offsets_ranges = createOffsetsAndRanges_branch06(step)
    elif branch_07:
        offsets_ranges = createOffsetsAndRanges_branch07(step)
    elif branch_08:
        offsets_ranges = createOffsetsAndRanges_branch08(step)
    elif branch_09:
        offsets_ranges = createOffsetsAndRanges_branch09(step)
    elif branch_10:
        offsets_ranges = createOffsetsAndRanges_branch10(step)
    elif branch_11:
        offsets_ranges = createOffsetsAndRanges_branch11(step)
    elif branch_12:
        offsets_ranges = createOffsetsAndRanges_branch12(step)
    else:
        return

    for ofst_x, ofst_y, rg in offsets_ranges:
        for i in rg:
            leds.append(createLed(angleRad, 50*i, slopeFn(-50*i, slope, ofst_y),
                                  REF_X = CENTER_X + ofst_x, REF_Y = CENTER_Y))

### MAIN FN ###
def main(args=None) -> str:
    argc  = len(sys.argv)
    argc -= 1 # Remove executable path from counted args

    # Default values that can depend from args
    display_filename = DEFAULT_OUT_FILE

    if (argc < 0) or (argc > 4):
        print('usage: %s [-h] [display_filename] [w=<width>] [h=<height>]' % sys.argv[0])
        return

    for arg in sys.argv[1:]: # Start after executable path
        if arg == '-h':
            print('       display_filename: Suffix needs to be \".disp\".')
            print('                         The program will add if it\'s '
                  'not the case.')
            print('                         When not specified, the default '
                  'is \"%s\"' % DEFAULT_OUT_FILE)
            print('       h=<height>      : Height of a display (in pixels)')
            print('       w=<width>       : Width  of a display (in pixels)')
            return
        else: # It's display_filename
            display_filename = arg
            
    # Prepare slopes
    slope_01_11 = computeSlopeFromPoints(p1=(-132,+68), p2=(-33, 17))
    slope_06_10 = (-1) * slope_01_11
    slope_02_12 = computeSlopeFromPoints(p1=(-132,+68), p2=(-33,-17))
    slope_05_09 = (-1) * slope_02_12
    slope_03_07 = computeSlopeFromPoints(p1=(- 33,-17), p2=(-20,-72))
    slope_04_08 = (-1) * slope_03_07

    # Generate display
    leds = []
    createBranch(leds, slope_01_11, branch_01=True)
    createBranch(leds, slope_02_12, branch_02=True)
    createBranch(leds, slope_03_07, branch_03=True)
    createBranch(leds, slope_04_08, branch_04=True)
    createBranch(leds, slope_05_09, branch_05=True)
    createBranch(leds, slope_06_10, branch_06=True)
    createBranch(leds, slope_03_07, branch_07=True)
    createBranch(leds, slope_04_08, branch_08=True)
    createBranch(leds, slope_05_09, branch_09=True)
    createBranch(leds, slope_06_10, branch_10=True)
    createBranch(leds, slope_01_11, branch_11=True)
    createBranch(leds, slope_02_12, branch_12=True)

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

