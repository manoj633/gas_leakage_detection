#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(9, 10);
int Sensor = 7;
int Speaker = 8;
int gas_value, gas_alert_val, gas_shut_val;
int gas_leak_status;
int sms_count = 0;

void setup()
{
  pinMode(Sensor, INPUT);
  pinMode(Speaker, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  delay(500);
}

void loop()
{
  checkgas();
  CheckshutDown();
  Serial.println(gas_value);
}

void checkgas()
{
  lcd.setCursor(0, 0);
  lcd.print("gas Scan-ON");
  gas_alert_val = digitalRead(Sensor);
  if (gas_alert_val == 1)
  {
    SetAlert();
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("no gas leaking");
  }
}

void SetAlert()
{
  digitalWrite(Speaker, HIGH);
  while (sms_count < 3)
  {
    SendTextMessage();
  }
  gas_leak_status = 1;
  lcd.setCursor(0, 1);
  lcd.print("gas alert! sms sent!");
}

void CheckshutDown()
{
  if (gas_leak_status = 0)
  {
    lcd.setCursor(0, 1);
    lcd.print("no gas leaking");
    digitalWrite(Speaker, LOW);
    sms_count = 0;
    gas_leak_status = 0;
  }
}

void SendTextMessage()
{
  mySerial.println("AT+CGMS=\"+phone_number\"\r");
  delay(1000);
  mySerial.println("Gas leaking!");
  delay(200);
  mySerial.println((char)26);
  delay(1000);
  sms_count++;
}
