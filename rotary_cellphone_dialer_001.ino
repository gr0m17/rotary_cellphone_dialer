int pulseState;

int lastpulseState;
int dialerPin;
int hookPin;
int hookState;
int PulseCount;
int dialDigit;
int cycleCount;
String dialNumber;
void setup()
{
  dialerPin = 8;
  hookPin = 10;
  lastpulseState = HIGH;
  pinMode(dialerPin, INPUT);
  pinMode(hookPin, INPUT);

  Serial.begin(9600);
  dialNumber = String();
}


void loop()
{
  hookState = digitalRead(hookPin);
  if (hookState == LOW) {
//    Serial.println("hook lifted");
    if (dialNumber.length() < 10) {
      pulseState = digitalRead(dialerPin);

      if (pulseState != lastpulseState) {

        if (pulseState == HIGH) {

          Serial.println("ON ------------------");
          PulseCount = PulseCount + 1;

          Serial.println("Pulses: ");
          Serial.println(PulseCount);

        }
        if (pulseState == LOW) {
          Serial.println("OFF -------------------");

        }
        delay(50);
        lastpulseState = pulseState;
        cycleCount = 0;

      } else {
        //    Serial.println("Pulse Cycle:");
        cycleCount = cycleCount + 1;
        //    Serial.println(cycleCount);
        delay(10);


        if (cycleCount >= 20) {

          if (PulseCount > 0) {

            Serial.println("Dialed:");
            Serial.println(PulseCount);

            if (PulseCount == 10) {
              Serial.println("pulsecount=10");
              dialDigit = 0;
            } else {
              dialDigit = PulseCount;
            }
            dialNumber = dialNumber + dialDigit;
            Serial.println("dialNumber: ");
            Serial.println(dialNumber);
            PulseCount = 0;
          }
        }
      }
    } else {

      Serial.print("Number Recieved! Dialing:");
      Serial.print(dialNumber);
      Serial.println(" ");
      Serial.println("----");
      delay(2000);
      Serial.println("clearing dialNumber.");
      dialNumber = "";
    }
  } else {
    Serial.println("Hook Down");
    Serial.println("clearing dialNumber.");
      dialNumber = "";
  }
}
