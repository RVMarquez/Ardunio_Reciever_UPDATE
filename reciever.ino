const int pResistor = A0;      //Photoresistor is connected to Analog pin A1 (LED Light)
const float VOLTAGE = 0.0049;  //Value used to calculate lgith level (5V)
const float TOLER = 0.10;      //Allow for 10% tolerance

int unit = 250;      //Unit for a dot (0.25 sec)
                      //Dashes are 3 times that
                      //Spaces are 7 time that
                      //Pause * 2  = break between words

int LEDValue;         //Value from Photoresistor checking the LED
int ambientLight = 0; //Value of the Ambient Light of the Room
int threshold = 0;    //Tolerance used to activate timing of sensor

bool LEDstate = false; //set to true if light is on
bool prevState = false; //Light on - True | Light off - False

int onTiming = 0;
int offTiming = 0;
int timeIndex = 0;

int space = 1000; //Add space after 1000 ms


String code = "";
String dash = "-";
String dot = ".";

typedef struct{
  bool state; //State of Light
  int millisec; //Duration of light
}stateTiming;

stateTiming timingHis[15];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pResistor, INPUT);


  // FINDING AVERAGE AMBIENT LIGHT LEVEL //
  
  float ambLight = 0; //first inital reaxing of the ambient light

  for (int i = 0; i<10; i++){
    ambLight += analogRead(pResistor) * VOLTAGE; //Calculate Ambient Light Level
    delay(250);
  }

  ambientLight = ambLight / 10;
  threshold = ambLight * TOLER;

  Serial.print("Ambient Light Level: ");
  Serial.println(ambientLight);
  
  Serial.println("Recieving Transmission");
 
}

void loop() {
 
  LEDValue = analogRead(pResistor); //get the value of the resistor pointing towards the LED's
  delay(100);

  //Serial.print("LED-Light: ");
  //Serial.println(LEDValue);
  

  //Note: As light it sensed, value decreases
  

  if ( (LEDValue * VOLTAGE) > (ambientLight + threshold) ){
    LEDstate = true; //Light on
  }
  else{
    LEDstate = false; //Light Off
  }


  if (LEDstate == false && prevState == true){ //LEDs Turn Off
    onTiming = millis();
    timingHis[timeIndex].state = true;
    timingHis[timeIndex].millisec = onTiming - offTiming;
    timeIndex++;
  }
  else if (LEDstate == true && prevState == false){ //LED turns ON
    offTiming = millis();
    timingHis[timeIndex].state = false;
    timingHis[timeIndex].millisec = offTiming - onTiming;
    timeIndex++;
  }

  if (timeIndex == 7){
    decodeMess(timingHis);
    timeIndex++:
  }
  prevState = LEDstate; 
}

void decodeMess(stateTiming timeHis[]){
  //Message should be added to "code" string

  for (int i = 1; i < 8; i++){

    if(timeHis[i].state == true){ //Light was on
      if (timeHis[i].millisec < 1500) { //duration was less than 1500ms
        code += dot;
      }
      else{ //Was longer == Dash
        code += dash;
      }
    }
  }

  //Serial.println(code)
  Serial.println(convert(code);
  
}



void convert(String text){
  if (text == ".-"){
    Serial.print("A");
  }
  else if (text == "-..."){
    Serial.print("B");
  }
  else if (text == "-.-."){
    Serial.print("C");
  }
  else if (text == "-.."){
    Serial.print("D");
  }
  else if (text == "."){
    Serial.print("E");
  }
  else if (text == "..-."){
    Serial.print("F");
  }
  else if (text == "--."){
    Serial.print("G");
  }
  else if (text == "...."){
    Serial.print("H");
  }
  else if (text == ".."){
    Serial.print("I");
  }
  else if (text == ".---"){
    Serial.print("J");
  }
  else if (text == "-.-"){
    Serial.print("K");
  }
  else if (text == ".-.."){
    Serial.print("L");
  }
  else if (text == "--"){
    Serial.print("M");
  }
  else if (text == "-."){
    Serial.print("N");
  }
  else if (text == "---"){
    Serial.print("O");
  }
  else if (text == ".--."){
    Serial.print("P");
  }
  else if (text == "--.-"){
    Serial.print("Q");
  }
  else if (text == ".-."){
    Serial.print("R");
  }
  else if (text == "..."){
    Serial.print("S");
  }
  else if (text == "-"){
    Serial.print("T");
  }
  else if (text == "..-"){
    Serial.print("U");
  }
  else if (text == "...-"){
    Serial.print("V");
  }
  else if (text == ".--"){
    Serial.print("W");
  }
  else if (text == "-..-"){
    Serial.print("X");
  }
  else if (text == "-.--"){
    Serial.print("Y");
  }
  else if (text == "--.."){
    Serial.print("Z");
  }
  else {
    Serial.print("?"); //Unknown Character
  }

  Serial.print(" ");
  text = "";           // Reset
  
}
