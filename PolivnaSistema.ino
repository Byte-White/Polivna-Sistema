#include <LiquidCrystal_I2C.h>


#define PHOTORESISTOR_PIN 2
#define TEMPERATURE_SENSOR_PIN 3
#define SOIL_MOISTURE_SENSOR_PIN 4

#define BUTTON_MINUS_PIN 10
#define BUTTON_OK_PIN 9
#define BUTTON_PLUS_PIN 8

#define WATERING_SYSTEM_PIN 7


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


class WateringSystem
{
  public:
  WateringSystem(int pin)
  :wateringSystemPin(pin)
  {
  }

  void Init()
  {
    pinMode(wateringSystemPin, OUTPUT);
  }

  void TurnOn()
  {
    digitalWrite(wateringSystemPin,HIGH);
  }

  void TurnOff()
  {
    digitalWrite(wateringSystemPin,LOW);
  }

  private:
  int wateringSystemPin;
};

//DISPLAY DATA PIN  - 19
//DISPLAY CLOCK PIN - 18
LiquidCrystal_I2C lcd(0x27,16,2);
PhotoResistor photoResistor(PHOTORESISTOR_PIN);
TemperatureSensor temperatureSensor(TEMPERATURE_SENSOR_PIN);
SoilMoistureSensor soilMoistureSensor(SOIL_MOISTURE_SENSOR_PIN);
WateringSystem wateringSystem(WATERING_SYSTEM_PIN);

Button minusButton(BUTTON_MINUS_PIN);
Button okButton(BUTTON_OK_PIN);
Button plusButton(BUTTON_PLUS_PIN);

enum class Tab
{
  Main = 0,
  MoistureLevel,
  DayTime,
  Count
};
const int TAB_COUNT = static_cast<int>(Tab::Count);


Tab selectedTab = Tab::Main;
bool selectedDayTime = true;
int selectedMoisturePercentage = 25;

void setup()
{
  	minusButton.Init();
  	okButton.Init();
  	plusButton.Init();

    wateringSystem.Init();
  
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
  	int moisturePercentage = soilMoistureSensor.CalculateMoisturePercentage();
    lcd.print(temperature);
  	lcd.print("C  ");
  
  
    lcd.print(photoResistor.GetLightLevelString());
  	lcd.print(" ");
    lcd.setCursor(0, 1);
    //lcd.print(photoResistor.GetLight());
  	lcd.print("Moisture: ");
  	lcd.print(moisturePercentage);
  	lcd.print("%  ");
}


void MoistureLevelTab()
{
  lcd.setCursor(0, 0);
  lcd.print("Select Moisture:");
  lcd.setCursor(0, 1);
  lcd.print(selectedMoisturePercentage);
  lcd.print("%  ");

  if(minusButton.IsClicked())
  {
    selectedMoisturePercentage = max(0,min(selectedMoisturePercentage-1,100));
    delay(50);
  }
  else if(plusButton.IsClicked())
  {
    selectedMoisturePercentage = max(0,min(selectedMoisturePercentage+1,100));
    delay(50);
  }
}

void DayTimeTab()
{
  lcd.setCursor(0, 0);
  lcd.print("Select DayTime:");
  lcd.setCursor(0, 1);
  lcd.print(selectedDayTime?"Day":"Night");
  lcd.print("  ");
  if(minusButton.IsClicked() || plusButton.IsClicked())
  {
    selectedDayTime = !selectedDayTime;
    delay(50);
  }
}

void waterIfNeeded()
{
  int moisturePercentage = soilMoistureSensor.CalculateMoisturePercentage();
  bool isDay = photoResistor.IsDay();

  if(isDay == selectedDayTime && (moisturePercentage <= selectedMoisturePercentage))
    wateringSystem.TurnOn();
  else 
    wateringSystem.TurnOff();
}

void loop()
{
  if(selectedTab == Tab::Main) MainTab();
  else if(selectedTab == Tab::MoistureLevel) MoistureLevelTab();
  else if(selectedTab == Tab::DayTime) DayTimeTab();
  
  if(okButton.IsClicked()) 
  {
    lcd.clear();
    selectedTab = static_cast<Tab>((static_cast<int>(selectedTab) + 1) % TAB_COUNT);
    delay(50);
  }

  waterIfNeeded();
}