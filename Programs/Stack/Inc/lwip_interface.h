#ifndef LWIP_INTERFACE_H_
#define LWIP_INTERFACE_H_

/**
* lwip_init();
*/
void init_lwip_stack(void);

/** 
 * netif add to lwip stack
*/
void  netif_config(void);

/**
 * check for new frames
 */
void check_input();
#endif // LWIP_INTERFACE_H_