import os
import sys

"""
lib_folder = os.path.dirname(os.path.abspath(__file__))

if lib_folder not in sys.path:
    sys.path.append(lib_folder)
"""

import bridge
import bridge_wrapper

def main():
    input = 4
    output = bridge_wrapper.functionTest(input)
    print("Return of {0} is {1}".format(input, output))

main()
