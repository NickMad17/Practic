# Arduino accelerometer
### How to start

Detailed instructions for connection:

1) Get the Arduino Nano and the necessary components: You will need an Arduino Nano, a USB cable to connect to your computer, and wires to connect the accelerometer MPU6050.

2) Connect the USB cable: Connect one end of the USB cable to the USB connector on the Arduino Nano, and the other end to an available USB port on your computer. This will power the microcontroller and allow communication with the Arduino IDE.


3) Prepare the accelerometer MPU6050: You must have an accelerometer module MPU6050. Make sure that it has connectors VCC, GND, SDA and SCL, which you can connect with wires.

4) Connect the accelerometer MPU6050 to the Arduino Nano: Connect the VCC pin of the accelerometer to the 5V pin of the Arduino Nano, the GND pin to the GND pin, the SDA pin to pin A4 (SDA) and the SCL pin to pin A5 (SCL) on the Arduino Nano. Make sure that the connection is correct and secure.


5) Connect the Arduino Nano to the Arduino IDE: Start the Arduino IDE on your computer. In the "Tools" menu, select the correct board (Arduino Nano) and the port that Arduino Nano is connected to. This will allow communication between the computer and the microcontroller.

## Code Description
Before starting to write the code, I made sure that the MPU6050 accelerometer is properly connected to the Arduino Nano. I connected the VCC and GND pins of the accelerometer to the corresponding pins of the Arduino Nano for power, and I connected the SDA and SCL pins of the accelerometer to the SDA and SCL pins of the Arduino Nano for I2C communication.

To work with the MPU6050 accelerometer and read the acceleration data, I used the following libraries:

1) MPU6050, which provides a convenient interface for interacting with the module. This library makes it easy to get acceleration data for the X, Y and Z axes.

2) I2Cdev, which provides methods that make it easier to interact with devices connected to the I2C bus.


3) LiquidCrystal_I2C - a library for working with an LCD display using the I2C protocol.

4) Math - a standard library for performing mathematical operations
Now let's move on to describe the optimal code for reading acceleration from the MPU6050 accelerometer using the Arduino IDE and Arduino Nano.

```cpp
#include <I2Cdev.h>
#include <MPU6050.h>
#define _LCD_TYPE 1
#include <LiquidCrystal_I2C.h>
#include <math.h>
```

These lines represent the connection of the necessary libraries for working with the MPU6050 sensor and the LCD display. Libraries have been described previously

```cpp
  LiquidCrystal_I2C lcd(0x27, 16, 2);
```

This line of code initializes the lcd object to work with the LCD display. The LiquidCrystal_I2C parameters specify the display address (0x27 in this case), the number of characters per line (16), and the number of lines (2).

  ```cpp
  MPU6050accel;
```

This line of code creates an accel object to work with the MPU6050 sensor.



```cpp
unsigned long int t_next;
double x;
```

 

The variables t_next and x are declared here. t_next is used to keep track of the time of the next measurement, and x will contain the acceleration value.

```cpp
void setup() {
   Serial.begin(9600);
   accel.initialize();
   accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
   Serial.println(accel.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
   lcd.init();
   lcd.backlight();
}

```

 
This setup() function is called once when the program starts. It initializes the serial port to output debug information at 9600 bps (Serial.begin(9600)). Then the MPU6050 sensor is initialized (accel.initialize()) and the full acceleration measurement range is set to ±16g (accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_16)). Then the connection with the sensor is checked and the corresponding message is output to the serial port. Next, the LCD is initialized (lcd.init()) and the backlight is turned on (lcd.backlight()).

  ```cpp
  void loop() {
   long int t = millis();

   if (t_next < t) {
     // ...
   }

   // ...
}

  ```

In the loop() function, the variable t is first defined and given the current time in milliseconds (millis()).

Then the if (t_next < t) condition is checked. If the current time t exceeds the value of the t_next variable, then the block of code inside the condition is executed (block inside). This allows you to control how often acceleration measurements are taken.

  ```cpp
      int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;

     t_next = t + T_OUT;
     accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
     lcd.setCursor(0, 0);

  ```

Inside the condition, the variables ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw are declared, which will be used to store the raw acceleration and gyroscope values read from the MPU6050 sensor. The variable t_next is then set to a new value equal to the current time t plus the delay T_OUT. This ensures that the next measurement will occur after a certain time interval.

  ```cpp
x = ax_raw / 2048.;
  ```

Next, the x-axis acceleration value is processed. The raw acceleration value ax_raw is divided by 2048 to get the acceleration value in g (gravity units)

(block inside)
```cpp
     if (x < 0.2 && x > -0.2) {
       x = 0;
     };
```
 

This block of code is responsible for eliminating the minor error in the x-axis acceleration value. This is where the check happens: if the x value is in the range from -0.2 to 0.2, then it is considered insignificant and is set to zero. This allows you to get rid of small errors and noise in the measurements that may occur on the sensor.

```cpp
     lcd.setCursor(0, 0);
     lcd print(x);
     Serial.println("$");
     Serial.println((x * 100), 0); // output to the port of the acceleration projection on the Y axis
     Serial.println(";");
```

After processing the acceleration value x, it is output to the LCD display and to the serial port.

1. 'lcd.setCursor(0, 0)' - sets the cursor position on the LCD display to the beginning of the first line.

2. 'lcd.print(x)' - prints the acceleration value x to the LCD.

3. Serial.println("$") - prints the $ character to the serial port to indicate the start of a string. Later in the section about the graphical interface I will tell you why this is needed.

4. ‘Serial.println((x * 100), 0)’ - prints the acceleration value of ‘x’ multiplied by 100 to the serial port. '0' sec

5. ‘Serial.println(";")’ - prints the character “ ; ” to the serial port to indicate the end of the line. More on this in the graphical interface section.

These operations allow you to display the acceleration value on the LCD and simultaneously send it to the serial port for further analysis or processing by an external device.
