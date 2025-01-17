#include "../../../../inc/MarlinConfig.h"
// #include <libmaple/fsmc.h>
// #include <libmaple/gpio.h>
// #include <libmaple/dma.h>
#include "LCD_Init.h"
#include "GUI.h"
#include "Menu/Settings.h"

// DZ301_TFT35
// TFT35_V2_0
#define DZ301_TFT35
#define ILI9488

#define Delay_ms(ms) delay(ms)


#ifdef LCD_BACKLIGHT_PIN
void LCD_LED_On()
{
  WRITE(LCD_BACKLIGHT_PIN, HIGH);
}
void LCD_LED_Off()
{
  WRITE(LCD_BACKLIGHT_PIN, LOW);
}

void LCD_LED_Init(void)
{
  OUT_WRITE(LCD_BACKLIGHT_PIN, LOW);
}
#endif

#if defined(TFT35_V1_2) || defined(TFT35_V2_0) || defined(TFT35_V3_0)
//ILI9488
void LCD_init_RGB(void) 
{
  LCD_WR_REG(0xC0); 
  LCD_WR_DATA(0x0c); 
  LCD_WR_DATA(0x02);	 
  LCD_WR_REG(0xC1); 
  LCD_WR_DATA(0x44); 
  LCD_WR_REG(0xC5); 
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x16); 
  LCD_WR_DATA(0x80);
  LCD_WR_REG(0x36); 
  LCD_WR_DATA(0x28); 
  LCD_WR_REG(0x3A); //Interface Mode Control
  LCD_WR_DATA(0x55);
  LCD_WR_REG(0XB0);  //Interface Mode Control  
  LCD_WR_DATA(0x00); 
  LCD_WR_REG(0xB1);   //Frame rate 70HZ  
  LCD_WR_DATA(0xB0); 
  LCD_WR_REG(0xB4); 
  LCD_WR_DATA(0x02); 
  LCD_WR_REG(0xB6); //RGB/MCU Interface Control
  LCD_WR_DATA(0x02); 
  LCD_WR_DATA(0x02); 
  LCD_WR_REG(0xE9); 
  LCD_WR_DATA(0x00);	 
  LCD_WR_REG(0XF7);    
  LCD_WR_DATA(0xA9); 
  LCD_WR_DATA(0x51); 
  LCD_WR_DATA(0x2C); 
  LCD_WR_DATA(0x82);
  LCD_WR_REG(0x11); 
  Delay_ms(120); 
  LCD_WR_REG(0x29); 
} 
#elif defined(TFT35_V1_1) || defined(TFT35_V1_0)
//RM68042
void LCD_init_RGB(void)
{
  LCD_WR_REG(0X11);
  Delay_ms(20);
  LCD_WR_REG(0XD0);//VCI1  VCL  VGH  VGL DDVDH VREG1OUT power amplitude setting
  LCD_WR_DATA(0X07); 
  LCD_WR_DATA(0X42); 
  LCD_WR_DATA(0X1C); 
  LCD_WR_REG(0XD1);//VCOMH VCOM_AC amplitude setting
  LCD_WR_DATA(0X00);
  LCD_WR_DATA(0X19);
  LCD_WR_DATA(0X16); 
  LCD_WR_REG(0XD2);//Operational Amplifier Circuit Constant Current Adjust , charge pump frequency setting
  LCD_WR_DATA(0X01);
  LCD_WR_DATA(0X11);
  LCD_WR_REG(0XE4);
  LCD_WR_DATA(0X00A0);
  LCD_WR_REG(0XF3);
  LCD_WR_DATA(0X0000);
  LCD_WR_DATA(0X002A);
  LCD_WR_REG(0XC0);//REV SM GS 
  LCD_WR_DATA(0X10);
  LCD_WR_DATA(0X3B);
  LCD_WR_DATA(0X00);
  LCD_WR_DATA(0X02);
  LCD_WR_DATA(0X11);
  LCD_WR_REG(0XC5);// Frame rate setting = 72HZ  when setting 0x03
  LCD_WR_DATA(0X03);
  LCD_WR_REG(0XC8);//Gamma setting
  LCD_WR_DATA(0X00);
  LCD_WR_DATA(0X35);
  LCD_WR_DATA(0X23);
  LCD_WR_DATA(0X07);
  LCD_WR_DATA(0X00);
  LCD_WR_DATA(0X04);
  LCD_WR_DATA(0X45);
  LCD_WR_DATA(0X53);
  LCD_WR_DATA(0X77);
  LCD_WR_DATA(0X70);
  LCD_WR_DATA(0X00);
  LCD_WR_DATA(0X04);
  LCD_WR_REG(0X20);//Exit invert mode
  LCD_WR_REG(0X36);
  LCD_WR_DATA(0X28);
  LCD_WR_REG(0X3A);
  LCD_WR_DATA(0X55);//16λģʽ 
  Delay_ms(120);
  LCD_WR_REG(0X29); 	 
}

