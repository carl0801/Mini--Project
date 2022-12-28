
//Pogram if the can is close
void canClose(){
  turnRight(20);
  motors.setSpeeds(200,200);
  delay(320);
  turnLeft(110);
  while(checkLineSensors() != true){
    motors.setSpeeds(200,200);
  }

  motors.setSpeeds(-200,-200);
  delay(500);
  turnRight(45);
  line.linePosition = resetLine(400,45,0);

}

 
