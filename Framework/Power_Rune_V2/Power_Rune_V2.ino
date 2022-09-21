#include <FastLED.h>
#include <ArduinoJson.h>
#include <freertos/FreeRTOS.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

#define SelfID 1
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#define Main_LED_PIN GPIO_NUM_16
#define Main_LED_NUM 320

#define Side_LED_PIN GPIO_NUM_21
#define Side_LED_NUM 70

#define Panel_LED_PIN GPIO_NUM_17
#define Panel_LED_NUM 60

#define ADC_Val 1000
#define HIT_SENSOR_PORT GPIO_NUM_33

#define LED_STRIP_COLUMN 8 //列
#define LED_STRIP_ROW 40   //行

#define LED_BRI

char *ssid = (char *)"robomasterserver"; //添加了(char*)
char *password = (char *)"12345678";     //

CRGB Main_LEDS[Main_LED_NUM];
CRGB Side_LEDS[Side_LED_NUM];
CRGB Panel_LEDS[Panel_LED_NUM];
bool Matrix[LED_STRIP_COLUMN][LED_STRIP_ROW];
bool StartFlag = 0;
bool HitFlag = 0;
int UdpPort = 2333;
int ReturnUdpPort = 2334;

void Main_LED(void *arg);
void LED_Test();
void LED_Refresh();
void Net_task();
void LED_Reset();
int R_Val = 0;
int G_Val = 0;
int B_Val = 255;
CRGB Color(R_Val, G_Val, B_Val);

