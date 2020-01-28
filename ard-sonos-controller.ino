#include "Button.h"
#include <WiFi.h>
#include "MicroXPath_P.h"
#include "SonosUPnP.h"

#define ETHERNET_ERROR_DHCP "E: DHCP"
#define ETHERNET_ERROR_CONNECT "E: Connect"

// Button setup
const byte volDownButtonPin    = 21;
const byte volUpButtonPin      = 22;
const byte playPauseButtonPin  = 19;

Button *volDownButton;
Button *volUpButton;
Button *playPauseButton;

// Network client creation
void ethConnectError();
WiFiClient client;
String ssid     = "";
String password = "";

// Sonos client setup
// Office sonos
IPAddress g_SonosIP(192, 168, 1, 188);
const char g_SonosID[] = "000E583301AE";

// Backyard
//IPAddress g_SonosIP(192, 168, 1, 201);
//const char g_SonosID[] = "949F3EB9E920";

// Sonos client creation
SonosUPnP g_sonos = SonosUPnP(client, ethConnectError);
int volumeState = 0;

void setup() {
  Serial.begin(115200);
  // Setup the buttons
  volDownButton = new Button(volDownButtonPin);
  volUpButton = new Button(volUpButtonPin);
  playPauseButton = new Button(playPauseButtonPin);

  // Connect to the network
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  Serial.println("connected to WiFi");
  Serial.println(WiFi.localIP());
  
  auto volume = g_sonos.getVolume(g_SonosIP);
 
  Serial.println("Volume is...");
  Serial.println(volume);
  
}

void loop() {
 Button::Event _volDownButtonEvent = volDownButton->getEvent();
 Button::Event _volUpButtonEvent = volUpButton->getEvent();
 Button::Event _playPauseButtonEvent = playPauseButton->getEvent();

  if (_volDownButtonEvent != Button::None) {
    Serial.println("Volume Down");
    int volumeState = g_sonos.getVolume(g_SonosIP);
    Serial.println("Volume is...");
    Serial.println(g_sonos.getVolume(g_SonosIP));
  } else if (_volUpButtonEvent != Button::None) {
    Serial.println("Volume Up");
    int volumeState = g_sonos.getVolume(g_SonosIP);
    Serial.println("Volume is...");
    Serial.println(g_sonos.getVolume(g_SonosIP));
  } else if (_playPauseButtonEvent != Button::None) {
    Serial.println("Play / Pause");
    g_sonos.togglePause(g_SonosIP);
  }

}

void ethConnectError()
{
  Serial.println(ETHERNET_ERROR_CONNECT);
  Serial.println("Wifi died.");
}
