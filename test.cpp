#pragma comment(lib,"Version.lib")
#pragma warning(disable : 4996)
#include "rapidjson/filereadstream.h"
#include "gtest/gtest.h"
#include <iostream>
#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>
#include <assert.h>
#include <rapidjson/document.h>
#include "rapidjson/writer.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <winver.h>
#include <array>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tchar.h>
#include <map>
#include <wincrypt.h>
#include <wintrust.h>
#include <Gtestutils.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <vector>

//#pragma comment(lib, "D:\\agent_dependency\\agent_dependency\\newSetup\\LIBXML\\libxml2-2.6.19\\win32\\bin.msvc\\dclibxml2.lib")



 
#pragma comment(lib, "crypt32.lib")
using namespace std;
using namespace rapidjson;
using namespace utils;
 clock_t begin_time=0;
 std::ofstream logFile;

	 
LPSTR gv_RegKey			= "Software\\AdventNet\\DesktopCentral\\DCAgent"; 


VOID startup(LPCTSTR lpApplicationName)
{
   // additional information
   STARTUPINFO si;     
   PROCESS_INFORMATION pi;

   // set the size of the structures
   ZeroMemory( &si, sizeof(si) );
   si.cb = sizeof(si);
   ZeroMemory( &pi, sizeof(pi) );

  // start the program up
  CreateProcess( lpApplicationName,   // the path
    NULL,        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Set handle inheritance to FALSE
    0,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory 
    &si,            // Pointer to STARTUPINFO structure
    &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
void RegistryCheck() {
    // Common test logic goes here
    bool check,Check_serverinfo;
	LPSTR Serverinfo[10]  = { "DCLastAccessName", "DCProductCode", "DCServerFlatName", "DCServerIPAddress","DCServerName","DCServerPort","DCServerProtocol","DCServerSecIPAddress","DCServerSecurePort","SERVER_OFFSET" };
    LPCSTR DCAgent_path = "SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent";
	LPCSTR DCAgent_certificate_path = "SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\Certificates";
	LPCSTR DCAgent_ServerInfo_path = "SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo";
   // bool check = CheckRegistryValue(DCAgent_path, "BlockCrashedConfig");
    //bool check1 = CheckRegistryValue(DCAgent_path, "CustomerId");
   if (CheckRegistryValue(DCAgent_path, "CustomerId")&&CheckRegistryValue(DCAgent_certificate_path, "ServerRootCertificateInstalled"))
   {
	    check= true;
		logFile<<"CustomerId and ServerRootCertificateInstalled Exist"<<endl;
   }
   else
   { 
	   check= false;
	   logFile<<"CustomerId and ServerRootCertificateInstalled not Exist"<<endl;
   }
   int arraysize= sizeof(Serverinfo)/sizeof(Serverinfo[0]);
   for (int i = 0; i < arraysize; i++)
   {
	  if(CheckRegistryValue(DCAgent_ServerInfo_path, Serverinfo[i]))
      {
	    Check_serverinfo= true;
		logFile<<string(Serverinfo[i])<<"registry value exist"<<endl;


	  }
       else
	   { 
		 Check_serverinfo= false;
		 logFile<<string(Serverinfo[i])<<"registry value not exist "<<endl;
       }
   }
    ASSERT_TRUE(true == check==Check_serverinfo);
}
void ExeCheck() {

bool status=false;
	ofstream of;
	of.open("C:\\mockserverbuild\\\logs\\MissingExe.txt", ios::app);
	LPSTR dcpath=nullptr;
	std::vector<std::wstring> dcNativeExecutables;
	std::vector<std::wstring> missingExecutables;
	vector<wstring> expectedExecuables;
	
expectedExecuables.push_back(L"7z.exe");
expectedExecuables.push_back(L"7za.exe");
expectedExecuables.push_back(L"NativeUIHandler.exe");
expectedExecuables.push_back(L"AgentQPPMUpgrader.exe");
expectedExecuables.push_back(L"agent_troubleshooting_tool.exe");
expectedExecuables.push_back(L"cfgUpdate.exe");
expectedExecuables.push_back(L"checkvolume.exe");
expectedExecuables.push_back(L"dcagentregister.exe");
expectedExecuables.push_back(L"dcagentservice.exe");
expectedExecuables.push_back(L"dcagenttrayicon.exe");
expectedExecuables.push_back(L"dcannouncement.exe");
expectedExecuables.push_back(L"dcappcontrol.exe");
expectedExecuables.push_back(L"dcchat.exe");
expectedExecuables.push_back(L"dcconfigexec.exe");
expectedExecuables.push_back(L"DCFAService.exe");
expectedExecuables.push_back(L"DCFAService64.exe");
expectedExecuables.push_back(L"DCFAUser.exe");
expectedExecuables.push_back(L"dcfilescan.exe");
expectedExecuables.push_back(L"dcinventory.exe");
expectedExecuables.push_back(L"dcmsghandler.exe");
expectedExecuables.push_back(L"dcondemand.exe");
expectedExecuables.push_back(L"dcpatchscan.exe");
expectedExecuables.push_back(L"DCProcessMonitor.exe");
expectedExecuables.push_back(L"DCProxyFinder.exe");
expectedExecuables.push_back(L"dcrdsagentwindow.exe");
expectedExecuables.push_back(L"dcrdservice.exe");
expectedExecuables.push_back(L"dcscreenrec.exe");
expectedExecuables.push_back(L"dcstatusutil.exe");
expectedExecuables.push_back(L"dcswmeter.exe");
expectedExecuables.push_back(L"dctask64.exe");
expectedExecuables.push_back(L"dctoolshardware.exe");
expectedExecuables.push_back(L"dcuninstallsw.exe");
expectedExecuables.push_back(L"dcupload.exe");
expectedExecuables.push_back(L"dcusb32.exe");
expectedExecuables.push_back(L"dcusb64.exe");
expectedExecuables.push_back(L"dcusbsummary.exe");
expectedExecuables.push_back(L"dcwol.exe");
expectedExecuables.push_back(L"dcwolsettings.exe");
expectedExecuables.push_back(L"DevExe32.exe");
expectedExecuables.push_back(L"DevExe64.exe");
expectedExecuables.push_back(L"dpinst64.exe");
expectedExecuables.push_back(L"dpinst86.exe");
//expectedExecuables.push_back(L"EMSAddonInstaller.exe");
expectedExecuables.push_back(L"meaap.exe");
expectedExecuables.push_back(L"meaaphelper.exe");
expectedExecuables.push_back(L"file_system_watcher.exe");
expectedExecuables.push_back(L"folder_backup.exe");
expectedExecuables.push_back(L"mdmregistrationhandler.exe");
expectedExecuables.push_back(L"mdmregistrationhandler_64.exe");
expectedExecuables.push_back(L"metroapps.exe");
expectedExecuables.push_back(L"rapchat.exe");
expectedExecuables.push_back(L"rdsrunasuser.exe");
expectedExecuables.push_back(L"secaddoncrashanalyser.exe");
expectedExecuables.push_back(L"SecureDCProcess.exe");
expectedExecuables.push_back(L"selfserviceportal.exe");
expectedExecuables.push_back(L"ToolsIQ.exe");
expectedExecuables.push_back(L"uemsnotifications.exe");
expectedExecuables.push_back(L"usbeDevicelist.exe");
expectedExecuables.push_back(L"WakeOnLan.exe");
expectedExecuables.push_back(L"dcconfig.exe");
	
	
	
	
    ReadRegSZ(HKEY_LOCAL_MACHINE,gv_RegKey,"DCAgentInstallDir",&dcpath);
	dcNativeExecutables=getFilesList(string(dcpath)+"\\bin\\","*.exe*");
	if(fileexists(string(dcpath)+"\\dcconfig.exe")){
		dcNativeExecutables.push_back(L"dcconfig.exe");
	}
	for (std::vector<std::wstring>::iterator itr = expectedExecuables.begin(); itr != expectedExecuables.end(); ++itr)
                {
                    std::wstring executableName = *itr;
					//of <<"expectedExecuables.push_back(L/"+Wstring_to_string(executableName)+"/);"<<endl;
					if (std::find(dcNativeExecutables.begin(), dcNativeExecutables.end(), executableName) == dcNativeExecutables.end()) {
            missingExecutables.push_back(executableName);
        }
	}
	if (missingExecutables.empty()) {
        std::cout << "No missing elements" << std::endl;
		status=true;
    } else {
        std::cout << "Missing element(s): ";
        for ( std::vector<std::wstring>::iterator itr = missingExecutables.begin(); itr != missingExecutables.end(); ++itr) {
			std::wstring executableName = *itr;
            of <<Wstring_to_string(executableName)<<endl;
        }
        std::cout << std::endl;
    }

	ASSERT_TRUE(status == true);

}
void Versioncheck() {
LPSTR dcpath = nullptr;
   LPSTR dcversion = nullptr;
   LPSTR version = "11.2.2300.11.W";

    ReadRegSZ(HKEY_LOCAL_MACHINE, gv_RegKey, "DCAgentInstallDir", &dcpath);
    std::string str = std::string(dcpath) + "\\bin\\cfgUpdate.exe";
    startup(str.c_str());
	Sleep(300000);
	LPSTR uninstall_key = "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{6AD2231F-FF48-4D59-AC26-405AFAE23DB7}";
   
    ReadRegSZ(HKEY_LOCAL_MACHINE, uninstall_key, "DisplayVersion", &dcversion);
    ASSERT_TRUE(dcpath != nullptr && strcmp(dcversion, version) == 0);

    if (dcpath != nullptr)
    {
        delete[] dcpath;
        dcpath = nullptr;
    }
	logFile<<"dxa";

}

void CheckServiceAndScheduler(){
system("start powershell.exe Set-ExecutionPolicy RemoteSigned \n");
   system("powershell.exe C:\\dcBuild\\CheckServiceScheduler.ps1");
 
   DWORD valueData=0;
   ReadDwordRegistryData(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", "dcServiceScheduler",  &valueData );
   ASSERT_TRUE(valueData == 0);
   

}

void CheckOndemandRunning(){
bool status=false;
	DWORD dwProcessId = GetProcessID("dcondemand.exe", -1);
	if (dwProcessId != 0)
	{
		//USERMSG("VerifyTrustedFiles.exe is still running with pid : %lu\n", dwProcessId);
		status=true;
	}
	else
	{ //failed
		status=false;
	}
	ASSERT_TRUE(status == true);
}

void CheckTrayiconRunning(){
//5mins sleep 
	bool status=false;
	DWORD dwProcessId = GetProcessID("dcagenttrayicon.exe", -1);
	if (dwProcessId != 0)
	{
		//USERMSG("VerifyTrustedFiles.exe is still running with pid : %lu\n", dwProcessId);
		status=true;
	}
	else
	{ //failed
		status=false;
	}
	ASSERT_TRUE(status == true);

}
void ResourceIdCheck(){
bool check;
    LPCSTR DCAgent_SystemDetails_path = "SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\SystemDetails";
	
   // bool check = CheckRegistryValue(DCAgent_path, "BlockCrashedConfig");
    //bool check1 = CheckRegistryValue(DCAgent_path, "CustomerId");
	
   if (CheckRegistryValue(DCAgent_SystemDetails_path, "DCAgentResourceID"))
   {
	    check= true;
   }
   else
   { 
	   check= false;
   }
   
    ASSERT_TRUE(true == check);

}
void modifyAgentComponentSettingsjson(string new_value)
{
    // Read the JSON file
    std::ifstream inputFile("C:\\mockserverbuild\\servecontent\\servecontent\\client-data\\1\\agent\\AgentComponentSettings.json");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open input file." << std::endl;
        return;
    }

    std::string jsonString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Parse the JSON string into a RapidJSON document
    rapidjson::Document document;
    rapidjson::ParseResult parseResult = document.Parse(jsonString.c_str());

    // Check if parsing was successful
    if (!parseResult) {
        std::cout << "Failed to parse JSON: " << std::endl;
        return;
    }

    // Modify the value of "2" if it exists
    if (document.HasMember("2")) {
        // Modify the value of "2"
        rapidjson::Value newValue(new_value.c_str(), document.GetAllocator());
        document["2"] = newValue;  // Replace "new value" with the desired new value

        // Convert the modified document back to a JSON string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string modifiedJsonString = buffer.GetString();

        // Save the modified JSON string back to the same file
        std::ofstream outputFile("C:\\mockserverbuild\\servecontent\\servecontent\\client-data\\1\\agent\\AgentComponentSettings.json");
        if (!outputFile.is_open()) {
            std::cout << "Failed to open output file." << std::endl;
            return;
        }
        outputFile << modifiedJsonString;
        outputFile.close();

        std::cout << "JSON file modified and saved successfully." << std::endl;
    } else {
        std::cout << "Key '2' not found in JSON." << std::endl;
    }
}


void AgentUpgradationCheck(){
	const char* filename = "testcase.json";

    // Remove the file "testcase.json"
    int result = remove(filename);
    int count = 0;

    while (count < 3) {
        LPCTSTR sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        LPCTSTR value = TEXT("DCServerProtocol");
        LPCTSTR data = TEXT("http");
        ModifyRegistryValue(sk, value, data);

        sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        value = TEXT("DCServerName");
        data = TEXT("acp-w10x64-2");
        ModifyRegistryValue(sk, value, data);

		sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        value = TEXT("DCLastAccessName");
        data = TEXT("acp-w10x64-2");
        ModifyRegistryValue(sk, value, data);

        sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent");
        value = TEXT("DCAgentVersion");
        data = TEXT("10.1.2219");
        ModifyRegistryValue(sk, value, data);

        LPSTR dcpath = nullptr;
        ReadRegSZ(HKEY_LOCAL_MACHINE, gv_RegKey, "DCAgentInstallDir", &dcpath);

        std::string str = std::string(dcpath) + "\\bin\\cfgUpdate.exe";
        startup(str.c_str());

        time_t starttime = time(0);
        tm* ltm = localtime(&starttime);
        int target_min = 32 + ltm->tm_min;

        while (1) {
            time_t now1 = time(0);
            tm* ltm1 = localtime(&now1);
            if (fileexists("testcase.json")) {
                break;
            }
            else if (30 + ltm1->tm_min == target_min) {
                break;
            }
        }

        count++;

        if (fileexists("testcase.json")) {
            break;
        }
    }

    std::string checkvalue;

    if (fileexists("testcase.json")) {
        FILE* fp = fopen("testcase.json", "r");

        if (fp != nullptr) {
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            Document d;
            d.ParseStream(is);
            fclose(fp);

            if (d.IsArray()) {
                const rapidjson::Value& attributes = d;

                for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
                    const rapidjson::Value& attribute = *itr;
                    if (attribute.IsObject()) {
                        checkvalue = attribute["status"].GetString();
                        break;
                    }
                }
            }
        }
    }
    else {
        checkvalue = "Failure";
    }

   

    ASSERT_EQ("Success", checkvalue) << "Custom failure message: Expected 'Success', but got '" << checkvalue << "'";
}
void AgentUpgradationbackup(){
	std::wstring taskName = L"DCAgentUpdater";

  
	const char* filename = "testcase.json";

    // Remove the file "testcase.json"
    int result1 = remove(filename);
    int count = 0;

    while (count < 3) {
       
       bool invoked = RunScheduledTask(taskName);
    if (invoked) {
        std::cout << "Task invocation successful." << std::endl;
    } else {
        std::cout << "Task invocation failed." << std::endl;
    }

        time_t starttime = time(0);
        tm* ltm = localtime(&starttime);
        int target_min = 32 + ltm->tm_min;

        while (1) {
            time_t now1 = time(0);
            tm* ltm1 = localtime(&now1);
            if (fileexists("testcase.json")) {
                break;
            }
            else if (30 + ltm1->tm_min == target_min) {
                break;
            }
        }

        count++;

        if (fileexists("testcase.json")) {
            break;
        }
    }

    std::string checkvalue;

    if (fileexists("testcase.json")) {
        FILE* fp = fopen("testcase.json", "r");

        if (fp != nullptr) {
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            Document d;
            d.ParseStream(is);
            fclose(fp);

            if (d.IsArray()) {
                const rapidjson::Value& attributes = d;

                for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
                    const rapidjson::Value& attribute = *itr;
                    if (attribute.IsObject()) {
                        checkvalue = attribute["status"].GetString();
                        break;
                    }
                }
            }
        }
    }
    else {
        checkvalue = "Failure";
    }

   

    ASSERT_EQ("Success", checkvalue) << "Custom failure message: Expected 'Success', but got '" << checkvalue << "'";
}


