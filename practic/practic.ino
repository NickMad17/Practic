#include <I2Cdev.h>
#include <MPU6050.h>
#define _LCD_TYPE 1
#include <LiquidCrystal_I2C.h>
//#include <LCD_1602_RUS_ALL.h>
//LCD_1602_RUS lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define T_OUT 20

MPU6050 accel;

unsigned long int t_next;
double x;
void setup() {
Serial.begin(9600);
accel.initialize();
accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
Serial.println(accel.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
lcd.init();
lcd.backlight();

}

void loop() {
long int t = millis();

if( t_next < t ){
int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;

t_next = t + T_OUT;
accel.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
lcd.setCursor(0, 0);
//string x = ax_raw / 2048.0;
//lcd.print(x);

x = ax_raw / 2048.;

if (x > -0.15){
  x = 0;
}

lcd.setCursor(0, 0);
lcd.print(x);
Serial.println(-x); // вывод в порт проекции ускорения на ось Y
}
delay(20);
}

