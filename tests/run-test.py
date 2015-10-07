import os
import sys

"""
lib_folder = os.path.dirname(os.path.abspath(__file__))

if lib_folder not in sys.path:
    sys.path.append(lib_folder)
"""

import bridge

def test_debug():
    import bridge_wrapper

    input = 3

    device = bridge_wrapper.Debug_new(input)
    factor = bridge_wrapper.Debug_multiplicationFactor()
    print("Multiplication factor is {0}".format(factor))

    output = bridge_wrapper.Debug_multiplicationResult(device)
    print("Return of {0} is {1}".format(input, output))

    bridge_wrapper.Debug_del(device)

def test_oculus():
    from bridge.oculus import HMD

    try:
        hmd = HMD()
    except Exception as E:
        print (E)
        return False

    # get FBO dimensions
    print("Dimensions: (l) {0} x {1} : (r) {2} x {3}".format(hmd.width_left, hmd.height_left, hmd.width_right, hmd.height_right))

test_debug()

test_oculus()