#elif defined(TFT28_V1_0)

void LCD_init_RGB(void) 
{
  Delay_ms(50); // delay 50 ms 
  
  LCD_WR_REG(0xCF);  
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0xC1); 
  LCD_WR_DATA(0X30);

  LCD_WR_REG(0xED);  
  LCD_WR_DATA(0x64); 
  LCD_WR_DATA(0x03); 
  LCD_WR_DATA(0X12); 
  LCD_WR_DATA(0X81);

  LCD_WR_REG(0xE8);   /// @diff :Driver timing control A
  LCD_WR_DATA(0x8A); 
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x78); 
  
  LCD_WR_REG(0xEA);  
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x00); 
  
  LCD_WR_REG(0xCB);  
  LCD_WR_DATA(0x39); 
  LCD_WR_DATA(0x2C); 
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x34); 
  LCD_WR_DATA(0x02);   
  
  LCD_WR_REG(0xF7);  
  LCD_WR_DATA(0x20);

  LCD_WR_REG(0xC0);    /// @diff Power control 
  LCD_WR_DATA(0x25);   // VRH[5:0]
   
  LCD_WR_REG(0xC1);    /// @diff control 
  LCD_WR_DATA(0x12);   // SAP[2:0];BT[3:0] 
  
  LCD_WR_REG(0xC5);    /// @diff VCM control 
  LCD_WR_DATA(0x33); 
  LCD_WR_DATA(0x3C); 
  
  LCD_WR_REG(0xC7);    ///@diff VCM control2 
  LCD_WR_DATA(0x9A); 
  
  LCD_WR_REG(0xB1);    /// @diff Frame Rate Control  
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x15);
  
  LCD_WR_REG(0x3A);  
  LCD_WR_DATA(0x55);
  
  LCD_WR_REG(0x36);    // Memory Access Control 
  LCD_WR_DATA(0x68); 
  
  LCD_WR_REG(0xB6);    // Display Function Control 
  LCD_WR_DATA(0x0A);
  LCD_WR_DATA(0xA2);

  LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
  LCD_WR_DATA(0x00);
   
  LCD_WR_REG(0x26);    // Gamma curve selected 
  LCD_WR_DATA(0x01);
   
  LCD_WR_REG(0xE0);    /// @diff Set Gamma 
  LCD_WR_DATA(0x1F); 
  LCD_WR_DATA(0x1C); 
  LCD_WR_DATA(0x1A); 
  LCD_WR_DATA(0x0B); 
  LCD_WR_DATA(0x0F); 
  LCD_WR_DATA(0x08); 
  LCD_WR_DATA(0x47); 
  LCD_WR_DATA(0xC8); 
  LCD_WR_DATA(0x37); 
  LCD_WR_DATA(0x0B); 
  LCD_WR_DATA(0x14); 
  LCD_WR_DATA(0x05); 
  LCD_WR_DATA(0x0A); 
  LCD_WR_DATA(0x08); 
  LCD_WR_DATA(0x00); 
   
  LCD_WR_REG(0XE1);    /// @diff Set Gamma 
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x24); 
  LCD_WR_DATA(0x25); 
  LCD_WR_DATA(0x04); 
  LCD_WR_DATA(0x10); 
  LCD_WR_DATA(0x07); 
  LCD_WR_DATA(0x38); 
  LCD_WR_DATA(0x48); 
  LCD_WR_DATA(0x48); 
  LCD_WR_DATA(0x03); 
  LCD_WR_DATA(0x0B); 
  LCD_WR_DATA(0x0A); 
  LCD_WR_DATA(0x35); 
  LCD_WR_DATA(0x37); 
  LCD_WR_DATA(0x1F); 

  LCD_WR_REG(0x2A); 
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x01);
  LCD_WR_DATA(0x3f);

  LCD_WR_REG(0x2B); 
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0xef);

  LCD_WR_REG(0x11); //Exit Sleep
  Delay_ms(120);
  LCD_WR_REG(0x29); //display on
}

