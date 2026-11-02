//-----------------------------------------------------------------------------
//STC12C2052  22.1184MHz  

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include<reg52.h>
#include<intrins.h>

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------
#define SYSCLK       22118400                                                         // SYSCLK frequency in Hz
#define BAUD_RATE    115200
#define uchar unsigned char 
#define uint unsigned int 

uint  j,level;
uchar i,value,num,add,dec,pppp,tttt;
uchar rec[8];

uchar pic[4]={0xAA,0x70,0x00,0x00};	                                          // "Display Picture-00" 	
uchar xdata text[17]={0xAA,0x98,0x01,0x54,0x00,0x43,0x03,0x85,0x04,0x00,0x00,0xFF,0xFF,0x00,0x32,0x00,0x30};   
//"Display the number of Temperature"	
uchar end[4]={0xCC,0x33,0xC3,0x3C};	                                          // "Frame end"	

uchar  clr[16]={0xAA,0x71,0x00,0x07,0x01,0x0A,0x00,0x32,0x01,0xD1,0x00,0xDD,0x01,0x0A,0x00,0x32};        
// "Lamp"
uchar clr1[16]={0xAA,0x71,0x00,0x06,0x01,0x0A,0x00,0x32,0x01,0xD1,0x00,0xDD,0x01,0x0A,0x00,0x32};  
// "Clean Lamp"

uchar xdata clr2[16]={0xAA,0x71,0x00,0x0B,0x00,0x25,0x00,0x0F,0x00,0x3A,0x00,0x2F,0x01,0x7A,0x00,0x11};   
//"Display the number of TV"
uchar xdata clr3[16]={0xAA,0x71,0x00,0x0B,0x00,0x0F,0x00,0x0F,0x00,0x25,0x00,0x2F,0x01,0x64,0x00,0x11};   
//"Display the number of 0"

uchar clr4[16]={0xAA,0x71,0x00,0x0A,0x01,0x33,0x00,0x3E,0x01,0x77,0x00,0x64,0x01,0x33,0x00,0x3E};  
// "Clean the number of Temperature"
		
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void Uart0_transmit(uchar i);                                      // "Send a byte to the terminal"
void Timer0(void);                                                       // "Time interrupt"
void send_str(uchar *p,uchar s);                                // "Send a string to the terminal"
void UART0_ISR(void);                                              // "Receive Character Interrupt"
void delay_ms(uchar n);                                            // "Delay"
void SysInit(void);                                                       // "Intialization of system"
void en(void);                                                              // "Send Frame end to the terminal"
void pic_str(uchar i);                                                  // "Picture Switch"
void bird_fly(void);                                                     // "Dynamic Bird-fly"
void Lamp(void);                                                        // "Lamp
void TV(void);                                                            // "TV"
void Air_condition(void);                                          // "Air_condition"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Timer0 interrupt                                                      // "Time interrupt"          
//-----------------------------------------------------------------------------
void Timer0(void)  interrupt 1 using 1   
{   
			TR0=0;
			TF0=0;
			TH0=0xDC;//B8;
			TL0=0x00;
			

		        TR0 = 1;		  
}       



//-----------------------------------------------------------------------------
// UART0_ISR                                                               //"Receive Character Interrupt"
//-----------------------------------------------------------------------------
//e.g:rec[10]={AA 78 00 00  CC 33 C3 3C}                                  
//"78 Command""If you touch the screen, the terminal will output a feedback value "AA 78 00 value CC 33 C3 3C" to your MCU."  
//"That is very important"                                                                                                                  
//"The value is set by touch control file . "


void UART0_ISR() interrupt 4                                                     
{ 
   uchar temp;                                                                          
   if(RI)
  {
        for(temp=0;temp<7;temp++)
           {rec[temp]=rec[temp+1];}                                                    
             rec[7]=SBUF;

             if((rec[0]==0xAA)&&(rec[1]==0x78)&&(rec[4]==0xCC)&&(rec[5]==0x33)&&(rec[6]==0xC3)&&(rec[7]==0x3C))             
                                                                                                                  //  "Judge whether somebody touches screen or not"
		{
		        value=rec[3];	                                           // "The feedback value"

                        
                                           if(rec[3]==0x15){add=1;dec=0;}                  //"Touch the'Add' button" "The value of 'Add' button is 0x15 "
                                          else if(rec[3]==0x16){add=0;dec=1;}            //"Touch the'Dec'button""The value of 'Dec' button is 0x16 "
                                                  
	                }
   

		RI=0;
     }	 
  else
  {
   TI=1;
  }
}