class CommonTest : public ::testing::Test {
protected:
	static LPSTR dcserviceName;
	static LPSTR dcpath;
    static void SetUpTestCase() {
		RecordProperty("timestamp", FormatEpochTimeInMillisAsIso8601());
        logFile.open("test_log.txt", std::ios::app); // Open the log file in append mode
        if (!logFile.is_open()) {
            std::cerr << "Error opening log file!" << std::endl;
        }
		LPSTR dcserviceNameBuffer = nullptr;
        ReadRegSZ(HKEY_LOCAL_MACHINE, gv_RegKey, "AgentServiceName", &dcserviceNameBuffer);
        if (dcserviceNameBuffer) {
           dcserviceName = new char[strlen(dcserviceNameBuffer) + 1];
            strcpy(dcserviceName, dcserviceNameBuffer);

            free(dcserviceNameBuffer);
        } else {
            std::cerr << "Error retrieving dcserviceName from registry!" << std::endl;
        }
		LPSTR dcpathBuffer = nullptr;
        ReadRegSZ(HKEY_LOCAL_MACHINE, gv_RegKey, "DCAgentInstallDir", &dcpathBuffer);
		if (dcpathBuffer) {
		
         dcpath = new char[strlen(dcpathBuffer) + 1];
            strcpy(dcpath, dcpathBuffer);
            free(dcpathBuffer);
		}
		else {
            std::cerr << "Error retrieving dcserviceName from registry!" << std::endl;
        }
        
		logFile<<"DCDirPath:"<<dcpath << std::endl;
		logFile<<"DCserviceName:"<<dcserviceName << std::endl;
    } 
	

