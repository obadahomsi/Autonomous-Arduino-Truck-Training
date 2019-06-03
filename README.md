# Autonomous-Arduino-Truck-Training

Summary:

An evolutionary algorithim was used to teach an Arduino vehicle obstacle detection. The evolutionary algorithim was constructed using numpy only inorder to enhance this learning experience. Serial was used to communicate between python and the vehicle. The vehicle supplied the input data in terms of 17 ultrasonic tests covering 180 degrees of the vehicles front view. The neural network then relayed what movement should the vehicles commense. 

The training proccess is slow due to the training taking place outside a simulation. Failure of the truck during a training session was relayed through a infrared remote. The same remote could be used to create an easier/faster method of learning; imitation learning. This would require changing the evolutionary algorithim and replacing it with gradient descent. 

Python3 dependencies:

- numpy 
- time 
- serial 
- re
- random

C++ depencies: 

- servo.h
- IRremote.h
