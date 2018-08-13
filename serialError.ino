#define ARDUINO_TURNED_LED_ON "LEDON"
#define ARDUINO_TURNED_LED_OFF "LEDOFF"
#define PC_REQUESTED_LED_STATE_CHANGE u8"CHANGELED"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);

}

String serialCmd = "";
bool ledState=false;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    serialCmd=Serial.readString();

    if (serialCmd==PC_REQUESTED_LED_STATE_CHANGE)
    {
      if (ledState)
      {
        digitalWrite(13, LOW);
        Serial.write(ARDUINO_TURNED_LED_OFF);
      }
      else
      {
        digitalWrite(13, HIGH);
        Serial.write(ARDUINO_TURNED_LED_ON);
      };

      ledState=!ledState;
      serialCmd="";
      
    }
    
  }

}
