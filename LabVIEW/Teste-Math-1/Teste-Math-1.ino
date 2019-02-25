void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}

void loop() {
  
//  double delta = 45.0;
//  double sine = sin( (DEG_TO_RAD * delta) );
//  Serial.println("sin");
//  Serial.println(sine,4);

  for(int d=0; d<360; d++)
  {
    Serial.print(cos(DEG_TO_RAD * d) );
    Serial.print(" ");
    Serial.println(sin(DEG_TO_RAD * d) );
  }
}
