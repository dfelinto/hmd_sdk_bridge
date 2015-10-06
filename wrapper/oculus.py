TODO = True

from .hmd import HMD as baseHMD
import bridge_wrapper as bridge

class HMD(baseHMD):
    def __init__(self):
        self._device = bridge.Oculus_new()
        self._near = -1
        self._far = -1

    @staticmethod
    def isConnected():
        """
        Check if device is connected

        :return: return True if the device is connected
        :rtype: bool
        """
        return bridge.Oculus_isConnected()

    def init(self):
        """
        Initialize device

        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return TODO
        """
        Oculus SDK bridge

        return: status, fbo, texture, projection matrix, eye separation, width, height
        """

    def loop(self):
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
        """
        TODO
        """
        Oculus SDK bridge
        """
        bridge.Oculus_frameReady()

    def reCenter(self):
        """
        Re-center the HMD device
        """
        bridge.Oculus_reCenter()

    def quit(self):
        """
        Garbage collection
        """
        TODO
        """
        Oculus SDK bridge

        delete fbo, rbo, tex_id
        """

