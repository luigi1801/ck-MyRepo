#
# CK program template
#
# See CK LICENSE.txt for licensing details
# See CK COPYRIGHT.txt for copyright details
#
# Developer: Grigori Fursin, 2018, Grigori.Fursin@cTuning.org, http://fursin.net
#

import os
import tensorflow as tf
import numpy as np
from tensorflow import keras
from tensorflow import lite

def createModel():
	model = keras.Sequential([keras.layers.Dense(units=1, input_shape=[1])])
	model.compile(optimizer='sgd', loss='mean_squared_error')

	xs = np.array([ -1.0, 0.0, 1.0, 2.0, 3.0, 4.0], dtype=float)
	ys = np.array([ -3.0, -1.0, 1.0, 3.0, 5.0, 7.0], dtype=float)

	model.fit(xs, ys, epochs=1000)

	print(model.predict([10.0]))

	keras_file = 'linear.h5'
	keras.models.save_model(model, keras_file)

	converter = lite.TocoConverter.from_keras_model_file(keras_file)
	tflite_model = converter.convert()
	open('linear.tflite', 'wb').write(tflite_model) 
	return(0)

def run():

    print ("Hello world")

    print ("")
    print ("CK_VAR1: "+os.environ.get('CK_VAR1',''))
    print ("CK_VAR2: "+os.environ.get('CK_VAR2',''))

    return 0

if __name__ == '__main__':
  exit(createModel())
