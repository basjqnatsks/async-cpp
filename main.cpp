#include <iostream>
#include <unistd.h>
#include <future>
#include <deque>
#include "curl/curl.h"
uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}
void task(){
			CURL *curl = curl_easy_init();
			struct curl_slist *headers = NULL;
			int response_code;
			std::string response_string;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);


			headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36");
			//headers = curl_slist_append(headers, "user-agent: ");
			//headers = curl_slist_append(headers, "Content-Language: en-US");
			//headers = curl_slist_append(headers, "Connection: close");
			//headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
			
			headers = curl_slist_append(headers, "Accept: application/json");
			headers = curl_slist_append(headers, "Authorization: mZimCgWF7ZHboAC4M1vxhZ1VnVnY3UbdWfaeIb47CUw.eyJpbnN0YW5jZUlkIjoiMDY3NDVhYWEtZmEyZC00ZjI0LTkxZGQtN2I0NTFiZTE0ZTk5IiwiYXBwRGVmSWQiOiIyMmJlZjM0NS0zYzViLTRjMTgtYjc4Mi03NGQ0MDg1MTEyZmYiLCJtZXRhU2l0ZUlkIjoiMDY3NDVhYWEtZmEyZC00ZjI0LTkxZGQtN2I0NTFiZTE0ZTk5Iiwic2lnbkRhdGUiOiIyMDIyLTAzLTA1VDIzOjU4OjEwLjU3OVoiLCJkZW1vTW9kZSI6ZmFsc2UsImFpZCI6IjkwOTQ1MTllLTdkZGEtNGM2MC1iN2U3LThhYTQzOTlhZTQzZCIsInNpdGVPd25lcklkIjoiMmQxMWMxNjctOTVhZS00NGRjLTgwMjktNTI0MzFjZTEwYzEwIn0");
			headers = curl_slist_append(headers, "content-type: application/json");
			headers = curl_slist_append(headers, "Content-Language: en-US");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_URL, "https://www.rodevy.biz/_api/wix-sm-webapp/v1/auth/signup");
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
			
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"email\":\"asdsaddfdsfdsf@gmail.com\",\"password\":\"dsdsdfsdfs\",\"profilePrivacyStatus\":\"PRIVATE\",\"contactInfo\":{\"customFields\":[],\"phones\":[],\"emails\":[\"asdsad@gmail.com\"]}}");

			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 1);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST , 1);
			//curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/certs/cabundle.pem");
			curl_easy_setopt(curl, CURLOPT_CAPATH, "/etc/cert-dir");
			//std::string lp = var->ProxyArray[(rand() % var->ProxyArraysize)];
			//std::cout << lp << "\n";
			//curl_easy_setopt(curl, CURLOPT_PROXY, lp.c_str());
			//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"agent\": {\"name\": \"Minecraft\",\"version\": 1},\"clientToken\":\"1\",\"username\": \"liciafaithful@hotmail.com\",\"password\": \"Awesome1\"}");
			CURLcode res = curl_easy_perform(curl);
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			if (response_code != 200){
				std::cout << response_code << "\n";
				//std::cout << response_string << "\n";
			}
			else{
				//std::cout << response_code << "\n";
			}
			
			curl_easy_cleanup(curl);
}





int main(void) {
	srand (timeSinceEpochMillisec());
	std::deque<std::future<void>> Container;
	for (int x = 0; x < 1; x++){
		Container.push_back(std::async(task));
	}
	
	while (!Container.empty()){
		Container.front().get();
		Container.pop_front();
	}
	std::cout << "hello\n";
  	return 0;
}

