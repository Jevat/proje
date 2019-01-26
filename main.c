
     ///// tm4c123gh için gerekli kütüphaneler
#include <stdint.h>
#include "tm4c123gh6pm.h"
     //////   program'da kullanilacak olan fonksiyonlar
void UART7Tx(char c);
char UART7Rx(void);
char UART5Rx(void); 
void UART5Tx(char c);
void delayMs(int n);
unsigned int check=0,i  ;
unsigned int check1=0,i1  ;
char info[800];
char info1[120];
char test[6]={"$GPRMC"};
void UART7_OutString(char *pt);
void getrx(void);
void UART_Init(void);

///////////// ANA PROGRAM //////////
int main(void) 
{
    char c;	
	    //////// UART'lari kurulur //////
    SYSCTL->RCGCUART |= 0xFF;  /* provide clock to UART5 and UART0 AND UART1 */
    SYSCTL->RCGCGPIO |= 0xFF;  /* Enable clock to PORTE AND PORT B AND PORT A*/

    /* UART5 initialization */
    UART5->CTL = 0;         /* disable UART5 */
    UART5->IBRD = 104;      /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
    UART5->FBRD = 11;       /* fraction part, see Example 4-4 */
    UART5->CC = 0;          /* use system clock */
    UART5->LCRH = 0x60;     /* 8-bit, no parity, 1-stop bit */
    UART5->CTL = 0x301;     /* enable UART5, TXE, RXE */
  
	   /* UART1 initialization */
    UART7->CTL = 0;         /* disable UART1 */
    UART7->IBRD = 104;      /* 50MHz/16=3.125MHz, 3.125MHz/325=9600 baud rate */
    UART7->FBRD = 11;       /* fraction part, see Example 4-4 */
    UART7->CC = 0;          /* use system clock */
    UART7->LCRH = 0x60;     /* 8-bit, no parity, 1-stop bit, no FIFO */
    UART7->CTL = 0x301;     /* enable UART1, TXE, RXE */

    /* UART5 TX5 and RX5 use PE5 and PE4. Set them up. */
    GPIOE->DEN = 0x33;      /* make PE5, PE4 as digital */
    GPIOE->AMSEL = 0;       /* turn off analog function */
    GPIOE->AFSEL = 0x33;    /* use PE5, PE4 alternate function */
		GPIOE->PCTL = 0x00110011;     /* configure PE5, PE4 for UART5 */

    UART_Init();
	 /// gsm fonksiyonu git ve baglantiyi orda kur ///
		UART_OutChar('\n');
		gsm();
		UART_OutChar('\n');
	   /// gps'i kur ve konum bilgileri al ///
		get_kordinat();
		
		/// bilgileri internet sayfasinda oku ///
int k=0;
for(k =0 ; k<10;k++)
	{
		delayMs(70000);
		UART7_OutString("AT+HTTPREAD=0,20\r\n");	
		
		for(k =0 ; k<54;k++)
		{
			delayMs(1);
			c =UART7Rx();        /* get a character from UART */}
		UART_OutChar('\n');
			UART_OutChar(k);
			UART_OutChar('\n');
		delayMs(1000);
			}

	UART7_OutString("AT+HTTPTERM\r\n");	
for(k =0 ; k<23;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);



		

		}

		
		
		
		
		
		
		///    sim800l baglantisini kur ve internet'e baglan ///
