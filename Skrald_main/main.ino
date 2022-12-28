#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors;
Zumo32U4IMU imu;
Zumo32U4ButtonA buttonA;
Zumo32U4OLED display;



//Plays the melodi
const char melody[] PROGMEM =
  "T127 L4 V15 O3 b-b-b-b-" 
  "b-8.b8.>e-8b-b-8r8 b-8.b8.>e-8b-b-8r8 b-8.b8.>e-8b-b-8r8 b-8.b8.>e-8b-b-8r8"
  "b-8.b8.>e-8>f>f8r8 >a-8.>g8.>f-8>e->e-8r8 >a-8.>g8.>f-8>e->e-8r8"
   "b-b-b-b-" 
  "b-8.b8.>e-8b-b-8r8 b-8.b8.>e-8b-b-8r8 b-8.b8.>e-8b-b-8r8 b-8.b8.>e-8b-b-8r8"
  "b-8.b8.>e-8>f>f8r8 >a-8.>g8.>f-8>e->e-8r8 >a-8.>g8.>f-8>e->e-8r8";

//variables in the code
struct gyro{
  float angle = 0;
  bool runner = true; 
  float gyroOffsetZ = 0;
  float gyroDriftZ =0;
};


struct line{
    uint8_t white = 100;
    uint16_t center = 2000;
    uint16_t values[5];
    char linePosition = 'r';
};


struct prox{
    int left = 0;
    int right = 0;
    int g_f = 2;
    int g_c = 4;
    uint16_t BrightnessLevel[4] = {0.5,0.8,7,8}; 
};

struct line line;
struct prox prox;
struct gyro gyro;



void setup() {
  //Use the 5 linesensors and the front proximity sensor
  lineSensors.initFiveSensors();
  proxSensors.initFrontSensor();

  //Set the brightnesslevels of the proximity sensors
  proxSensors.setBrightnessLevels(prox.BrightnessLevel, 4);

  // Play a little welcome song
  buzzer.play(">g32>>c32");

  // Wait for button A to be pressed and released.
  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to calib"));
  buttonA.waitForButton();
  display.clear();
  display.print(F("Calib"));
  buzzer.playFromProgramSpace(melody);

  //calibrate the sensors
  gyroCal();
  calibrateLineSensorsAuto();

  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to start"));
  buttonA.waitForButton();

}


//Make a right turn with the gyro
void turnRight(int t){
  gyro.angle = 0;
  while(gyro.angle > 0-t){
    display.clear();
    updateAngleGyro();
    display.print((String)gyro.angle);
    motors.setSpeeds(200, -200);
  }
  motors.setSpeeds(0, 0);
}

//Make a left turn with the gyro
void turnLeft(int s){
  gyro.angle = 0;
  display.print("LEFT");
  delay(300);
  while(gyro.angle < s){
    display.clear();
    updateAngleGyro();
    display.print((String)gyro.angle);
    motors.setSpeeds(-200, 200);
  }
  motors.setSpeeds(0, 0);
}

//main loop
void loop() {
  //buzzer.playFromProgramSpace(melody);
  if (line.linePosition != 's'){
    delay(600);
    detectLine();
    while(endLine() == false){
    }
    motors.setSpeeds(200,200);
    delay(150);
  } 
  motors.setSpeeds(0, 0);
  lineCal(line.linePosition);
  line.linePosition = 'r';

  while(endLine() == false){
    followLine();
  }

  switch (garbage()){
    case 'f': canFar(); break;
    case 'c': canClose(); break;
  }

}




