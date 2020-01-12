const int rmb = 6;      //Left motor forward
const int rmf = 5;      //Left motor backward
const int lmb = 8;      //Right motor forward
const int lmf = 7;      //Right motor backward
const int ultra_l = 4;  //right sensor trigger pin
const int ultra_f = 3;  //right sensor echo pin
const int ultra_r = 2;  //left sensor trigger pin
const int ultra_b = 10; //sraight sensor echo pin

int rotation = 0;
int degree = 0;
int glength = 0;
String direction = "f";
#define outputA 9
#define outputB 2

int checkpoint = 0;
bool dleft = false;
bool dright = false;
bool dfront = false;
int hazarder = 0;
int victimer = 0;
int gogoagone[64][2];
void setup()
{
  Serial.begin(9600);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(ultra_l, OUTPUT);
  pinMode(ultra_f, OUTPUT);
  pinMode(ultra_r, OUTPUT);
  pinMode(9, INPUT);
  pinMode(2, INPUT);
  pinMode(20, INPUT);

 visitall(0, 0);
}

void loop()
{
  /*rightTurn();
  delay(1000);
  leftTurn();
  delay(1000);
*/
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void Front(int x, int y)
{
  forward();
  if (direction == "f")
  {
    x += 1;
  }
  if (direction == "b")
  {
    x -= 1;
  }
  if (direction == "l")
  {
    y += 1;
  }
  if (direction == "r")
  {
    y -= 1;
  }
  visitall(x, y);
  retreat();
}
void cursedRight(int x, int y)
{
  rightTurn();
  forward();
  if (direction == "f")
  {
    x += 1;
  }
  if (direction == "b")
  {
    x -= 1;
  }
  if (direction == "l")
  {
    y += 1;
  }
  if (direction == "r")
  {
    y -= 1;
  }
  visitall(x, y);
 // leftTurn();
  
  retreat();
   delay(500);

  leftTurn();
}
void cursedLeft(int x, int y)
{
  leftTurn();
  forward();
  if (direction == "f")
  {
    x += 1;
  }
  if (direction == "b")
  {
    x -= 1;
  }
  if (direction == "l")
  {
    y += 1;
  }
  if (direction == "r")
  {
    y -= 1;
  }
   // rightTurn();
  visitall(x, y);
   // leftTurn();
 
  retreat();
    delay(500);

  rightTurn();
}
void visitall(int x, int y)
{
  gogoagone[glength][0] = x;
  gogoagone[glength][1] = y;
  glength++;
  Serial.println("visitall");
  delay(500);
  measure();

  if (dfront == true && dleft == false && dright == false)
  {
    if (valid(x, y, "f"))
    {
      Front(x, y);
    }
  }
  if (dright == true && dleft == false && dfront == false)
  {
    if (valid(x, y, "r"))
    {
      cursedRight(x, y);
    }
  }
  if (dleft == true && dright == false && dfront == false)
  {
    if (valid(x, y, "l"))
    {
      cursedLeft(x, y);
    }
  }
  if (dright == true && dleft == true && dfront == false)
  {
    if (valid(x, y, "r"))
    {
      cursedRight(x, y);
    }
    if (valid(x, y, "l"))
    {

      cursedLeft(x, y);
    }
  }
  if (dright == true && dleft == false && dfront == true)
  {
    if (valid(x, y, "f"))
    {

      Front(x, y);
    }
    if (valid(x, y, "r"))
    {

      cursedRight(x, y);
    }
  }
  if (dright == false && dleft == true && dfront == true)
  {
    if (valid(x, y, "f"))
    {
      Front(x, y);
    }
    if (valid(x, y, "l"))
    {
      cursedLeft(x, y);
    }
  }
  if (dright == true && dleft == true && dfront == true)
  {

    if (valid(x, y, "f"))
    {
      Front(x, y);
    }
    if (valid(x, y, "r"))
    {
      cursedRight(x, y);
    }
    if (valid(x, y, "l"))
    {
      cursedLeft(x, y);
    }
  }
}

bool valid(int x, int y, String s){
  int tx;
  int ty;
  if (s == "f")
  {
    if (direction == "f")
    {
    tx = x + 1;
    }
    if (direction == "b")
    {
    tx = x - 1;
    }
    if (direction == "l")
    {
    ty = y + 1;
    }
    if (direction == "r")
    {
    ty =y- 1;
    }
  }
  if (s == "l")
  {
if (direction == "f")
    {
    ty = y + 1;
    }
    if (direction == "b")
    {
      ty =y- 1;
    }
    if (direction == "l")
    {
      tx =x- 1;
    }
    if (direction == "r")
    {
      tx =x+1;
    }
  }
  if (s == "r")
  {
if (direction == "f")
    {
    ty = y- 1;
    }
    if (direction == "b")
    {
      ty=y+ 1;
    }
    if (direction == "l")
    {
      tx =x+ 1;
    }
    if (direction == "r")
    {
      tx =x-1;
    }  }

  for (int i = 0; i < glength; i++)
  {
    if (gogoagone[i][0] == tx && gogoagone[i][1] == ty)
    {
      return false;
    }
    Serial.print("x:");
    Serial.print(gogoagone[i][0]);
    Serial.print("y:");
    Serial.print(gogoagone[i][1]);
  }

  return true;
}
void measure()
{
  pinMode(ultra_l, OUTPUT);
  pinMode(ultra_f, OUTPUT);
  pinMode(ultra_r, OUTPUT);
  pinMode(ultra_b, OUTPUT);

  bool right = false;
  bool left = false;
  bool front = false;
  bool back = false;

  long duration_r, cm_r, duration_l, cm_l, duration_s, cm_s, duration_b, cm_b;

  digitalWrite(ultra_l, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_l, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultra_l, LOW);
  pinMode(ultra_l, INPUT);
  duration_l = pulseIn(ultra_l, HIGH);
  cm_l = microsecondsToCentimeters(duration_l);
  if (cm_l > 1000)
  {
    cm_l = 500;
  }

  digitalWrite(ultra_r, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_r, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultra_r, LOW);
  pinMode(ultra_r, INPUT);
  duration_r = pulseIn(ultra_r, HIGH);
  cm_r = microsecondsToCentimeters(duration_r);
  if (cm_r > 1000)
  {
    cm_r = 500;
  }

  digitalWrite(ultra_f, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_f, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultra_f, LOW);
  pinMode(ultra_f, INPUT);
  duration_s = pulseIn(ultra_f, HIGH);
  cm_s = microsecondsToCentimeters(duration_s);
  if (cm_s > 1000)
  {
    cm_s = 500;
  }
  /*digitalWrite(ultra_b, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_b, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultra_b, LOW);
      pinMode(ultra_b, INPUT);
  duration_b = pulseIn(ultra_b, HIGH);
  cm_b = microsecondsToCentimeters(duration_b);
  if (cm_b > 1000)
  {
    cm_b = 500;
  }*/

  if (cm_l >= 15)
  {
    left = true;
  }
  else
  {
    left = false;
  }
  if (cm_r >= 15)
  {
    right = true;
  }
  else
  {
    right = false;
  }

  if (cm_s >= 15)
  {
    front = true;
  }
  else
  {
    front = false;
  }
  Serial.print("front:");
  Serial.println(cm_s);
  Serial.print("left:");
  Serial.println(cm_l);
  Serial.print("right:");
  Serial.println(cm_r);
  /*if (direction == "f")
  {*/
  dfront = front;
  dleft = left;
  dright = right;
  /*}

  if (direction == "l")
  {
    dfront = right;
    dleft = front;
    dright = back;
  }
  if (direction == "r")
  {
    dfront = left;
    dleft = back;
    dright = front;
  }
  if (direction == "b")
  {
    dright = back;
    dleft = right;
    dleft = left;
  }*/
}
void leftTurn()
{
  if (direction == "f")
  {
    direction = "l";
  }
  else if (direction == "l")
  {
    direction = "b";
  }
  else if (direction == "b")
  {
    direction = "r";
  }
  else if (direction == "r")
  {
    direction = "f";
  }

  bool x;
  bool prevstate;
  degree = 0;

  int stripe = 14;

  while ((true))
  {
    // put your main code here, to run repeatedly:
    prevstate = x;
    x = digitalRead(9);
    if (x != prevstate && x == 1)
    {
      degree++;
    }
    if (degree <= stripe)
    {
      analogWrite(rmf, 100);
      analogWrite(lmb, 100);
      digitalWrite(rmb, LOW);
      digitalWrite(lmf, LOW);
    }
    else
    {
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
      delay(500);
      break;
    }
  }
}
void uturn()
{
  if (direction == "f")
  {
    direction = "b";
  }
  else if (direction == "l")
  {
    direction = "r";
  }
  else if (direction == "b")
  {
    direction = "f";
  }
  else if (direction == "r")
  {
    direction = "l";
  }
  bool x;
  bool prevstate;
  float distance = 0;
  int stripe = 32;
  degree = 0;
  while ((true))
  {
    prevstate = x;
    x = digitalRead(9);
    if (x != prevstate && x == 1)
    {
      degree++;
    }
    if (degree <= stripe)
    {
      analogWrite(lmf, 100);
      analogWrite(rmb, 100);
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
    }
    else
    {

      digitalWrite(lmf, LOW);
      digitalWrite(rmb, LOW);
      break;
    }
  }
}

void rightTurn()
{
  if (direction == "f")
  {
    direction = "r";
  }
  else if (direction == "r")
  {
    direction = "b";
  }
  else if (direction == "b")
  {
    direction = "l";
  }
  else if (direction == "l")
  {
    direction = "f";
  }
  bool x;
  bool prevstate;
  degree = 0;
  int stripe = 14;
  while ((true))
  {
    // put your main code here, to run repeatedly:
    prevstate = x;
    x = digitalRead(9);
    if (x != prevstate && x == 1)
    {
      degree++;
    }
    if (degree <= stripe)
    {
      analogWrite(lmf, 100);
      analogWrite(rmb, 100);
      digitalWrite(rmf, LOW);
      digitalWrite(lmb, LOW);
    }

    else
    {
      digitalWrite(lmf, LOW);
      digitalWrite(rmb, LOW);
      delay(500);
      break;
    }
  }
}
void forward()
{
  bool x;
  bool prevstate;
  rotation = 0;
  bool stoper = false;
  int distance;
  unsigned long duration_s,cm_s;
  while (true)
  {
   /*   pinMode(ultra_f, OUTPUT);

    digitalWrite(ultra_f, LOW);
  delayMicroseconds(2);
  digitalWrite(ultra_f, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultra_f, LOW);
  pinMode(ultra_f, INPUT);
  duration_s = pulseIn(ultra_f, HIGH);
  cm_s = microsecondsToCentimeters(duration_s);
  if (cm_s > 1000)
  {
    cm_s = 500;
  }if (cm_s <= 7) {
      stopBot();
      break;
    }*/
    prevstate = x;
    x = digitalRead(9);
    if (x != prevstate && x == 0)
    {
      rotation++;
    }
    distance = rotation * 21 / 20;

    if (distance <= 29)
    {
      analogWrite(lmf, 100);
      analogWrite(rmf, 100);
      digitalWrite(lmb, LOW);
      digitalWrite(rmb, LOW);
    }
    else
    {
      stopBot();
      delay(500);
      break;
    }
  }
}

void stopBot()
{
  analogWrite(lmb, 0);
  analogWrite(rmb, 0);
  analogWrite(lmf, 0);
  analogWrite(rmf, 0);
}
void retreat() // Cool Your Name
{
  bool x;
  bool prevstate;
  rotation = 0;
  bool stoper = false;
  int distance = 0;
  while (true)
  {
    prevstate = x;
    x = digitalRead(9);
    if (x != prevstate && x == 1)
    {
      rotation++;
    }
    distance = rotation * 21 / 20;

    if (distance <= 28)
    {
      analogWrite(lmb, 100);
      analogWrite(rmb, 100);
      digitalWrite(lmf, LOW);
      digitalWrite(rmf, LOW);
    }
    else
    {
      stopBot();
      delay(500);
      break;
    }
  }
}
