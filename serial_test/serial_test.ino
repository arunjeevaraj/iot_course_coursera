
void setup() {
Serial.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println("ASCII Table ~ Character Map");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
    Serial.println("Hello, world");
}