    static void TearDownTestCase() {
        logFile.close(); // Close the log file
    }
 // Add dcpath as a member variable
	

};

LPSTR CommonTest::dcserviceName = nullptr;
LPSTR CommonTest::dcpath = nullptr;
class Mockserver : public CommonTest{
 protected:
	/* static void SetUpTestCase() { RecordProperty("timestamp", FormatEpochTimeInMillisAsIso8601());
	  logFile.open("test_log.txt", std::ios::app); // Open the log file in append mode
        if (!logFile.is_open()) {
            std::cerr << "Error opening log file!" << std::endl;
        }}

	 static void TearDownTestCase() {
        logFile.close(); // Close the log file
    }*/
  

 
};
class Server : public CommonTest {
 protected:
\
	// static void SetUpTestCase() { RecordProperty("timestamp", FormatEpochTimeInMillisAsIso8601()); }
  

 
};

class Server_repair : public CommonTest {
 protected:
 
	// static void SetUpTestCase() { RecordProperty("timestamp", FormatEpochTimeInMillisAsIso8601()); }
  

 
};

class DcAgentMonitoring : public CommonTest {
 protected:

	// static void SetUpTestCase() { RecordProperty("timestamp", FormatEpochTimeInMillisAsIso8601()); }
  

 
};




TEST_F(Mockserver, Installationstatus) {
	logFile << "Log message for Installationstatus" << std::endl;
	const char* valueName = "ClockBeginTime";
    
    // Get the current clock time
    clock_t begin_time = clock();
	printf("Retrieved value: %ld\n", static_cast<unsigned long long>(begin_time));

    // Add the clock time to the Windows Registry
    AddClockRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation",valueName, begin_time);
	clock_t retrievedValue = GetClockRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", valueName);
	printf("Retrieved value: %ld\n", static_cast<unsigned long long>(retrievedValue));
	CreatePerformanceCounterAlert();
	int count=0;
  while(count<3)
	{
	time_t starttime = time(0);
	tm *ltm = localtime(&starttime);
	int min=32+ltm->tm_min;
	while(1)
	{  time_t now1 = time(0);
		tm *ltm1 = localtime(&now1);
		if(fileexists("testcase.json"))
		{break;
		}
		else if(30+ltm1->tm_min==min)
		{break;
		}

	}
  count++;
  if(fileexists("testcase.json"))
		{break;
		}
  }
    string str;
  if(fileexists("testcase.json"))
  {

	 FILE* fp = fopen("testcase.json", "r");
   
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    //assert(d.IsArray());
    fclose(fp);
    //printf("hello = %s\n", d["status"].GetString());
   // str = d["status"].GetString();
	const rapidjson::Value& attributes =d;
   assert(attributes.IsArray()); 

   int counter = 0; 

   for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) 
   {
      const rapidjson::Value& attribute = *itr;
      assert(attribute.IsObject()); // each attribute is an object
	  str = attribute["status"].GetString();
   }}
  else{str="Failure";}
   RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_0706496");
   RecordProperty("testcasedescription", "it checks the agent installation status");
   cout<<"find me"<<str;
   
   ASSERT_TRUE("Success" == str);
}

