#include <Arduino.h>
#line 1 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
#line 1 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.
#include "AZ3166WiFi.h"
#include "DevKitMQTTClient.h"
#include "RGB_LED.h"
#include <ArduinoJson.h>
#include <math.h>

#define INTERVAL 2000
#define MESSAGE_MAX_LEN 256

static bool hasWifi = false;
static bool hasWinner = false;
int RED_LED = 20;
int GREEN_LED = 19;
int BLUE_LED = 39;

#line 18 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
static void showWinner(JsonObject &payloadBuffer);
#line 33 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
static JsonObject& parsePayload(const unsigned char *payload);
#line 45 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
static void InitWifi();
#line 61 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
static int DeviceMethodCallback(const char *methodName, const unsigned char *payload, int size, unsigned char **response, int *response_size);
#line 90 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
void setup();
#line 112 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
void ledParty();
#line 134 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
void loop();
#line 18 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
static void showWinner(JsonObject &payloadBuffer)
{
  //generate a random number
  int randomNumber = random(1, 50);

  //display the random number on the serial monitor
  Screen.print(1, "CONGRATULATIONS!  ", true);
  delay(1000);

  const char *yourstring = payloadBuffer["Name"];
  Screen.print(1, yourstring, true);

  hasWinner = true;
}

static JsonObject &parsePayload(const unsigned char *payload)
{
  LogInfo("parsing payload\n");
  DynamicJsonBuffer dBuffer;
  JsonObject &payloadBuffer = dBuffer.parseObject(payload);
  const char *yourstring = payloadBuffer["Name"];

  LogInfo(yourstring);

  return payloadBuffer;
}

static void InitWifi()
{
  Screen.print(3, "connecting...");

  if (WiFi.begin() == WL_CONNECTED)
  {
    hasWifi = true;
    Screen.print(3, "connected!");
  }
  else
  {
    hasWifi = false;
    Screen.print(3, "No Wi-Fi");
  }
}

static int DeviceMethodCallback(const char *methodName, const unsigned char *payload, int size, unsigned char **response, int *response_size)
{
  const char *responseMessage = "\"Successfully invoke device method\"";
  int result = 200;

  LogInfo("received device method call\n\n");

  if (strcmp(methodName, "showWinner") == 0)
  {
    JsonObject &payloadBuffer = parsePayload(payload);
    if (payloadBuffer.size())
    {
      showWinner(payloadBuffer);
    }
  }
  else
  {
    Screen.print(1, "no method found");
    responseMessage = "\"No method found\"";
    result = 404;
  }

  *response_size = strlen(responseMessage);
  *response = (unsigned char *)malloc(*response_size);
  strncpy((char *)(*response), responseMessage, *response_size);

  return result;
}

void setup()
{
  Screen.init();

  InitWifi();
  if (!hasWifi)
  {
    return;
  }

  DevKitMQTTClient_Init(true);
  DevKitMQTTClient_SetDeviceMethodCallback(DeviceMethodCallback);

  Screen.print(0, "THE WINNER IS...");
  Screen.print(3, "waiting...");

  // initialize the pins as digital output.
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void ledParty()
{
  // turn red LED on
  digitalWrite(RED_LED, HIGH);
  delay(500);
  // turn red LED off
  digitalWrite(RED_LED, LOW);
  delay(200);
  // turn green LED on
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  // turn green LED off
  digitalWrite(GREEN_LED, LOW);
  delay(200);
  // turn blue LED on
  digitalWrite(BLUE_LED, HIGH);
  delay(500);
  // turn blue LED off
  digitalWrite(BLUE_LED, LOW);
  delay(200);
}

void loop()
{
  DevKitMQTTClient_Check();

  if (hasWinner)
  {
    ledParty();
  }
}

