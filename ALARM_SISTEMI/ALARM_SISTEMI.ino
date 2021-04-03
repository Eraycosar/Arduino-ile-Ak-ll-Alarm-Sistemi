#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = "PoEXQhfryg6MphfVFJHZaoq1yFehR8yK";
char ssid[] = "TTNET_ERAY";
char pass[] = "ibrahimeray";
#define EspSerial Serial1
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
BlynkTimer timer;

#define yesilled 5
#define kirmiziled 7
#define pir 13
#define buzzer 2

int hareket;
String h;

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  
  if(pinValue == HIGH)
  {
    hareket = digitalRead(pir);
    h="ALARM AKTIF";
    Serial.println("ALARM AKTİF");
    Blynk.virtualWrite(V2, h);

    if(hareket == HIGH)
    {
      Blynk.notify("HAREKET TESPİT EDİLDİ !");
      Blynk.email("eraycosar@hotmail.com", "ALARM SİSTEMİ", "HAREKET TESPİT EDİLDİ !");
      h="HAREKET TESPİT EDİLDİ !";
      Blynk.virtualWrite(V2, h);
      Serial.println("HAREKET TESPİT EDİLDİ !");
      digitalWrite(yesilled, LOW);
      digitalWrite(kirmiziled, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(350);
      digitalWrite(kirmiziled, LOW);
      digitalWrite(buzzer, LOW);
      delay(10);
    }
    else
    {
      digitalWrite(yesilled, HIGH);
      digitalWrite(kirmiziled, LOW);
    }
  }
  else
  {
    h="ALARM KAPALI";
    Serial.println("ALARM KAPALI");
    Blynk.virtualWrite(V2, h);
    digitalWrite(yesilled, LOW);
    digitalWrite(kirmiziled, LOW);
    noTone(buzzer);
  }
  Blynk.run(); 
  pinValue = 0; 
  Blynk.syncVirtual(V1);
}

void setup() 
{
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);

  pinMode(yesilled, OUTPUT);
  pinMode(kirmiziled, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pir, INPUT);
}

void loop() 
{
  Blynk.run(); 
  timer.run();
}
