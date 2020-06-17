from ctypes import c_int, c_void_p, cdll


class Tinystepperdriver:
    """Wrapper for tinystepperdriver C++ library"""

    def __init__(self, pin_step, pin_dir):
        self.lib = cdll.LoadLibrary('./libtinystepperdriver.so')
        # Answer from Gabriel Devillers
        # https://stackoverflow.com/questions/1615813/how-to-use-c-classes-with-ctypes
        constructor = self.lib.tinystepperdriver_new
        constructor.restype = c_void_p
        self._obj = c_void_p(constructor(c_int(pin_step), c_int(pin_dir)))

    def move(self, steps, direction, duration):
        return bool(self.lib.tinystepperdriver_move(self._obj, c_int(steps), c_int(direction), c_int(duration)))

    def iterate(self):
        return bool(self.lib.tinystepperdriver_iterate(self._obj))

    def cancel(self):
        return bool(self.lib.tinystepperdriver_cancel(self._obj))
