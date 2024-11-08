#include "LCD_GUI.h"
#include "lwip/apps/lwiperf.h"
#include <string.h>

typedef struct _iperf_info {
  char clientip[16];
  u32_t bandwidth_kbitpsec;
  u32_t bytes_transferred;
  u32_t cnt;
} IPERF_INFO;
volatile IPERF_INFO iperf_info = {"0.0.0.0", 0, 0, -1};

// Funktion für statische Inhalte und Texte
void display_static_info_iperf() {
  // Hintergrundfarbe festlegen und Bildschirm leeren
  GUI_clear(LCD_BACKGROUND);

  // Statische Informationen darstellen
  GUI_disStr((Coordinate){10, 10}, "IPerf Information", &Font16, WHITE, BLACK);
  GUI_disStr((Coordinate){10, 30}, "Client IPv4:", &Font16, WHITE, BLACK);
  GUI_disStr((Coordinate){10, 60}, "BW: kbit/s:", &Font16, WHITE, BLACK);
  GUI_disStr((Coordinate){10, 90}, "TX: tbytes:", &Font16, WHITE, BLACK);
  GUI_disStr((Coordinate){10, 120}, "Run:", &Font16, WHITE, BLACK);
}

void display_dynamic_info_iperf() {

  static char ip_string_old[16];
  if (strcmp(ip_string_old, (const char *)iperf_info.clientip) != 0) {
    GUI_disStr((Coordinate){150, 30}, (const char *)iperf_info.clientip,
               &Font16, WHITE, BLACK);
    strcpy(ip_string_old, (const char *)iperf_info.clientip);
  }
  static uint32_t bandwidth_kbitpsec_old = 0;
  if (bandwidth_kbitpsec_old != iperf_info.bandwidth_kbitpsec) {
    GUI_disNum((Coordinate){150, 60}, iperf_info.bandwidth_kbitpsec, &Font16,
               WHITE, BLACK);
    bandwidth_kbitpsec_old = iperf_info.bandwidth_kbitpsec;
  }
  static uint32_t bytes_transferred_old = 0;
  if (bytes_transferred_old != iperf_info.bytes_transferred) {
    GUI_disNum((Coordinate){150, 90}, iperf_info.bytes_transferred, &Font16,
               WHITE, BLACK);
    bytes_transferred_old = iperf_info.bytes_transferred;
  }

  GUI_disNum((Coordinate){150, 120}, iperf_info.cnt++, &Font16, WHITE, BLACK);
}

void lwiperf_report(void *arg, enum lwiperf_report_type report_type,
                    const ip_addr_t *local_addr, u16_t local_port,
                    const ip_addr_t *remote_addr, u16_t remote_port,
                    u32_t bytes_transferred, u32_t ms_duration,
                    u32_t bandwidth_kbitpsec) {
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(local_addr);
  LWIP_UNUSED_ARG(local_port);

  /*
    printf("IPERF report: type=%d, remote: %s:%d, total bytes: %" U32_F
           ", duration in ms: %" U32_F ", kbits/s: %" U32_F "\n",
           (int)report_type, ipaddr_ntoa(remote_addr), (int)remote_port,
           bytes_transferred, ms_duration, bandwidth_kbitpsec);
  */
  if (report_type == LWIPERF_TCP_DONE_SERVER) {
    iperf_info.bandwidth_kbitpsec = bandwidth_kbitpsec;
    iperf_info.bytes_transferred = bytes_transferred;
    sprintf((char *)iperf_info.clientip, "%s", ipaddr_ntoa(remote_addr));
    iperf_info.cnt++;
    display_dynamic_info_iperf();
  }
}