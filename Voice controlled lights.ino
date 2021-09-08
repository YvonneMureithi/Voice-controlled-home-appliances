#define WIFI_NAME "********"
#define WIFI_PASSWORD "*********"
#define DEVICE_ID 2
#define DEVICE_NAME "Google_ESP"
#define TOKEN "~1005414_T1rxsp5LTq1icC94eu1WVEGW"
#define Relay_1 5 

#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>
#include <RemoteMeDirectWebSocketConnector.h> // !important library needs WebSockets by Markus Sattler Please install it from Library manager

#include <ESP8266WiFi.h>



RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

//*************** CODE FOR COMFORTABLE VARIABLE SET *********************

inline void setRelay(boolean b) {remoteMe.getVariables()->setBoolean("Relay", b); }

//*************** IMPLEMENT FUNCTIONS BELOW *********************

void onRelayChange(boolean b) {
	Serial.printf("onRelayChange: b: %d\n",b);
  digitalWrite(Relay_1, b ? HIGH : LOW);
}




void setup() {
	Serial.begin(115200);
  pinMode(Relay_1, OUTPUT);
  digitalWrite(Relay_1, LOW);

	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}

	remoteMe.getVariables()->observeBoolean("Relay" ,onRelayChange);

	remoteMe.setConnector(new RemoteMeSocketConnector());
	remoteMe.setDirectConnector(new RemoteMeDirectWebSocketConnector());
	remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);
}


void loop() {
	remoteMe.loop();
}
