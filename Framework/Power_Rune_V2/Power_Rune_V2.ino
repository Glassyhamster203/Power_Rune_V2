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

#define LED_STRIP_COLUMN 8
#define LED_STRIP_ROW 40

#define LED_BRI

char *ssid = (char *)"robomasterserver"; //添加了(char*)
char *password = (char *)"12345678";     //

bool HitFlag = 0;

CRGB Main_LEDS[Main_LED_NUM];
CRGB Side_LEDS[Side_LED_NUM];
CRGB Panel_LEDS[Panel_LED_NUM];

void Main_LED(void *arg);
void LED_Test();

void Main_LED(void *arg)
{
    /*
                000111000
                000011100
                000001110
                000000111
                000000111
                000001110
                000011100
                000111000
                */
    
    bool Matrix[LED_STRIP_COLUMN][LED_STRIP_ROW];
    for (int detal = 0;detal < count; i++)
    {
        /* code */
    }
    
    for (int i = 0; i < ; i++)
    {
        switch ((i + detal) % 9)
        {
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
        case 6:
        case 7:
        case 8:
        }

        vTaskDelay(1000);
    }

    // vTaskDelay(1000);
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

void setup()
{
    LEDS.addLeds<LED_TYPE, Main_LED_PIN, COLOR_ORDER>(Main_LEDS, Main_LED_NUM);
    LEDS.addLeds<LED_TYPE, Side_LED_PIN, COLOR_ORDER>(Side_LEDS, Side_LED_NUM);
    LEDS.addLeds<LED_TYPE, Panel_LED_PIN, COLOR_ORDER>(Panel_LEDS, Panel_LED_NUM);
    LED_Test();
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    vTaskStartScheduler();
    // xTaskCreate(Main_LED, "Main_LED", 2048, NULL, 4, NULL);
}

void loop()
{
}
