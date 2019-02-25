
struct RGB {
  byte r;
  byte g;
  byte b;
};

struct VECTOR {
  unsigned long delta_X;
  float vel_X;
  unsigned long delta_Y;
  float vel_Y;
  bool pen;
};

RGB variable = { 255 , 0 , 0 };

RGB meuArray[2];

char inByte;

bool motor;

bool mystep_X = false;
bool mystep_Y = false;
 
unsigned long contador_X;
unsigned long contador_Y;

unsigned int sent_X = 8; 
unsigned int step_X = 7;

unsigned int sent_Y = 6;
unsigned int step_Y = 5;

unsigned int vel_X = 10000;
unsigned int vel_Y = 10000;

bool dir_X = false;
bool dir_Y = false;
char command;

unsigned long number;

char buf[100];
String inputString = "";         // a String to hold incoming data

unsigned int square_side = 4;

int led_status_pin = 2;
bool led_status;
unsigned int led_status_time = 500; // 500 ms
unsigned int led_status_get_time;
unsigned int led_status_get_time_old;

unsigned int timer_global;
unsigned int timer_vel_X_old;
unsigned int timer_vel_Y_old;

unsigned long get_time_final;
unsigned long get_time_initial;

void setup() {
  // start serial port at 9600 bps:

  Serial.begin(9600);
  
  // initialize digital pin as an output.
  pinMode(sent_X, OUTPUT);
  pinMode(step_X, OUTPUT);
  
  pinMode(sent_Y, OUTPUT);
  pinMode(step_Y, OUTPUT); 

  pinMode(led_status_pin, OUTPUT);
  
  // reserve 10 bytes for the inputString:
  //inputString.reserve(10);


}

