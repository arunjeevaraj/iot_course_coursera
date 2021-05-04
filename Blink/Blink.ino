
// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);  // make LED13 output pin
}


void blink_led(int delay_time_ms)
{
   digitalWrite(13, HIGH);
   delay(delay_time_ms);
   digitalWrite(13, LOW);
   delay(delay_time_ms);
}

// the loop function runs over and over again forever
void loop() 
{
  int blink_count = 0;
  bool fast = true;
  while(1) {
    if (fast) {
      blink_led(500); // a delay of 500 msec
      if (++blink_count == 5) {
        fast = 0; // make it blink slow
        blink_count = 0;
      }
    } else {
      blink_led(2000); // delay time of 2 secs between on and off
      if (++blink_count == 5) {
        fast = 1; // make it blink fast
        blink_count = 0;
      }
    }
  }
}
