#pragma once

class AsyncWebServer;  // forward declaration
class LED;

class WebServer {
 public:
  explicit WebServer(LED* led);

 private:
  AsyncWebServer* asyncWebServer;
  LED* led;
};
