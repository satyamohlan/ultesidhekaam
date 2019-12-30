const int rmf = 9;                        //Left motor forward
const int rmb = 10;                        //Left motor backward
const int lmf = 5;                       //Right motor forward
const int lmb = 3;                        //Right motor backward
const int trigPin_l = 11;                 //right sensor trigger pin
const int echoPin_l = 12;                //right sensor echo pin
const int trigPin_r = 7;                   //left sensor trigger pin
const int echoPin_r = 6;                 //sraight sensor echo pin
const int trigPin_s = 4;                  //straight sensor trigger pin
const int echoPin_s = 8;                 //left sensor echo pin
const int trigPin_b = 26;           
const int echoPin_b = 2;
 //establish variables for duration of the ping, and the distance result in cm
int lm_status, rm_status;         //left motor status, right motor status, 0 = none , 1 = forward, -1 = backward
int tiles = 0;
int pref[3] = {1, -2, 2};
int tiles_to_cover = 32;
int pos[2] = {1, 1};
int len[2] = {4, 8};
int arr[200];
int last[200];
int count = 0;
int togo[200] = {};
int tgcount;
int rotation = 0;
bool right = false;
bool left = false;
bool front = false;
String direction = "forward";
int lstcounter = 0;
int corner = 0;
int checkpoint=0;
int hazarder = 0;
int victimer=0;
/*const int trigPin= 11;
  const int echoPin= 12;
  const int trigPin2= 7;
  const int echoPin2= 6;
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(trigPin_l, OUTPUT);
  pinMode(trigPin_s, OUTPUT);
  pinMode(trigPin_r, OUTPUT);
  pinMode(echoPin_l, INPUT);
  pinMode(echoPin_s, INPUT);
  pinMode(echoPin_r, INPUT);
  pinMode(13, INPUT);
  pinMode(20, INPUT);
  for (int x = 0; x < 200; x++) {
    arr[x] = 0;
    last[x] = 0;
    togo[x] = 0;
  }
visitall();
}



void loop() {
 
 


}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void leftTurn() {
  bool x;
  bool prevstate;
  rotation = 0;

  int stripe = 0;
  x = digitalRead(13);
  if (x == HIGH) {
    stripe = 8;
  }
  if (x == LOW) {
    stripe = 8;
  }
  while ((true)) {
    // put your main code here, to run repeatedly:

    prevstate = x;
    x = digitalRead(13);
    if (x != prevstate && x == 1) {
      rotation++;
    }
    if (rotation <= stripe) {
      analogWrite(rmf, 155);
      analogWrite(lmb, 155);
      digitalWrite(rmb, LOW);
      digitalWrite(lmf, LOW);
    }
    else {
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
      break;
    }


  }


}
void uturn () {

  bool x;
  bool prevstate;
  float distance = 0;
  int stripe = 0;
  rotation = 0;

  x = digitalRead(13);
  if (x == HIGH) {
    stripe = 16;
  }
  if (x == LOW) {
    stripe = 16;
  }
  while ((true)) {
    prevstate = x;
    x = digitalRead(13);
    if (x != prevstate && x == 1) {
      rotation++;
    }
    if (rotation <= stripe) {
      analogWrite(lmf, 155);
      analogWrite(rmb, 155);
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
    }
    else {

      digitalWrite(lmf, LOW);
      digitalWrite(rmb, LOW);
      break;
    }


  }
}


void rightTurn() {
  bool x;
  bool prevstate;
  rotation = 0;

  int stripe = 0;
  x = digitalRead(13);
  if (x == HIGH) {
    stripe = 8;
  }
  if (x == LOW) {
    stripe = 8;
  }



  while (true) {
    // put your main code here, to run repeatedly:

    prevstate = x;
    x = digitalRead(13);
    if (x != prevstate && x == 1) {
      rotation++;
    }
    if (rotation <= stripe) {
      analogWrite(lmf, 155);
      analogWrite(rmb, 155);
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
    }

    else {
      digitalWrite(lmf, LOW);
      digitalWrite(rmb, LOW);
      break;
    }

  }
}



void forward() {


  bool x;
  bool prevstate;
  rotation = 0;
  bool stoper = false;
  int distance = 0;
  while (true) {
    digitalWrite(trigPin_s, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_s, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_s, LOW);
   long duration_s = pulseIn(echoPin_s, HIGH);
    long cm_s = microsecondsToCentimeters(duration_s);
    if (cm_s > 1000) {
      cm_s = 500;
    }
    if (cm_s <= 10) {
      stopBot();
      break;
    }
    prevstate = x;
    x = digitalRead(13);
    if (x != prevstate && x == 1) {
      rotation++;
    }
    distance = rotation * 21 / 10;

    if (distance <= 30) {
      digitalWrite(lmf, HIGH);
      digitalWrite(rmf, HIGH);
      digitalWrite(lmb, LOW);
      digitalWrite(rmb, LOW);
    }
    else {
      digitalWrite(lmf, LOW);
      digitalWrite(rmf, LOW);
    

      break;
    }
  }



}

void stopBot() {
  analogWrite(lmb, 0);
  analogWrite(rmb, 0);
  analogWrite(lmf, 0);
  analogWrite(rmf, 0);
}
void hazard(){

   bool x;
  bool prevstate;
  while (true) {

    prevstate = x;
    x = digitalRead(13);
    if (x != prevstate && x == 0&&rotation>0) {
      rotation--;
    }
    if (rotation>0){
      digitalWrite(lmf, LOW);
      digitalWrite(rmf, LOW);
       digitalWrite(lmb, HIGH);
      digitalWrite(rmb, HIGH);
      }
       else {
      digitalWrite(lmf, LOW);
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
      digitalWrite(rmb, LOW);
      break;
    }

  }
  uturn();

    for (int x = 0; x < count - last[lstcounter-1]; x++) {
      Serial.println(arr[count-x]);
      if (arr[count - x] == 2) {
        rightTurn();
        arr[count - x] = 0;

      }
      if (arr[count - x] == -2) {
        leftTurn();
        arr[count - x] = 0;
      }
      if (arr[count - x] == 1) {
        forward();
        arr[count - x] = 0;
      }


    }
    count = last[lstcounter];
    last[lstcounter] = 0;
    lstcounter--;
    if(togo[tgcount-1]==-2){
    leftTurn();

    }
     if(togo[tgcount-1]==2){
    rightTurn();

    }
     if(togo[tgcount-1]==1){
    forward();

    }
  }
void BackItUp(){
   bool x;
  bool prevstate;
  while (true) {

    prevstate = x;
    x = digitalRead(13);
    if (x != prevstate && x == 0 && rotation>0 ) {
      rotation--;
    }
    if (rotation>0){
      digitalWrite(lmf, LOW);
      digitalWrite(rmf, LOW);
       digitalWrite(lmb, HIGH);
      digitalWrite(rmb, HIGH);
      }
       else {
      digitalWrite(lmf, LOW);
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
      digitalWrite(rmb, LOW);
      break;
    }

  }
}
void visitall() {
  Serial.println("visitall");
  delay(1000);
  long duration_r, cm_r, duration_l, cm_l, duration_s, cm_s; 
 

  digitalWrite(trigPin_l, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_l, LOW);
  duration_l = pulseIn(echoPin_l, HIGH);
  cm_l = microsecondsToCentimeters(duration_l);
  if (cm_l > 1000) {
    cm_l = 500;
  }

  digitalWrite(trigPin_r, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_r, LOW);
  duration_r = pulseIn(echoPin_r, HIGH);
  cm_r = microsecondsToCentimeters(duration_r);
  if (cm_r > 1000) {
    cm_r = 500;
  }

  digitalWrite(trigPin_s, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_s, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_s, LOW);
  duration_s = pulseIn(echoPin_s, HIGH);
  cm_s = microsecondsToCentimeters(duration_s);
  if (cm_s > 1000) {
    cm_s = 500;
  }

  Serial.print("front: ");
  Serial.print(cm_s);
  Serial.print(" left: ");
  Serial.print(cm_l);
  Serial.print(" right: ");
  Serial.println(cm_r);
  if (cm_l >= 15) {
    left = true;

  }
  if(cm_l <= 15){
    left = false;

  }
  if (cm_r >= 15) {
    right = true;

  }
  if (cm_r <= 15) {
    right = false;

  }
  
  if (cm_s >= 18) {
    front = true;
  }
  if (cm_s <= 18) {
    front = false;
  }
 
  
 

  if (front == true) {
    forward();
    visitall();
    BackItUp();
     }
      if (right == true) {
    rightTurn();
    forward();
    leftTurn();
    visitall();
    rightTurn();
    BackItUp();
    leftTurn();
  }
   if (left == true) {
    leftTurn();
    forward();
    rightTurn();
    visitall();
    leftTurn();
    BackItUp();
    rightTurn();
  }

}
