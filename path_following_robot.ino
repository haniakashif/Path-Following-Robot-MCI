#include <Servo.h>

  Servo myservo1;
  Servo myservo2;

  int servo1_control_pin = 18;  
  int servo2_control_pin = 19;

  int servo1_pos = 0;
  int servo2_pos = 0;  
  // Motor A, TivaC and L298N connections
  int enA = 14;   //ENABLE pin (PD3) for Motor A to provide PWM 
  int enB = 15;
  int in1 = 6;   //IN1 pin (PA2) for Motor A for direction
  int in2 = 9;   //IN2 pin (PA3) for Motor A for direction
  int in3 = 10;
  int in4 = 11;

  int s1 = 2;
  int s2 = 3;

  int echo = 4;
  int  trig = 5;

  int r1;
  int r2;


  int r_m_s = 150;
  int l_m_s = 150;

  long distance, cm, duration;
  

  // const int SW2 = 17;   //Pin number for Switch SW2
  bool direction = true;  //Flag for clockwise or anti-clockwise direction
  char blueTooth;
  int state = 0;
  
  void setup() {

    myservo1.attach(servo1_control_pin);
    myservo2.attach(servo2_control_pin);
    //Serial initializing for Debugging
    //Specify pinModes for enA, in1 and in2 below
    Serial.begin(9600);
    pinMode(enA, OUTPUT); //Enable pin for Motor A
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT); //Direction pin 1 for Motor A
    pinMode(in2, OUTPUT); //Direction pin 2 for Motor A
    pinMode(in3, OUTPUT); //Direction pin 1 for Motor A
    pinMode(in4, OUTPUT); //Direction pin 2 for Motor A
  
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    pinMode(echo, OUTPUT);
    pinMode(trig, OUTPUT);
  
    //Initialize SW2 Switch as Input
    // pinMode(SW2, INPUT_PULLUP);  //State for SW2 with pullUp resistor
  }
  
  void move_direction(char blueTooth){
    if (blueTooth == 'A'){
      state = 1;
    }
    else if (blueTooth == 'B'){
      state = 2;
    }
    else if (blueTooth == 'C'){
      state = 3;
    }
    else if (blueTooth == 'D'){
      state = 4;
    }
    else if (blueTooth == '0'){
      state = 0;
    }
    else if (blueTooth == 'S'){
      state = 5;
    }
    else if (blueTooth == 'M'){
      state = 6;
    }
    else if (blueTooth == 'N'){
      state = 7;
    }
    else if (blueTooth == 'O'){
      state = 8;
    }
    else if (blueTooth == 'P'){
      state = 9;
    }
  }  


void Update_Ultra_Sonic()
{
  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
//  digitalRead(anypin/switch) //Use this function to read the state of any Pin/Switch i.e. SW1 and SW2

  duration = pulseIn(echo, HIGH);   // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
  cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
  //Sending through serial port to print on Monitor
  }

long microsecondsToCentimeters(long microseconds)
{
  long distance = 0.03448 * microseconds; // 1/29 = 0.03448
  return distance / 2;
}



  void loop() {
      r1 = digitalRead(s1);
      r2 = digitalRead(s2);

      // Make the motor run clockwise direction using in1 and in2 states below
      if(Serial.available()>0){
    
        //Read the bluetoot data and store it in colorDetect variable using Serial.read() command here
        blueTooth = Serial.read();

        //Following lines help debugging by printing whatever character recieved on Serial Monitor
        char Rec = char(blueTooth);
        if (Rec != '0')
        {
        Serial.println(Rec); //This is to visualise the received character on the serial monitor
        }  
      }
      // else{
      //   blueTooth = '0';
      // }
      move_direction(blueTooth);
      
      Serial.print('\n');
      Update_Ultra_Sonic();
      if (cm <= 20){
        state = 0;
      }

      Serial.print(state);
      Serial.print("  dist= ");
      Serial.print(cm);
      if (state == 0){
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
      if (state == 1){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enA, 255); 
        analogWrite(enB, 255);
      }
      else if (state == 2){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enA, 255);
        analogWrite(enB, 255);
      }
      else if (state == 3){
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        // analogWrite(enA, 255);
        analogWrite(enB, 150);
      }
      else if (state == 4){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(enA, 150);
        // analogWrite(enB, 255);
      }
      else if (state == 5){
          Serial.print(r1);
          Serial.print(r2);
          
          if ((r1 == 0)&&(r2 == 0)){
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, HIGH);
              analogWrite(enA, 135); 
              analogWrite(enB, 135);
            }
          if ((r1 == 1)&&(r2 == 0)){

              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, HIGH);
              analogWrite(enB, 130);

              

          }
          if ((r1 == 0)&&(r2 == 1)){
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              analogWrite(enA, 130);

              
          }
          if ((r1 == 1)&&(r2 == 1)){
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
          }           
        }
        else if (state == 6){
          servo1_pos += 1;
          if (servo1_pos >= 180) servo1_pos = 180;
        }
        else if (state == 7){
          servo1_pos -= 1;
          if (servo1_pos <= 0) servo1_pos = 0;
        }
        else if (state == 8){
          servo2_pos += 1;
          if (servo2_pos >= 180) servo2_pos = 180;
        }
        else if (state == 9){
          servo2_pos -= 1;
          if (servo2_pos <= 0) servo2_pos = 0;
        }
        myservo1.write(servo1_pos);
        myservo2.write(servo2_pos);
        delay(200);
        }