
//Calibrate the line sensors
void calibrateLineSensorsAuto(){
  display.clear();
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  { 
    display.print("Auto");
    display.gotoXY(0, 1);
    display.print("Cali");
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

//Makes the turn until the 2 og 4 line sensors hit the line
void lineCal(char linePosition){
  if (linePosition == 'r'){
    while(true){
      motors.setSpeeds(200,-200);
      lineSensors.readLine(line.values);
      if (line.values[1] < line.white){
        motors.setSpeeds(0, 0);
        break;
      }
    } 
  }   
  else if (linePosition == 'l'){
    while(true){
      motors.setSpeeds(-200,200);
      lineSensors.readLine(line.values);
      if (line.values[3] < line.white){
        motors.setSpeeds(0, 0);
        break;
      }  
    }
  }  
}

// Drives forward until the zumo hit the line
void detectLine(){
  while(endLine() == false){
    motors.setSpeeds(200,200);     
  }
  motors.setSpeeds(0,0);
}

//Follow the line and use PID regulation 
void followLine(){
  uint16_t position = lineSensors.readLine(line.values);

  if (position < line.center){
    float speed_l = (((2000-((float)position))/500)*3)+200;
    motors.setSpeeds(speed_l, 100);

  }
  else if (position > line.center){
    float speed_r = (((((float)position)-2000)/500)*3)+200;
    motors.setSpeeds(100, speed_r);
  }
  else
    motors.setSpeeds(100, 100);

}

//Centralize the zumo after the zumo has found the line
bool endLine(){
  lineSensors.readLine(line.values);
  if (line.values[0] < line.white){
    motors.setSpeeds(0,0);
    while(true){
      lineSensors.readLine(line.values);
      motors.setSpeeds(-200,200);
      if (line.values[4] < line.white){
        motors.setSpeeds(0,0);
        return(true);
      }
    } 
  }  
  else if (line.values[4] < line.white){
    motors.setSpeeds(0,0);
    while(true){
      lineSensors.readLine(line.values);
      motors.setSpeeds(200,-200);
      if (line.values[0] < line.white){
        motors.setSpeeds(0,0);
        return(true);
      }
    }
  }
  return(false);    
}


//Checks for a line
bool checkLineSensors(){
  lineSensors.readLine(line.values);
  if (line.values[0] < line.white || line.values[1] < line.white || line.values[2] < line.white || line.values[3] < line.white || line.values[4] < line.white){
    return(true);
  }
  else 
    return(false);
}

