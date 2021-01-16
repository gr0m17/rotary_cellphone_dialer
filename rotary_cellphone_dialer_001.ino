int pulseState;

int lastpulseState;

int PulseCount;
int dialDigit;
int cycleCount;
String dialNumber;
void setup()
{
  lastpulseState = HIGH;
  pinMode(8, INPUT);
  Serial.begin(9600);
  dialNumber = String();
}


void loop()
{
  if (dialNumber.length() < 10) {
    pulseState = digitalRead(8);
    
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
}
