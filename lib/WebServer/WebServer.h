#pragma once

class AsyncWebServer;  // forward declaration
class LED;
class Battery;

class WebServer {
 public:
  explicit WebServer(LED* led, Battery* battery);

 private:
  AsyncWebServer* asyncWebServer;
  LED* led;
  Battery* battery;
};
