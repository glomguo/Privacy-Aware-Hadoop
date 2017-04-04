#include "ip.h"

string IP::GetHostName(string ipAddress) {
	int segmentCount = 0;
	string hostName = "Hadoop";

	for (int i = 0; i < ipAddress.size(); i++) {
		if (ipAddress[i] == '.') {
			segmentCount++;
		} else if (segmentCount == 3 && ipAddress[i] >= '0' && ipAddress[i] <= '9') {
			hostName = hostName + ipAddress[i];
		}
	}

	return hostName;
}

bool IP::ValidIPAddress(string ipAddress) {
	int segmentCount = 0;
	int segmentValue = 0;

	for (int i = 0; i < ipAddress.size(); i++) {
		if (ipAddress[i] == '.') {
			if (segmentValue > 256)
				return false;
			segmentValue = 0;
			segmentCount++;
		} else if (ipAddress[i] >= '0' && ipAddress[i] <= '9') {
			segmentValue = segmentValue * 10 + (ipAddress[i] - '0');
		} else
			return false;
	}

	if (segmentValue > 256 || segmentCount != 3)
		return false;
	else
		return true;
}
