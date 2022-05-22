//Libraries
#include <NewTone.h> //adding NewTone library (tone/noTone)
#include <NewPing.h> //adding NewPing library (sonar)

//Sonar setup for ultrasonic sensor
#define trigger 8 //trigger pin on ultrasonic sensor set as digital pin 8
#define echo 9 //echo pin on ultrasonic sensor set as digital pin 9
#define max_dist 400 //max distance in cm to ping

//Buzzer setup
#define buzzer 7 //+ side pin on buzzer set as digital pin 7

//Notes setup
#define D5 587
#define Cs5 554
#define A4 440
#define G4 392
#define Fs4 370
#define E4 330
#define B4 494

int notes[] = {D5, Cs5, A4, G4, Fs4, G4, E4, Fs4, G4, A4, B4, D5, Cs5, A4, Fs4};
double durations[] = {6.25, 6.25, 0.75, 8, 8, 0.75, 8, 8, 1.25, 4, 4, 4, 4, 4, 0.75};
//There are 15 elements each in the arrays
int len = sizeof(notes) / sizeof(notes[0]); //length of array: should be 15

//NewPing setup
NewPing sonar(trigger, echo, max_dist);

//Other variables
float dist; //distance that the sensor will detect
int currNote; //current note to be played

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println((String) "The length of the array is " + len); //checking that len is 15
}

void loop() {
  // put your main code here, to run repeatedly:
  dist = sonar.ping_cm();
  Serial.println((String) "The distance is " + dist);
  if(dist < 20 && dist > 0) {
    for(currNote = 0; currNote < len; currNote++) {
      int duration = 1000 / durations[currNote];
      NewTone(buzzer, notes[currNote], duration);

      //pause between notes
      int pause = duration * 1.3;
      delay(pause); 

      //stop the tone
      noNewTone(buzzer);
    }
  }
}
