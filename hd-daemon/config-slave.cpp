#include "common.h"
#include "ip.h"

using namespace std;

bool SlaveConfigHosts() {
	IP ip;

	string configContent;
	configContent = "127.0.0.1\tlocalhost\n";
	configContent += HADOOP_MASTER_DIP + "\tHadoopMaster\n";

	WriteFile("/etc/hosts", configContent);

	return true;
}