void loop() {

  variable.r = 0;
  meuArray[0].r = 10;
  
  led_status_get_time = millis();
  if ( led_status_get_time - led_status_get_time_old >= led_status_time )
  {
      led_status = !led_status;
      digitalWrite(led_status_pin, led_status);
      led_status_get_time_old = millis();
  }
  
  //Serial.setTimeout(10);
if (Serial.available() > 0) {
    
    //Serial.println("serial in");

    int len = Serial.readBytes(buf,136);
    //  Serial.print("buffer=");
    //Serial.println(len);
    
    //if (buf[0] == 'M') 
    //{
       if ( buf[0] == 'X' || buf[0] == 'Y' || buf[0] == 'S' )
       {
           command = buf[0];
            
           if ( buf[1] == '-' )
           {
              if ( command == 'X' )
              {
                dir_X = true;
              }
              if ( command == 'Y' )
              {
                dir_Y = true;
              }

              for (int i=0; i <= len; i++){
                if (buf[i+2] == '\n')
                {
                  break;
                }
                inputString += buf[i+2];
              }// for
           }
           else
           {
              dir_X = false;
              dir_Y = false;
              
              for (int i=0; i <= len; i++){
                if (buf[i+1] == '\n')
                {
                  break;
                }
                inputString += buf[i+1];
              }// for
           }
            
           number = inputString.toInt();
           
           //Serial.print("N PASSOS : ");
           //Serial.println(number);
           //Serial.println(number * 2);
           
           motor = true;
           inputString = "";
           memset(buf, 0, sizeof(buf)); //Limpa Buffer
           get_time_initial = micros();

       }else
       {
        Serial.println("Outro Comando");
       }

    //}// if

//    //Serial.flush();

} // if (Serial.available() > 0)
 

timer_global = micros();

if( motor )
{
//-----------------------------------------------  
   if ( command == 'T' )
   {
    if ( timer_global - timer_vel_X_old >= vel_X )
    {
       if (contador_X <= number*2)
       {
          //dir_X = false;
          digitalWrite(sent_X, dir_X);
          digitalWrite(step_X, mystep_X);
          mystep_X = !mystep_X;
          //delayMicroseconds(vel_X);
          contador_X++;
          timer_vel_X_old = micros();
       }
        else
       {
          contador_X = 0;
          motor = false;
          digitalWrite(step_X, LOW);
          dir_X = false;
          
          //get_time_final = micros();
          //Serial.print("elapsed time = ");
          //Serial.println(get_time_final - get_time_initial);
       }
     }
   }  
//-----------------------------------------------  
   if ( command == 'X' )
   {
    if ( timer_global - timer_vel_X_old >= vel_X )
    {
       if (contador_X <= number*2)
       {
          //dir_X = false;
          digitalWrite(sent_X, dir_X);
          digitalWrite(step_X, mystep_X);
          mystep_X = !mystep_X;
          //delayMicroseconds(vel_X);
          contador_X++;
          timer_vel_X_old = micros();
       }
        else
       {
          contador_X = 0;
          motor = false;
          digitalWrite(step_X, LOW);
          dir_X = false;
          
          //get_time_final = micros();
          //Serial.print("elapsed time = ");
          //Serial.println(get_time_final - get_time_initial);
          Serial.println("OK");
       }
     }
   }
//-----------------------------------------------  
   if ( command == 'Y' )
   {
    if ( timer_global - timer_vel_Y_old >= vel_Y )
    {
       if ( contador_Y <= (number*2)*2.45 )
       {
          //dir_Y = false;
          digitalWrite(sent_Y, dir_Y);
          digitalWrite(step_Y, mystep_Y);
          mystep_Y = !mystep_Y;
          //delayMicroseconds(vel_Y);
          contador_Y++;
          timer_vel_Y_old = micros();
       }
        else
       {
          contador_Y = 0;
          motor = false;
          digitalWrite(step_Y, LOW);
          dir_Y = false;
       }
    }
   }   
//-----------------------------------------------
  if ( command == 'S' )
   {
       //Serial.println("-----------> S");
       //Serial.print("SIDE = ");
       //Serial.println(square_side);
       
       //------------
       // side = 4 --> X
       if ( square_side == 4 )
       {
         if (contador_X <= number*2)
         {
            dir_X = false;
            digitalWrite(sent_X, dir_X);
            digitalWrite(step_X, mystep_X);
            mystep_X = !mystep_X;
            delayMicroseconds(vel_X);
            contador_X++;
         }else
         {
            square_side = 3;
            contador_X = 0;
            digitalWrite(step_X, LOW);
         }
       }
       //------------
       // side = 3 --> Y
       if ( square_side == 3 )
       {
         if (contador_Y <= (number*2)*2.45)
         {
            dir_Y = false;
            digitalWrite(sent_Y, dir_Y);
            digitalWrite(step_Y, mystep_Y);
            mystep_Y = !mystep_Y;
            delayMicroseconds(vel_Y);
            contador_Y++;
         }else
         {
            square_side = 2;
            contador_Y = 0;
            digitalWrite(step_Y, LOW);
         }
       }
       //------------
       // side = 2 <-- X
       if ( square_side == 2 )
       {
         if (contador_X <= number*2)
         {
            dir_X = true;
            digitalWrite(sent_X, dir_X);
            digitalWrite(step_X, mystep_X);
            mystep_X = !mystep_X;
            delayMicroseconds(vel_X);
            contador_X++;
         }else
         {
            square_side = 1;
            contador_X = 0;
            digitalWrite(step_X, LOW);
         }
       }
       //------------
       // side = 1 <-- Y
       if ( square_side == 1 )
       {
         if (contador_Y <= (number*2)*2.45)
         {
            dir_Y = true;
            digitalWrite(sent_Y, dir_Y);
            digitalWrite(step_Y, mystep_Y);
            mystep_Y = !mystep_Y;
            delayMicroseconds(vel_Y);
            contador_Y++;
         }else
         {
            square_side = 4;
            contador_Y = 0;
            digitalWrite(step_Y, LOW);
            motor = false;
            command = '0';
         }
       }
      //------------

   } 
//-----------------------------------------------   
}
 
 
  
}
