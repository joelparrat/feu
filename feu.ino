
/*
  Feux tricolore
*/

// digital output feu 1 pin D0=rouge1 D1=jaune1 D2=vert1
// digital output feu 2 pin D3=rouge2 D4=jaune2 D5=vert2
// digital input pieton pin D6=pieton1 D7=pieton2

#include "ESP8266WiFi.h"

#define ROUGE1 0x80
#define JAUNE1 0x40
#define VERT1 0x20
#define ROUGE2 0x10
#define JAUNE2 0x8
#define VERT2 0x4
#define ATT0 0
#define ATT1 1
#define ATT2 2
#define ATT3 3
#define TMP0 30
#define TMP1 10
#define TMP2 5
#define TMP3 1

// feu francais

// etat 1 rouge1 et vert2  att0 = tmp0 = 30s
// etat 2 rouge1 et jaune2 att1 = tmp1 = 10s
// etat 3 rouge1 et rouge2 att2 = tmp2 =  5s
// etat 4 vert1  et rouge2 att0 = tmp0 = 30s
// etat 5 jaune1 et rouge2 att1 = tmp1 = 10s
// etat 6 rouge1 et rouge2 att2 = tmp2 =  5s

// etat 0 valeur 3 tout les feux en cligno jaune
// etat n valeur 0 fin des etape repart en 1

char ett[] = {3, ROUGE1|VERT2|ATT0, ROUGE1|JAUNE2|ATT1, ROUGE1|ROUGE2|ATT2, VERT1|ROUGE2|ATT0, JAUNE1|ROUGE2|ATT1, ROUGE1|ROUGE2|ATT2, 0};
char dre[] = {TMP0, TMP1, TMP2, TMP3};
char ind = 1;
byte serveur[] = {192,168,1,7};
byte port = 80;

WiFiClient client;

// setup

void setup()
{
	Serial.begin(115200);

	// feu 1
	
	pinMode(D0, OUTPUT);
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	
	// feu 2
	
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);

	// pieton 1 et 2
	
	pinMode(D6, INPUT);
	pinMode(D7, INPUT);
/*
	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(2000);
	Serial.println("scan start");
	
	// WiFi.scanNetworks will return the number of networks found
	
	int n = WiFi.scanNetworks();
	
	Serial.println("scan done");
	if (n == 0)
		Serial.println("no networks found");
	else
	{
		Serial.print(n);
		Serial.println(" networks found");
		for (int i=0; i<n; i++)
		{
			// Print SSID and RSSI for each network found
			
			Serial.print(i+1);
			Serial.print(": ");
			Serial.print(WiFi.SSID(i));
			Serial.print(" (");
			Serial.print(WiFi.RSSI(i));
			Serial.print(")");
			Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
			delay(10);
		}
	}
	Serial.println("");
*/

	// Connexion a mon telephone
	
	Serial.println();
	Serial.print("Connexion wifi ");
	//WiFi.begin("Archos 50f Helium", "12345678");
	WiFi.begin("SFR_7260", "ooteranaff4eummandin");
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(200);
	}
	Serial.println();
	Serial.print("IP=");
	Serial.println(WiFi.localIP());
	
	if (!client.connect(serveur, port))
	{
		Serial.println("Erreur connexion au serveur !!!");
		while (true);
	}
}

// loop

void loop()
{
	char f1=0, f2=0;
	
	if (ett[ind] & ROUGE1)
	{
		digitalWrite(D0, HIGH);
		f1 |= 1;
	}
	else
		digitalWrite(D0, LOW);

	if (ett[ind] & JAUNE1)
	{
		digitalWrite(D1, HIGH);
		f1 |= 2;
	}
	else
		digitalWrite(D1, LOW);

	if (ett[ind] & VERT1)
	{
		digitalWrite(D2, HIGH);
		f1 |= 4;
	}
	else
		digitalWrite(D2, LOW);

	if (ett[ind] & ROUGE2)
	{
		digitalWrite(D3, HIGH);
		f2 |= 1;
	}
	else
		digitalWrite(D3, LOW);

	if (ett[ind] & JAUNE2)
	{
		digitalWrite(D4, HIGH);
		f2 |= 2;
	}
	else
		digitalWrite(D4, LOW);

	if (ett[ind] & VERT2)
	{
		digitalWrite(D5, HIGH);
		f2 |= 4;
	}
	else
		digitalWrite(D5, LOW);

	// Make a HTTP request:
	
	if (!client.connected())
		client.connect(serveur, port);
		
	client.println("POST /feu/ecrire.php HTTP/1.1");
	client.println("Host: 192.168.1.7:80");
	client.println("Connection: keep-alive");
	//client.println("Cache-Control: max-age=0");
	client.println("Accept: */*");	//text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
	//client.println("Origin: http://localhost:8080");
	//client.println("User-Agent: Mozilla/5.0");
	client.println("Content-Type: text/plain;charset=UTF-8");	//application/x-www-form-urlencoded
	//client.println("Referer: http://localhost:8080/bibliotheque/faces/views/categorie/List.xhtml");
	//client.println("Accept-Encoding: gzip, deflate");
	//client.println("Accept-Language: fr,fr-FR;q=0.8,en;q=0.6");
	//client.println("Cookie: JSESSIONID=d64a9484e61761662575b5d14af1");
	client.println("Content-Length: 19");
	client.println();
	client.print("{\"feu1\":");
	client.write('0'+f1);
	client.print(",\"feu2\":");
	client.write('0'+f2);
	client.print("}");
	Serial.print("19c. --> ");
	Serial.print("{\"feu1\":");
	Serial.write('0'+f1);
	Serial.print(",\"feu2\":");
	Serial.write('0'+f2);
	Serial.println("}");
	
	// wait response
	
	delay(5);
	
	while (client.available())
		Serial.print(client.read());		
	Serial.println();


	delay(dre[ett[ind]&3]*1000);
	ind++;
	if (ett[ind] == 0)
		ind = 1;
}
