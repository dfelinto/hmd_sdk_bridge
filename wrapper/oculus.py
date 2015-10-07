TODO = True

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

    def getProjectionMatrixLeft(self, near, far):
        if self._cameraClippingChanged(near, far):
            mat = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]

            bridge.Oculus_projectionMatrixLeft(self._device, near, far, mat)
            self.projection_matrix_left = mat

        return super(HMD, self).projection_matrix_left

    def getProjectionMatrixRight(self, near, far):
        if self._cameraClippingChanged(near, far):
            self.projection_matrix_right = \
                    bridge.Oculus_projectionMatrixRight(
                            self._device, near, far)

        return self.projection_matrix_right

    def init(self, framebuffer_left, framebuffer_right):
        """
        Initialize device

        :param framebuffer_object_left: framebuffer object created externally
        :type framebuffer_object_left: GLuint
        :param framebuffer_object_right: framebuffer object created externally
        :type framebuffer_object_right: GLuint
        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return bridge.Oculus_setup(framebuffer_left, framebuffer_right)

    def update(self):
        """
        Get fresh tracking data
        """
        TODO
        """
        Oculus SDK bridge

        return:head position, head orientation
        """

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
