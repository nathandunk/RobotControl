#include <Encoder.h>
#include <PD_Controller.h>
#include <Filter.hpp>
#include <DualTB9051FTGMotorShield.h>

Encoder myEnc(2, 3);
float position1 = 0.0;
float velocity1 = 0.0;
float pos_last = 0.0;
float torque1   = 0.0;
PD_Controller pd(8, 0.01, 1);
float ref1 = 0.0;

FilterBuLp2 filter;

unsigned char M1EN   = 5;
unsigned char M1DIR  = 7;
unsigned char M1PWM  = 9;
unsigned char M1DIAG = 6;
unsigned char M1OCM  = A0;
unsigned char M2EN   = 4;
unsigned char M2DIR  = 8;
unsigned char M2PWM  = 10;
unsigned char M2DIAG = 12;
unsigned char M2OCM  = A1;

DualTB9051FTGMotorShield driver(M1EN, M1DIR, M1PWM, M1DIAG, M1OCM, M2EN, M2DIR, M2PWM, M2DIAG, M2OCM);

unsigned long last_us = 0L;
unsigned long last_move_time = 0L;
int period = 2000; // microseconds

bool plotting = true;

void stopIfFault() {
  if (driver.getM1Fault())
  {
    Serial.println("M1 fault");
    driver.disableDrivers();
    while (1);
  }
  if (driver.getM2Fault())
  {
    Serial.println("M2 fault");
    driver.disableDrivers();
    while (1);
  }
}

void setup() {
   Serial.begin(115200);
   driver.init();
   driver.enableDrivers();
   delay(1);
}

void loop() {
  position1 = myEnc.read()/2248.86*360;
  if (micros () - last_us > period){
    velocity1 = (position1-pos_last)/float(micros()-last_us)*1000000.0;
    
    velocity1 = filter.step(velocity1);
    
    ref1 = 50*sin(0.5*2*PI*last_us/1000000.0);
    torque1 = pd.CalcTorque(position1, velocity1, ref1, 0.0);
    torque1 = constrain(torque1,-100.0,100.0);
    if(abs(torque1) < 10 && abs(velocity1) < 5){
      driver.setM2Speed(0);      
    }
    else{
      driver.setM2Speed(int(torque1));  
    }
    
    stopIfFault();
    
    pos_last  = position1;
    last_us = micros();
  }
  else{
    if(!plotting){
      Serial.println(micros () - last_us);
    }
  }
  if(plotting){
    Serial.print(position1);
    Serial.print(" ");
    Serial.print(velocity1);
    Serial.print(" ");
    Serial.print(torque1);
    Serial.print(" ");
    Serial.println(ref1);
  }
}
