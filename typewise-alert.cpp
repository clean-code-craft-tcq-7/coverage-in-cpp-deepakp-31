#include "typewise-alert.h"
#include <stdio.h>

std::map<CoolingType, Limits> coolingTypeLimits = {
    {PASSIVE_COOLING, {0, 35}},
    {HI_ACTIVE_COOLING, {0, 45}},
    {MED_ACTIVE_COOLING, {0, 40}}};

BreachType inferBreach(double value, Limits limit)
{
  if (value < limit.lowerLimit)
  {
    return TOO_LOW;
  }
  if (value > limit.upperLimit)
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC)
{
  Limits temperatureLimit;
  // switch(coolingType) {
  //   case PASSIVE_COOLING:
  //     temperatureLimit.lowerLimit = 0;
  //     temperatureLimit.upperLimit = 35;
  //     break;
  //   case HI_ACTIVE_COOLING:
  //     temperatureLimit.lowerLimit = 0;
  //     temperatureLimit.upperLimit = 45;
  //     break;
  //   case MED_ACTIVE_COOLING:
  //     temperatureLimit.lowerLimit = 0;
  //     temperatureLimit.upperLimit = 40;
  //     break;
}
return inferBreach(temperatureInC, temperatureLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{

  BreachType breachType = classifyTemperatureBreach(
      batteryChar.coolingType, temperatureInC);

  switch (alertTarget)
  {
  case TO_CONTROLLER:
    sendToController(breachType);
    break;
  case TO_EMAIL:
    sendToEmail(breachType);
    break;
  }
}

void sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType)
{
  const char *recepient = "a.b@c.com";
  switch (breachType)
  {
  case TOO_LOW:
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
    break;
  case TOO_HIGH:
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
    break;
  case NORMAL:
    break;
  }
}
