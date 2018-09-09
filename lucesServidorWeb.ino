#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 
int ledcuarto = 4;
int ledcocina=8;
int ledbano=5;
int ledcomedor=9;
int ledentrada=6;


Servo microservo; 
int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 0, 3 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 1, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(ledcuarto, OUTPUT);
  pinMode(ledcocina, OUTPUT);
  pinMode(ledbano, OUTPUT);
  pinMode(ledcomedor, OUTPUT);
  pinMode(ledentrada, OUTPUT);

   pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(7,LOW);//Apaga el servomotor
  microservo.attach(7);
 for(pos = 70; pos>=1; pos-=4)     // goes from 180 degrees to 0 degrees 

                {                                
                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(15);  
                  
                } 
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
}


void loop() {


  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 105) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://casadomatica.260mb.net/style.css' />");
           client.println("<TITLE>CASA DOMOTICA UD </TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>CASA DOMOTICA UD </H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">PRENDER CUARTO</a>");
           client.println("<a href=\"/?button1off\"\">APAGAR CUARTO</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           
           client.println("<a href=\"/?button2on\"\">ENCENDER COCINA</a>");
           client.println("<a href=\"/?button2off\"\">APAGAR COCINA</a><br />");   
           client.println("<br />");     
               client.println("<br />"); 
               
           client.println("<a href=\"/?button3on\"\">ENCENDER BANO</a>");
           client.println("<a href=\"/?button3off\"\">APAGAR BANO</a><br />");   
           client.println("<br />");     
               client.println("<br />"); 

           client.println("<a href=\"/?button4on\"\">ENCENDER COMEDOR</a>");
           client.println("<a href=\"/?button4off\"\">APAGAR COMEDOR</a><br />");   
           client.println("<br />");     
              client.println("<br />"); 
               
           
            client.println("<a href=\"/?cortinaon\"\">SUBIR CORTINA</a>");
           client.println("<a href=\"/?cortinaoff\"\">BAJAR CORTINA</a><br />"); 
           client.println("<br />");     
           client.println("<br />");
           
           client.println("<a href=\"/?puertaon\"\">ABRIR PUERTA</a>");
           client.println("<a href=\"/?puertaoff\"\">CERRAR PUERTA</a><br />"); 
           client.println("<p>Created by Paola Martinez , Carlos Diaz and Jorge hernandez</p>");  
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
    
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?button1on") >0){
               digitalWrite(ledcuarto, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(ledcuarto, LOW);
           }

            if (readString.indexOf("?button2on") >0){
               digitalWrite(ledcocina, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(ledcocina, LOW);
           }

           if (readString.indexOf("?button3on") >0){
               digitalWrite(ledbano, HIGH);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(ledbano, LOW);
           }

           if (readString.indexOf("?button4on") >0){
               digitalWrite(ledcomedor, HIGH); 
               digitalWrite(ledentrada, HIGH);
           }
           if (readString.indexOf("?button4off") >0){
               digitalWrite(ledcomedor, LOW);
               digitalWrite(ledentrada, LOW);
           }

           


           if (readString.indexOf("?cortinaon") >0){
                int segundos=0;
                while(segundos<165)
                {
                digitalWrite(3, LOW);
               digitalWrite(2, HIGH);
               delay(15); 
               segundos++;
                }
                digitalWrite(2, LOW);
           }
           if (readString.indexOf("?cortinaoff") >0){
                 int segundos=0;
                while(segundos<165)
                {
                  digitalWrite(3, HIGH);
                 digitalWrite(2, LOW);
               
               delay(15); 
               segundos++;
                }

                 digitalWrite(3, LOW);
           }

           
           
           if (readString.indexOf("?puertaon") >0){
                for(pos = 0; pos < 72; pos += 3)  // goes from 0 degrees to 180 degrees 
                {                                  // in steps of 1 degree 
                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(15);                       // waits 15ms for the servo to reach the position 
                } 
           }
           if (readString.indexOf("?puertaoff") >0){
                for(pos = 72; pos>=1; pos-=3)     // goes from 180 degrees to 0 degrees 

                {                                
                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
                  delay(15);  
                  
                } 
           }
            //clearing string for next read
            readString="";  
           
         }
       }
    }
}
}
