#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H


#include <stdbool.h>


typedef struct {
    char topic[64];
    char data[128];
} mqtt_message_t;

// Function publish msg
void mqtt_pin_publish();
bool check_mqtt_network(void);
void init_mqtt_subscriber(void);

void  MQTT_ConnectTimer_Init();
#endif // MQTT_CLIENT_H 