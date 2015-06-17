
 int incomingByte = 0;   // for incoming serial data
 int total = 0;
 int count = 1;
 int ms = 0;
 int delaytime = 0;



void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(7, OUTPUT);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps  
}

void loop() {
   
   if (Serial.available() >= 0) {
               
     // read the incoming byte:
     incomingByte = Serial.read();
     //if the incoming byte is not a period (giving it a value higher than 46) we add it to the total ms num. 
     //It is added in reverse order, so 12345 would be recorded as 54321. This is corrected later.
     while (incomingByte > 46){
       total += (incomingByte-48)*count; //subtract 48 to get integer value
       count *= 10; //increment 10's digit
       //then we look for the next number
       incomingByte = Serial.read();
       }
      //if the incoming byte is a period (signifying end of ms)
      if(incomingByte == 46){
      //if the total is 0 we don't need to do anything with it
        if(total == 0){
          ms = total;
        } 
        //if the total is not 0, we reverse the digits
        while(total != 0){
          ms= ms * 10;
          ms = ms + total%10;
          total = total/10;
          }
                  
         //for testing purposes. You can remove this
         Serial.println(ms, DEC);
                  
         //resets count
         count = 1;
                  
                  
         delaytime = ms;
         }
                  
                  
      }
         //activates shutter
         digitalWrite(7, LOW);   // set the LED on
         delay(delaytime);              // wait for a second
          
         digitalWrite(7, HIGH);// set the LED off
         delay(1);
         //deactivates shutter
         delaytime = 0;
          
         //resets stuff
         total = 0;
         reverse = 0;
  
  
}
