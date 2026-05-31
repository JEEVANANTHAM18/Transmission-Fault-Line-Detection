#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Transmission Line Fault Detection"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Enter your Wi-Fi credentials
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ----- Transmission Line Pins -----
int L1 = 4;
int L2 = 5;
int L3 = 21;

// ----- Output Pins -----
int relay = 23;
int buzzer = 19;

void setup()
{
  Serial.begin(115200);

  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);

  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(relay, HIGH);
  digitalWrite(buzzer, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();

  int line1 = digitalRead(L1);
  int line2 = digitalRead(L2);
  int line3 = digitalRead(L3);

  Blynk.virtualWrite(V0, (line1 == HIGH) ? 0 : 1);
  Blynk.virtualWrite(V1, (line2 == HIGH) ? 0 : 1);
  Blynk.virtualWrite(V2, (line3 == HIGH) ? 0 : 1);

  if (line1 == HIGH && line2 == HIGH && line3 == HIGH)
  {
    digitalWrite(relay, LOW);
    digitalWrite(buzzer, LOW);
  }
  else
  {
    digitalWrite(relay, HIGH);
    digitalWrite(buzzer, HIGH);
  }
}