int gsm(void)
{
	char c;
	
//	c = UART7Rx();
	delayMs(1500);
	int k=0;
	
UART7_OutString("AT\r\n");  //// çipin çalistigindan emin olmak için ///	
for(k =0 ; k<8 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        }
	 
	UART_OutChar('\n');
		delayMs(100);
		UART7_OutString("AT+CBAND?\r\n");	   /// bandin içinde olmasi gerekir ///
for(k =0 ; k<45 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        }
	 
	UART_OutChar('\n');
		delayMs(100);
		
		UART7_OutString("AT+CGATT=1\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(100);
		UART7_OutString("AT+CSMINS?\r\n");	  /// SIM kartin çipte olmasindan emin olmamiz lazim 
for(k =0 ; k<28 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		UART7_OutString("AT+CSPN?\r\n");	
for(k =0 ; k<20 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		UART7_OutString("AT+CPAS\r\n");
		
for(k =0 ; k<18 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		UART7_OutString("AT+CFUN?\r\n");	  ///// simin fonkisyonluk durumundan emin olmak için 
for(k =0 ; k<26 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		
		delayMs(1000);
		
		UART7_OutString("AT+COPS?\r\n");	
for(k =0 ; k<35 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 UART_OutChar('\n');
			delayMs(1000);

		
		UART7_OutString("AT+COPS?\r\n");	
for(k =0 ; k<35 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);

		
UART7_OutString("AT+CBC\r\n");	//// enerji durumundan emin olmak için 
		
for(k =0 ; k<27 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 delayMs(1000);
	UART_OutChar('\n');
		UART7_OutString("AT+CREG=?\r\n");	   /// register durumunu bilmek için 
for(k =0 ; k<30 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	
		
		 delayMs(1000);
	UART_OutChar('\n');
		UART7_OutString("AT+CSTT?\r\n");	
for(k =0 ; k<30 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		UART7_OutString("AT+CREG?\r\n");	
for(k =0 ; k<25 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
				delayMs(1000);
		UART7_OutString("AT+CREG=1\r\n");	    //// sebekeye kayid olmak komutu 
		UART_OutChar('\n');
		delayMs(1000);
UART7_OutString("AT+CREG?\r\n");	
for(k =0 ; k<25 ;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
			
		delayMs(1000);
UART7_OutString("AT+HTTPPARA?\r\n");	
for(k =0 ; k<164;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		UART7_OutString("AT+COPS=1,2,""28601""\r\n");	///// sebeke'deki bir hosta baglanmak için 
		delayMs(1000);
			UART7_OutString("AT+COPS?\r\n");	
for(k =0 ; k<35;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);

		
		/////   asagdaki komutlar HTTP BAGLANTISI KURMAK IÇIN GEREKLI OLAN KOMUTLARDIR
		UART7_OutString("AT+SAPBR=3,1,""Contype"",""GPRS""\r\n");	    /// http baglantisi hazirlamak için
for(k =0 ; k<23;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		UART7_OutString("AT+SAPBR=3,1,""APN"",""CMNET""\r\n");	// http baglantisi hazirlamak için
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
				UART7_OutString("AT+SAPBR =1,1\r\n");	// http baglantisi hazirlamak için
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
		
				UART7_OutString("AT+SAPBR=2,1\r\n");	// http baglantisi hazirlamak için
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		

					UART7_OutString("AT+HTTPPARA=""REDIR"",1\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
							UART7_OutString("AT+HTTPSSL=0\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
					
		
		
			UART7_OutString("AT+HTTPSSL=1\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
//				UART7_OutString("AT+HTTPSCONT?\r\n");	
//for(k =0 ; k<123;k++)
//	{
//		delayMs(1);
//		c =UART7Rx();        /* get a character from UART */}
//	 
//	UART_OutChar('\n');
//		delayMs(1000);
//		

			UART7_OutString("AT+HTTPPARA=""PROIP"",""148.233.151.240""\r\n");	
for(k =0 ; k<15;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
			UART7_OutString("AT+HTTPPARA=""PROPORT"",""8080""\r\n");	
for(k =0 ; k<15;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
		
		
		UART_OutChar('\n');
		UART_OutChar('h');
		UART_OutChar('\n');
		
		///// BAGLANTI KURULACAK OLAN WEB SITE ADRESI //////
		UART7_OutString("AT+HTTPPARA=""URL"",""http://api.thingspeak.com/apps/thinghttp/send_request?api_key=SHJKOGBNQ14RN5BH""\r\n");	
for(k =0 ; k<25;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		

		
//		UART7_OutString("AT+SAPBR=3,1,""USER"","" ""\r\n");	
//for(k =0 ; k<31;k++)
//	{
//		delayMs(1);
//		c =UART7Rx();        /* get a character from UART */}
//	 
//	UART_OutChar('\n');
//		delayMs(1000);
//		
//		UART7_OutString("AT+SAPBR=3,1,""PWD"","" ""\r\n");	
//for(k =0 ; k<21;k++)
//	{
//		delayMs(1);
//		c =UART7Rx();        /* get a character from UART */}
//	 
	UART_OutChar('\n');
		delayMs(1000);
				
		UART7_OutString("AT+HTTPPARA=""CID"",1\r\n");	
for(k =0 ; k<23;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		delayMs(1000);
		
		UART7_OutString("AT+CGATT=1\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
				
		UART7_OutString("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
						
		UART7_OutString("AT+SAPBR=3,1,\"APN\",\"\"\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
							
		UART7_OutString("AT+SAPBR=1,1\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
			
	
	UART7_OutString("AT+HTTPINIT\r\n");	
for(k =0 ; k<14;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
		
		UART7_OutString("AT+HTTPPARA=""URL"",""http://ptsv2.com/t/kbuproject/post""\r\n");	
for(k =0 ; k<25;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
				
			UART7_OutString("AT+HTTPACTION=0\r\n");	
for(k =0 ; k<47;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
	
		
		
				delayMs(300);
		UART7_OutString("AT+HTTPREAD=0,20\r\n");	
for(k =0 ; k<54;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
		UART7_OutString("AT+HTTPPARA?\r\n");	
for(k =0 ; k<187;k++)
	{
		delayMs(1);
		c =UART7Rx();        /* get a character from UART */}
	 
	UART_OutChar('\n');
		delayMs(1000);
		
		
	
}




 
///// KONUMU BILGILERI ELDE EDILMEK IÇINDIR /////
//// 
int get_kordinat(void)
{
	char c;
	for(check =0 ; check<550 ;check++)
	{
			delayMs(1);
	

			c = UART5Rx();          /* get a character from UART */

			info[check++] = c;
  }
		for(check =0 ; check<600;check++)
    {	
				for(check =0 ; check<600 ;check++)
				{
					if(info[check]!=test[check])
					{
						for(check =1 ; check<200 ;check++)
						{
							UART_OutChar(info[check]);
						}
						UART_OutChar('\n');
						

						delayMs(5000);
//						get_kordinat();
											
					}
					
					
				}
			}
}
		//////////////////////////////
		/////   SIM CODE   ///////////
    ///// ABDULJAWAD KAYALI //////
		//////////////////////////////

		
		


//void find_comma()
//{
//unsigned int i,count=0;
//for(i=0;i<70;i++)
//{ 
//if(info[i]==',')
//{
//	comma_position[count++]=i;
//}
//    }
//}

/* UART0 Receive */
char UART5Rx(void)  
{
  char c;
    while((UART5->FR & 0x10) != 0); /* wait until the buffer is not empty */
    c = UART5->DR;                  /* read the received data */
//		UART0->DR = c;
//	  info[check++] = c;
    return c;                       /* and return it */
}

/* UART5 Transmit */
void UART5Tx(char c)  
{
    while((UART5->FR & 0x20) != 0); /* wait until Tx buffer not full */
    UART5->DR = c;                  /* before giving it another byte */
	  UART_OutChar(c);
	
	}

	
void UART7Tx(char c) {
    while((UART7->FR & 0x20) != 0); /* wait until Tx buffer not full */
//	  c = 'h';
//	  UART0->DR = UART_InChar();
//	  c = UART0->DR;
    UART7->DR = c;                  /* before giving it another byte */
//	UART_OutChar(c);
//		UART_OutString("AT");
//	UART_OutString(c);
	
//		UART0->DR = c;
//	  UART7->FR =0;
	 
}
 void UART7_OutString(char *pt){
  while(*pt){
    UART7Tx(*pt);
		UART_OutChar(*pt);
    pt++;
  }
	UART_OutChar('\n');
	
	
}


char UART7Rx(void)  
{
  char b;
    while((UART7->FR & 0x10) != 0); /* wait until the buffer is not empty */
    b = UART7->DR;                  /* read the received data */
//	  UART_OutString(c);
//		UART0->DR = c;
//	  info[check++] = c;
	  UART_OutChar(b);
//	   UART7->FR =0;
    return b;                       /* and return it */
}


/* Append delay functions and SystemInit() here */

void delayMs(int n) {
    int i, j;
    for(i = 0 ; i< n; i++)
        for(j = 0; j < 2000; j++)
            {}  /* do nothing for 1 ms */
							
	}

