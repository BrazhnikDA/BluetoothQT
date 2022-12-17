#include "BluetoothSerial.h"
 
BluetoothSerial ESP_BT; // Объект для Bluetooth
 
void setup() {
  Serial.begin(9600); // Запускаем последовательный монитор со скоростью 9600
  Serial.print(9600);  
  ESP_BT.begin("ESP32_LED_Control"); // Задаем имя вашего устройства Bluetooth
  Serial.println("Bluetooth Device is Ready to Pair");  // По готовности сообщаем, что устройство готово к сопряжению
 
  pinMode (2, OUTPUT);// задаем контакт подключения светодиода как выходной
 
  digitalWrite(2, HIGH);
  ESP_BT.println("LED turned ON");
}
 
void loop() {
  int incoming;
  if (ESP_BT.available()) // Проверяем, не получили ли мы что-либо от Bluetooth модуля
  {
    Serial.println("somebody:");
    incoming = ESP_BT.read(); // Читаем, что получили
    Serial.print("Received:"); Serial.println(incoming);
 
    if (incoming == 49)  // Если значение равно единице, включаем светодиод
        {
        digitalWrite(2, HIGH);
        Serial.println("LED turned ON");
        }
 
    if (incoming == 48)  // Если значение равно нулю, выключаем светодиод
        {
        digitalWrite(2, LOW);
        Serial.println("LED turned OFF");
        }     
  }
  delay(20);
}