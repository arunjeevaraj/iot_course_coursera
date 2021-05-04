void setup() 
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT); // make  pin 13 to drive the led
  Serial.begin(9600);
  while(!Serial) {
    ; // waiting for serial to be ready  
  }
  digitalWrite(13, LOW); // initially LED is off.
}

void loop() {
  // put your main code here, to run repeatedly:
  int read_value;
  if (Serial.available() > 0) {
    //Serial.print("read value : ");      // used for debugging.
    //read_value = Serial.read();
    //Serial.print(read_value); 
    //Serial.print('\n');
    
    if(read_value == '0') {
      digitalWrite(13, LOW);
    } else if (read_value == '1') {
      digitalWrite(13, HIGH);
    } else if (read_value == 10) { // new line ignore
      ;
    } else {
      Serial.print("invalid command, either enter '0' or '1' to control the led \n");
    }
  }
}
