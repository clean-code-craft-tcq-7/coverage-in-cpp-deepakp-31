#include "typewise-alert.h"

std::map<CoolingType, std::vector<int>> temperatureLimits = {
    {PASSIVE_COOLING, {0, 35}},
    {MED_ACTIVE_COOLING, {0, 40}},
    {HI_ACTIVE_COOLING, {0, 45}}};

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

  return inferBreach(temperatureInC, temperatureLimits[coolingType].at(0), temperatureLimits[coolingType].at(1));
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
  std::cout << header << " : " << breachType << "\n";
}

void sendToEmail(BreachType breachType)
{
  const char *recepient = "a.b@c.com";
  switch (breachType)
  {
  case TOO_LOW:
    std::cout << "To: " << recepient << "\n";
    std::cout << "Hi, the temperature is too low\n";
    break;
  case TOO_HIGH:
    std::cout << "To: " << recepient << "\n";
    std::cout << "Hi, the temperature is too high\n";
    break;
  default:
    break;
  }
}
