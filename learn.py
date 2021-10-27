import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

import custom_layers as clay

tf.keras.utils.get_custom_objects().update({'sine': tf.keras.layers.Activation(clay.sine)})

data = np.loadtxt('data/data.csv', unpack=True)

x_train = np.array([data[0][:int(len(data[0])/2)] for i in range(len(data) - 1)]).T
y_train = np.array([data[i][:int(len(data[i])/2)] for i in range(1, len(data))]).T

x_test = np.array([data[0][int(len(data[0])/2):] for i in range(len(data) - 1)]).T
y_test = np.array([data[i][int(len(data[i])/2):] for i in range(1, len(data))]).T

model = tf.keras.models.Sequential([
  tf.keras.layers.Flatten(input_shape=(len(x_train.T),)),
  clay.Sinusoidal(A=1.0, omega=1.0, phi=0.0, a1 = 1.0, b1 = 1.0, trainable=True),
  tf.keras.layers.Dense(len(x_train.T), activation='linear'),
  clay.Sinusoidal(A=1.0, omega=1.0, phi=0.0, a1 = 1.0, b1 = 1.0, trainable=True),
  tf.keras.layers.Dense(len(x_train.T), activation='linear'),
])

model.compile(
                optimizer='adam',
                loss='mse',
                metrics=['accuracy']
              )

ep = int(input("Number of epochs: "))

model.fit(x_train, y_train, epochs=ep)
model.evaluate(x_test, y_test)

plt.plot(x_train.T[0].T, y_train.T[0].T)
plt.plot(x_test.T[0].T, y_test.T[0].T)
plt.plot(x_test, model.predict(x_test))
plt.plot(x_train, model.predict(x_train))

plt.savefig("plots/learn" + str(ep) + ".pdf")
plt.show()
