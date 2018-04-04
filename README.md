# App-controlled-car

The principle behind the robot car is simple enough, the car is controlled through an app and the commands are transmitted to the car via Bluetooth. This technique for controlling the car was built upon on a previous project that controlled the car using an accelerometer and sending the information using RF transmissions. By using an app, it allows more freedom and accessibility for the user when controlling the car. The user will have two options for the UI (User Interface) of the car, either using the accelerometer method or a simple button control panel. The car will operate on the following processes:

1.	A command is sent to the car to check if the Bluetooth connection is stable.
2.	A response will be sent from the target car to the app, indicating it is ready.
3.	The user will then select which type of UI to use.
4.	Depending on the interface the car can be controlled differently.
5.	The accelerometer uses pitch and tilt of the phone to indicate the desired vector of the car and then send it over Bluetooth.
6.	The button control panel is simple, each corresponding button sends a certain vector command to the car.
7.	A stop button will be shown on the UI to stop the car at any given moment.
