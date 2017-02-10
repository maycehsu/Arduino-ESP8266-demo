
#define esp8266 Serial2   // use esp8266 to talk to esp8266
#define DEBUG true
#define MYSSID "esp8266" 
#define MYPASS "1234567890ab"
#define MYCHANNEL "11"

/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

/*
* Name: readData
* Description: Function used to read data from ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String readData(const int timeout, boolean debug){
  long int time = millis();
  String response = "";
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("connecting esp8266 serial port");
  delay(3000);
  esp8266.begin(115200);
  Serial.println("connected esp8266 serial port");
  int i=0;
  
  sendData("AT+RST\r\n",3000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  String cmd="AT+CWSAP=\"";
  cmd+=MYSSID;
  cmd+="\",\"";
  cmd+=MYPASS;
  cmd+="\",";
  cmd+=MYCHANNEL;
  cmd+=",3\r\n";
  sendData(cmd,1000,DEBUG); // configure SSID/password
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  //connectWiFi_APMode();
    //esp8266.println("AT+RST");
    //delay(1000);
  
  
}


void loop() {
  if(esp8266.available()) // check if the esp is sending a message 
  {
    
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    } 
    
   
  }

  

}
