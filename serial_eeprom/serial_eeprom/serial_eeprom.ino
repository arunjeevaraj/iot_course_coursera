#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // for debugging
  while(!Serial) {
    ; // waiting for serial to be ready  
  }
}

int read_data_buffer[64];
const int write_command[] = {119, 114, 105, 116, 101};
const int read_command[] = {114, 101, 97, 100};


typedef struct {
  bool rnw; // 1 = read and not 1 is write
  int addr;
  int data;  // if data is to be written
} command_read;

command_read command_to_process;

void clear_read_data_buffer()
{
  for(int i = 0; i < 64; i++) 
    read_data_buffer[i] = 1255;  
  
}

bool char_match(int* src, int* dest, int len)
{
  while(len--) {
    //Serial.write(src[len]);
    //Serial.print(" <-s  d->");
    //Serial.write(dest[len]);
    //Serial.print("\n");
    //Serial.print(dest[len]);
    if (src[len] == dest[len]) {
      ; // do nothing  
    }  else {
      return 0;  
    }
  }  
  return 1;
}

void parse_write_data_address()
{
  int address = 0;
  int data = 0;
  int index = 6;
  while(1) {
    if (read_data_buffer[index] == 32 || read_data_buffer[index] == 1255) { // 32 is space
      index++;
      break;  
    } else {
     address = address*10 + (read_data_buffer[index] - 48); // 48 is 0 in ascii 
     index++;
    }
  }  

  Serial.print("address :");
  Serial.print(address);
  Serial.print("\n");
  command_to_process.addr= address;
  
  while(1) {
    if (read_data_buffer[index] == 32 || read_data_buffer[index] == 1255 || read_data_buffer[index] == 10) { // 32 is space
      index++;
      break;  
    } else {
     data = data*10 + (read_data_buffer[index] - 48); // 48 is 0 in ascii 
     index++;
    }
  }   
  Serial.print("data :");
  Serial.print(data);
  Serial.print("\n");
  command_to_process.data = data;
}

void parse_read_address()
{
  int address = 0;
  int data = 0;
  int index = 5;
  while(1) {
    if (read_data_buffer[index] == 32 || read_data_buffer[index] == 1255 || read_data_buffer[index] == 10) { // 32 is space
      index++;
      break;  
    } else {
     address = address*10 + (read_data_buffer[index] - 48); // 48 is 0 in ascii 
     index++;
    }
  }  

  Serial.print("address :");
  Serial.print(address);
  Serial.print("\n");
  command_to_process.addr = address;
}


void parse_command()
{ 
  if (char_match(read_command, read_data_buffer, 4)) {
    Serial.println("read command matched");
    command_to_process.rnw = 1;
    parse_read_address();  
  } else if (char_match(write_command, read_data_buffer, 5)) {
    Serial.println("write command matched");
    command_to_process.rnw = 0; 
    parse_write_data_address();
  }

  
}

void read_command_from_serial()
{
  int bytes_read = 0;
  int data_read;
  int i;
  while (1) {
    if(Serial.available()) {
      data_read = Serial.read();
      read_data_buffer[bytes_read++] = data_read; // store it in a buffer.
      if (data_read == 10) { // new line, the end of the command
        //Serial.println("End of command");
        //Serial.print(bytes_read);
        Serial.print("Command read : ");
        for (i = 0; i < bytes_read; i++) {
          Serial.write(read_data_buffer[i]);  
        }
        Serial.print("\n");
        parse_command();
        break;
      } else {
        // keep on storing the data
      }      
     } else {
     // waiting for the command 
     }
     
  }
}


void run_command()
{
    int data_read;
    if (command_to_process.rnw) {
      Serial.print("reading from eeprom addr :");
      Serial.print(command_to_process.addr);
      data_read = EEPROM.read(command_to_process.addr);
      Serial.print("  data: ");
      Serial.print(data_read);
      Serial.print("  \n");
    } else {
      Serial.print("writing from eeprom addr :");
      Serial.print(command_to_process.addr);
      Serial.print("  data: ");
      Serial.print(command_to_process.data);
      Serial.print("  \n");
      EEPROM.write(command_to_process.addr, command_to_process.data);
    } 
}

void loop() {
  clear_read_data_buffer();
  Serial.println("Enter a new command");
  read_command_from_serial();
  run_command();
}
