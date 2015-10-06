import os
import sys

"""
lib_folder = os.path.dirname(os.path.abspath(__file__))

if lib_folder not in sys.path:
    sys.path.append(lib_folder)
"""

import bridge

def test_simple():
    import bridge_wrapper

    input = 4
    output = bridge_wrapper.functionTest(input)

    print("Return of {0} is {1}".format(input, output))


def test_oculus():
    from bridge.oculus import HMD

    if HMD.isConnected():
        print("Oculus is connected")
    else:
        print("Oculus not connected")
        return

    hmd = HMD()

    # get FBO dimensions
    print("Dimensions: (l) {0} x {1} : (r) {2} {3}".format(hmd.width_left, hmd.height_left, hmd.width_right, hmd.height_right))

    # cleanup
    del hmd

test_simple()

test_oculus()
