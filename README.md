# Final-Project
We use the model from here: https://github.com/peikexin9/deepxplore/tree/master/Driving

The files we did not revise: driving_models.py, data_utils.py, configs.py

The part we revised:

In gen_diff.py:

Line 22: We add four more choices of realistic transformation type: 'circle', 'color', 'Blur', 'Fisheye'

Line 56: We create a txt file to record the neuron coverage in each loop

Line from 58 ~ 63: Randomly choose an input from the center file and copy this image to do the further transformation.

Line from 64 ~ 76: Compute the shape of the original input and randomly generate the position of the circle(the constraint_circle() function)

Line 143 ~ 147: Record the neuron coverage of the original preprocessed input in the txt file

Line 167 ~ 211: Add four transformation operations when we use these four choices: 'circle', 'color', 'Blur', 'Fisheye'

Line 241: close the txt file

In utils.py:

Line 75 ~ 84: We add the constraint_colorChange() function

Line 87 ~ 109: We add the constraint_myFisheye() function

Line 113 ~ 117: We add the constraint_myBlur() function

Line 199 ~ 127: We add the constraint_circle() function

The files we write: color.cpp, blur.cpp, fish_eye.cpp, CMakeLists.txt
