#include "FirebaseJson.h"
#include <WiFiClientSecureAxTLS.h>
//Google firebase fingerprint(~2019.7.3~?)
const char* fingerprint = "B6:F5:80:C8:B1:DA:61:C1:07:9D:80:42:D8:A9:1F:AF:9F:C8:96:7D";
#define PORT 443
axTLS::WiFiClientSecure client;
typedef String Json;
Json json;
class FirebaseJson {
private:
	const char*Server, *Auth, *uri;
public:


	FirebaseJson(const char* server, const char* auth)
	{
		Server = server;
		Auth = auth;
	}
	int ReadytoSend() {
		int k = client.connect(Server, PORT);
		if (!k) {
			client.verify(fingerprint, Server);
			client.connect(Server, PORT);
		}
		return k;
	}

	void SetJson(String key, String val) {
		String n = "\"";
		String ptr = "{" + n + key + n + ":" + n + val + n + "}";
		json = ptr;
	}
	void SetJson(String key, int val) {
		String n = "\"";
		String ptr = "{" + n + key + n + ":" + n + String(val) + n + "}";
		json = ptr;
	}
	void SetJson(String key, double val) {
		String n = "\"";
		String ptr = "{" + n + key + n + ":" + n + String(val) + n + "}";
		json = ptr;
	}
	void Send(const char* method, const char* uri) {
		client.print(String(method) + " " + String(uri) + ".json HTTP/1.1\n");
		client.print("HOST: " + String(Server) + "\n");
		client.print("Connection: close\n");
		client.print("Authorization: " + String(Auth) + "\n");
		client.print("Content-Type: application/json; UTF-8\n");
		client.print("Content-Length: " + String(json.length()) + "\n\n");
		client.println(json + "\n\n");
	}
	void Send(const char* uri) {
		Send("GET", uri);
	}
};