#elif defined(TFT24_V1_1)
void LCD_init_RGB(void) 
{
  Delay_ms(120);             // Delay 120 ms 
  //************* Start Initial Sequence **********//
  LCD_WR_REG(0xCF);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0xC1);
  LCD_WR_DATA(0X30);
  LCD_WR_REG(0xED);
  LCD_WR_DATA(0x64);
  LCD_WR_DATA(0x03);
  LCD_WR_DATA(0X12);
  LCD_WR_DATA(0X81);
  LCD_WR_REG(0xE8);
  LCD_WR_DATA(0x85);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x79);
  LCD_WR_REG(0xCB);
  LCD_WR_DATA(0x39);
  LCD_WR_DATA(0x2C);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x34);
  LCD_WR_DATA(0x02);
  LCD_WR_REG(0xF7);
  LCD_WR_DATA(0x20);
  LCD_WR_REG(0xEA);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_REG(0xC0); //Power control
  LCD_WR_DATA(0x1D); //VRH[5:0]
  LCD_WR_REG(0xC1); //Power control
  LCD_WR_DATA(0x12); //SAP[2:0];BT[3:0]
  LCD_WR_REG(0xC5); //VCM control
  LCD_WR_DATA(0x33);
  LCD_WR_DATA(0x3F);
  LCD_WR_REG(0xC7); //VCM control
  LCD_WR_DATA(0x92);
  LCD_WR_REG(0x3A); // Memory Access Control
  LCD_WR_DATA(0x55);
  LCD_WR_REG(0x36);    // Memory Access Control 
  LCD_WR_DATA(0x68); 
  LCD_WR_REG(0xB6);    // Display Function Control 
  LCD_WR_DATA(0x0A); 
  LCD_WR_DATA(0xA2); 
  LCD_WR_REG(0xB1);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x12);
  LCD_WR_REG(0x44);
  LCD_WR_DATA(0x02);
  LCD_WR_REG(0xF2); // 3Gamma Function Disable
  LCD_WR_DATA(0x00);
  LCD_WR_REG(0x26); //Gamma curve selected
  LCD_WR_DATA(0x01);
  LCD_WR_REG(0xE0); //Set Gamma
  LCD_WR_DATA(0x0F);
  LCD_WR_DATA(0x22);
  LCD_WR_DATA(0x1C);
  LCD_WR_DATA(0x1B);
  LCD_WR_DATA(0x08);
  LCD_WR_DATA(0x0F);
  LCD_WR_DATA(0x48);
  LCD_WR_DATA(0xB8);
  LCD_WR_DATA(0x34);
  LCD_WR_DATA(0x05);
  LCD_WR_DATA(0x0C);
  LCD_WR_DATA(0x09);
  LCD_WR_DATA(0x0F);
  LCD_WR_DATA(0x07);
  LCD_WR_DATA(0x00);
  LCD_WR_REG(0XE1); //Set Gamma
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x23);
  LCD_WR_DATA(0x24);
  LCD_WR_DATA(0x07);
  LCD_WR_DATA(0x10);
  LCD_WR_DATA(0x07);
  LCD_WR_DATA(0x38);
  LCD_WR_DATA(0x47);
  LCD_WR_DATA(0x4B);
  LCD_WR_DATA(0x0A);
  LCD_WR_DATA(0x13);
  LCD_WR_DATA(0x06);
  LCD_WR_DATA(0x30);
  LCD_WR_DATA(0x38);
  LCD_WR_DATA(0x0F);
  LCD_WR_REG(0x11); //Exit Sleep
  Delay_ms(120);
  LCD_WR_REG(0x29); //Display on
}

#elif defined(DZ301_TFT35)
void LCD_init_Reg(void)
{
  LCD_WR_REG(0x36);  // memory acess dir
  LCD_WR_DATA(infoSettings.rotate_ui ? 0x28 : 0xE8);
  LCD_WR_REG(0x3A);  // color bit depth
  LCD_WR_DATA(0x55); // 0x66 18bit; 0x55 16bit
  LCD_WR_REG(0x38);  // idle mode off, disable reduce color
  LCD_WR_REG(0x34);
  LCD_WR_REG(0x20);  // invert color off
  LCD_WR_REG(0x29);
  LCD_WR_REG(0x13);  // display normal mode
  LCD_WR_REG(0x11);  // sleep out
}

