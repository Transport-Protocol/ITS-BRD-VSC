#include "stm32f4xx_hal.h"

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"

#include "net/ethernetif.h"
#include "netif/ethernet.h"

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
// 192.168.33.99
#define IP_ADDR0 (uint8_t)192
#define IP_ADDR1 (uint8_t)168
#define IP_ADDR2 (uint8_t)33
#define IP_ADDR3 (uint8_t)99

/*NETMASK*/
// 255.255.255.0
#define NETMASK_ADDR0 (uint8_t)255
#define NETMASK_ADDR1 (uint8_t)255
#define NETMASK_ADDR2 (uint8_t)255
#define NETMASK_ADDR3 (uint8_t)0

/*Gateway Address*/
// 192.168.33.1
#define GW_ADDR0 (uint8_t)192
#define GW_ADDR1 (uint8_t)168
#define GW_ADDR2 (uint8_t)33
#define GW_ADDR3 (uint8_t)1

extern ETH_HandleTypeDef EthHandle;
#define CHECK_ETH_FRAME_RECEIVED(heth)                                         \
  (((heth)->RxDesc->Status & ETH_DMARXDESC_OWN) == 0)

struct netif its_brd_netif;

void init_lwip_stack() {
  // Init the stack
  lwip_init();

  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#ifdef USE_DHCP // If DHCP everything is wildcard
  ip_addr_set_zero_ip4(&ipaddr);
  ip_addr_set_zero_ip4(&netmask);
  ip_addr_set_zero_ip4(&gw);
#else
  IP_ADDR4(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP_ADDR4(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2,
           NETMASK_ADDR3);
  IP_ADDR4(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#endif /* USE_DHCP */

  /* Add the network interface */
  netif_add(&its_brd_netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init,
            &ethernet_input);
}

void netif_config() {

  /* Registers the default network interface. */
  netif_set_default(&its_brd_netif);

  if (netif_is_link_up(&its_brd_netif)) {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&its_brd_netif);
  } else {
    /* When the netif link is down this function must be called */
    netif_set_down(&its_brd_netif);
  }

  // Ethernet prio should in our project higer as the SPI I
  HAL_NVIC_SetPriority(ETH_IRQn, 5, 0);
  HAL_NVIC_SetPriority(SPI1_IRQn, 11, 0);
}

void check_input() {
  if (CHECK_ETH_FRAME_RECEIVED(&EthHandle)) {
    ethernetif_input(&its_brd_netif);
  }
  sys_check_timeouts();
}