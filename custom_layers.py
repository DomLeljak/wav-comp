import tensorflow as tf
from keras import backend as K
from keras.layers import Layer
import numpy as np
tf.debugging.enable_check_numerics()

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

K.set_floatx('float64')

def sine(x, A=1.0, omega=1.0, y=0., a1 = 1., b1 = 1.):
    result = y + A * (a1 * K.abs(x)**b1) * K.sin(omega * x)
    return result

class Sinusoidal(Layer):

    def __init__(self, A = 1.0, omega = 1.0, phi = 0.0, a1 = 1.0, b1 = 0.0, trainable=False, **kwargs):
        super(Sinusoidal, self).__init__(**kwargs)
        self.supports_masking = True
        self.A = A
        self.omega = omega
        self.phi = phi
        self.a1 = a1
        self.b1 = b1
        self.trainable = trainable

    def build(self, input_shape):
        self.amplitude  = K.variable(self.A,     dtype=K.floatx(), 
                                                 name='amplitude')
        self.frequency  = K.variable(self.omega, dtype=K.floatx(),
                                                 name='frequency'),
        self.phase      = K.variable(self.phi,     dtype=K.floatx(),
                                                 name='phase')
        self.slope      = K.variable(self.a1,    dtype=K.floatx(),
                                                 name='slope')
        self.power      = K.variable(self.b1,    dtype=K.floatx(),
                                                 name='power')

        if self.trainable:
            self._trainable_weights.append(self.amplitude)
            self._trainable_weights.append(self.frequency)
            self._trainable_weights.append(self.phase)
            self._trainable_weights.append(self.slope)
            self._trainable_weights.append(self.power)

        super(Sinusoidal, self).build(input_shape)

    def call(self, inputs, mask=None):
        return sine(inputs, self.amplitude, self.frequency, self.phase, self.slope, self.power)

    def get_config(self):
        config = {
                'amplitude': self.get_weights()[0] if self.trainable else self.A,
                'frequency': self.get_weights()[1] if self.trainable else self.omega,
                'phase':     self.get_weights()[2] if self.trainable else self.phi,
                'slope':     self.get_weights()[3] if self.trainable else self.a1,
                'power':     self.get_weights()[4] if self.trainable else self.b1,
                'trainable': self.trainable
                }
        base_config = super(Sinusoidal, self).get_config()
        return dict(list(base_config.items()) + list(config.items()))

    def compute_output_shape(self, input_shape):
        return input_shape