TEST_F(Mockserver, DriverInstallationStatus) {
	logFile << "Log message for DriverInstallationStatus" << std::endl;
	modifyAgentComponentSettingsjson("1");
	DWORD data = 0;
    RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_7842306");
    RecordProperty("testcasedescription", "it checks the driver installation and running status");
  //  LPSTR dcpath = nullptr;
    //GetDCAgentDirectory(&dcpath);

    ReadRegSZ(HKEY_LOCAL_MACHINE, gv_RegKey, "DCAgentInstallDir", &dcpath);
    int count = 0;
    bool DriverInstallation = false;
    bool DriverRunningstatus = false;
    while (count < 3) {
        try {
				std::wstring specificRegistryKeyPath = L"SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\MetadataVersions";
				std::wstring valueName = L"AgentComponentsSettingsTime";
				data++;
				 bool modificationSuccessful = ModifyRegistryDWORDValue(specificRegistryKeyPath, valueName, data);
				if (modificationSuccessful) {
					logFile << "Registry value modified successfully." << std::endl;
				} else {
					logFile << "Failed to modify registry value." << std::endl;
				}
            LPCTSTR sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
            LPCTSTR value = TEXT("DCServerProtocol");
            LPCTSTR data = "http";
            ModifyRegistryValue(sk, value, data);
            sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
            value = TEXT("DCServerName");
            data = "acp-w10x64-2";
            ModifyRegistryValue(sk, value, data);

            string str = string(dcpath) + "\\bin\\cfgUpdate.exe";
            startup(str.c_str());
            time_t starttime = time(0);
            tm* ltm = localtime(&starttime);
            int min = 32 + ltm->tm_min;
            while (1) {
                time_t now = time(0);
                tm* ltm = localtime(&now);
                if (isDriverInstalled()) {
                    DriverInstallation = true;
                    break;
                }
                else if (30 + ltm->tm_min == min) {
                    break;
                }
            }
            count++;
            if (DriverInstallation == true) {
                if (CheckIfAlreadyRunning("DCFAUser.exe")) {
                    DriverRunningstatus = true;
                   
                    break;
                }
            }
        }
        catch (const std::exception& e) {
            // Handle the exception
            // You can log the exception details or perform any necessary cleanup
            // For example:
           logFile << "Exception occurred: " << e.what() << std::endl;
        }
    }

    ASSERT_TRUE(DriverRunningstatus == true);
}

TEST_F(Mockserver, KillProcessByNameTest) {
	 // Specify the names of the processes to kill
    std::vector<std::string> processNames;
    processNames.push_back("dcconfig.exe");
    processNames.push_back("agent_troubleshooting_tool.exe");

    // Try to kill each process by name
    bool allProcessesKilled = true;
    for (std::vector<std::string>::const_iterator it = processNames.begin(); it != processNames.end(); ++it) {
        const std::string& processName = *it;
        bool killed = killProcess(processName);
        if (killed) {
            allProcessesKilled = false;
            break;
        }
    }

    // Verify that all processes were unable to be killed
    ASSERT_TRUE(allProcessesKilled);
}

// Test case to check registry key permissions with all access blocked
TEST_F(Mockserver, CheckRegistryPermissions) {
    
  
   std::wstring specificRegistryKeyPath = L"SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent";

bool isAccessible = CheckRegistryKeyAccessibility(specificRegistryKeyPath);
    EXPECT_FALSE(isAccessible);
}

