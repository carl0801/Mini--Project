
char garbage(){
  //Use the linesensors to make the zumo turn the right way
  while(true){
    lineSensors.readLine(line.values);
    motors.setSpeeds(-100,0);
    if (line.values[0] > line.white){
      motors.setSpeeds(0,0);
      delay(100);
      break;
    }
  }  
  while(true){
    lineSensors.readLine(line.values);
    motors.setSpeeds(0,-100);
    if (line.values[4] > line.white){
      motors.setSpeeds(0,0);
      delay(100);
      break;
    }
  } 

  while(true){
    lineSensors.readLine(line.values);
    motors.setSpeeds(-100,-100);
    if (line.values[0] > 200 && line.values[4] > 200){
      motors.setSpeeds(0,0);
      delay(100);
      break;
    }
  }  
  while(true){
    lineSensors.readLine(line.values);
    motors.setSpeeds(100,100);
    if (line.values[0] < 200 && line.values[4] < 200){
      motors.setSpeeds(0,0);
      delay(100);
      break;
    }
  }   
  //Check witch can that comes (if it is close or far)
  while(true){
    display.clear();
    lineSensors.emittersOn();
    proxSensors.read();

    prox.left = proxSensors.countsFrontWithLeftLeds();
    prox.right = proxSensors.countsFrontWithRightLeds();
    display.print(prox.left);
    display.gotoXY(3, 0);
    display.print(prox.right);
    delay(100);

    if (0 < prox.left && prox.left <= prox.g_f && 0 < prox.right && prox.right <= prox.g_f){
      delay(100);
      lineSensors.emittersOff();
      delay(100);
      display.clear();
      display.print("Object_c");
      delay(100);
      return('f');
      } 

    else if (prox.left >= prox.g_c && prox.right >= prox.g_c){
      delay(800);
      lineSensors.emittersOff();
      display.clear();
      display.print("Object_f");
      delay(100);
      return('c');      
    }
  }
}


//Pogram if the can is far
char canFar(){
  motors.setSpeeds(200,200);
  delay(300);
  while(checkLineSensors() != true){
    motors.setSpeeds(200,200);
  }
  motors.setSpeeds(0,0);
  delay(1000);
  display.clear();
  display.print("sejt");
  motors.setSpeeds(-200,-200);
  delay(300);
   
  line.linePosition = resetLine(250,90,400);
} 

//Return to start point
char resetLine(int i, int t, int v){ 
  while(checkLineSensors() != true){
    motors.setSpeeds(-200,-200);
  }
  motors.setSpeeds(0,0);
  display.clear();
  lineSensors.readLine(line.values);
  delay(100);
  motors.setSpeeds(-200,-200);
  delay(i);
  motors.setSpeeds(0,0);
  while(true){
    if (line.values[0] < line.white){
      int position = lineSensors.readLine(line.values);
      if (1700 < position && 2300 > position && line.values[2] < line.white){
        motors.setSpeeds(-200,-200);
        delay(100);
        motors.setSpeeds(0,0);
        return('s');
      }
      else
        turnLeft(t);
        motors.setSpeeds(-200,-200);
        delay(v);
        motors.setSpeeds(0,0);
        return('r');
    }
    else if (line.values[4] < line.white){
      int position = lineSensors.readLine(line.values);
      if (1700 < position && 2300 > position && line.values[2] < line.white){
        motors.setSpeeds(-200,-200);
        delay(100);
        motors.setSpeeds(0,0);
        return('s');
      }
      else
        turnRight(t);
        motors.setSpeeds(-200,-200);
        delay(v);
        motors.setSpeeds(0,0);
        return('l'); 
    }
  }     
}




