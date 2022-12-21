//Calibrate the gyro
void gyroCal(){
 Wire.begin();
 imu.init();
 imu.enableDefault();

  for (uint16_t i = 0; i < 1024; i++)
  {
  // Wait for new data to be available, then read it.
    while(!imu.gyroDataReady()) {}
    imu.readGyro();

    // Add the Y axis reading to the total.
    gyro.gyroOffsetZ += imu.g.z;
  }
  gyro.gyroOffsetZ /= 1024;

  // korigere for gryo shift
  for (int s = 0; s<9; s++){
    while(!imu.gyroDataReady()) {}
    imu.readGyro();

    gyro.gyroDriftZ += imu.g.z-gyro.gyroOffsetZ;
    delay(200);
  }
  gyro.gyroDriftZ /= 10;

}


//Find the angle of the gyro
void updateAngleGyro(){   // Taget fra https://github.com/pololu/zumo-32u4-arduino-library/blob/master/examples/Balancing/Balancing.ino#L186
    // Figure out how much time has passed since the last update.
    static uint16_t lastUpdate = 0;
    uint16_t m = micros();
    uint16_t dt = m - lastUpdate;
    lastUpdate = m;

    imu.readGyro();

    // Calculate how much the angle has changed, in degrees, and
    // add it to our estimation of the current angle.  The gyro's
    // sensitivity is 0.07 dps per digit
    gyro.angle += ((float)imu.g.z - gyro.gyroOffsetZ-gyro.gyroDriftZ)*dt*9/1000000000;
}


