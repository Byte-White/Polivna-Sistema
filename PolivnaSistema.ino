#include <LiquidCrystal_I2C.h>


#define PHOTORESISTOR_PIN 2
#define TEMPERATURE_SENSOR_PIN 3
#define SOIL_MOISTURE_SENSOR_PIN 4

#define BUTTON_MINUS_PIN 10
#define BUTTON_OK_PIN 9
#define BUTTON_PLUS_PIN 8


class TemperatureSensor
{  
  public:
  TemperatureSensor(int pin)
  : tempSensorPin(pin)
  {
  }
  
  
  float GetTemperature()
  {
    int temperatureValue = analogRead(tempSensorPin);
    float temperatureC = ConvertToTemperature(temperatureValue);
    return temperatureC;
  }
  
  private:
  float ConvertToTemperature(int value) 
  {
    float voltage = value * (5.0 / 1023.0);
    float temperatureC = (voltage - 0.5) * 100.0;
    return temperatureC;
}

  int tempSensorPin;
};

enum class DayTime
{
  Day,
  Night
};

class PhotoResistor
{
  public:
  PhotoResistor(int pin)
  : photoResistorPin(pin)
  {
  }
  
  int GetLight()
  {
    return analogRead(photoResistorPin);
  }
  
  String GetLightLevelString()
  {
    int lightValue = GetLight();

    if (lightValue <= 80) 
    {
      return "Sunny";
    } 
    else if (lightValue <= 150) 
    {
      return "Cloudy";
    } 
    else 
    {
      return "Night";
    }
  }


  bool IsDay()
  {
    return (GetLight() <= 150);
  }

  bool IsNight()
  {
    return !IsDay();
  }

  DayTime GetDayTime()
  {
    if(IsDay()) return DayTime::Day;
    else return DayTime::Night;
  }

  private:
  int photoResistorPin;
};

class SoilMoistureSensor
{
  public:
    static const int MinMoisture;
    static const int MaxMoisture;

    SoilMoistureSensor(int pin)
    : soilMoistureSensorPin(pin)
    {
    }

    int GetMoistureLevel()
    {
      return analogRead(soilMoistureSensorPin);
    }

    int CalculateMoisturePercentage()
    {
      return MoistureLevelToPercentage(GetMoistureLevel());
    }

    static int MoistureLevelToPercentage(int level)
    {
      return MapValue(level, MinMoisture, MaxMoisture, 0, 100);
    }
    
    static int MoisturePercentageToLevel(int percentage)
    {
      return MapValue(percentage, 0, 100, MinMoisture, MaxMoisture);
    }

  private:
    static int MapValue(int value, int inMin, int inMax, int outMin, int outMax) 
    {
      return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
    }
  int soilMoistureSensorPin;
};
const int SoilMoistureSensor::MinMoisture = 716;
const int SoilMoistureSensor::MaxMoisture = 886;


class Button
{
  public:
  Button(int pin)
    :buttonPin(pin)
  {
  }
  
  void Init()
  {
    pinMode(buttonPin, INPUT_PULLUP);
  }
  
  bool IsClicked()
  {    
    return (digitalRead(buttonPin) == 0);
  }
  private:
  int buttonPin;
};


//DISPLAY DATA PIN  - 19
//DISPLAY CLOCK PIN - 18
LiquidCrystal_I2C lcd(0x27,16,2);
PhotoResistor photoResistor(PHOTORESISTOR_PIN);
TemperatureSensor temperatureSensor(TEMPERATURE_SENSOR_PIN);
SoilMoistureSensor soilMoistureSensor(SOIL_MOISTURE_SENSOR_PIN);

Button minusButton(BUTTON_MINUS_PIN);
Button okButton(BUTTON_OK_PIN);
Button plusButton(BUTTON_PLUS_PIN);

enum class Tab
{
  Main = 0,
  Moisture,
  DayTime
};


Tab selectedTab = Tab::Main;
DayTime selectedDayTime = DayTime::Day;
int selectedMoisturePercentage = 25;

void setup()
{
  	minusButton.Init();
  	okButton.Init();
  	plusButton.Init();
  
    lcd.init();
    lcd.backlight();
  	lcd.setCursor(0, 0);
    lcd.print("Polivna Sistema");
  	delay(1000);
  	lcd.clear();
}

void MainTab()
{
   	lcd.setCursor(0, 0);
  	float temperature = roundf(temperatureSensor.GetTemperature() * 10) / 10.0;
  	lcd.print(temperature);
  	lcd.print("C  ");
  
  
    lcd.print(photoResistor.GetLightLevelString());
  	lcd.print(" ");
    lcd.setCursor(0, 1);
    //lcd.print(photoResistor.GetLight());
  	lcd.print("Moisture: ");
  	lcd.print(soilMoistureSensor.CalculateMoisturePercentage());
  	lcd.print("%  ");
}


void loop()
{
	MainTab();
}