#include <Wire.h>
#include <math.h>

const int MPU_addr = 0x68; // Адрес MPU-6050

int16_t accelerometerX, accelerometerY, accelerometerZ; // Переменные для хранения значений ускорения

float sumacc;

void setup() {
  Wire.begin(); // Инициализация шины I2C
  Serial.begin(9600); // Инициализация монитора серийного порта

  // Установка режима активации акселерометра
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  delay(100); // Задержка для стабилизации
}

void loop() {
  // Чтение значений ускорения по осям X, Y и Z
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // Адрес регистра начала чтения данных акселерометра
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);

  accelerometerX = Wire.read() << 8 | Wire.read();
  accelerometerY = Wire.read() << 8 | Wire.read();
  accelerometerZ = Wire.read() << 8 | Wire.read();

  // Преобразование значений в g
  float accelerationX = accelerometerX;
  float accelerationY = accelerometerY;
  float accelerationZ = accelerometerZ;

  sumacc = sqrt(pow(accelerationX,2)+pow(accelerationY,2)+pow(accelerationZ,2))/ 14600;

  // // Вывод значений ускорения
  // Serial.print("Ускорение X: ");
  // Serial.print(accelerationX);
  // Serial.print(" g ");
  // Serial.println(" ");

  // Serial.print("Ускорение Y: ");
  // Serial.print(accelerationY);
  // Serial.print(" g ");
  // Serial.print(" ");

  // Serial.print("Ускорение Z: ");
  // Serial.print(accelerationZ);
  // Serial.println(" g ");

  // Serial.print("Общее ускорение: ");
  Serial.println(sumacc);
  // Serial.println(" g ");





}
