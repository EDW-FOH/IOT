#include <WiFi101.h>
#include <string.h>  //used for some string handling and processing.
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int status = WL_IDLE_STATUS;
WiFiServer server(80);

const int RESPONSE_TIMEOUT = 6000; //ms to wait for response from host
const int GETTING_PERIOD = 5000; //periodicity of getting a number fact.
const uint16_t IN_BUFFER_SIZE = 1000; //size of buffer to hold HTTP request
const uint16_t OUT_BUFFER_SIZE = 1000; //size of buffer to hold HTTP response
char request_buffer[IN_BUFFER_SIZE]; //char array buffer to hold HTTP request
char response_buffer[OUT_BUFFER_SIZE]; //char array buffer to hold HTTP response

char output[1000];

//Options Type: 0=temp 1=time 2=date 3=visibility 4=humidity 5=pressure
int option_type;
#define TEMP 0

#define VISIBILITY 3
#define HUMIDITY 4
#define PRESSURE 5

//Button pin and val
const uint8_t button_pin = 7;
uint8_t val;


//Button states
uint8_t state;
#define REST 0
#define PUSH 1
#define RELEASE 2

char network[] = "YourNetworkName";  //SSID CHANGE!!
char password[] = "YourWiFiPassword"; //Password for WiFi CHANGE!!!

void setup() {
  Serial.begin(115200); //for debugging if needed.
  delay(50); //pause to make sure comms get set up
  
  //LCD Setup
  analogWrite(A3, 0);
  lcd.begin(16, 2);
  lcd.print("Connecting to");
  lcd.setCursor(0, 2);
  lcd.print(network);
  
  //WiFi Setup
  Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    return; // don't continue
  }
  Serial.println("DETECTED");
  uint8_t count = 0; //count used for Wifi check times
  while ( status != WL_CONNECTED && count < 6) { // try 6 times
    Serial.print("Attempting to connect to ");
    Serial.println(network);
    WiFi.begin(network, password); //attempt to connect to wifi
    // wait .5 seconds before trying again
    delay(500);
    Serial.print(".");
    count++;
  }
  delay(2000);  //acceptable since it is in the setup function.
  if (status == WL_CONNECTED) {
    Serial.println("CONNECTED!");
    delay(500);
  } else { //if we failed to connect just Try again.
    Serial.println("Failed to Connect :/  Plz restart");
    Serial.println(WiFi.status());
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected!");

  state = REST; //Set button state to rest
  pinMode(button_pin, INPUT_PULLUP); //Setup button pin
}

void loop() {
  
  //Your code here
  
}
