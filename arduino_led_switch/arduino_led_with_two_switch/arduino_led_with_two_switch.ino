int sw1,sw2; // to store the states of sw1 and 2 when it is read
int sw1_prev, sw2_prev;
int led_state;


void setup() 
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT); // make  pin 13 to drive the led
  pinMode(2, INPUT);   // make  pin 2 as input and sw1
  pinMode(4, INPUT);   // make  pin 4 as input and sw2
  Serial.begin(9600);  // for debugging
  while(!Serial) {
    ; // waiting for serial to be ready  
  }
  digitalWrite(13, LOW); // initially LED is off.
  sw1_prev = 500;
  sw2_prev = 500;
  led_state = 0;
}



void debounce_sw()
{
  //delay(1200);
}

void check_for_toggle()
{
  sw1 = digitalRead(2);
  sw2 = digitalRead(4);
  debounce_sw(); // to debounce the sw
  if ((sw1_prev == 0 && sw1 == 1) || (sw2_prev == 0 &&  sw2 == 1)) {
    //Serial.print("switch_toggle detected ");
    //Serial.print(sw1);
    //Serial.print(" ");
    //Serial.print(sw1_prev);

    //Serial.print(sw2);
    //Serial.print(" ");
    //Serial.print(sw2_prev);
    
    if (led_state == 0) {
      //Serial.println("LED is off");
      digitalWrite(13, LOW); //  LED is off.
      led_state = 1;
    } else {
      //Serial.println("LED is on");
      digitalWrite(13, HIGH); //  LED is on.  
      led_state = 0;
    }
  }
  sw1_prev = sw1;  // store the value.
  sw2_prev = sw2;
}

void loop() {
  // put your main code here, to run repeatedly:
  check_for_toggle();
}
