/**
 * @file measureDistance.ino
 * @brief This example demonstrated the basic distance measuring function of LIDAR07, the range is 0.2m-12m (Operating voltage: 5 V)
 * @n Connection rules: PIN1-PIN8 are in the front of the sensor from right to left. 
 * @n          PIN1----------------------SCL--------------------Maincontroller SCL（IIC mode）
 * @n          PIN2----------------------SDA--------------------Maincontroller SDA（IIC mode）
 * @n          PIN3----------------------Light source power supply ground--------------Maincontroller GND
 * @n          PIN4----------------------Light source power supply(5V)--------Maincontroller VCC
 * @n          PIN5----------------------TX---------------------Maincontroller RX pin, which is set to be used for serial communication with the sensor (UART mode)
 * @n          PIN6----------------------RX---------------------Maincontroller TX pin, which is set to be used for serial communication with the sensor (UART mode)
 * @n          PIN7----------------------Module main power supply ground------------Maincontroller GND
 * @n          PIN8----------------------Module main power supply(5V)------Maincontroller VCC
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version  V1.0
 * @date  2022-06-20
 * @url https://github.com/DFRobot/DFRobot_LIDAR07
 */
 
#include <dfrobot_crc.h>
#include <DFRobot_LIDAR07.h>

DFRobot_LIDAR07_UART  LIDAR07;

//Serial prints to Serial monitor
//Serial1 reads sensor output

void setup() {
  // put your setup code here, to run once:
    uint32_t version;
   Serial.begin(115200);
  Serial1.begin(115200);
  while(!LIDAR07.begin(Serial1)){
    Serial1.println("The sensor returned data validation error");
    delay(1000);
  }
  version = LIDAR07.getVersion();
  Serial1.print("VERSION: ");
  Serial1.print((version>>24)&0xFF,HEX);
  Serial1.print(".");Serial1.print((version>>16)&0xFF,HEX);
  Serial1.print(".");Serial1.print((version>>8)&0xFF,HEX);
  Serial1.print(".");Serial1.println((version)&0xFF,HEX);
  LIDAR07.startFilter();

  while(!LIDAR07.setMeasureMode(LIDAR07.eLidar07Single)){
      Serial1.println("set measure mode err");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  LIDAR07.startMeasure();

  //Get the collected data
  if(LIDAR07.getValue()){
    Serial.print("Distance:");Serial.print(LIDAR07.getDistanceMM());Serial.println(" mm");
//    Serial.print("Amplitude:");Serial1.println(LIDAR07.getSignalAmplitude());
  }
  delay(1000);
  Serial.println("nueva lectura");
  Serial.println("-");
  Serial.println("-");
  Serial.println("-");
}
