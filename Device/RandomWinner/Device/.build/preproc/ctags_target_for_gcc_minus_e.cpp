# 1 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
# 1 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license.
# 4 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2
# 5 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2
# 6 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2
# 7 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 2





static bool hasWifi = false;

static void generateRandomNumber(JsonObject& payloadBuffer)
{
  //generate a random number
  int randomNumber = random(1, 50);

  //display the random number on the serial monitor
  Screen.print(1, "The xx Number is ..  ");
  char cstr[16];

  Screen.print(3, itoa(randomNumber, cstr, 10));
}

static JsonObject &parsePayload(const unsigned char *payload)
{
  do{{ if (0) { (void)printf("parsing payload\n"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 28 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 3 4
 __null
# 28 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
 ) l(AZ_LOG_INFO, "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino", __func__, 28, 0x01, "parsing payload\n"); } }; }while((void)0,0);
  DynamicJsonBuffer dBuffer;
  JsonObject& payloadBuffer = dBuffer.parseObject(payload);
  const char *yourstring = payloadBuffer["Name"];

  do{{ if (0) { (void)printf(yourstring); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 33 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 3 4
 __null
# 33 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
 ) l(AZ_LOG_INFO, "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino", __func__, 33, 0x01, yourstring); } }; }while((void)0,0);

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
# 59 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino" 3 4
 __null
# 59 "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino"
 ) l(AZ_LOG_INFO, "d:\\Repos\\GitHub\\IotRandomWinner\\Device\\RandomWinner\\Device\\device.ino", __func__, 59, 0x01, "received device method call\n\n"); } }; }while((void)0,0);

  if (strcmp(methodName, "generateRandomNumber") == 0)
  {
    JsonObject &payloadBuffer = parsePayload(payload);
    if (payloadBuffer.size())
    {
      generateRandomNumber(payloadBuffer);
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

  Screen.print(0, "And the winner is...");
  Screen.print(3, "waiting...");
}

void loop()
{
  DevKitMQTTClient_Check();
  delay(66);
}
