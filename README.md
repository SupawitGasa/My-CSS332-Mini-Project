# My-CSS332-Mini-Project
## This is the source code written in Arduino of my microcontroller project, which is a safe locker.
This is a mini project of the course named "Minicrocontrollers and Applications" (CSS332).
I decided to make a safe locker, which comprises an ultrasonic sensor, a servo motor, an active buzzer module, and a keypad(4x4).
Here are how it works:
1) First of all, The ultrasonic sensor keeps measuring the distance between the locker and a user, who is in front of it.
2) Once the distance becomes not exceeding 10 centimeters, there is a message shown on the Serial monitor to invite a user to enter the password.
3) If the password is correct, the servo motor rotate to 90 degrees, i.e., the door of the locker is open.
4) Moreover, the user can simply close the door by pressing a button on the keypad.
5) Otherwise, it counts the number of the wrong times that a user has given the incorrect password.
6) Whenever the number of times reaches 5, the active buzzer will be ringing for 5 times.
7) Lastly, everything returns back to the initial stage.
