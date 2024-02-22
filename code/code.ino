#define enA 9
#define in1 6
#define in2 7
#define enB 3
#define in3 4
#define in4 5
String red,l,r;
char c;
int pwm_l,pwm_r,pwmOutput_l,pwmOutput_r;
void setup(){
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.begin(57600);

}

void loop(){
  while (Serial.available()){
      c = Serial.read();  //gets one byte from serial buffer
      red += c; //makes the string readString
  }
  
   //Serial.println(red[0]);
   int len = red.length();
   //Serial.println(len);
   if(len==6){
      l= red.substring(0,2);
      r= red.substring(3,5);
      pwm_l = l.toInt();
      pwm_r = r.toInt();
      int pwmOutput_l = map(pwm_l, 0, 35, 0 , 255);
      int pwmOutput_r = map(pwm_r, 0, 35, 0 , 255);
      analogWrite(enA, pwmOutput_l); // Send PWM signal to L298N Enable pin
      digitalWrite(in1,HIGH);
      digitalWrite(in2, LOW);
   }
   //ELSE IF - 5
   else if(len ==5){
      if(red[0]!=1){
        
        //LEFT TURN
        
        l= red.substring(1,2);
        r= red.substring(3,4);
        pwm_l = l.toInt();
        pwm_r = r.toInt();  
      }
      else{
         //RIGHT TURN
         l= red.substring(0,1);
         r= red.substring(3,4);
         pwm_l = l.toInt();
         pwm_r = r.toInt();   
      }
   }
   else if (len==8){
      l= red.substring(1,3);
      r= red.substring(5,7);
      pwm_l = l.toInt();
      pwm_r = r.toInt();  
   }

   else if ( len==4 && red[0]==0){
      analogWrite(enA,0);
      digitalWrite(in1,LOW);
      digitalWrite(in2, LOW);
    
   }
   Serial.println(pwm_l);
   Serial.println(pwm_r);
   int pwmOutput_l = map(pwm_l, 0, 35, 0 , 255);
   int pwmOutput_r = map(pwm_r, 0, 35, 0 , 255);
   Serial.print("The PWM of L wheel set to : ");
   Serial.println(pwmOutput_l);
   Serial.print("The PWM of R wheel set to : ");
   Serial.println(pwmOutput_r);
   red = "";
  }
