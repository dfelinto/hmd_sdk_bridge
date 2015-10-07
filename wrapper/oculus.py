TODO = True

from ctypes import (
        c_float,
        )

from .hmd import HMD as baseHMD
import bridge_wrapper as bridge

class HMD(baseHMD):
    def __init__(self):
        super(HMD, self).__init__()
        self._device = bridge.Oculus_new()

    def __del__(self):
        bridge.Oculus_del(self._device)

    @property
    def width_left(self):
        return bridge.Oculus_widthLeft(self._device)

    @property
    def width_right(self):
        return bridge.Oculus_widthRight(self._device)

    @property
    def height_left(self):
        return bridge.Oculus_heightLeft(self._device)

    @property
    def height_right(self):
        return bridge.Oculus_heightRight(self._device)

    def _getProjectionMatrix(self, near, far, bridge_func):
        mat = [i for i in range(16)]
        arr = (c_float * len(mat))(*mat)

        bridge_func(self._device, c_float(near), c_float(far), arr)
        return [i for i in arr]

    def _updateProjectionMatrix(self, near, far):
        self.projection_matrix_left = self._getProjectionMatrix(
                near, far, bridge.Oculus_projectionMatrixLeft)

        self.projection_matrix_right = self._getProjectionMatrix(
                near, far, bridge.Oculus_projectionMatrixRight)

    def setup(self, framebuffer_left, framebuffer_right):
        """
        Initialize device

        :param framebuffer_object_left: framebuffer object created externally
        :type framebuffer_object_left: GLuint
        :param framebuffer_object_right: framebuffer object created externally
        :type framebuffer_object_right: GLuint
        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return bridge.Oculus_setup(self._device, framebuffer_left, framebuffer_right)

    def update(self):
        """
        Get fresh tracking data
        """
        TODO
        """
        Oculus SDK bridge

        return:head position, head orientation
        """
        return [[j for j in range(4)] for i in range(4)], [i for i in range(3)], [i for i in range(3)]

    def frameReady(self):
        """
        The frame is ready to be send to the device

        :return: return True if success
        :rtype: bool
        """
        return bridge.Oculus_frameReady(self._device)

    def reCenter(self):
        """
        Re-center the HMD device

        :return: return True if success
        :rtype: bool
        """
        return bridge.Oculus_reCenter(self._device)
