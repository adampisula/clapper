#include <Timer.h>
#include <Event.h>


int relay = 3;
int input = 2;

int prev = 0;
int zero = 0;
int one = 0;

int count = 0;

int lastclap = 0;
int lastzero = 0;

boolean relayState = 1;

Timer t;

void checkState() {
  boolean state = !digitalRead(input);

  if(prev != state)
  {
    /*Serial.print("STATE: ");
    Serial.println(state);
    Serial.print("ZERO: ");
    Serial.println(zero);
    Serial.print("ONE: ");
    Serial.println(one);
    Serial.print("LASTCLAP: ");
    Serial.println(lastclap);
    Serial.print("LASTZERO: ");
    Serial.println(lastzero);
    Serial.print("RELAYSTATE: ");
    Serial.println(relayState);
    Serial.println("-----");*/
    
    if(!state && lastclap > 35 && lastclap < 150) {
      //Serial.println("lastclap > 50 && lastclap < 150");
      if(lastzero > 50 && lastzero < 200) {
        //Serial.println("lastzero > 50 && lastzero < 150");
        if(one > 35 && one < 150) {
          //Serial.println("one > 50 && one < 150");
          relayState = !relayState; 
        }
      }
    }
    
    if(!state)
      lastclap = one;
    if(state)
      lastzero = zero;

    zero = 0;
    one = 0;

    prev = state;
  }

  else
  {
    if(prev == 0)
      zero++;
    else
      one++;
  } 
}

void setup() {
  Serial.begin(9600);

  pinMode(relay, OUTPUT);
  pinMode(input, INPUT_PULLUP);

  t.every(1, checkState);
}

void loop() {
  t.update();

  digitalWrite(relay, relayState);
}