TEST_F(Mockserver, BlockReadWriteModify) {
std::vector<std::pair<std::string, std::string>> foldersAndFiles;
    foldersAndFiles.push_back(std::make_pair( string(dcpath)+"\\bin", "agent_troubleshooting_tool.exe"));
    foldersAndFiles.push_back(std::make_pair(string(dcpath)+"\\bin", "dcagentregister.exe"));
    foldersAndFiles.push_back(std::make_pair(string(dcpath)+"\\Certificates", "client.p12"));
	foldersAndFiles.push_back(std::make_pair(string(dcpath)+"\\data", "agent-settings.xml"));
	foldersAndFiles.push_back(std::make_pair(string(dcpath)+"\\Scripts", "Bit-locker.bat"));
	foldersAndFiles.push_back(std::make_pair(string(dcpath)+"\\licenses", "LICENSE_LIBXML.txt"));
	foldersAndFiles.push_back(std::make_pair(string(dcpath)+"\\rds", "AgentHook.dll"));

    for (std::vector<std::pair<std::string, std::string>>::const_iterator it = foldersAndFiles.begin(); it != foldersAndFiles.end(); ++it) {
        const std::pair<std::string, std::string>& folderAndFile = *it;
        const std::string& folder = folderAndFile.first;
        const std::string& file = folderAndFile.second;

        std::string filePath = folder + "\\" + file;
		std::ifstream fileStream(filePath);
        bool fileExists = fileStream.good();
        fileStream.close();

      // Check if the file exists
        if (fileExists) {
            // Attempt to open the file with exclusive access
            std::ifstream inputFile(filePath, std::ios::in | std::ios::binary);
            bool canRead = !inputFile;

            // Attempt to write to the file
            std::ofstream outputFile(filePath);
            bool canWrite = outputFile.is_open();
            outputFile.close();

            // Attempt to modify the file
            bool canModify = std::rename(filePath.c_str(), filePath.c_str()) == 0;

            if (canRead) {
                logFile << "File path " << filePath << std::endl;
            }

            // Verify the results
            EXPECT_FALSE(canRead);
            EXPECT_FALSE(canWrite);
            EXPECT_FALSE(canModify);
        } else {
            logFile << "File does not exist: " << filePath << std::endl;
            // Handle the case where the file doesn't exist
            // For example, you could skip the operations or take other actions
        }
    }

}


TEST_F(Mockserver, AgentUpgradationCheck) {
	modifyAgentComponentSettingsjson("0");
	std::string str = "\"" + string(dcpath) + "\\bin\\DCFAService.exe\" -stop DFMFilter";
system(str.c_str());

str = "\"" + string(dcpath) + "\\bin\\DCFAService.exe\" -stop DRMFilter";
system(str.c_str());
	logFile << "Log message for AgentUpgradationCheck" << std::endl;
    RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0857395");
    RecordProperty("testcasedescription", "it checks the agent upgradation flow");
	AgentUpgradationCheck();
	StartPerformanceCounterAlert();

    
}

TEST_F(Mockserver, Servicerunningstatus){
	 RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_7311248");
    RecordProperty("testcasedescription", "it checks service running status after upgradation");
	logFile << "Log message for Servicerunningstatus" << std::endl;
	Sleep(10000);
	LPSTR dcserviceName= nullptr;
 ReadRegSZ(HKEY_LOCAL_MACHINE,gv_RegKey,"AgentServiceName",&dcserviceName);
 logFile << "Log message for Servicerunningstatus" << std::endl;
 
	std::wstring serviceName = LPSTRToWString(dcserviceName);
    bool isRunning = IsServiceRunning(serviceName);
    if (isRunning) {
       logFile<< "Service is running." << std::endl;
    } else {
        logFile<< "Service is not running." << std::endl;
    }
	ASSERT_TRUE(isRunning,true);

}


TEST_F(Mockserver, TOTPAgentUpgradationCheck)
{
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_7651149");
    RecordProperty("testcasedescription", "it checks the agent upgradation flow with TOTP enabled");
	logFile << "Log message for TOTPAgentUpgradationCheck" << std::endl;
	const char* subKey = "Software\\AdventNet\\DesktopCentral\\DCAgent\\Settings";  
    const char* valueName = "PPUEnabled";      

    if (DeleteRegistryValue(HKEY_LOCAL_MACHINE, subKey, valueName)) {
        // Registry value deleted successfully
    } else {
        // Failed to delete registry value
    }
	 AgentUpgradationCheck();

}

TEST_F(Mockserver, MsichecksumVerify)
{
	logFile << "Log message for MsichecksumVerify" << std::endl;LPSTR dcpath= nullptr;
 ReadRegSZ(HKEY_LOCAL_MACHINE,gv_RegKey,"DCAgentInstallDir",&dcpath);
	std::string file1 = string(dcpath)+"\\updates\\DesktopCentralAgent.msi";
    std::string file2 = "C:\\mockserverbuild\\servecontent\\servecontent\\agent\\DesktopCentralAgent.msi";
	printf("file1 = %s\n",file1);
	printf("file2 = %s\n",file2);


    // Calculate checksums
    uint32_t checksum1 = calculateChecksum(file1);
    uint32_t checksum2 = calculateChecksum(file2);

    // Compare checksums
    if (checksum1 == checksum2) {
        std::cout << "Checksum verification successful. The files are identical." << std::endl;
    } else {
        std::cout << "Checksum verification failed. The files are different." << std::endl;
    }
	ASSERT_TRUE(checksum1 == checksum2);
}


TEST_F(Mockserver, AgentUpgradationbackup){
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_8085404");
    RecordProperty("testcasedescription", "it checks the agent upgradation backup via scheduler");
	logFile << "Log message for AgentUpgradationbackup" << std::endl;
    const char* oldFileName = "C:\\mockserverbuild\\servecontent\\servecontent\\agent\\DesktopCentralAgent.msi";
    const char* newFileName = "C:\\mockserverbuild\\servecontent\\servecontent\\agent\\DesktopCentralAgent_old.msi";

    int result = std::rename(oldFileName, newFileName);
	LPCTSTR sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        LPCTSTR value = TEXT("DCServerProtocol");
        LPCTSTR data = TEXT("http");
        ModifyRegistryValue(sk, value, data);

        sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        value = TEXT("DCServerName");
        data = TEXT("acp-w10x64-2");
        ModifyRegistryValue(sk, value, data);

		sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        value = TEXT("DCLastAccessName");
        data = TEXT("acp-w10x64-2");
        ModifyRegistryValue(sk, value, data);

        sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent");
        value = TEXT("DCAgentVersion");
        data = TEXT("10.1.2219");
        ModifyRegistryValue(sk, value, data);

        LPSTR dcpath = nullptr;
        ReadRegSZ(HKEY_LOCAL_MACHINE, gv_RegKey, "DCAgentInstallDir", &dcpath);

        std::string str = std::string(dcpath) + "\\bin\\cfgUpdate.exe";
        startup(str.c_str());
		Sleep(30000);
		result = std::rename(newFileName,oldFileName);
		AgentUpgradationbackup();
}

