/*
this program print the fibonacci series in to the serial port of the arduino
*/

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  
}


void generate_fibonacii(int* fib_series, int length)
{
  fib_series[0] = 0;
  if (length == 1)
    return;
  fib_series[1] = 1;
  if (length == 2)
    return;
  if (length > 2) {
    int l = 2;
    while (l<length) {
      fib_series[l] = fib_series[l-1] + fib_series[l-2];
      l++;
    }
  }
}

void print_result(int* fib_series, int length)
{

  Serial.println("Fibonacci series");
  int i = 0;
  while (i < length) {
    Serial.print(fib_series[i]);
    i++;
    Serial.println(" ");
  }
  
}

void loop() {
  // prints value unaltered, i.e. the raw binary version of the byte.
  // The Serial Monitor interprets all bytes as ASCII, so 33, the first number,
  // will show up as '!'
  setup();

  int length_of_fib_series = 6;
  Serial.println("Fibonacci series length :");
  Serial.print(length_of_fib_series);
  Serial.println("\n");
  int fib_series[length_of_fib_series];
  generate_fibonacii(fib_series, length_of_fib_series);
  print_result(fib_series, length_of_fib_series);


  Serial.write("Done !"); 
  while(1) {
    
  }
  
}
