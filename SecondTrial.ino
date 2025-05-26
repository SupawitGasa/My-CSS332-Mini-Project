#include <Servo.h>
#include <Keypad.h>

const int servo_pin = 13;
const int trig_pin = 11;
const int echo_pin = 12;
const int buzzer_pin = 10;
const int password = 1234;

int input_password = 0;
long duration;
float distance;
int wrong_times = 0;

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char Layout[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad mykeypad = Keypad(makeKeymap(Layout), rowPins, colPins, ROWS, COLS);
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servo_pin);
  myservo.write(0);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, HIGH);
}

void loop() {
  // measure the distance
  while (true)
  {
    delay(1000);
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    
    duration = pulseIn(echo_pin, HIGH);
    distance = get_distance_cm(duration);

    if (distance <= 10)
    {
      break;
    }
    else
    {
      continue;
    }
  }
  // enter the input password:
  char mykey;
  Serial.print("\nEnter the correct password (press # to confirm): ");
  while (true)
  {
    mykey = mykeypad.getKey();
    if (mykey == '#')
    {
      Serial.println(input_password);
      break;
    }
    else if (mykey)
    {
      input_password *= 10;
      input_password += (int) mykey;
      input_password -= 48;
    }
    else
    {
      continue;
    }
  }
  // verify the input password:
  if (input_password == password)
  {
    Serial.println("\nCorrect password :)");
    Serial.println("The door is opening ...");
    delay(2000);
    myservo.write(90);
    Serial.println("\nIf you want to close the door, please press *");
    while (true)
    {
      mykey = mykeypad.getKey();
      if (mykey == '*')
      {
        delay(2000);
        myservo.write(0);
        break;
      }
      else
      {
        continue;
      }
    }
  }
  else
  {
    wrong_times += 1;
    Serial.println("\nIncorrect password ! Try Again.");
    Serial.print("Number of wrong times: ");
    Serial.println(wrong_times);
    myservo.write(0);

  }
  input_password = 0;
  // check the buzzer condition:
  if (wrong_times == 5)
  {
    wrong_times = 0;
    // Buzzer is working:
    buzzer_works();
  }
}

float get_distance_cm(long time)
{
  float dcm = (0.0343*time)/2;
  return dcm;
}

void buzzer_works()
{
  for (int i=0; i<5; i++)
  {
    digitalWrite(buzzer_pin, LOW);
    delay(1000);
    digitalWrite(buzzer_pin, HIGH);
    delay(1000);
  }
}