# Door Control
Door-Control is a garage-style sliding door system for automated vertical operation, with the ability to auto-close after the car enters the garage and to detect if the car is under the door.
## 🛠️ Components Required  
- An ESP8266EX nodemcu microcontroller  
- An Ultrasonic sensor (HC SR04)
- A DC motor (I used a 6V DC motor)  
- A Motor driver module (L298N Dual H-Bridge is the one I used)  
- A power source to power the motor/motor driver (4 1.5v AA batteries in parallel will do the job)
- a thin rope or  
## ⚙️ How It Works  
1. You issue an open command through a firebase webapp to open the door  
2. The microcontroller receives the signal and activates the motor to open the door.  
3. The door waits for the car to enter then closes the door (Optional: can be disabled through firebase)  
4. The door’s status is sent to the firebase app for remote monitoring and control.
## 🪛 Circuit setup
1. Wire HC SR04 Trigger to D2 and Echo to D1, power to 3v and ground to GND
2. Connect the 4 AA batteries holder to the motor driver
3. Wire the DC motor to OUT1, OUT2 pins of the motordriver
4. Wire IN1 to D7, IN2 to D6 (IN1, IN2 are the input pins on L298N)
## 💻 Code setup
1. Install [vscode](https://code.visualstudio.com/), [C/C++ extension from Microsoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
2. Add your wifi ssid, password to include/credentials.hpp
4. Create a firebase project then add your firebase database api_key, db_url, email, db_password to include/credentials.hpp
5. Open firebase realtime database and import door-control.json
6. Adjust the door height in src/main.cpp to your own door height (Mine measured 13cm). This step is required for the door to operate correctly
7. Use platformIO to flash the code to the microcontroller
## ⚙️ Operation
- Once everything is up and running, operation commands can be issued from firebase realtime DB by editing **order** to 1 (OPEN), 2 (CLOSE).  
- Auto close can be toggled through **auto** key.  
- Although it's not included in this repository, it'd be ideal to create a web interface that issues Firebase commands.  