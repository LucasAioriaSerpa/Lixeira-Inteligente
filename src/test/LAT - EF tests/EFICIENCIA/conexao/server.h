#ifndef SERVER_H
#define SERVER_H

#include <WebServer.h>

#define SERVER_PORT 80

void initServer();
void handleRoot();

extern WebServer servidor;

#endif