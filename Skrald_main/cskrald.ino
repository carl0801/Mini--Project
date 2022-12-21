
//Pogram if the can is close
char canClose(){
  turnRight(20);
  motors.setSpeeds(200,200);
  delay(320);
  turnLeft(110);
  while(checkLineSensors() != true){
    motors.setSpeeds(200,200);
  }

  /*while(true){
    proxSensors.read();
    prox.left = proxSensors.countsFrontWithLeftLeds();
    prox.right = proxSensors.countsFrontWithRightLeds();
    display.clear();
    display.print(prox.left);
    display.gotoXY(3, 0);
    display.print(prox.right);
    delay(100);

    if (prox.left > prox.right){
      //float speed_l = ((abs(diffProx)/10)*3)+2;
      //drive.setSpeed(speed_l, 1,0);
      motors.setSpeeds(-100,100);

    }
    else if (prox.left > prox.right){
      //float speed_r = ((abs(diffProx)/10)*3)+2;
      //drive.setSpeed(1, speed_r,0);
      motors.setSpeeds(100,-100);
    }
    else if (prox.left == prox.right && prox.left > 2 && prox.right > 2){
      motors.setSpeeds(200,200);
      delay(500);
      break;
    }
  }*/

  motors.setSpeeds(-200,-200);
  delay(500);
  turnRight(45);
  line.linePosition = resetLine(400,45,0);

}

 
