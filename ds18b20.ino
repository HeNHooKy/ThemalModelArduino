/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
#define ONE_WIRE_BUS_OUT 3

#define MY_CONNECTION_NUMBER 1
#define LAST_NUMBER 100
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
OneWire oneWire_out(ONE_WIRE_BUS_OUT);

/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensor(&oneWire);
DallasTemperature sensor_out(&oneWire_out);

/********************************************************************/
DeviceAddress detector_0 = { 0x28, 0xB8, 0x49, 0x95, 0xF0, 0x1, 0x3C, 0x96 };//28 B8 49 95 F0 1 3C 96
DeviceAddress detector_1 = { 0x28, 0xD7, 0x60, 0x95, 0xF0, 0x1, 0x3C, 0x7A };//28 D7 60 95 F0 1 3C 7A
DeviceAddress detector_2 = { 0x28, 0x3E, 0x35, 0x95, 0xF0, 0x1, 0x3C, 0x82 };//28 3E 35 95 F0 1 3C 82
DeviceAddress detector_3 = { 0x28, 0x50, 0x4B, 0x95, 0xF0, 0x1, 0x3C, 0x9D };//28 50 4B 95 F0 1 3C 9D
DeviceAddress detector_4 = { 0x28, 0xCC, 0xB8, 0x95, 0xF0, 0x1, 0x3C, 0xB9 };//28 CC B8 95 F0 1 3C B9
DeviceAddress detector_5 = { 0x28, 0xC1, 0x53, 0x95, 0xF0, 0x1, 0x3C, 0x59 };//28 C1 53 95 F0 1 3C 59
DeviceAddress detector_6 = { 0x28, 0x32, 0x90, 0x95, 0xF0, 0x1, 0x3C, 0x1E };//28 32 90 95 F0 1 3C 1E
DeviceAddress detector_7 = { 0x28, 0xFE, 0x9F, 0x95, 0xF0, 0x1, 0x3C, 0x93 };//28 FE 9F 95 F0 1 3C 93
DeviceAddress detector_out = { 0x28, 0xC3, 0xD1, 0x95, 0xF0, 0x1, 0x3C, 0x7F };//28 C3 D1 95 F0 1 3C 7F

double last_0[LAST_NUMBER];
double last_1[LAST_NUMBER];
double last_2[LAST_NUMBER];
double last_3[LAST_NUMBER];
double last_4[LAST_NUMBER];
double last_5[LAST_NUMBER];
double last_6[LAST_NUMBER]; 
double last_7[LAST_NUMBER];
double last_8[LAST_NUMBER];

int iteration_num;

/********************************************************************/ 
void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
 sensor.begin(); 
 sensor_out.begin();
 iteration_num = 0;
} 


void loop(void) 
{ 
 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus  
 // Send the command to get temperature readings 
 sensor.requestTemperatures(); 
 sensor_out.requestTemperatures();

 double detector_0_data = sensor.getTempC(detector_0);
 double detector_1_data = sensor.getTempC(detector_1);
 double detector_2_data = sensor.getTempC(detector_2);
 double detector_3_data = sensor.getTempC(detector_3);
 double detector_4_data = sensor.getTempC(detector_4);
 double detector_5_data = sensor.getTempC(detector_5);
 double detector_6_data = sensor.getTempC(detector_6);
 double detector_7_data = sensor.getTempC(detector_7);
 double detector_out_data = sensor_out.getTempC(detector_out);
 
 last_0[iteration_num] = detector_0_data;
 last_1[iteration_num] = detector_1_data;
 last_2[iteration_num] = detector_2_data;
 last_3[iteration_num] = detector_3_data;
 last_4[iteration_num] = detector_4_data;
 last_5[iteration_num] = detector_5_data;
 last_6[iteration_num] = detector_6_data;
 last_7[iteration_num] = detector_7_data;
 
 Serial.print(MY_CONNECTION_NUMBER);
 Serial.print(";");
 Serial.print(detector_out_data);
 Serial.print(",");
 Serial.print(detector_0_data);
 Serial.print(",");
 Serial.print(detector_1_data);
 Serial.print(",");
 Serial.print(detector_2_data); 
 Serial.print(",");
 Serial.print(detector_3_data);
 Serial.print(",");
 Serial.print(detector_4_data);
 Serial.print(",");
 Serial.print(detector_5_data);
 Serial.print(",");
 Serial.print(detector_6_data);
 Serial.print(",");
 Serial.print(detector_7_data);
 Serial.println();

 
 delay(1000); 

 iteration_num++;
 if(iteration_num == LAST_NUMBER) {
  iteration_num = 0;
 }
}

double getStandartDeviation(double* last, double data) {
  double sum = 0;
  for(int i = 0; i < LAST_NUMBER; i++) {
    sum += last[i];
  }
  double avg = sum / LAST_NUMBER;
  
  double sumOf2PowDif = 0;
  for(int i = 0; i < LAST_NUMBER; i++) {
    sumOf2PowDif += pow((last[i] - avg), 2);
  }

  double S = sqrt(sumOf2PowDif / LAST_NUMBER);

  return S;
}
