#include "common.h"
#include "ip.h"

using namespace std;

void DebugPrintVector(vector<string> &printingVector) {
	cerr << "DEBUG: Printing Vector" << endl;
	for (int i = 0; i < printingVector.size(); i++)
		cerr << i << ": " << printingVector[i] << endl;
}

vector<string> PhraseArgv(int argc, char* argv[]) {
	vector<string> result;

	result.clear();

	for (int i = 1; i < argc; i++) {
		string lineArg = "";
		for (int len = 0; argv[i][len] != '\0'; len++)
			lineArg = lineArg + argv[i][len];

		result.push_back(lineArg);
	}

	return result;
}

string ExecuteShellCommand(string cmd) {
	string result = "";
	char buffer[256];
	FILE *stream = popen(cmd.c_str(), "r");
	if (!stream)
		return "Execute failed";

	while (!feof(stream)) {
		if (fgets(buffer, 256, stream) != NULL) {
			result.append(buffer);
		}
	}

	pclose(stream);
	
	return result;
}

bool StartMasterWithSlaves(vector<string> &arg) {
	if (!UpdateSlaves(arg, false))
		return false;

	// disable ssh key checking
	MasterDisableSSHChecking();

	// start Hadoop
	ExecuteShellCommand(HADOOP_DIR + "sbin/start-dfs.sh");
	ExecuteShellCommand(HADOOP_DIR + "sbin/start-yarn.sh");

	Jps();

	return true;
}

bool StartSlave(vector<string> &arg) {
	//if (!SlaveConfigHosts())
	//	return false;
	if (!UpdateSlaves(arg, false))
		return false;

	// disable ssh key checking
	MasterDisableSSHChecking();

	// start Hadoop
	ExecuteShellCommand(HADOOP_DIR + "sbin/start-dfs.sh");

	Jps();

	return true;
}

bool StopMaster() {
	ExecuteShellCommand(HADOOP_DIR + "sbin/stop-dfs.sh");
	ExecuteShellCommand(HADOOP_DIR + "sbin/stop-yarn.sh");

	return true;
}

bool StopSlave() {
	ExecuteShellCommand(HADOOP_DIR + "sbin/stop-dfs.sh");

	return true;
}

bool Jps() {
	cout << ExecuteShellCommand("jps | grep -v \"process information unavailable\"") << endl;

	return true;
}

bool UpdateSlaves(vector<string> &arg, bool isDistribute) {
	if (arg.size() < 2) {
		cout << "FAIL: missing the paramenter: number of slaves" << endl;
		return false;
	}

	int numberSlaves = atoi(arg[1].c_str());
	if (arg.size() < numberSlaves + 2) {
		cout << "FAIL: number of IPs in the list smaller than the parameter named number of slaves" << endl;
		return false;
	}

	IP ip;
	for (int i = 2; i < numberSlaves + 2; i++)
		if (!ip.ValidIPAddress(arg[i])) {
			cout << "FAIL: invalid IP address of slave" << (i - 1) << endl;
			return false;
		}

	// set /etc/hosts
	MasterConfigHosts(vector<string>(arg.begin() + 2, arg.end()));

	MasterConfigHDPMaster();

	MasterConfigHDPSlaves(vector<string>(arg.begin() + 2, arg.end()));

	if (isDistribute)
		MasterDistributeConfig(vector<string>(arg.begin() + 2, arg.end()));

	return true;
}

bool WriteFile(string fileName, string content) {
	//cerr << "DEBUG: WriteFile" << endl;
	//cerr << "FileName: " << fileName << endl;
	//cerr << content << endl;

	ofstream writer;
	writer.open(fileName.c_str());
	writer << content;
	writer.close();

	return true;
}

int main(int argc, char* argv[]) {
	vector<string> arg = PhraseArgv(argc, argv);
	//DebugPrintVector(arg);	
	
	if (arg.size() == 0) {
		cout << "FAIL: missing any method in argv" << endl;
		return 0;
	}

	// Switch
	if (arg[0] == "startmaster") {
		if (StartMasterWithSlaves(arg))
			cout << "OK" << endl;
	} else if (arg[0] == "update") {
		if (UpdateSlaves(arg, false))
			cout << "OK" << endl;
	} else if (arg[0] == "startslave") {
		if (StartSlave(arg))
			cout << "OK" << endl;
	} else if (arg[0] == "stopmaster") {
		if (StopMaster())
			cout << "OK" << endl;
	} else if (arg[0] == "stopslave") {
		if (StopSlave())
			cout << "OK" << endl;
	} else if (arg[0] == "jps") {
		if (Jps())
			cout << "OK" << endl;
	} else {
		cout << "FAIL: matching the given method failed" << endl;
	}
}
