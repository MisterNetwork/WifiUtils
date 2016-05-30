#ifndef WifiFunctions_H
#define WifiFunctions_H

extern int getWifiPercentage(int rssiVal);
extern void showNetworksAroundHere(void);
extern void OutputStoredConnections(void);
extern void showWifiDetails(bool internalAntenna, bool showStoredConnections, bool showNetworks);



#endif
