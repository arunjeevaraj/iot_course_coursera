


int ldr_voltage_val;

void setup() 
{
  pinMode(13, OUTPUT); // make  pin 13 to drive the led
  pinMode(2, INPUT);   // make  pin 2 as input and sw1
  
  Serial.begin(9600);  // for debugging
  while(!Serial) {
    ; // waiting for serial to be ready  
  }
  digitalWrite(13, LOW); // initially LED is off.
}

void loop() {
  // put your main code here, to run repeatedly:

  ldr_voltage_val = analogRead(0); // pin 0 connnected to the ldr
  Serial.print(ldr_voltage_val);
  Serial.print("\n");
  delay(500);
  if (ldr_voltage_val > 600) {
    digitalWrite(13, HIGH);  
  } else {
    digitalWrite(13, LOW);
  }
}
