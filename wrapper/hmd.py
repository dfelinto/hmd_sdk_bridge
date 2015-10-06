TODO = True

class HMD:
    def __init__(self):
        self._device = None

    @staticmethod
    def isConnected():
        """
        Check if device is connected

        :return: return True if the device is connected
        :rtype: bool
        """
        TODO

    def init(self):
        """
        Initialize device

        :return: return True if the device was properly initialized
        :rtype: bool
        """
        return TODO

    def loop(self):
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

