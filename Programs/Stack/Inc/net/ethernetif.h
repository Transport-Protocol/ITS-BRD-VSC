#ifndef ETHERNETIF_H_
#define ETHERNETIF_H_

#include "lwip/err.h"
#include "lwip/netif.h"

err_t ethernetif_init(struct netif *netif);
void ethernetif_input(struct netif *netif);

#endif