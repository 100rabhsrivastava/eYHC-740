/*COVID'19 PATIENT MONITORING SYSTEM.
 
 - There are many scenarios when patient suffering from covid'19 suddenly becomes very serious due 
   to sudden decrease in oxygen level and many other factors and doctors are not aware of. Taking care at
   right time may save a person's life. To tackle this scenario we have developed a system which monitors 
   patient's oxygen level , body temperature and pulse rate and pushes this data in real time in the hospital's
   database. This will help doctors in monitoring patients accurately saving lots of time. 
 - To demonstrate this we have made a program which autogenerates patient monitoring data and pushes the data in
   real time on google sheets
 - If the data parameters go below the certain parameters the doctors are notified that patient is serious via the 
   Covid'19 app which we created.
-*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

//http://gsx2json.com/api?id=1bVamuJOdpYO4VGlus3CNb1sXbidPh6g4oFcdSSLSNG4&sheet=1

class Covid19_Patient_Monitor
  {
   /*
   _____________________________________________________________
  |
  | Description
  | -----------
  | - This class will be used for live monitoring of a patients
  |   who are suffering from COVID'19
  |
  |.............................................................
  |
  | Attributes
  | ----------
  | Patient : String
  |    -  Name of the patient
  |
  | ID : String
  |    - Unique Id which is given to all the patients in the.
  |      hospital.
  |
  |............................................................
  |
  | Methods
  | -------
  | initialize_patient_data()
  |       - Initialises the patient monitoring sensor data.
  |
  | update_data()
  |       - Pushes the real time values of the sensor data to the
  |         hospital patient monitoring database. eg: firebase,
  |         google sheets.(For this is made to push data to google
  |         sheets).
  |
  | read_data()
  |       - Reads real time sensor data from the sensors.
  |
  | generate_monitoring_data()
  |       - Generates random values of patient monitoring data.
  |         This is used for debugging purposes or when no sensor
  |         data is available. In this project this will used for 
  |         project demonstration.
  |____________________________________________________________
  */
  
    private:
         const char* ssid = "VARUN";//VARUN
         const char* password = "varun03*";//varun03*
         const char* host = "script.google.com";
         const int port = 443;
         
    protected:
         String URL = "https://script.google.com/macros/s/AKfycbxbTaoBBBIPOI2FDi0HngxBBF4scQRrB884dIS3/exec?id=Sheet1&"; 
         String ALTERNATE_URL = "/macros/s/AKfycbzOlo3dEwrRFvNBtB3sCYzRDGNWWcjbftvgT8PHXSjz_0RSOHWTf3iv5uOXAdb1xlT2/exec?id=Sheet1&";
         String ID = "AKfycbyhlyoC6gsDWG5ziWkelEfb5jtEoO1Rls4Uf0s6Gw2vIMS3QcI";
         String webapp_path;
         String patient_data;
         
    public:     
         float oxygen_level;
         float temperature;
         float pulse_rate;
         String patient_name;
         String patient_id;

         WiFiClientSecure router;
         HTTPClient http;
         //DHT dht(2,DHT11);
         
         Covid19_Patient_Monitor(String Patient, String Identification)
           {
            oxygen_level = 0;
            temperature = 0;
            pulse_rate = 0;

            patient_name = Patient;
            patient_id = Identification;
           }

         void Init()
           {
             Serial.begin(9600);
             //dht.begin();
             WiFi.begin(ssid, password);

             while(WiFi.status()!= WL_CONNECTED)
                 {
                  delay(500);
                  Serial.print(".");
                 }
             Serial.println();
             Serial.println("WiFi Connected");

             router.setInsecure();
             router.connect(host,port);
           }


         void set_alternate_data()
       /*
        _____________________________________________________________
       |
       | Description
       | -----------
       | - Autogenerates patient monitoring data.
       |
       |.............................................................
       |
       | Attributes
       | ----------
       |  None
       |............................................................
       |
       | Returns
       | -------
       |  None
       |_____________________________________________________________
       */
           {
            oxygen_level = random(50,150);
            temperature = random(60,180);
            pulse_rate = random(70,90);
           }
         
         void read_data()
           { 
        /*
        _____________________________________________________________
       |
       | Description
       | -----------
       | - Reads real time data from sensors.(Haven't used this as no
       |   sensors were avaliable with us in this pandemic.
       |
       |.............................................................
       |
       | Attributes
       | ----------
       |  None
       |............................................................
       |
       | Returns
       | -------
       |  None
       |_____________________________________________________________
       */
            temperature = 11;     
           }

         void initialize_patient_data()
           {
        /*
        _____________________________________________________________
       |
       | Description
       | -----------
       | - Intilaizes the patient monitoring data.
       |
       |.............................................................
       |
       | Attributes
       | ----------
       |  None
       |............................................................
       |
       | Returns
       | -------
       |  None
       |_____________________________________________________________
       */
            webapp_path = URL + "Pno="+ patient_id + "&" + "Name=" + patient_name + "&" + "Oxygen=" + String(oxygen_level) + "&" + "Temperature=" + String(temperature) + "&" + "Heartbeat=" + String(pulse_rate);
            http.begin(router,webapp_path);
            http.GET();
            
            //router.print(String("GET ")+URL+" HTTP/1.1\r\n"+
                         //"Host: "+ host + "\r\n"+
                         //"Connection: close \r\n\r\n");
           }

         void update_data()   
           {
        /*
        _____________________________________________________________
       |
       | Description
       | -----------
       | - Pushes the patient monitoring data in real time on google
       |   sheets database.
       |
       |.............................................................
       |
       | Attributes
       | ----------
       |  None
       |............................................................
       |
       | Returns
       | -------
       |  None
       |_____________________________________________________________
       */
             set_alternate_data();
             patient_data = URL + "Pno="+ patient_id + "&" + "Name=" + patient_name + "&" "Oxygen=" + String(oxygen_level) + "&" + "Temperature=" + String(temperature) + "&" + "Heartbeat=" + String(pulse_rate);
             http.begin(router,patient_data);
             http.GET();
           }
   };
   
//Declare the object of the class here.
Covid19_Patient_Monitor Monitor("Varun","XXYOQ3560");

void setup() 
{
 Monitor.Init();

 Monitor.set_alternate_data();

 Monitor.initialize_patient_data();
}

void loop() 
{
  Monitor.update_data();
  delay(2000);
}
