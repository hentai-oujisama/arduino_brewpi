#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

//Data wire connected to GPIO5
#define DHT_PIN 2 
#define DHTTYPE DHT11

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

//Setting up DHT instance
DHT dht(DHT_PIN , DHTTYPE);


// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


int deviceCount = 0;
float tempC;
float temp_deltaC;
float temp_deltaF;
float report_temp_deltaC;
float report_temp_deltaF;
float humidity;

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  
  // Start up the library
  
  sensors.begin();
  
  dht.begin();


  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount , DEC);
  Serial.println(" devices");
  Serial.println("");

  
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 


  //Call humidity sensors
  humidity = dht.readHumidity();
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  
  // Display temps for each sensor

  for (int i=0; i < deviceCount ; i++)
    {
      Serial.print("Sensor ");
      Serial.print(i+1);
      Serial.print(" : ");
      tempC = sensors.getTempCByIndex(i);
      Serial.print(tempC);
      Serial.print("º"); //show degree symbol
      Serial.print("C  |  ");
    
      Serial.print(DallasTemperature::toFahrenheit(tempC));
      Serial.print("º");//shows degrees character
      Serial.println("F");

            
    }

//print temperature delta between sensors
  for (int x = 0; x < deviceCount ; x++)

    {
//if index outside of range, do nothing.
      if ( (x+1) <= deviceCount -1)
      {
        temp_deltaC = sensors.getTempCByIndex(x) - sensors.getTempCByIndex(x+1);
        temp_deltaF = DallasTemperature::toFahrenheit(sensors.getTempCByIndex(x)) - DallasTemperature::toFahrenheit(sensors.getTempCByIndex(x+1));

        report_temp_deltaC = abs(temp_deltaC);
        report_temp_deltaF = abs(temp_deltaF);

        Serial.print("Temperature delta between Sensor 1 and 2 is ");
        Serial.print(report_temp_deltaC);
        Serial.print("ºC  |  ");
        
        Serial.print(report_temp_deltaF);
        Serial.print("º");//shows degrees character
        Serial.println("F");
        
      }
        
    }
  
  Serial.println("");
  delay(3000);
}
