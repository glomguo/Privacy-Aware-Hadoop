#include "common.h"
#include "ip.h"

using namespace std;

bool MasterConfigHosts(vector<string> slavesList) {
	IP ip;

	string configContent;
	configContent = "127.0.0.1\tlocalhost\n";
	configContent += HADOOP_MASTER_DIP + "\tHadoopMaster\n";
	
	for (int i = 0; i < slavesList.size(); i++) {
		configContent += slavesList[i] + "\t" + ip.GetHostName(slavesList[i]) + "\n";
	}

	WriteFile("/etc/hosts", configContent);

	return true;
}

bool MasterConfigHDPMaster() {
	WriteFile(HADOOP_DIR + "etc/hadoop/masters", "HadoopMaster");

	// core-site.xml
	string core_site = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<?xml-stylesheet type=\"text/xsl\" href=\"configuration.xsl\"?>\n<configuration>\n";
	core_site += "<property>\n<name>fs.default.name</name>\n<value>hdfs://HadoopMaster:9000</value>\n";
	core_site += "<description>Default FS</description>\n</property>\n</configuration>\n";
	WriteFile(HADOOP_DIR + "etc/hadoop/core-site.xml", core_site);

	// hdfs-site.xml
	string hdfs_site = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<?xml-stylesheet type=\"text/xsl\" href=\"configuration.xsl\"?>\n<configuration>\n";
	hdfs_site += "<property>\n<name>dfs.replication</name>\n<value>3</value>\n</property>\n";
	hdfs_site += "<property>\n<name>dfs.namenode.name.dir</name>\n<value>file:/usr/local/hadoop_tmp/hdfs/namenode</value>\n</property>\n";
	hdfs_site += "<property>\n<name>dfs.datanode.data.dir</name>\n<value>file:/usr/local/hadoop_tmp/hdfs/datanode</value>\n</property>\n</configuration>\n";
	WriteFile(HADOOP_DIR + "etc/hadoop/hdfs-site.xml", hdfs_site);

	// yarn-site.xml
	string yarn_site = "<?xml version=\"1.0\"?>\n<configuration>\n";
	yarn_site += "<property>\n<name>yarn.nodemanager.aux-services</name>\n<value>mapreduce_shuffle</value>\n</property>";
	yarn_site += "<property>\n<name>yarn.nodemanager.aux-services.mapreduce_shuffle.class</name>\n<value>org.apache.hadoop.mapred.ShuffleHandler</value>\n</property>\n";
	yarn_site += "<property>\n<name>yarn.resourcemanager.resource-tracker.address</name>\n<value>HadoopMaster:8025</value>\n</property>\n";
	yarn_site += "<property>\n<name>yarn.resourcemanager.scheduler.address</name>\n<value>HadoopMaster:8035</value>\n</property>\n";
	yarn_site += "<property>\n<name>yarn.resourcemanager.address</name>\n<value>HadoopMaster:8050</value>\n</property>\n</configuration>\n";
	WriteFile(HADOOP_DIR + "etc/hadoop/yarn-site.xml", yarn_site);

	// mapred-site.xml
	string mapred_site = "<?xml version=\"1.0\"?>\n<?xml-stylesheet type=\"text/xsl\" href=\"configuration.xsl\"?>";
	mapred_site += "<configuration>\n<property>\n<name>mapreduce.job.tracker</name>\n<value>HadoopMaster:5431</value>\n</property>\n<property>\n<name>mapred.framework.name</name>\n<value>yarn</value>\n</property>\n</configuration>\n";
	WriteFile(HADOOP_DIR + "etc/hadoop/mapred-site.xml", mapred_site);

	return true;
}

bool MasterConfigHDPSlaves(vector<string> slavesList) {
	IP ip;

	string configContent;
	configContent = "HadoopMaster";
	
	for (int i = 0; i < slavesList.size(); i++) {
		configContent += "\n" + ip.GetHostName(slavesList[i]);
	}

	WriteFile(HADOOP_DIR + "etc/hadoop/slaves", configContent);

	return true;
}

bool MasterDistributeConfig(vector<string> slavesList) {
	IP ip;
	for (int i = 0; i < slavesList.size(); i++)
		ExecuteShellCommand("rsync -avxP " + HADOOP_DIR + " hduser@" + ip.GetHostName(slavesList[i]) + ":" + HADOOP_DIR);

	return true;
}

bool MasterDisableSSHChecking() {
	string configContent = "Host *\n    SendEnv LANG LC_*\n    HashKnownHosts yes\n    GSSAPIAuthentication yes\n    GSSAPIDelegateCredentials no\n";
	configContent += "Host *\n    StrictHostKeyChecking no\n    UserKnownHostsFile=/dev/null\n";

	WriteFile("/etc/ssh/ssh_config", configContent);

	WriteFile("/root/.ssh/known_hosts", "");

	return true;
}