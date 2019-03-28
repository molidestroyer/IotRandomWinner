# 1 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
# 1 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.
# 4 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2
# 5 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2
# 6 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2
# 7 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2





static bool hasWifi = false;
static bool hasWinner = false;
int RED_LED = 20;
int GREEN_LED = 19;
int BLUE_LED = 39;

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
  do{{ if (0) { (void)printf("parsing payload\n"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 35 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 3 4
 __null
# 35 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
 ) l(AZ_LOG_INFO, "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino", __func__, 35, 0x01, "parsing payload\n"); } }; }while((void)0,0);
  DynamicJsonBuffer dBuffer;
  JsonObject &payloadBuffer = dBuffer.parseObject(payload);
  const char *yourstring = payloadBuffer["Name"];

  do{{ if (0) { (void)printf(yourstring); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 40 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 3 4
 __null
# 40 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
 ) l(AZ_LOG_INFO, "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino", __func__, 40, 0x01, yourstring); } }; }while((void)0,0);

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

  do{{ if (0) { (void)printf("received device method call\n\n"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 66 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 3 4
 __null
# 66 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
 ) l(AZ_LOG_INFO, "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino", __func__, 66, 0x01, "received device method call\n\n"); } }; }while((void)0,0);

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
  pinMode(RED_LED, 0x2);
  pinMode(GREEN_LED, 0x2);
  pinMode(BLUE_LED, 0x2);
}

void ledParty()
{
  // turn red LED on
  digitalWrite(RED_LED, 0x1);
  delay(500);
  // turn red LED off
  digitalWrite(RED_LED, 0x0);
  delay(200);
  // turn green LED on
  digitalWrite(GREEN_LED, 0x1);
  delay(500);
  // turn green LED off
  digitalWrite(GREEN_LED, 0x0);
  delay(200);
  // turn blue LED on
  digitalWrite(BLUE_LED, 0x1);
  delay(500);
  // turn blue LED off
  digitalWrite(BLUE_LED, 0x0);
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