//-----------------------------------------------------------------------------
// Uart0_transmit
//-----------------------------------------------------------------------------
void Uart0_transmit(uchar i)	                                                                   // "Send a byte to the terminal"      
{ 
			ES=0;
			TI=0;
			SBUF=i; 		                                // "Send data to uart0"
			while (!TI); 		              // "wait for the finish of sending a byte"
			TI=0 ; 			              // "Cleaar the interruption mark"
			ES=1;
}

void send_str(uchar *p,uchar s)                                                                    // "Send a string to the terminal"
{
			uchar m;
			for(m=0;m<s;m++)
			{
				Uart0_transmit(*p);
				p++;
			}
}
//-----------------------------------------------------------------------------
// delay                                                                                                                                                                                                              
//-----------------------------------------------------------------------------
void delay_ms(uchar n)                                                                                 //"Delay unit is 25ms"
{  
			 uint i,j;  
			 for(i=1000;i>0;i--) {
			 for(j=25*n;j>0;j--) {;}
			 }
}

//-----------------------------------------------------------------------------
// SysInit                                                                                                           //"Intialization of system"
//-----------------------------------------------------------------------------
void SysInit(void)
{
                        				
				PCON |=0x80;
				SCON=0x50;
				TMOD=0x21;
				TH1=255;
				TL1=255;
				TR1=1;
	      ES=0;
	      TH0=0xDC;
	      TL0=0x00;
	      TR0=1;
	      ET0=1;

   num=0;
   add=0;
   dec=0;
}

//-----------------------------------------------------------------------------
// end_str                                                                                                           //"Send Frame end to the terminal"
//-----------------------------------------------------------------------------                         //"Must send Frame end when you send a command"
void en(void)
{
		send_str(end,4);	
}

//-----------------------------------------------------------------------------
// pic_str                                                                                                          //"Picture Switch"
//-----------------------------------------------------------------------------
void pic_str(uchar i)
{
		pic[3]=i;
		send_str(pic,4);
		en();
}

//-----------------------------------------------------------------------------
// bird_fly                                                                                                          //"Dynamic Bird fly"         
//-----------------------------------------------------------------------------
void bird_fly(void)
{
     
     for(tttt=0;tttt<=2;tttt++)                                                                                //"Display a group of pictures in a cycle "   
        {
          if(value==0x17)                                                                                     //"Touch 'Open' button""The value of 'Open' button is 0x17 " 
             {
              for(pppp=14;pppp<=21;pppp++)
	         {	
		  pic_str(pppp);                                       				   			
		  delay_ms(5);			             //"Delay"		               
	         }
             }
          else if(value==0x18)                                                                             //"Touch 'Close'button""The value of 'Close' button is 0x18 "
             {
              for(pppp=21;pppp>=14;pppp--)
	         {	
		  pic_str(pppp);				   			
		  delay_ms(5);							               
	         }
             }
         }                   								 	
}     
                     
//-----------------------------------------------------------------------------
// Lamp                                                                                                             // "Lamp"                                                                          
//-----------------------------------------------------------------------------
void Lamp(void)
{
     if(value==0x0F){ clr1[10]=0x00;clr1[11]=0x32;}                                     //"Choose brightness Level-01"
else if(value==0x0E){ clr1[10]=0x00;clr1[11]=0x53; }                                 //"Choose brightness Level-02"
else if(value==0x0D){ clr1[10]=0x00;clr1[11]=0x6F; }                                //"Choose brightness Level-03"
else if(value==0x0C){ clr1[10]=0x00;clr1[11]=0x8B;}                                //"Choose brightness Level-04"
else if(value==0x0B){ clr1[10]=0x00;clr1[11]=0xA7;}                                 //"Choose brightness Level-05"
else if(value==0x0A){ clr1[10]=0x00;clr1[11]=0xC3;}                                 //"Choose brightness Level-06"

if(value==0x0F){clr[6]=clr[14]=0x00;clr[7]=clr[15]=0x32;}                         //"Choose brightness Level-01"
else if(value==0x0E){ clr[6]=clr[14]=0x00;clr[7]=clr[15]=0x53;}                //"Choose brightness Level-02"
else if(value==0x0D){ clr[6]=clr[14]=0x00;clr[7]=clr[15]=0x6F;}               //"Choose brightness Level-03"
else if(value==0x0C){ clr[6]=clr[14]=0x00;clr[7]=clr[15]=0x8B;}                //"Choose brightness Level-04"
else if(value==0x0B){ clr[6]=clr[14]=0x00;clr[7]=clr[15]=0xA7;}                //"Choose brightness Level-05"
else if(value==0x0A){ clr[6]=clr[14]=0x00;clr[7]=clr[15]=0xC3; }                //"Choose brightness Level-06"

          send_str(clr1,16);                                                                                //"Clean"
          en();

          delay_ms(1);
          send_str(clr,16);                                                                                   // "Display the brightness level"
          en();  
          value=0x30;
                            								 	
}       

