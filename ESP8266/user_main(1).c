/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_main.c
 *
 * Description: entry file of user application
 *
 * Modification history:
 *     2014/1/1, v1.0 create this file.
*******************************************************************************/
#include "ets_sys.h"
#include "osapi.h"
#include "mem.h"
#include "ip_addr.h"
#include "user_interface.h"
#include "json/json.h"
#include "user_devicefind.h"
#include "os_type.h"
#include "driver/uart.h"
#include "c_types.h"
#include "espconn.h"
#include "ip_addr.h"

os_event_t * testQueue1;
os_event_t * testQueue2;
os_timer_t  *my_time;
struct espconn ptrespconn_tcp;
struct station_config stationConf;
struct jsonparse_state *state;
struct ip_info  info;
uint8_t  flag;
uint8_t  endflag;
void ICACHE_FLASH_ATTR
SEND_HTTP(void)//·¢ÆðHTTPÇëÇó
{

//if(
	espconn_sent(&ptrespconn_tcp,"GET  /v1.0/device/19574/sensor/34358/datapoints HTTP/1.1\r\nHost: api.yeelink.net\r\nAccept: */*\r\nU-ApiKey: 8f2202bbb9a3c23f8c27f7f5b672c876\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",189);
//==0)
//espconn_sent(&ptrespconn_tcp,"GET http://api.yeelink.net/v1.0/device/19574/sensor/34358/datapoints HTTP/1.1\r\nHost: api.yeelink.net\r\nU-ApiKey: 8f2202bbb9a3c23f8c27f7f5b672c876\r\n\r\n",156);
 //WRITE_PERI_REG(0x60000914, 0x73);

//os_printf("\n·¢ÆðHTTPÇëÇó\n");
//else
	//system_restart();
}
void ICACHE_FLASH_ATTR
tcp_connect_fail(void *arg, sint8 err)//ÖØÁ¬»Øµ÷º¯Êý
{
//os_printf("\n³öÏÖ´íÎó\n");
//espconn_connect(&ptrespconn_tcp);
system_restart();
}
//void ICACHE_FLASH_ATTR
/*sendcb(void *arg)                //·¢ËÍÊý¾Ý»Øµ÷º¯Êý
{

}
*/

void ICACHE_FLASH_ATTR
recv_cb(void *arg, char *pusrdata, unsigned short length)//½ÓÊÜÊý¾Ý»Øµ÷º¯Êý
{
//os_printf("\n½ÓÊÕµ½´Óyeelink.net·þÎñÆ÷·¢À´µÄÊý¾Ý\n");
//os_printf("\n%s",pusrdata);
//os_printf("\n%c",*(pusrdata+os_strlen(pusrdata)-10));
//os_printf("\n%c",*(pusrdata+os_strlen(pusrdata)-9));
//flag=1;//ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½Êý¾Ý±êÖ¾ Èç¹ûÃ»ÓÐ½ÓÊÕµ½Êý¾ÝÖØÆôÏµÍ³
if(*(pusrdata+length-9)=='1')
      gpio_output_set(BIT13,0 , BIT13, 0);  
      else
         gpio_output_set(0, BIT13, BIT13, 0);

}
void ICACHE_FLASH_ATTR
my_control_tcp_connect_su(void *arg)                  //Á¬½Ó³É¹¦»Øµ÷º¯Êý
{
	//	os_printf("\n·ÃÎÊyeelinked.net ³É¹¦\n");

		SEND_HTTP();
 
}
void ICACHE_FLASH_ATTR
autho_connnect(void)
{
		system_os_post(0,0,0);
		//espconn_connect(&ptrespconn_tcp);
			
}
void ICACHE_FLASH_ATTR
tcp_discconnect(void *arg)//Á´½Ó´íÎó»Øµ÷º¯Êý
{ 

	//os_printf("\nÒÑÓë·þÎñÆ÷¶Ï¿ªÁ¬½Ó\n");
       os_timer_disarm (&my_time);
       os_timer_setfn (&my_time, (os_timer_func_t *)autho_connnect,NULL);
       os_timer_arm (&my_time,5000,0);
}
void ICACHE_FLASH_ATTR
 remote_init(os_event_t *event)
{          
                uint8 ipaddress[4]={42,96,164,52};
                //uint8 ipaddress[4]={192,168,1,129};
	         uint32 ipport=80;
		//  os_printf("\nµ÷ÓÃTCP ³õÊ¼»¯³É¹¦\n");
                ptrespconn_tcp.type = ESPCONN_TCP;
		 /* ptrespconn_tcp.proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
		  ptrespconn_tcp.proto.tcp->local_port = 8080;
		  ptrespconn_tcp.proto.tcp->local_ip[0]=ipaddress[0];
		  ptrespconn_tcp.proto.tcp->local_ip[1]=ipaddress[1];
		  ptrespconn_tcp.proto.tcp->local_ip[2]=ipaddress[2];
		  ptrespconn_tcp.proto.tcp->local_ip[3]=ipaddress[3];
		  ptrespconn_tcp.proto.tcp->local_port=ipport;*/
		  
		  ptrespconn_tcp.proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
		 // ptrespconn_tcp.proto.tcp->local_port = 8080;
		  ptrespconn_tcp.proto.tcp->remote_ip[0]=ipaddress[0];
		  ptrespconn_tcp.proto.tcp->remote_ip[1]=ipaddress[1];
		  ptrespconn_tcp.proto.tcp->remote_ip[2]=ipaddress[2];
		  ptrespconn_tcp.proto.tcp->remote_ip[3]=ipaddress[3];
		  ptrespconn_tcp.proto.tcp->remote_port=ipport;
		  //espconn_regist_sentcb(&ptrespconn_tcp,sendcb);                                           //×¢²á·¢ËÍÊý¾Ý»Øµ÷º¯Êý
		  espconn_regist_connectcb(&ptrespconn_tcp,my_control_tcp_connect_su);  //×¢²áÁ´½Ó³É¹¦»Øµ÷º¯Êý
		  espconn_regist_recvcb(&ptrespconn_tcp, recv_cb);                                        //×¢²á½ÓÊÜÊý¾Ý»Øµ÷º¯Êý
		  espconn_regist_reconcb(&ptrespconn_tcp,tcp_connect_fail);                         //×¢²áÖØÁ¬»Øµ÷º¯Êý
		  espconn_regist_disconcb(&ptrespconn_tcp,tcp_discconnect);                         //×¢²áÁ¬½Ó´íÎó»Øµ÷º¯Êý
		  espconn_connect(& ptrespconn_tcp);	                                                               //Á¬½Ó·þÎñÆ÷
}