void LCD_init_RGB(void) 	
{
  Delay_ms(120);             // Delay 120 ms 
  //************* Start Initial Sequence **********// 	
  LCD_WR_REG(0XF7);    	
  LCD_WR_DATA(0xA9); 	
  LCD_WR_DATA(0x51); 	
  LCD_WR_DATA(0x2C); 	
  LCD_WR_DATA(0x82);

  LCD_WR_REG(0XEC);    	
  LCD_WR_DATA(0x00); 	
  LCD_WR_DATA(0x02); 	
  LCD_WR_DATA(0x03); 	
  LCD_WR_DATA(0x7A);

  LCD_WR_REG(0xC0); 	
  LCD_WR_DATA(0x13); 	
  LCD_WR_DATA(0x13); 	
    
  LCD_WR_REG(0xC1); 	
  LCD_WR_DATA(0x41); 	
    
  LCD_WR_REG(0xC5); 	
  LCD_WR_DATA(0x00); 	
  LCD_WR_DATA(0x28); 	
  LCD_WR_DATA(0x80);
    
  LCD_WR_REG(0xB1);   //Frame rate 70HZ  	
  LCD_WR_DATA(0xB0);
  LCD_WR_DATA(0x11);	
    
  LCD_WR_REG(0xB4); 	
  LCD_WR_DATA(0x02);   	
    
  LCD_WR_REG(0xB6); //RGB/MCU Interface Control	
  LCD_WR_DATA(0x02);   //MCU	
  LCD_WR_DATA(0x02); 

  LCD_WR_REG(0xB7); 	
  LCD_WR_DATA(0xc6); 

  LCD_WR_REG(0xBE); 	
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x04);	
    
  LCD_WR_REG(0xE9); 	
  LCD_WR_DATA(0x00);

  LCD_WR_REG(0xF4); 	
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x0f);	
    
  LCD_WR_REG(0xE0); 	
  LCD_WR_DATA(0x00); 	
  LCD_WR_DATA(0x04); 	
  LCD_WR_DATA(0x0E); 	
  LCD_WR_DATA(0x08); 	
  LCD_WR_DATA(0x17); 	
  LCD_WR_DATA(0x0A); 	
  LCD_WR_DATA(0x40); 	
  LCD_WR_DATA(0x79); 	
  LCD_WR_DATA(0x4D); 	
  LCD_WR_DATA(0x07); 	
  LCD_WR_DATA(0x0E); 	
  LCD_WR_DATA(0x0A); 	
  LCD_WR_DATA(0x1A); 	
  LCD_WR_DATA(0x1D); 	
  LCD_WR_DATA(0x0F);  	
    
  LCD_WR_REG(0xE1); 	
  LCD_WR_DATA(0x00); 	
  LCD_WR_DATA(0x1B); 	
  LCD_WR_DATA(0x1F); 	
  LCD_WR_DATA(0x02); 	
  LCD_WR_DATA(0x10); 	
  LCD_WR_DATA(0x05); 	
  LCD_WR_DATA(0x32); 	
  LCD_WR_DATA(0x34); 	
  LCD_WR_DATA(0x43); 	
  LCD_WR_DATA(0x02); 	
  LCD_WR_DATA(0x0A); 	
  LCD_WR_DATA(0x09); 	
  LCD_WR_DATA(0x33); 	
  LCD_WR_DATA(0x37); 	
  LCD_WR_DATA(0x0F); 


  LCD_WR_REG(0xF4);      //解决电荷残留问题
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x00);
  LCD_WR_DATA(0x0f);	
    
  LCD_WR_REG(0x20); 
  LCD_WR_REG(0x36); 	
  LCD_WR_DATA(0xE8); 	
    
  LCD_WR_REG(0x3A);
  LCD_WR_DATA(0x55);  //0x66 18bit; 0x55 16bit			
    
  LCD_WR_REG(0x11); 	
  Delay_ms(20); 	
  LCD_WR_REG(0x29);
  Delay_ms(10); 
}
#endif

void LCD_RefreshDirection(void)
{
  LCD_WR_REG(0X36);
  LCD_WR_DATA(infoSettings.rotate_ui ? 0x28 : 0xE8);
}
uint16_t gcolor = WHITE;
void LCD_Init(void)
{
  // dma_init(FSMC_DMA_DEV);
  // dma_disable(FSMC_DMA_DEV, FSMC_DMA_CHANNEL);
  // dma_set_priority(FSMC_DMA_DEV, FSMC_DMA_CHANNEL, DMA_PRIORITY_MEDIUM);
  LCD_FSMCInit(FSMC_CS_PIN, FSMC_RS_PIN);

  LCD_init_RGB();
  LCD_RefreshDirection();
  #if 1
    GUI_Clear(BLACK);
  #endif
  // while(1) {
  //   GUI_Clear(gcolor);
  //   delay(200);
  // }
  
 Delay_ms(20);
  
#ifdef LCD_BACKLIGHT_PIN
  LCD_LED_Init();
  LCD_LED_On();
#endif
}
