#include "LedPatterns.h"
// #include "patterns/confetti.h"
#include "./patterns/rainbowCycle.h"
#include "./patterns/bpm.h"
#include "./patterns/simpleRainbow.h"
#include "./patterns/pride.h"
#include "./patterns/ledStripCycle.h"
#include "./patterns/pacifica.h"
#include "./patterns/colorWipe.h"
#include "./patterns/twinkleFox.h"
#include "./patterns/colorFade.h"
#include "./patterns/cyclon.h"
#include "./patterns/colorWipe.h"
#include "./patterns/sinePulse.h"
#include "./patterns/immediateColor.h"



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
#define FASTLED_RMT_MAX_CHANNELS 1 #endif
#endif

#define PIXELS 5
#define PIN 15

const char *ssid = "";
const char *password = "";

const char *key = "/joshua/";
uint8_t keyLen = strlen(key);


CRGB leds1[PIXELS];
CRGB leds2[PIXELS];
CRGB leds3[PIXELS];
LedPatterns led;

// Using this for routes with wild cards
bool handleRequest(char *incomming)
{
    String request = String(incomming + keyLen - 1);
    Serial.println(request);

    bool validRequest = true;


    // Check for key
    if (strncmp(key, incomming, keyLen) != 0){ return false; }

    if(request.indexOf("/rainbowcycle")==0) led.setPattern(new RainbowCycle(&led));
    else if(request.indexOf( "/bpm" ) == 0) led.setPattern(new Bpm(&led));
    else if(request.indexOf( "/simplerainbow" ) == 0) led.setPattern(new SimpleRainbow(&led));
    else if(request.indexOf( "/immediatecolor" ) == 0) led.setPattern(new ImmediateColor(&led));
    else if(request.indexOf( "/sinepulse" ) == 0) led.setPattern(new SinePulse(&led));
    else if(request.indexOf( "/colorwipe" ) == 0) led.setPattern(new ColorWipe(&led));
    else if(request.indexOf( "/cyclon" ) == 0) led.setPattern(new Cyclon(&led));
    else if(request.indexOf( "/colorfade" ) == 0) led.setPattern(new ColorFade(&led));
    else if(request.indexOf( "/twinklefox" ) == 0) led.setPattern(new TwinkleFox(&led));
    else if(request.indexOf( "/colorwipe" ) == 0) led.setPattern(new ColorWipe(&led));
    else if(request.indexOf( "/pacifica" ) == 0) led.setPattern(new Pacifica(&led));
    else if(request.indexOf( "/ledstripcycle" ) == 0) led.setPattern(new LedStripCycle(&led));
    else if(request.indexOf( "/pride" ) == 0) led.setPattern(new Pride(&led));
    else validRequest = false;

    int position = request.indexOf("/rgb/");
    if (position >= 0) // Assign and check in a single step
    {
        led.immediateOff();
        led.deleteCurrentPattern(); 
        int r, g, b;
        int startIndex = position + 5; 
        getRGBfromString(request, startIndex, &r, &g, &b);
        led.colorsForPatterns[0] = CRGB(r,g,b);
        validRequest = true;
    }

    return validRequest;
}

void handleRoutes(){
    char incomming[200];
    server.uri().toCharArray(incomming, 200-1);

    bool handled  = handleRequest(incomming);

    if (handled)
        server.send(200, "application/json", "{'ok': true}");
    else
        server.send(404, "application/json", "{'ok': false}");
}

void getRGBfromString(String request, int fSlash, int *r, int *g, int *b)
{
    String temp = request.substring(fSlash);

    *r = temp.substring(0, temp.indexOf("/")).toInt();
    temp = temp.substring(temp.indexOf("/") + 1);

    *g = temp.substring(0, temp.indexOf("/")).toInt();
    temp = temp.substring(temp.indexOf("/") + 1);

    *b = temp.toInt();
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

    FastLED.addLeds<WS2811, 19, BRG>(leds1, PIXELS);
    FastLED.addLeds<WS2811, 16, BRG>(leds2, PIXELS);
    FastLED.addLeds<WS2811, 23, BRG>(leds3, PIXELS);

    FastLED.setBrightness(255);

    led.addLeds(leds2, PIXELS);
    led.addLeds(leds3, PIXELS);
    led.addLeds(leds1, PIXELS);
    led.immediateOff();

    FastLED.show();

led.setPattern(new Pacifica(&led));
//WIFI_Connect();

    // server.onNotFound(handeRoutes);
    // server.enableCORS(); //This is the magic
    // server.begin();
    // Serial.println("HTTP server started");

    // led.colorsForPatterns[0] = CRGB(255,255,0);
    // led.setPattern(new ColorFade(&led));

}

void loop(void)
{
  // if (WiFi.status() != WL_CONNECTED)
  // {
  //   Serial.println("wifi disconnected ");
  //   WIFI_Connect();
  // }

  // server.handleClient();
  led.Update();
  delay(5);
}
