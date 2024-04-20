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

enum class LightLevel
{
  Night = 0,
  Cloudy,
  Sunny
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
  
  LightLevel GetLightLevel()
  {
    int lightValue = GetLight();

    if (lightValue <= 200) 
    {
      return LightLevel::Night;
    } else if (lightValue <= 500) 
    {
      return LightLevel::Cloudy;
    } else 
    {
      return LightLevel::Sunny;
    }
  }
  
  String GetLightLevelString()
  {
    LightLevel lightLevel = GetLightLevel();
    switch(lightLevel)
    {
      case LightLevel::Night: return "Night";
      case LightLevel::Cloudy: return "Cloudy";
      case LightLevel::Sunny: return "Sunny";
      default: return "ERROR";
    }
  }
  
  private:
  int photoResistorPin;
};

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

Button minusButton(BUTTON_MINUS_PIN);
Button okButton(BUTTON_OK_PIN);
Button plusButton(BUTTON_PLUS_PIN);

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

void loop()
{
  	lcd.setCursor(0, 0);
  	float temperature = roundf(temperatureSensor.GetTemperature() * 10) / 10.0;
  
  	lcd.print("Temp:");
  	lcd.print(temperature);
	lcd.print("C");
  
  
    lcd.setCursor(0, 1);
    lcd.print("Light:");
    lcd.print(photoResistor.GetLightLevelString());
    //lcd.print(photoResistor.GetLight());
}