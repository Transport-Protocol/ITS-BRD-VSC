
#include <string.h>
#include "lcd.h"
#include "lwip/tcp.h"

/* Definiere TCP Server Port */
#define TCP_SERVER_PORT    7 /* Echo-Port */

/*
 * TCP-Callback-Funktionen
 */
 static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
 static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
 static void tcp_server_error(void *arg, err_t err);
 static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);
 static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
 

 /* TCP-Serverstruktur */
struct tcp_pcb *tcp_server_pcb;

/* Puffer für die Datenübertragung */
static char hello_msg[] = "Hello World from ITS-Board TCP Server!";



/**
  * @brief  Initialisiert den TCP-Server
  * @param  None
  * @retval None
  */
void tcp_server_init(void)
  {
    /* Erstelle neuen TCP PCB */
    tcp_server_pcb = tcp_new();
    
    if (tcp_server_pcb != NULL)
    {
      err_t err;
      
      /* Binde den PCB an den Port */
      err = tcp_bind(tcp_server_pcb, IP_ADDR_ANY, TCP_SERVER_PORT);
      
      if (err == ERR_OK)
      {
        /* Starte das Lauschen auf dem PCB */
        tcp_server_pcb = tcp_listen(tcp_server_pcb);
        
        /* Registriere Callback für eingehende Verbindungen */
        tcp_accept(tcp_server_pcb, tcp_server_accept);
        
        lcdPrintlnS("TCP-Server gestartet auf Port 7");
      }
      else
      {
        /* Fehlerbehandlung */
        lcdPrintlnS("TCP-Server konnte nicht gestartet werden");
        memp_free(MEMP_TCP_PCB, tcp_server_pcb);
      }
    }
  }

  

/**
  * @brief  Callback-Funktion für eingehende Verbindungen
  * @param  arg: Nicht verwendet
  * @param  newpcb: Neuer PCB für die Verbindung
  * @param  err: Fehlerstatus
  * @retval err_t: Fehlercode
  */
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);
  
  /* Registriere Callback-Funktionen für den neuen PCB */
  tcp_recv(newpcb, tcp_server_recv);
  tcp_err(newpcb, tcp_server_error);
  tcp_poll(newpcb, tcp_server_poll, 1);
  
  /* Sende Hello-Nachricht an den Client */
  tcp_write(newpcb, hello_msg, strlen(hello_msg), TCP_WRITE_FLAG_COPY);
  tcp_output(newpcb);
  
  lcdPrintlnS("Neue TCP-Verbindung hergestellt");
  
  ret_err = ERR_OK;
  return ret_err;  
}


/**
  * @brief  Callback-Funktion für empfangene Daten
  * @param  arg: Nicht verwendet
  * @param  tpcb: TCP-PCB der die Daten empfangen hat
  * @param  p: Empfangene Daten
  * @param  err: Fehlerstatus
  * @retval err_t: Fehlercode
  */
  static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
  {
    LWIP_UNUSED_ARG(arg);
    
    /* Wenn Daten empfangen wurden (p != NULL) */
    if (p != NULL)
    {
      /* Empfangene Daten auf dem LCD ausgeben */
      char buffer[128];
      memcpy(buffer, p->payload, p->len > 127 ? 127 : p->len);
      buffer[p->len > 127 ? 127 : p->len] = '\0';
      
      lcdPrintS("Empfangen: ");
      lcdPrintlnS(buffer);
      
      /* Bestätige den Empfang der Daten */
      tcp_recved(tpcb, p->tot_len);
      
      /* Echo die Daten zurück */
      tcp_write(tpcb, p->payload, p->tot_len, TCP_WRITE_FLAG_COPY);
      tcp_output(tpcb);
      
      /* Puffer freigeben */
      pbuf_free(p);
    }
    else if (err == ERR_OK)
    {
      /* Wenn p NULL ist und err OK ist, wurde die Verbindung geschlossen */
      lcdPrintlnS("Verbindung geschlossen");
      tcp_close(tpcb);
    }
    
    return ERR_OK;
  }


/**
  * @brief  Callback-Funktion für TCP-Fehler
  * @param  arg: Nicht verwendet
  * @param  err: Fehlerstatus
  * @retval None
  */
static void tcp_server_error(void *arg, err_t err)
{
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);
  
  lcdPrintlnS("TCP-Fehler aufgetreten");
}

/**
  * @brief  Callback-Funktion für regelmäßige Abfragen
  * @param  arg: Nicht verwendet
  * @param  tpcb: TCP-PCB
  * @retval err_t: Fehlercode
  */
static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb)
{
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(tpcb);
  
  return ERR_OK;
}

/**
  * @brief  Callback-Funktion für gesendete Daten
  * @param  arg: Nicht verwendet
  * @param  tpcb: TCP-PCB
  * @param  len: Anzahl der gesendeten Bytes
  * @retval err_t: Fehlercode
  */
static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(tpcb);
  LWIP_UNUSED_ARG(len);
  
  return ERR_OK;
}
