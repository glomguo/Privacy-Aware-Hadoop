#ifndef __COMMON__
#define __COMMON__

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "config.h"

using namespace std;

void DebugPrintVector(vector<string> &printingVector);
vector<string> PhraseArgv(int argc, char* argv[]);

string ExecuteShellCommand(string cmd);

bool StartMasterWithSlaves(vector<string> &arg);
bool UpdateSlaves(vector<string> &arg, bool isDistribute);
bool StartSlave(vector<string> &arg);
bool StopMaster();
bool StopSlave();
bool Jps();

// config-master.cpp
bool MasterConfigHosts(vector<string> slavesList);
bool MasterConfigHDPMaster();
bool MasterConfigHDPSlaves(vector<string> slavesList);
bool MasterDistributeConfig(vector<string> slavesList);
bool MasterDisableSSHChecking();

// config-slave.cpp
bool SlaveConfigHosts();

bool WriteFile(string fileName, string content);

#endif