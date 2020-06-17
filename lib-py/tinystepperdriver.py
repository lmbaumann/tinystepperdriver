from ctypes import cdll, c_int, c_void_p


class Tinystepperdriver:

    def __init__(self, pin_step, pin_dir):
        self.lib = cdll.LoadLibrary('./libtinystepperdriver.so')
        # Answer from Gabriel Devillers
        # https://stackoverflow.com/questions/1615813/how-to-use-c-classes-with-ctypes
        constructor = self.lib.tinystepperdriver_new
        constructor.restype = c_void_p
        self.obj = c_void_p(constructor(c_int(pin_step), c_int(pin_dir)))

    def move(self, steps, direction, duration):
        return self.lib.tinystepperdriver_move(self.obj, c_int(steps), c_int(direction), c_int(duration))

    def iterate(self):
        return self.lib.tinystepperdriver_iterate(self.obj)

    def cancel(self):
        return self.lib.tinystepperdriver_cancel(self.obj)

    def test(self):
        self.lib.tinystepperdriver_test(self.obj)
