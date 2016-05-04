"""
Head Mounted Display
====================

Base class to be inherited by all HMDs
"""

TODO = True

class HMD:
    def __init__(self):
        self._device = None
        self._near = -1
        self._far = -1
        self._projection_matrix = [[i for i in range(16)], [i for i in range(16)]]
        self._orientation = [[i for i in range(4)] for i in range(2)]
        self._position = [[i for i in range(3)] for i in range(2)]
        self._width = [0, 0]
        self._height = [0, 0]
        self._status = ""
        self._state_bool = False


    @property
    def projection_matrix_left(self):
        return self._projection_matrix[0]

    @projection_matrix_left.setter
    def projection_matrix_left(self, value):
        self._projection_matrix[0] = value

    @property
    def projection_matrix_right(self):
        return self._projection_matrix[1]

    @projection_matrix_right.setter
    def projection_matrix_right(self, value):
        self._projection_matrix[1] = value

    @property
    def width_left(self):
        return self._width[0]

    @property
    def width_right(self):
        return self._width[1]

    @property
    def height_left(self):
        return self._height[0]

    @property
    def height_right(self):
        return self._height[1]

    def get_status(self):
        return self._status

    def get_state_bool(self):
        return self._state_bool


    def init(self):
        """
        Initialize device

        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return TODO

    def setup(self, color_texture_left, color_texture_right):
        """
        Initialize device

        :param color_texture_left: framebuffer object created externally
        :type color_texture_left: GLuint
        :param color_texture_right: framebuffer object created externally
        :type color_texture_right: GLuint
        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return TODO

    def update(self):
        """
        Get fresh tracking data

        :return: return left orientation, left_position, right_orientation, right_position
        :rtype: tuple(list(4), list(3), list(4), list(3))
        """
        return self._orientation[0], self._position[0], self._orientation[1], self._position[1]

    def frameReady(self):
        """
        The frame is ready to be send to the device
        """
        return TODO

    def quit(self):
        """
        Garbage collection
        """
        return TODO

    def _cameraClippingChanged(self, near, far):
        """
        check if near of far values changed
        """
        if near == self._near and far == self._far:
            return False

        self._near = near
        self._far = far

        return True

    def getProjectionMatrixLeft(self, near, far):
        if self._cameraClippingChanged(near, far):
            self._updateProjectionMatrix(near, far)
        return self.projection_matrix_left

    def getProjectionMatrixRight(self, near, far):
        if self._cameraClippingChanged(near, far):
            self._updateProjectionMatrix(near, far)
        return self.projection_matrix_right
