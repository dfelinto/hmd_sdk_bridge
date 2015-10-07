import os
import sys
import ctypes

"""
lib_folder = os.path.dirname(os.path.abspath(__file__))

if lib_folder not in sys.path:
    sys.path.append(lib_folder)
"""

import bridge

def test_debug():
    import bridge_wrapper

    input = 3

    debug = bridge_wrapper.Debug_new(input)
    factor = bridge_wrapper.Debug_multiplicationFactor()
    print("Multiplication factor is {0}".format(factor))

    output = bridge_wrapper.Debug_multiplicationResult(debug)
    print("Return of {0} is {1}".format(input, output))

    mat = [i for i in range(4)]
    arr = (ctypes.c_float * len(mat))(*mat)

    bridge_wrapper.Debug_matrix(arr)

    mat = [i for i in arr]

    print("Matrix: {0}".format(mat))

    mat = [i for i in range(4)]
    arr = (ctypes.c_float * len(mat))(*mat)

    bridge_wrapper.Debug_matrixNonStatic(debug, arr)

    mat = [i for i in arr]

    print("Matrix: {0}".format(mat))
    bridge_wrapper.Debug_del(debug)

def test_oculus():
    from bridge.oculus import HMD
    import bridge_wrapper

    try:
        hmd = HMD()
    except Exception as E:
        print (E)
        return False

    # get FBO dimensions
    print("Dimensions: (l) {0} x {1} : (r) {2} x {3}".format(hmd.width_left, hmd.height_left, hmd.width_right, hmd.height_right))

    mat = [i for i in range(16)]
    arr = (ctypes.c_float * len(mat))(*mat)

    bridge_wrapper.Oculus_projectionMatrixLeft(hmd._device, 1, ctypes.c_float(157.9), arr)
    mat = [i for i in arr]

    print("Projection Matrix Left: {0}".format(mat))
    print("Projection Matrix Left: {0}".format(hmd.getProjectionMatrixLeft(0.1, 157.0)))

test_debug()

test_oculus()
