#include <FastLED.h>
#include <ArduinoJson.h>
#include <freertos/FreeRTOS.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#define SelfID 1
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#define Main_LED_PIN GPIO_NUM_16
#define Main_LED_NUM 320

#define Side_LED_PIN GPIO_NUM_21
#define Side_LED_NUM 50

#define Panel_LED_PIN GPIO_NUM_17
#define Panel_LED_NUM 40

#define ADC_Val 1000
#define ADC_PIN 2

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
void Main_LED(void *arg);
void LED_Test();
void LED_Refresh();
void Main_LED(void *arg)
{
    int shift = 0;
    while (1)
    {
        if (StartFlag && !HitFlag)
        {
            for (int i = 0; i < LED_STRIP_ROW; i++)
            {
                switch (i % 9)
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
                Main_LEDS[k] = CRGB::Blue;
            }
        }
    }
}
void LED_Test()
{
    for (int i = 0; i < Main_LED_NUM; i++)
    {
        Main_LEDS[i] = CRGB::Blue;
        FastLED.show();
        vTaskDelay(100);
    }

    for (int i = 0; i < Side_LED_NUM; i++)
    {
        Side_LEDS[i] = CRGB::Blue;
        FastLED.show();
        vTaskDelay(100);
    }

    for (int i = 0; i < Panel_LED_NUM; i++)
    {
        Panel_LEDS[i] = CRGB::Blue;
        FastLED.show();
        vTaskDelay(100);
    }
}
void Main_Reset()
{
    for (int i = 0; i < Main_LED_NUM; i++)
    {
        Main_LEDS[i] = CRGB::Black;
    }
    FastLED.show();
}
void setup()
{
    LEDS.addLeds<LED_TYPE, Main_LED_PIN, COLOR_ORDER>(Main_LEDS, Main_LED_NUM);
    LEDS.addLeds<LED_TYPE, Side_LED_PIN, COLOR_ORDER>(Side_LEDS, Side_LED_NUM);
    LEDS.addLeds<LED_TYPE, Panel_LED_PIN, COLOR_ORDER>(Panel_LEDS, Panel_LED_NUM);
    LED_Test();
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    vTaskStartScheduler();
    xTaskCreate(Main_LED, "Main_LED", 2048, NULL, 4, NULL);
}

void loop()
{
}
