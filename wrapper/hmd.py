TODO = True

class HMD:
    def __init__(self):
        self._device = None
        self._near = -1
        self._far = -1
        self._projection_matrix = [None, None]

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

    def init(self):
        """
        Initialize device

        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return TODO

    def update(self):
        """
        Get fresh tracking data
        """
        return TODO

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
