int sw = 2;
int led1 = 6;
int led2 = LED_BUILTIN;

bool alreadyRun = false;   // to stop repeating

void setup()
{
  pinMode(sw, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop()
{
  int state = digitalRead(sw);

  if (state == LOW && alreadyRun == false)
  {
    // turn both ON
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);

    delay(30000);  // 30 sec

    digitalWrite(led1, LOW);  // first off

    delay(30000);  // another 30 sec

    digitalWrite(led2, LOW);  // second off

    alreadyRun = true;  // stop repeating
  }

  
  if (state == HIGH)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    alreadyRun = false;
  }
}
