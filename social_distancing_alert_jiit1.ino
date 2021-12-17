// Social Distancing Alert JIIT
#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
int ledPin= 3;
// How many NeoPixels are attached to the Arduino?
int ledNo= 12;
// Declare our NeoPixel strip object:
// When we set up the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledNo,ledPin,NEO_RGB+NEO_KHZ800);
// which pin on the Arduino is connected to buzzer
int buzzerPin= 2;
//which pin on the Arduino is connected to echoPin
int echoPin= 6;
//which pin on the Arduino is connected to trigPin
 
int trigPin= 5;
//setting the minimum and maximum distance
int minDistance = 100;
int maxDistance = 300;
 
void setup() 
{
  pinMode(buzzerPin, OUTPUT);//sets the buzzerPin as output
  pinMode(trigPin, OUTPUT);//sets the trigPin as output
  pinMode(echoPin, INPUT);//sets the buzzerPin as output
  Serial. begin(9600);// starts the serial communication
  strip.begin(); // prepares data pin for Neopixel output
  for(int i = 0; i < ledNo; i++)
  {
// setting the led colour black
   strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();// initialise all pixels to “off”
}
void loop() 
{
  int distance = calcDistance();
  Serial.println(distance);
  int ledsToGlow = map(distance, minDistance, maxDistance, ledNo, 1);
  //Serial.println(ledsToGlow);
  if(ledsToGlow == 12)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
  for(int i = 0; i < ledsToGlow; i++)
  {
    if(i < 4)
    {
      strip.setPixelColor(i,strip.Color(50,0,0));//green,red,blue
    }
    else if(i >= 4 && i < 8)
    {
      strip.setPixelColor(i,strip.Color(50,50,0));//green,red,blue
    }
    else if(i >= 8 && i < 12)
    {
      strip.setPixelColor(i,strip.Color(0,50,0));//green,red,blue
    }
  }
  for(int i = ledsToGlow; i < ledNo; i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
  delay(50);
}

int calcDistance()
{
  long distance,duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/29/2;
  if(distance >= maxDistance)
  {
    distance = maxDistance;
  }
  if(distance <= minDistance)
  {
    distance = minDistance;
  }
  return distance;
}