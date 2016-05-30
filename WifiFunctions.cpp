#include "application.h"
#include "WifiFunctions.h"


void showWifiDetails(bool internalAntenna, bool showStoredConnections, bool showNetworks)
{
    String message = "";

    if ( showStoredConnections)
        OutputStoredConnections();
        
    int wifiStrength = WiFi.RSSI();
    
    int wifiPtage = getWifiPercentage(wifiStrength);
    if ( wifiStrength > 0)
    {
        if ( internalAntenna)
            message = String( "Internal Wifi Error:") + String(wifiStrength) + String(" on Network: ") + String(WiFi.SSID());
        else
            message = String( "External Wifi Error:") + String(wifiStrength) + String(" on Network: ") + String(WiFi.SSID());
    }
    else if (wifiStrength < 1)
    {
        if ( internalAntenna)
            message = String( "Internal Wifi Stength %:") + String(wifiPtage)+ String(" on Network: ") + String(WiFi.SSID());
        else
            message = String( "External Wifi Stength %:") + String(wifiPtage)+ String(" on Network: ") + String(WiFi.SSID());

    }
    
    Particle.publish(message, String( wifiPtage) );
    if ( showNetworksAroundHere)
        showNetworksAroundHere();
    
}


int getWifiPercentage(int rssiVal)
{
    // -127 weak
    // -1 strong
    
    if ( rssiVal >=0) return 0;
    if ( rssiVal < -127)
        rssiVal = -127;
    rssiVal = abs(rssiVal);
    
    int ptage = map( rssiVal, 1, 127, 100,0);
    
    return ptage;
}


void showNetworksAroundHere()
{
    String message = "";

    WiFiAccessPoint aps[20];
    int found = WiFi.scan(aps, 20);

    String data = "";
    message = String("Networks Found: ");
    message += String( found);
    Particle.publish(message, found );

    for (int i=0; i<found; i++) 
    {
        WiFiAccessPoint& ap = aps[i];
        if ( data.length()  < 230)
        {
            data.concat(ap.ssid);
            data.concat(", ");
        }
    }
    Particle.publish("SSID's Found", data);
    
}

void OutputStoredConnections()
{
    WiFiAccessPoint ap[5];
    int found = WiFi.getCredentials(ap, 5);
    for (int i = 0; i < found; i++) 
    {
        char buffer[256];
        sprintf(buffer, "SSID:%s", ap[i].ssid);
        Particle.publish("Stored SSID: ", buffer);
    }
}
