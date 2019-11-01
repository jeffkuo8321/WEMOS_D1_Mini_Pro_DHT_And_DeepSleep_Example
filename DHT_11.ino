
// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
       Name:  DHT_11.ino
    Created:  2019/11/01 上午 01:45:43
     Author:  JeffKuo
*/


// Define User Types below here or use a .h file
  
  //有少元件到以下網址自取
  //https://github.com/adafruit/DHT-sensor-library
  
  #include <Adafruit_Sensor.h>
  #include <DHT.h>
  #include <DHT_U.h>


// Properties
  
  //使用 wemos d1 mini pro 上的D6腳位當DHT11的訊號接收腳
  #define DHTPIN D6     // Digital pin connected to the DHT sensor 
  // Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
  // Pin 15 can work but DHT must be disconnected during program upload.
  
  // Uncomment the type of sensor in use:
  //#define DHTTYPE    DHT11     // DHT 11
  #define DHTTYPE    DHT11     // DHT 22 (AM2302)
  //#define DHTTYPE    DHT21     // DHT 21 (AM2301)
  
  
  // See guide for details on sensor wiring and usage:
  //   https://learn.adafruit.com/dht/overview
  
  DHT_Unified dht(DHTPIN, DHTTYPE);
  
  uint32_t delayMS; 
  int HDTPowerPin=D8;       // 這邊使用wemos d1 mini pro上的 D8腳位控制dht 11的電源.
  int mDeepSleepDelay=30;   // 要睡眠的時間(秒)
  

// The setup() function runs once each time the micro-controller starts
  
  void setup() 
  {

    // Serial 亂碼: 由于8266在上電时會出現亂碼，這是正常現象，當切换成74880 baudrate时，就可以看到這串亂碼其實是8266啟動時的版本號,使用其他協定輸出資料時就不會有這個問題。
    
    
    pinMode(LED_BUILTIN,OUTPUT);
    pinMode(HDTPowerPin,OUTPUT);
  
    
    // setup built in LED On. 板子上的LED應該是負緣觸發，所以要讓它亮要設為false,其他腳位則是正緣觸發).
    digitalWrite(LED_BUILTIN,false);
    
    // use do to control dht power
    digitalWrite(HDTPowerPin,true);
    
    
    
    Serial.flush();
    Serial.begin(9600);
  
    // delay 1.5 second wait for HDT and serial port hard ware initial. 
    delay(1500);
    
    
    
    Serial.flush();
    Serial.println("");
    Serial.println("Start procedure.");
    
    // Initialize device.
    //Serial.println("Init DHT");
    dht.begin();
    //Serial.println("Init DHT done");
    delay(500);
    //Serial.println(F("DHTxx Unified Sensor Example"));
    // Print temperature sensor details.
    
    
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
  
    dht.humidity().getSensor(&sensor);
    // Set delay between sensor readings based on sensor details.
    delayMS = sensor.min_delay / 1000;
  }

// The loop() function runs alway loop .

  void loop() 
  {
  
    Serial.println("wake up");
    
    // dht 模組的取樣周期要大於2秒.
    delay(delayMS);
    
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
      Serial.println(F("Error reading temperature!"));
    }else{
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }
    
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
      Serial.println(F("Error reading humidity!"));
    }else {
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    
    Serial.println("go to deep sleep");
        
    digitalWrite(HDTPowerPin,false);
    ESP.deepSleep(mDeepSleepDelay*1000000);
}