TEST_F(Mockserver, ServiceCrashbackup)
{
		RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_8283221");
    RecordProperty("testcasedescription", "it checks the agent upgradation after agent service crashed");
	logFile << "Log message for ServiceCrashbackup" << std::endl;
	std::string exeName = "dcagentservice.exe";
LPSTR dcserviceName= nullptr;
 ReadRegSZ(HKEY_LOCAL_MACHINE,gv_RegKey,"AgentServiceName",&dcserviceName);
	std::wstring serviceName = LPSTRToWString(dcserviceName);
    bool isRunning = true;
	int count=0;
	
	//Crash Dcagent service
while(count<2&&isRunning) 
{
// Call the function to kill the process
    if (killProcessByName(exeName)) {
       logFile << "Process terminated successfully." << std::endl;
		
    } else {
        logFile<< "Failed to terminate process." << std::endl;
		
    }
	Sleep(30000);
	isRunning = IsServiceRunning(serviceName);
}
	LPCTSTR sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        LPCTSTR value = TEXT("DCServerProtocol");
        LPCTSTR data = TEXT("http");
        ModifyRegistryValue(sk, value, data);

        sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        value = TEXT("DCServerName");
        data = TEXT("acp-w10x64-2");
        ModifyRegistryValue(sk, value, data);

		sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent\\ServerInfo");
        value = TEXT("DCLastAccessName");
        data = TEXT("acp-w10x64-2");
        ModifyRegistryValue(sk, value, data);

        sk = TEXT("SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent");
        value = TEXT("DCAgentVersion");
        data = TEXT("10.1.2219");
        ModifyRegistryValue(sk, value, data);
		AgentUpgradationbackup();

}

TEST_F(Mockserver, testUninstallationstatus) {
	
	logFile << "Log message for Uninstallationstatus" << std::endl;
	int count=0;
	char filename[] = "testcase.json";
  // remove the file "program.cpp"
  int result = remove(filename);
	system("C:\\dcBuild\\runmockserversetup.bat Uninstallagent");
    string status;
  while(count<3)
	{
	time_t starttime = time(0);
	tm *ltm = localtime(&starttime);
	int min=32+ltm->tm_min;
	while(1)
	{  time_t now1 = time(0);
		tm *ltm1 = localtime(&now1);
		if(fileexists("testcase.json"))
		{break;
		}
		else if(30+ltm1->tm_min==min)
		{break;
		}

	}
  count++;
  if(fileexists("testcase.json"))
		{break;
		}
  }

  if(fileexists("testcase.json"))
  {

	 FILE* fp = fopen("testcase.json", "r");
   
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    //assert(d.IsArray());
    fclose(fp);
    //printf("hello = %s\n", d["status"].GetString());
   // str = d["status"].GetString();
	const rapidjson::Value& attributes =d;
   assert(attributes.IsArray()); 

   int counter = 0; 

   for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) 
   {
      const rapidjson::Value& attribute = *itr;
      assert(attribute.IsObject()); // each attribute is an object
	  status = attribute["status"].GetString();
   }}
  else{status="Failure";}
   RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_4545362");
   RecordProperty("testcasedescription", "it checks the agent Uninstallation status");
   ASSERT_TRUE("Success" == status);
}

TEST_F(Mockserver, testUninstallationContolPanelCheck){

   RecordProperty("severity", "HIGH");
   RecordProperty("description", " UI_DCEE_AgentFramework_8533024");
   RecordProperty("testcasedescription", "it checks whether agent deleted from control panel");
	logFile << "Log message for UninstallationContolPanelCheck" << std::endl;
	std::string softwareName = "ManageEngine Endpoint Central - Agent";


	bool check =IsSoftwareInstalled(softwareName);
    if (check)
    {
         logFile << "Software is installed." << std::endl;
    }
    else
    {
        logFile << "Software is not installed." << std::endl;
    }
   ASSERT_TRUE(false == check);

}

TEST_F(Mockserver, testServiceStoppedstatus){
	logFile << "Log message for ServiceStoppedstatus" << std::endl;

 RecordProperty("severity", "HIGH");
   RecordProperty("description", " UI_DCEE_AgentFramework_0753066");
   RecordProperty("testcasedescription", "checks whether service is stopped ");
	std::wstring serviceName = LPSTRToWString(dcserviceName);
	logFile <<"dcserviceName"<<Wstring_to_string(serviceName)<< std::endl;
    bool isRunning = IsServiceDeleted(serviceName);
    if (isRunning) {
       logFile<< "Service is deleted." << std::endl;
    } else {
        logFile<< "Service is not deleted." << std::endl;
    }
	ASSERT_TRUE(isRunning);

}

TEST_F(Mockserver, testcheckForResidueExe){
	logFile << "Log message for checkForResidueExe" << std::endl;
	 RecordProperty("severity", "HIGH");
   RecordProperty("description", " UI_DCEE_AgentFramework_0904400");
   RecordProperty("testcasedescription", "Checks whether all exe deleted in uninstallation");
	cout<<dcpath;
	std::string folderPath = string(dcpath);
	logFile <<folderPath << std::endl;
	std::ofstream outputFile(folderPath+"//example.txt"); // Create or open the file "example.txt"

    if (outputFile.is_open()) {
        outputFile << "This is some text written to the file." << std::endl;
        outputFile << "More text on a new line." << std::endl;
        outputFile.close(); // Close the file
        logFile << "File created successfully." << std::endl;
    } else {
       logFile << "Error creating file." << std::endl;
    }
    bool status = IsExeFileNotPresent(folderPath);
    if (status) {
        logFile << "No executable files are present in the folder." << std::endl;
    } else {
        logFile << "At least one executable file exists in the folder." << std::endl;
    }
	ASSERT_TRUE(status,true);

}

TEST_F(Mockserver,testRootCertificateNotInstalled){
	logFile << "Log message for RootCertificateNotInstalled" << std::endl;

	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_3231014");
    RecordProperty("testcasedescription", "it checks whether Root certificate deleted ");
	bool check;

	std::wstring issuerName1 = L"ManageEngineCA";
	std::wstring issuerName2 = L"ManageEngineCA-DS-CA";

    if (isRootCertificateNotInstalled(issuerName1))
    {
        logFile << "Root certificate with the specified issuer name is installed." << std::endl;
		check=true;
    }
    else
    {
        logFile<< "Root certificate with the specified issuer name is not installed." << std::endl;
		check = false;
    }
	 ASSERT_TRUE(check);
}

