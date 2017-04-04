#ifndef __IP_CLASS__
#define __IP_CLASS__

#include "common.h"

class IP {
public:
	string GetHostName(string ipAddress);
	bool ValidIPAddress(string ipAddress);
};

#endif
