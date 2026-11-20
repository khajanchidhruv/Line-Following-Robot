This is my first project as i am starting my journey in the exciting field of robotics. 

Objective: 
This line follower is supposed to follow this track of black line as you can see in    this video

Components Used:
1. 3D Printed Chassis
2. Yellow Geared DC Motors x 2
3. ESP-32 Development Board
4. L298N Motor Driver
5. IR Sensors (3 pin) x 3
6.  Wheels x 2
7. L18650 x 2 batteries (the blue one in video)
8. Battery holder
9. Mini Breadboard

I was pretty surprised seeing how long it took me to build a simpe line follower which was roughly 2 days. 

First i accidentally burned my motor driver because during connections my positive and negative terminal wires accidentally touched each other while being in L298N. 

Then after i replaced that and continued building for some reason, my robot wouldn't move it would just circle around. 
Then i realized my IR Sensors were touching the ground so maybe they didn't left any room for emission and transmission of light. So then i double taped it.

Use this code in building your own line follower just make sure to change the values accordingly.

https://github.com/user-attachments/assets/d048d946-7023-4b86-86bd-085b202931fc