//-----------------------------------------------------------------------------
// TV                                                                         //"TV"                                                                               
//-----------------------------------------------------------------------------
void TV(void)
{
     
   if(value==0x01) {clr2[4]=0x00; clr2[5]=0x25; clr2[8]=0x00; clr2[9]=0x3A;}           //"Press '1'"
   else if(value==0x02) {clr2[4]=0x00; clr2[5]=0x3B; clr2[8]=0x00; clr2[9]=0x50;}   //"Press '2'"
   else if(value==0x03) {clr2[4]=0x00; clr2[5]=0x51; clr2[8]=0x00; clr2[9]=0x66;}   //"Press '3'"
   else if(value==0x04) {clr2[4]=0x00; clr2[5]=0x66; clr2[8]=0x00; clr2[9]=0x7C;} //"Press '4'"
   else if(value==0x05) {clr2[4]=0x00; clr2[5]=0x7C; clr2[8]=0x00; clr2[9]=0x91;}   //"Press '5'"
   else if(value==0x06) {clr2[4]=0x00; clr2[5]=0x92; clr2[8]=0x00; clr2[9]=0xA7;}    //"Press '6'"
   else if(value==0x07) {clr2[4]=0x00; clr2[5]=0xA7; clr2[8]=0x00; clr2[9]=0xBC;}    //"Press '7'"
   else if(value==0x08) {clr2[4]=0x00; clr2[5]=0xBD; clr2[8]=0x00; clr2[9]=0xD2;}   //"Press '8'"
   else if(value==0x09) {clr2[4]=0x00; clr2[5]=0xD3; clr2[8]=0x00; clr2[9]=0xE8;}     //"Press '9'"

   send_str(clr3,16);                                                                                                         //"Display the number of 0" 
   en();    

   send_str(clr2,16);                                                                                                        //"Display the number of TV"            
   en();  
    
   value=0x30;                                          
                   								 	
}     

//-----------------------------------------------------------------------------
// Air_condition                                                                                                                //"Air-condition"                                                                               
//-----------------------------------------------------------------------------
void Air_condition(void)
{
        if(value==0x15){add=1;dec=0;}                     //"Touch the'Add' button" "The value of 'Add' button is 0x15 "
        else if(value==0x16){add=0;dec=1;}             //"Touch the'Dec'button""The value of 'Dec' button is 0x16 "

        num=num+add-dec;                      

        if(num>=0x0A){num=0x09;}
        else if(num<=0){num=0x01;}

        send_str(clr4,16);                                           //"Clean the number of temperature" 
        en();

        text[16]=0x30+num;
        send_str(text,17);                                            //"Display the number of temperature"
        en();
                                           
                   								 	
}                                                                    

                                                          
//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------
void main (void)
{	   
   EA=0;                                   //"turning off interruption"
   SysInit();	                               //"Intialization of system"
   EA=1;                                   //"turning on interruption"
  
   delay_ms(2);
                            
   pic[1]=0x00;
   send_str(pic,2);                  //"Handshake Command AA 00 CC 33 C3 3C"	
   en();

   value=0x30;
   	 
   delay_ms(20);
   pic[1]=0x70;                               
   pic_str(0);                            //"Display picture-00"    
   
               
   while (1) 
 {    
						
if(value==0x00)                     //"Main Interface" "the value of 'Back' button is 0x00."
   {  	                      
      delay_ms(1);

      pic_str(1);                         //"Display picture-01"  
      value=0x30;                                      	   		
   }

                                                              
          
else if((value>=0x0A)&&(value<=0x0F))     //"Lamp Subprogram" The value of brightness level are from 0x0A to 0x0F."
    {
       delay_ms(1);
       Lamp();
       value=0x30;

    }                      

else if((value>=0x01)&&(value<=0x09))      //"TV Subprogram""The value of 'keyboard' are from 0x01 to 0x09."
     {
       delay_ms(1);                                                           
           
       TV();               
                  
       value=0x30;
     }

else if((value==0x15)||(value==0x16))      //"Air-condition Subprogram""The value of 'Add'&'Dec'button are 0x15 & 0x16."
     {
       delay_ms(1);
       Air_condition();
        
       value=0x30;
     }

else if((value==0x17)||(value==0x18))      //"Curtain Subprogram"" "The value of 'Open'&'Close' are 0x17 &0 x18."
   {     
     delay_ms(1);
     bird_fly();                               //"Bird Fly"  
     pic_str(12);                           //"Display picture-12"   
                                                                                  
     value=0x30;                                                       					
   }
 }
  
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------