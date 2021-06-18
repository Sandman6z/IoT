#include <ESP8266WiFi.h>
#include <aJSON.h>
//=============  此处必须修该============
String DEVICEID = "14174"; //你的设备编号==
String APIKEY = "fccd78312"; //设备密码==
const char* ssid = "Sandman"; //WiFi名称
const char* password = "key147852369zbn"; //WiFi密码
//=======================================
#define OUT 0//输出控制继电器端口
//=======================================
unsigned long lastCheckInTime = 0; //记录上次报到时间
const unsigned long postingInterval = 40000; //每隔40秒向服务器报到一次
const char* host = "www.bigiot.net";
const int httpPort = 8181;
WiFiClient client;
void setup()
{
  pinMode(OUT, OUTPUT); //设置输出
  digitalWrite(OUT, LOW); //上电打开输出
  pinMode(LED_BUILTIN, OUTPUT); //设备板载LED输出模式
  digitalWrite(LED_BUILTIN, HIGH); //关闭LED
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  WiFi.begin(ssid, password); //连接WiFi
  while (WiFi.status() != WL_CONNECTED) //等待WiFi连接成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
}
void loop()
{
  // Use WiFiClient class to create TCP connections
  if (!client.connected())
  {
    if (!client.connect(host, httpPort))
    {
      Serial.println("connection failed");
      delay(5000);
      return;
    }
  }
  if (millis() - lastCheckInTime > postingInterval || lastCheckInTime == 0)
    checkIn();

  // Read all the lines of the reply from server and print them to Serial
  if (client.available())
  {
    String inputString = client.readStringUntil('\n');
    inputString.trim();
    Serial.println(inputString);
    int len = inputString.length() + 1;
    if (inputString.startsWith("{") && inputString.endsWith("}"))
    {
      char jsonString[len];
      inputString.toCharArray(jsonString, len);
      aJsonObject *msg = aJson.parse(jsonString);
      processMessage(msg);
      aJson.deleteItem(msg);
    }
  }
}
void processMessage(aJsonObject *msg)
{
  aJsonObject* method = aJson.getObjectItem(msg, "M");
  aJsonObject* content = aJson.getObjectItem(msg, "C");
  aJsonObject* client_id = aJson.getObjectItem(msg, "ID");
  if (!method)
    return;
  String M = method->valuestring;
  if (M == "say")
  {
    String C = content->valuestring;
    String F_C_ID = client_id->valuestring;
    digitalWrite(LED_BUILTIN, LOW); //接收到指令就闪一下LED
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    if (C == "stop") //接收到的是停止指令
    {
      digitalWrite(OUT, LOW); //关闭
      sayToClient(F_C_ID, "LED All off!");
    }
    else//接收到的不是停止指令
    {
      digitalWrite(OUT, HIGH); //打开
      sayToClient(F_C_ID, "LED All on!");
    }
  }
}
void checkIn()
{
  String msg = "{\"M\":\"checkin\",\"ID\":\"" + DEVICEID + "\",\"K\":\"" + APIKEY + "\"}\n";
  client.print(msg);
  lastCheckInTime = millis();
}
void sayToClient(String client_id, String content)
{
  String msg = "{\"M\":\"say\",\"ID\":\"" + client_id + "\",\"C\":\"" + content + "\"}\n";
  client.print(msg);
  lastCheckInTime = millis();
}