TEST_F(Mockserver, Ds_installationstatus){


	logFile << "Log message for Uninstallationstatus" << std::endl;
	int count=0;
	char filename[] = "testcase.json";
  // remove the file "program.cpp"
  int result = remove(filename);
	system("C:\\dcBuild\\localsetup\\setup.bat 1");
    string status;
  while(count<3)
	{
	time_t starttime = time(0);
	tm *ltm = localtime(&starttime);
	int min=32+ltm->tm_min;
	while(1)
	{  time_t now1 = time(0);
		tm *ltm1 = localtime(&now1);
		if(fileexists("testcase.json"))
		{break;
		}
		else if(30+ltm1->tm_min==min)
		{break;
		}

	}
  count++;
  if(fileexists("testcase.json"))
		{break;
		}
  }

  if(fileexists("testcase.json"))
  {

	 FILE* fp = fopen("testcase.json", "r");
   
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document d;
    d.ParseStream(is);
    //assert(d.IsArray());
    fclose(fp);
    //printf("hello = %s\n", d["status"].GetString());
   // str = d["status"].GetString();
	const rapidjson::Value& attributes =d;
   assert(attributes.IsArray()); 

   int counter = 0; 

   for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) 
   {
      const rapidjson::Value& attribute = *itr;
      assert(attribute.IsObject()); // each attribute is an object
	  status = attribute["status"].GetString();
   }}
  else{status="Failure";}
   RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_4545362");
   RecordProperty("testcasedescription", "it checks the agent Uninstallation status");
   ASSERT_TRUE("Success" == status);

}




