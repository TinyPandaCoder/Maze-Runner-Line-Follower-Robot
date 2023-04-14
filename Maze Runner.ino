#define motoa1 7
  #define motoa2 8
  #define motob1 9
  #define motob2 10
  #define ENA 6
  #define ENB 11
  #define sen1 2
  #define sen2 3
  #define sen3 A5
  #define sen4 5
  #define sen5 12
bool a , b , c , d , e;
int x=90,y=85;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motoa1 , OUTPUT);
  pinMode(motoa2 , OUTPUT);
  pinMode(motob1 , OUTPUT);
  pinMode(motob2 , OUTPUT);
  pinMode(ENA , OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(sen1 , INPUT);
  pinMode(sen2, INPUT);
  pinMode(sen3, INPUT);
  pinMode(sen4 , INPUT);
  pinMode(sen5 , INPUT);

  //pinMode(sen5, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly
    //analogWrite(ENA, 209);
    //analogWrite(ENB, 219);
   
    a = digitalRead(sen1); // right
    b = digitalRead(sen2); // center right
    c = digitalRead(sen3); // center left
    d = digitalRead(sen4); // left
    e = digitalRead(sen5); // front
    Serial.println(d);
    //e = digitalRead(sen5);  
   check();
    
    if( c==!b){
      adjust();
      check();
    }
    if(d){
      _stop();
      turnLeft();
      check();
    }
    else if(b && c){
      forward();
      check();
    }
    else if(a){
      _stop();
      turnRight();
      check();
    }
    else{
      _stop();
      reverse();
      check();
    }
    
}
void forward(){
  Serial.println("forward");
   analogWrite(ENA, 95);
   analogWrite(ENB, 90);
  digitalWrite(motoa1, HIGH);
  digitalWrite(motoa2, LOW);
  digitalWrite(motob1 , HIGH);
  digitalWrite(motob2, LOW);
}
void rotateLeft(){
  analogWrite(ENA,x);
  digitalWrite(motoa1, HIGH);
  digitalWrite(motoa2, LOW);
  digitalWrite(motob1 , LOW);
  digitalWrite(motob2, LOW);
}
void rotateRight(){
  analogWrite(ENB,y);
  digitalWrite(motob1, HIGH);
  digitalWrite(motob2, LOW);
  digitalWrite(motoa1 , LOW);
  digitalWrite(motoa2, LOW);
}

void adjust(){
  while(!b&&c){
    Serial.println("adjust1");
    rotateLeft();
    _update();
    check();
  }
  while(!c&&b){
    Serial.println("adjust2");
        Serial.println(c);

    rotateRight();
         _update();
         check();
  }
}
void turnLeft(){
  while(d){
    Serial.println("turnleft");
    rotateLeft();
      _update();
      check();
    }
}
void turnRight(){
  while(a){
    Serial.println("turnright");
    rotateRight();
    _update();
    check();
  }
}
void reverse()
 {
   while (!b&&!c)
   {
       Serial.println("Reverse");
      analogWrite(ENA,x);
      analogWrite(ENB,y );
      digitalWrite(motoa1, HIGH);
      digitalWrite(motoa2, LOW);
      digitalWrite(motob1 , LOW);
      digitalWrite(motob2, HIGH);
      _update();
      check();
   }
 }
void _stop(){
     Serial.println("stop");
     digitalWrite(motoa1, LOW);
     digitalWrite(motoa2, LOW);
     digitalWrite(motob1 , LOW);
     digitalWrite(motob2, LOW);
     
}
void _update()
{
    a = digitalRead(sen1); // right
    b = digitalRead(sen2); // center right
    c = digitalRead(sen3); // center left
    d = digitalRead(sen4); // left
    e = digitalRead(sen5);
}
void check(){
  if(a && b && c && d && e){
    while(true){
      _stop();
      _update();
      if(!a || !b || !c || !d || !e) break;
    }
  }
}
