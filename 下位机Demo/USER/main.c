#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include <string.h>
 
 u8 i = 3;
 u16 x = 30, y = 550;
 u8 d = 20;   //���
 u8 sz = 40;
 //0xF800-��ɫ, 0x07E0��ɫ, 0xFFE0��ɫ
 u16 colors[] = {0x07E0, 0xFFE0, 0xF800};
	
 int main(void)
 {	 
 	u8 x=0;
	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();
	POINT_COLOR=RED;
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣		
	
  	while(1) 
	{		 
		POINT_COLOR=RED;	  
//		LCD_ShowString(30,40,210,24,24,"WarShip STM32 ^_^"); 
//		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
//		LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
// 		LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID
//		LCD_ShowString(30,130,200,12,12,"2014/5/4");	 

//		LCD_ShowString(30,150,200,16,16,"ren-shi-hao");    
//		LCD_ShowString(160,150,200,24,24,"ren-shi-hao");  

//		LCD_ShowString(30,300,200,24,24,"rec_cnt: ");  
//		LCD_ShowxNum(160, 300, cnt, 2, 24, 0);
//		LCD_ShowString(30,350,200,24,24,"judge: ");  
//		LCD_ShowxNum(160, 350, ff, 2, 24, 0);
		
		//LCD_Fill(30, 550, 70, 590, 0xF800);  //0xF800-��ɫ, 0x07E0��ɫ, 0xFFE0��ɫ  ���ұ���x���ѿ�������ϵ, ����40*40
		
		LCD_ShowString(30,210,200,24,24,"Empty: ");
		LCD_ShowString(30,250,200,24,24,"Occupancy : ");
		LCD_ShowString(30,290,200,24,24,"Used: ");
		
		
		if(dis_flag){
			LCD_Clear(WHITE);
			dis_flag = 0;
			//LCD_ShowString(30,200,200,24,24, "rec_buf: ");
			//LCD_ShowString(160,200,200,24,24, rec_buf); 
			
			//�߼��жϲ���
//			if(strcmp((char*)rec_buf, "43200312a") == 0){
//				ff++;  //У��ͨ��
//			}
			1
			//��ʾ������λ���������
			LCD_ShowxNum(160, 210, rec_buf[0] - '0', 2, 24, 0);
			LCD_ShowxNum(160, 250, rec_buf[1] - '0', 2, 24, 0);
			LCD_ShowxNum(160, 290, rec_buf[2] - '0', 2, 24, 0);
			
			x = 30, y = 360;   //��ʼ����
			//��ʾ�����ɫ�飬��ʾ��Ӧ����λ���
			for(i = 3; i < idx - 1; i++){
				if(rec_buf[i] == '3') {  //����һ�е����׻���
					x = 30, y += d + sz;
					continue;
				}
				LCD_Fill(x, y, x + sz, y + sz, colors[rec_buf[i] - '0']);
				x += d + sz;
			}
			
//			LCD_ShowString(30,300,200,24,24,"rec_cnt: ");  
//			LCD_ShowxNum(160, 300, cnt, 2, 24, 0);
//			LCD_ShowString(30,350,200,24,24,"judge: ");  
//			LCD_ShowxNum(160, 350, ff, 2, 24, 0);
			
			memset(rec_buf, 0, sizeof rec_buf);
			idx = 0;
			
//			LCD_ShowString(30,250,200,24,24, "flag: ");
//			LCD_ShowString(160,250,200,24,24, flag); 
		}

		LED0=!LED0;				   		 
		delay_ms(1000);	
	} 
}
