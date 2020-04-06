#include <Arduino.h>
#include <WiFi.h>

// Custom libraries
#include <utlgbotlib.h>

const char* BotToken = "1035089740:AAEK_F4xoLKIjyPJy7byZfWJjZAoUuVLJxY";


char ssid[] = "Harshseth";       // your network SSID (name)
char password[] = "12344444";

uTLGBot Bot(BotToken);

void setup() {
  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  Bot.getMe();
  
}



void loop() {



  

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("harshseth");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  long rssi[50];
  // Measure Signal Strength (RSSI) of Wi-Fi connection
  
  for(int i=0;i<5;i++)
  { 
    rssi[i] = WiFi.RSSI();
  }
  long mean=0,sum=0;
  for(int i=0;i<5;i++)
  {
    sum+=rssi[i];
  }
    mean=sum/5;
    
    if(mean>-57 && mean<-52)
    {
      Serial.println(mean);
  
      Serial.println("!!!SITTING!!!");
      while(Bot.getUpdates())
      {
          // Send an echo message back
          Bot.sendMessage(Bot.received_msg.chat.id, "SITTING");
  
          // Feed the Watchdog
          yield();
      }
     
    }
    else if(mean>-62 && mean<-58)
    {
      Serial.println(mean);
      Serial.println("!!!STANDING!!!");
      while(Bot.getUpdates())
      {
          // Send an echo message back
          Bot.sendMessage(Bot.received_msg.chat.id, "STANDING");
  
          // Feed the Watchdog
          yield();
      }
     
    }
    else if(mean>-51 && mean<-50)
  {
    Serial.println(mean);
    Serial.println("!!!WALKING!!!");
    while(Bot.getUpdates())
    {
        // Send an echo message back
        Bot.sendMessage(Bot.received_msg.chat.id, "WALKING");

        // Feed the Watchdog
        yield();
    }
   
  }


  else
  {
    Serial.println(mean);
    Serial.println("!!!SOMEONE IS PRESENT!!!");
    while(Bot.getUpdates())
    {
        // Send an echo message back
        Bot.sendMessage(Bot.received_msg.chat.id,"!!!SOMEONE IS PRESENT!!!");

        // Feed the Watchdog
        yield();
    }
  }

  
  // Write value to Field 1 of a ThingSpeak Channel
 // int httpCode = ThingSpeak.writeField(myChannelNumber, 1, rssi, myWriteAPIKey);


  //if (httpCode == 200) {
    //Serial.println("Channel write successful.");
 // }
  //else {
    //Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  //}

  // Wait 20 seconds to update the channel again
}
