#include "LedPatterns.h"

#ifdef ESP8266
#include "LedPatterns.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
ESP8266WebServer server(80);
#endif

#ifdef ESP32
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
WebServer server(80);
#endif

#define PIXELS 100
#define PIN 15

const char *ssid = "St4rbride";
const char *password = "3L3Ctr1CSh33p";

const char *key = "/joshua/";
uint8_t keyLen = 6 + 2;
uint8_t interval = 20;

LedPatterns led(PIXELS, PIN);

// Using this for routes with wild cards
void handleRoutes()
{
    char incomming[100];
    server.uri().toCharArray(incomming, 100);
    bool handled = true;

    // Check for key
    if (strncmp(key, incomming, keyLen) == 0)
    {
        String request = server.uri().substring(keyLen - 1);
        Serial.println(request);

        if (request == "/rainbow")
            led.startSimplePattern(RAINBOW_CYCLE);
        if (request == "/cyclon")
            led.startSimplePattern(CYCLON);
        else if (request == "/simplerainbow")
            led.startSimplePattern(SIMPLE_RAINBOW_CYCLE);
        // todo
        else if (request == "/off")
            led.startSimplePattern(RAINBOW_CYCLE);
        led.ColorWipe(0, 0, 0, interval);
        else if (request == "/fire")
            led.startSimplePattern(FIRE);
        led.Fire(false, interval);
        else if (request == "/pacifica")
            led.startSimplePattern(PACIFICA);
        else if (request == "/pride")
            led.startSimplePattern(PRIDE);
        else if (request == "/confetti")
            led.startSimplePattern(CONFETTI);
        else if (request == "/bpm")
            led.startSimplePattern(BPM);
        else if (request == "/twinkle")
            led.startSimplePattern(TWINKLEFOX);
        else if (request == "/juggle")
            led.startSimplePattern(JUGGLE);
        else if (request.indexOf("/interval") == 0)
        {
            interval = request.substring(10).toInt();
            led.Interval = interval;
        }
        else if (request.indexOf("/rgb") == 0)
        {
            int r, g, b;
            getRGBfromString(request, 5, &r, &g, &b);

            led.colorWipe(r, g, b);
        }
        else if (request.indexOf("/irgb") == 0)
        {
            int r, g, b;
            getRGBfromString(request, 6, &r, &g, &b);
            led.immediateColor(r, g, b);
        }
        else if (request.indexOf("/pulse") == 0)
        {
            int r, g, b;
            getRGBfromString(request, 7, &r, &g, &b);
            led.simplePulse(r, g, b);
        }
        else if (request.indexOf("/sinpulse") == 0)
        {
            int r, g, b;
            getRGBfromString(request, 10, &r, &g, &b);
            led.sinePulse(r, g, b);
        }
        else handled = false;
    }
    else
        handled = false;

    if (handled)
        server.send(200, "application/json", "{'ok': true}");
    else
        server.send(404, "application/json", "{'ok': false}");
}

void getRGBfromString(String request, int fSlash, int *r, int *g, int *b)
{
    String temp = request.substring(fSlash);

    *b = temp.substring(0, temp.indexOf("/")).toInt();
    temp = temp.substring(temp.indexOf("/") + 1);

    *g = temp.substring(0, temp.indexOf("/")).toInt();
    temp = temp.substring(temp.indexOf("/") + 1);

    *r = temp.toInt();
}

void WIFI_Connect()
{
    WiFi.disconnect();
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);

    for (int i = 0; i < 60; i++)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(500);
        }
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.println("WiFi Connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void setup(void)
{
    Serial.begin(115200);

    //    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2812, 15, RGB>(led.leds, led.NUM_LEDS);
    //        .setCorrection(TypicalLEDStrip);
    // led.ColorWipe(0, 0, 0, interval)    ;

    WIFI_Connect();

    server.onNotFound(handleRoutes);

    server.begin();
    Serial.println("HTTP server started");
    //    led.Pride(interval);
}

void loop(void)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("wifi disconnected ");
        WIFI_Connect();
    }

    server.handleClient();
    led.Update();
    delay(5);
}