void Main_LED(void *arg)
{
    int shift = 0;
    while (1)
    {
        if (StartFlag && !HitFlag)
        {
            for (int row_count = 0; row_count < 9; row_count++)
            {
                for (int i = 0; i < LED_STRIP_ROW; i++)
                {
                    switch (i % 9 + row_count)
                    { /*
                     000111000
                     000011100
                     000001110
                     000000111
                     000000111
                     000001110
                     000011100
                     000111000
                     */
                    //学长写的,直接抄了
                    case 0:
                    {
                        Matrix[i][0] = 0;
                        Matrix[i][1] = 0;
                        Matrix[i][2] = 0;
                        Matrix[i][3] = 1;
                        Matrix[i][4] = 1;
                        Matrix[i][5] = 0;
                        Matrix[i][6] = 0;
                        Matrix[i][7] = 0;
                    }
                    break;

                    case 1:
                    {
                        Matrix[i][0] = 0;
                        Matrix[i][1] = 0;
                        Matrix[i][2] = 1;
                        Matrix[i][3] = 1;
                        Matrix[i][4] = 1;
                        Matrix[i][5] = 1;
                        Matrix[i][6] = 0;
                        Matrix[i][7] = 0;
                    }
                    break;
                    case 2:
                    {
                        Matrix[i][0] = 0;
                        Matrix[i][1] = 1;
                        Matrix[i][2] = 1;
                        Matrix[i][3] = 1;
                        Matrix[i][4] = 1;
                        Matrix[i][5] = 1;
                        Matrix[i][6] = 1;
                        Matrix[i][7] = 0;
                    }
                    break;
                    case 3:
                    {
                        Matrix[i][0] = 1;
                        Matrix[i][1] = 1;
                        Matrix[i][2] = 1;
                        Matrix[i][3] = 0;
                        Matrix[i][4] = 0;
                        Matrix[i][5] = 1;
                        Matrix[i][6] = 1;
                        Matrix[i][7] = 1;
                    }
                    break;
                    case 4:
                    {
                        Matrix[i][0] = 1;
                        Matrix[i][1] = 1;
                        Matrix[i][2] = 0;
                        Matrix[i][3] = 0;
                        Matrix[i][4] = 0;
                        Matrix[i][5] = 0;
                        Matrix[i][6] = 1;
                        Matrix[i][7] = 1;
                    }
                    break;
                    case 5:
                    {
                        Matrix[i][0] = 1;
                        Matrix[i][1] = 0;
                        Matrix[i][2] = 0;
                        Matrix[i][3] = 0;
                        Matrix[i][4] = 0;
                        Matrix[i][5] = 0;
                        Matrix[i][6] = 0;
                        Matrix[i][7] = 1;
                    }
                    break;
                    default:
                    {

                        for (int j = 0; j < LED_STRIP_COLUMN; j++)
                        {
                            Matrix[i][j] = 0;
                        }
                        break;
                    }
                        if (i = LED_STRIP_ROW)
                        {
                            LED_Refresh();
                        }
                    }

                    vTaskDelay(1000);
                }
            }
        }
    }

    // vTaskDelay(1000);
}
void LED_Refresh()
{
    int k = 0;
    for (int i = LED_STRIP_COLUMN; i > 0; i--)
    {
        for (int j = LED_STRIP_ROW; j > 0; j--)
        {
            if (Matrix[i][j])
            {
                k = i * 8 + j;
                Main_LEDS[k] = Color;
            }
        }
    }
}
void LED_Test()
{
    for (int i = 0; i < Main_LED_NUM; i++)
    {
        Main_LEDS[i] = Color;
        FastLED.show();
        vTaskDelay(1);
    }

    for (int i = 0; i < Side_LED_NUM; i++)
    {
        Side_LEDS[i] = Color;
        FastLED.show();
        vTaskDelay(1);
    }

    for (int i = 0; i < Panel_LED_NUM; i++)
    {
        Panel_LEDS[i] = Color;
        FastLED.show();
        vTaskDelay(1);
    }
}
void LED_Reset()
{
    for (int i = 0; i < Main_LED_NUM; i++)
    {
        Main_LEDS[i] = CRGB::Black;
    }

    for (int i = 0; i < Side_LED_NUM; i++)
    {
        Side_LEDS[i] = CRGB::Black;
    }

    for (int i = 0; i < Panel_LED_NUM; i++)
    {
        Panel_LEDS[i] = CRGB::Black;
    }
    FastLED.show();
}
void Main_Reset()
{
    for (int i = 0; i < Main_LED_NUM; i++)
    {
        Main_LEDS[i] = CRGB::Black;
    }
    FastLED.show();
}
void Net_task(void *arg)
{
    WiFiUDP UdpConnect;
    WiFiUDP ReturnUdp;

    UdpConnect.begin(UdpPort);
    ReturnUdp.begin(ReturnUdpPort);

    Serial.println("Udp is ready!");
    DynamicJsonDocument json(1024);
    String UdpData = "";

    UdpConnect.readString();
    while (1)
    {
        while (Serial.available() > 0)
        {
            UdpData += char(Serial.read());
        }
        if (UdpData != "")
        {

            // For serial debug
            // UdpData = UdpConnect.readString(); // read the data form udp sever

            DeserializationError err = deserializeJson(json, UdpData);
            if (err)
            {
                Serial.printf("Json Error");
            }
            else
            {
                if (json["id"] = SelfID)
                { // Udp 命令行
                    Serial.println("ready");
                    if (json["command"] = "start" && !StartFlag)
                    {
                        StartFlag = 1;
                        fill_solid(Panel_LEDS, Panel_LED_NUM, Color);
                        FastLED.show();
                        Serial.println("Started!");
                    }
                    if (json["command"] = "stop")
                    {
                        ReturnUdp.beginPacket("255.255.255.255", ReturnUdpPort);
                        ReturnUdp.print("{\"id\":" + String(SelfID) + ",\"status\":\"off\"}");
                        ReturnUdp.endPacket();
                        StartFlag = 0;
                        fill_solid(Panel_LEDS, Panel_LED_NUM, CRGB::Black);
                    }
                    if (json["command"] = "on")
                    {
                        Serial.println("ON");
                        StartFlag = 0;
                        fill_solid(Main_LEDS, Main_LED_NUM, CRGB::Black);
                        fill_solid(Panel_LEDS, Panel_LED_NUM, Color);
                        fill_solid(Side_LEDS, Side_LED_NUM, Color);
                    }
                    if (json["command"] = "color")
                    {
                        StartFlag = 1;
                        R_Val = json["R"].as<int>();
                        G_Val = json["G"].as<int>();
                        B_Val = json["B"].as<int>();
                    }
                }
                if (analogRead(HIT_SENSOR_PORT) >= ADC_Val && StartFlag)
                { //传感器部分
                    HitFlag = 1;
                    Serial.println("hit");
                    StartFlag = 0;
                    ReturnUdp.beginPacket("255.255.255.255", ReturnUdpPort);
                    ReturnUdp.print("{\"id\":" + String(SelfID) + ",\"status\":\"hit\"}");
                    ReturnUdp.endPacket();
                }
            }
        }
    }
}
void setup()
{
    LEDS.addLeds<LED_TYPE, Main_LED_PIN, COLOR_ORDER>(Main_LEDS, Main_LED_NUM);
    LEDS.addLeds<LED_TYPE, Side_LED_PIN, COLOR_ORDER>(Side_LEDS, Side_LED_NUM);
    LEDS.addLeds<LED_TYPE, Panel_LED_PIN, COLOR_ORDER>(Panel_LEDS, Panel_LED_NUM);
    LED_Test();
    LED_Reset();
    
    delay(100);
    pinMode(HIT_SENSOR_PORT, INPUT);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA); 
    WiFi.begin(ssid, password);
    // vTaskStartScheduler();
    Serial.println("Booted");
    xTaskCreate(Main_LED, "Main_LED", 2048, NULL, 4, NULL);
    xTaskCreate(Net_task, "Net_task", 2048, NULL, 3, NULL);
    vTaskStartScheduler();
    
    
}

void loop()
{
}
