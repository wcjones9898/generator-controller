String command;

// 0=on 1=off
int genStatus = 0;
// 0=on 1=off
int gridStatus = 0;

int genStartPin = 2;
int genStopPin = 3;
int genChokePin = 4;

void setup() {
    Serial.begin(9600); 
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(genStartPin, OUTPUT);
    digitalWrite(genStartPin, HIGH);
    pinMode(genStopPin, OUTPUT);
    digitalWrite(genStopPin, HIGH);
    pinMode(genChokePin, OUTPUT);
    digitalWrite(genChokePin, HIGH);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
}
 
void loop() {
    if(Serial.available()){
      command = Serial.readStringUntil('\n');
      commandHandler(command); 
    }
    genStatus = digitalRead(9);
    Serial.println(genStatus);
    gridStatus = digitalRead(10);
    Serial.println(gridStatus);
    delay(1000); //demonstrating that we won't miss a read because the data sits in the buffer until we read it
}

void commandHandler(String command){
  if(command.equals("on")){
      turnLedOn();
  }
  else if(command.equals("off")){
      turnLedOff();
  }
  else if(command.equals("1on")){
      digitalWrite(genStartPin, LOW);
  }
  else if(command.equals("1off")){
      digitalWrite(genStartPin, HIGH);
  }
  else if(command.equals("2on")){
      digitalWrite(genStopPin, LOW);
  }
  else if(command.equals("2off")){
      digitalWrite(genStopPin, HIGH);
  }
  else if(command.equals("3on")){
      digitalWrite(genChokePin, LOW);
  }
  else if(command.equals("3off")){
      digitalWrite(genChokePin, HIGH);
  }
  else if(command.equals("4on")){
      digitalWrite(5, LOW);
  }
  else if(command.equals("4off")){
      digitalWrite(5, HIGH);
  }
  else if(command.equals("alloff")){
      digitalWrite(genStartPin, HIGH);
      digitalWrite(genStopPin, HIGH);
      digitalWrite(genChokePin, HIGH);
      digitalWrite(5, HIGH);
  }
  else{
      Serial.println("Invalid command");
  }
}

void turnLedOn(){
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnLedOff(){
  digitalWrite(LED_BUILTIN, LOW);
}

//Do we need a command for this? Or should it just be something we periodically write as a serial message?
void checkStatus(){
  //return grid is up or down
  //maybe this just need to be a coded general status indicator i.e.
  //1 - grid is up, all is normal
  //2 - grid is out, generator not started yet
  //3 - grid is out, generator running
  //4 - grid is out, generator running and providing power
  //5 - grid is up, generator running and providing power
  //6 - grid is up, generator running
  //7 - grid is out, generator failed to start, probably need to write a serial message for errors and let raspberry pi send notification

}

//This function will run in the event of a power outage and can be used to start the generator from serial command
bool switchToGeneratorPower(){
  //1. startGenerator()
  //2. Wait 30 seconds, need to find a non-blocking way to do this
  //3. Send power to transfer switch
  //4. return true if generator started or false if it didn't
}

bool switchToGridPower(){

}

bool startGenerator(){
  //1. Apply choke
  //2. Send start signal for 2 seconds
  //3. Read generator power status checkPowerStatus("generator")
  //4. If no power re-try up to 3 times
  //5. turn choke off
}

bool stopGenerator(){
  //1. turn off transfer switch
  //2. wait 30 seconds
  //3. send stop command to generator
}

//create definitions for powerSource digitalRead pins
bool checkPowerStatus(int powerSource){
  //Read appropriate Optocoupler input
  //Return true for up, false for down
}