TEST_F(Server, CheckExeSign) {
	logFile << "Log message for CheckExeSign" << std::endl;
	StartPerformanceCounterAlert();
	
	system("start powershell.exe Set-ExecutionPolicy RemoteSigned \n");
	system("powershell.exe C:\\dcBuild\\CheckIfExecutablesAreSigned.ps1");
	ifstream infile("C:\\dcBuild\\checkexesign.txt");
	string sLine;
  if (infile.good())
  {
    
    getline(infile, sLine);
    cout << sLine << endl;
  }
	 RecordProperty("failure", sLine);
	 RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_0706476");
   RecordProperty("testcasedescription", "it checks if exes signed or not");
	DWORD valueData=0;
	 ReadDwordRegistryData(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", "dcExesignature",  &valueData );
	ASSERT_TRUE(valueData == 0);
   
}

TEST_F(Server, ExeCheck){
	logFile << "Log message for ExeCheck" << std::endl;
	RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_5119342");
   RecordProperty("testcasedescription", "checks the list of  exes are downloaded");
	
	ExeCheck();
}


TEST_F(Server, RegistryCheck) {
	logFile << "Log message for RegistryCheck" << std::endl;
	
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0706515");
    RecordProperty("testcasedescription", "it checks the registry entry");
	RegistryCheck();

}

TEST_F(Server, Versioncheck)
{   RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0200319");
    RecordProperty("testcasedescription", "it checks the version in uninstall path");
	
	Versioncheck();
}

TEST_F(Server, Servicerunningstatus){
	 RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_3740658");
   RecordProperty("testcasedescription", "it checks service is running ");
	LPSTR dcserviceName= nullptr;
 ReadRegSZ(HKEY_LOCAL_MACHINE,gv_RegKey,"AgentServiceName",&dcserviceName);
	std::wstring serviceName = LPSTRToWString(dcserviceName);
    bool isRunning = IsServiceRunning(serviceName);
    if (isRunning) {
        std::cout << "Service is running." << std::endl;
    } else {
        std::cout << "Service is not running." << std::endl;
    }
	ASSERT_TRUE(isRunning);
}

TEST_F(Server, CheckupgraderScheduler) {
    RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_0706533");
   RecordProperty("testcasedescription", "it checks for service and scheduler exist");
   std::wstring taskName = L"DCAgentUpdater";
    bool exists = IsScheduledTaskExists(taskName);
    //CheckServiceAndScheduler();
	ASSERT_TRUE(exists,true);

}


TEST_F(Server, CheckOndemandRunning)
{   
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0493421");
    RecordProperty("testcasedescription", "it checks the agent ondemand exe running status");
	CheckOndemandRunning();
}

TEST_F(Server, CheckTrayiconRunning)
{
	RecordProperty("severity", "HIGH");
    RecordProperty("description", " UI_DCEE_AgentFramework_0706533");
    RecordProperty("testcasedescription", "it checks the agent trayicon runnigng status");
	CheckTrayiconRunning();
}


TEST_F(Server, ResourceIdCheck) {
	
	RecordProperty("severity", "HIGH");
    RecordProperty("description", " UI_DCEE_AgentFramework_1578504");
    RecordProperty("testcasedescription", "it checks the resource id ");
	ResourceIdCheck();
}

TEST_F(Server, CSRCertificateCheck) {
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_1995512");
    RecordProperty("testcasedescription", "checks whether the CSR certificate installed ");
    bool check=false;
    if(fileexists(string(dcpath)+"//Certificates//client.p12"))
     {check=true;
      }
 ASSERT_TRUE(true == check);

}

TEST_F(Server, AuthTokenCheck) {
	bool check;
    LPCSTR DCAgent_path = "SOFTWARE\\WOW6432Node\\AdventNet\\DesktopCentral\\DCAgent";
	
   // bool check = CheckRegistryValue(DCAgent_path, "BlockCrashedConfig");
    //bool check1 = CheckRegistryValue(DCAgent_path, "CustomerId");
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_2429562");
    RecordProperty("testcasedescription", "it checks the AuthToken ");
   if (CheckRegistryValue(DCAgent_path, "Authtoken"))
   {
	    check= true;
   }
   else
   { 
	   check= false;
   }
   
    ASSERT_TRUE(true == check);

}
TEST_F(Server,IsRootCertificateInstalled){

	RecordProperty("severity", "HIGH");
    RecordProperty("description", " UI_DCEE_AgentFramework_2762923");
    RecordProperty("testcasedescription", "it checks whether Root certificate installed  ");
	bool check;

	std::wstring issuerName1 = L"ManageEngineCA";
	std::wstring issuerName2 = L"ManageEngineCA-DS-CA";

    if (isRootCertificateInstalled(issuerName1))
    {
        std::cout << "Root certificate with the specified issuer name is installed." << std::endl;
		check=true;
    }
    else
    {
        std::cout << "Root certificate with the specified issuer name is not installed." << std::endl;
		check = false;
    }
	 ASSERT_TRUE(true == check);
}

TEST_F(Server_repair, Repairstatus)
{   
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0323098");
    RecordProperty("testcasedescription", "Checks the repair status");
	bool checkstatus;
	
		 std::string str_old = std::string(dcpath) + "\\dcconfig.exe";
		 std::string str_new = std::string(dcpath) + "\\dcconfig_old.exe";
		 const char* oldFileName = str_old.c_str();
    const char* newFileName = str_new.c_str();

    int result = std::rename(oldFileName, newFileName);
    if (result == 0) {
        printf("File renamed successfully.\n");
    } else {
        perror("Error renaming file");
    }
	string repaircommand="start /wait msiexec.exe /fa {6AD2231F-FF48-4D59-AC26-405AFAE23DB7} /qn";
	const char* command = repaircommand.c_str();
    system(command);
	if(fileexists((std::string(dcpath) + "\\dcconfig.exe")))
	{checkstatus=true;

	}
	else{
		checkstatus=false;
		 result = std::rename(newFileName, oldFileName);
    if (result == 0) {
        printf("File renamed successfully.\n");
    } else {
        perror("Error renaming file");
    }
	}
	
	ASSERT_TRUE(checkstatus==true);
	

}

TEST_F(Server_repair, Versioncheck)
{ RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0915853");
    RecordProperty("testcasedescription", "Post repair-it checks the version in uninstall path");
   
	Versioncheck();
}
TEST_F(Server_repair, RegistryCheck) {
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_2655641");
    RecordProperty("testcasedescription", "Post repair-it checks the registry entry");
	
	RegistryCheck();
}



TEST_F(Server_repair, ExeCheck){
	RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_2655663");
   RecordProperty("testcasedescription", "Post repair-checks the list of  exes are downloaded");
	
	logFile << "Log message for ExeCheck" << std::endl;
	ExeCheck();
}

TEST_F(Server_repair, CheckServiceAndScheduler) {
	 RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_2655681");
   RecordProperty("testcasedescription", "Post repair-it checks for service and scheduler exist");
	CheckServiceAndScheduler();
   
}


TEST_F(Server_repair, CheckOndemandRunning)
{
	RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_2655700");
   RecordProperty("testcasedescription", "Post repair-it checks the agent ondemand exe running status");
	CheckOndemandRunning();
}

TEST_F(Server_repair, CheckTrayiconRunning)
{
	
	RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_3243670");
   RecordProperty("testcasedescription", "Post repair- it checks the agent trayicon running status");
   CheckTrayiconRunning();
	
}
TEST_F(Server_repair, ResourceIdCheck) {
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_2655719");
    RecordProperty("testcasedescription", "Post repair-it checks the resource id  ");
	
	ResourceIdCheck();
}

TEST_F(Server,Execrashcheck )
{  RecordProperty("severity", "HIGH");
   RecordProperty("description", "UI_DCEE_AgentFramework_5213848");
   RecordProperty("testcasedescription", "it checks the exe crash while running other testcases");
   
   const char* valueName = "ClockBeginTime";
   const char* subKey = "SOFTWARE\\WOW6432Node\\AdventNet\\Automation";
	//GetDCAgentDirectory(&dcpath);

	
	string str=string(dcpath)+"\\bin\\DCFAService.exe -stop DFMFilter";
	const char* command = str.c_str();
    system(command);
	str=string(dcpath)+"\\bin\\DCFAService.exe -stop DRMFilter";
	command = str.c_str();
	system(command);
	addRegistryKey( HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation" );
	 begin_time = GetClockRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", valueName);
   
   int timedif=  clock () - begin_time ;

  // string timedif_str= StreamableToString(timedif);
   string timedif_str="7200000";
   timedif_str =timedif_str+"]]";
   checkexecrash(timedif_str);
   DWORD valueData=0;
   ReadDwordRegistryData(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", "dcNativeCrash",  &valueData );
	ASSERT_TRUE(valueData == 0);
}

TEST_F(Server,CPUUsagecheck )
{   RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_1161589");
    RecordProperty("testcasedescription", "it checks the cpu Usage while running other testcases");
	const char* valueName = "ClockBeginTime";
	const char* subKey = "SOFTWARE\\WOW6432Node\\AdventNet\\Automation";
	writeValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\WOW6432Node\\AdventNet\\Automation","dcNativeCPUAlert","0",REG_DWORD);
	StopPerformanceCounterAlert();
	 begin_time = GetClockRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", valueName);
    int timedif=  clock () - begin_time ;
   // string timedif_str= StreamableToString(timedif);
	string timedif_str="7200000";
    timedif_str =timedif_str+"]]";
    checkCPUUsuageAlertEventLog(timedif_str);
    DWORD valueData=0;
    ReadDwordRegistryData(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", "dcNativeCPUAlert",  &valueData );
    ASSERT_TRUE(valueData == 0);
}

TEST_F(Server,MemoryUsagecheck )
{
	RecordProperty("severity", "HIGH");
    RecordProperty("description", "UI_DCEE_AgentFramework_0630956");
    RecordProperty("testcasedescription", "it checks the memory Usage while running other testcases");
	const char* valueName = "ClockBeginTime";
	const char* subKey = "SOFTWARE\\WOW6432Node\\AdventNet\\Automation"; 
	writeValue(HKEY_LOCAL_MACHINE,"SOFTWARE\\WOW6432Node\\AdventNet\\Automation","dcNativeMemoryAlert","0",REG_DWORD);
    int timedif=  clock () - begin_time ;
	 begin_time = GetClockRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", valueName);
    //string timedif_str= StreamableToString(timedif);
	string timedif_str="7200000";
    timedif_str =timedif_str+"]]";
    checkMemoryUsuageAlertEventLog(timedif_str);
    DWORD valueData=0;
    ReadDwordRegistryData(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\AdventNet\\Automation", "dcNativeMemoryAlert",  &valueData );
	ASSERT_TRUE(valueData == 0);
}

int main(int argc, char** argv)
{    
	 testing::InitGoogleTest(&argc, argv);
	  // Redirect the standard output to a file
               // Redirect cout to the file

    int result = RUN_ALL_TESTS();

    // Restore cout's original stream buffer
   
	//::testing::GTEST_FLAG(filter) = "Mockserver.*,Server.*Exe"; 
	 //--gtest_filter=Mockserver.DriverInstallationStatus
	  return result;
}