void ICACHE_FLASH_ATTR
 get_wifi_state(void)                                                   //»ñµÃÁ¬½Ó×´Ì¬»Øµ÷º¯Êý
{

if(wifi_station_get_connect_status()==STATION_GOT_IP)
{
    /*   if(++flag==1)
       	{
       wifi_get_ip_info(0x00,&info);
  	os_printf("\nget ip: %d",info.ip.addr&0xff);
	os_printf(".");
	os_printf("%d",(info.ip.addr>>8)&0xff);
	os_printf(".");
	os_printf("%d",(info.ip.addr>>16)&0xff);
	os_printf(".");
	os_printf("%d",(info.ip.addr>>24)&0xff);
	flag=0;*/
	system_os_post(0,0,0); 
	
       //}
}

}


void  ICACHE_FLASH_ATTR
 wifi_init(os_event_t * event)
{
		char your_ssid[9]="yangguang";
		char your_pawd[14]="yangguang@123#";

              if(wifi_get_opmode()!=STATIONAP_MODE)  
	   	wifi_set_opmode(STATION_MODE);
	
		os_bzero(&stationConf, sizeof(struct station_config));
		os_memcpy(&stationConf.ssid,&your_ssid,9);
		os_memcpy(&stationConf.password,&your_pawd,14);
             wifi_station_set_config(&stationConf);
	      wifi_station_set_auto_connect(1);
		  
	      os_timer_disarm (&my_time);
             os_timer_setfn (&my_time, (os_timer_func_t *)get_wifi_state,NULL);
             os_timer_arm (&my_time,5000,0);
	      
}
void  ICACHE_FLASH_ATTR
GPIO_INIT(viod)
{
       PIN_PULLUP_EN(PERIPHS_IO_MUX_MTCK_U);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	gpio_output_set(0, BIT13, BIT13, 0);
	//PIN_FUNC_SELECT(FUNC_U0TXD_BK, FUNC_GPIO2);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
       //system_uart_swap();
         os_printf("SDK version:%s\n", system_get_sdk_version());
	//  uart_init(BIT_RATE_115200,BIT_RATE_115200);
         GPIO_INIT();
	  testQueue1=(os_event_t*)os_malloc(sizeof(os_event_t)*1);
	  testQueue2=(os_event_t*)os_malloc(sizeof(os_event_t)*1);	
	 //  wifi_init();
	  system_os_task(remote_init,0,testQueue1,1);
         system_os_task(wifi_init,1,testQueue2,1); 
         system_os_post(1,0,0); 

}



