#ifndef IPERF_GUI_H
#define IPERF_GUI_H

#include "lwip/apps/lwiperf.h"

void lwiperf_report(void *arg, enum lwiperf_report_type report_type,
                           const ip_addr_t *local_addr, u16_t local_port,
                           const ip_addr_t *remote_addr, u16_t remote_port,
                           u32_t bytes_transferred, u32_t ms_duration,
                           u32_t bandwidth_kbitpsec);

void display_static_info_iperf();
void display_dynamic_info_iperf();
#endif // IPERF_GUI_H


