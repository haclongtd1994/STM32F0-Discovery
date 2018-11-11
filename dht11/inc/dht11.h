#ifndef __DHT11_H__
#define __DHT11_H__
#include "project.h"
extern int dht11_data[5];

extern void dht11_init();
extern unsigned int dht11_receive_data();

#endif
