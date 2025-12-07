#include "hal.h"
#include "ca_segment_7.h"
#include "keypad_4x4.h"

#define led_data PORT_A
#define segment_data PORT_B

#define column_data PORT_F
#define row_data PORT_K
void main() {
  // put your setup code here, to run once:
  volatile uint8_t keypressed,last_key;
  volatile uint16_t num1,num2,display_num,temp_num,operation,result;

  const uint8_t equal_to_key='E';
  keypad_init(row_data,column_data);
  commonanode_init(led_data,segment_data);

  while(1)
  {
    keypressed=keypad_number();
    if(keypressed!=0 && keypressed>='0' && keypressed<='9')
    {
      
      {
        temp_num=(temp_num*10)+(keypressed-'0');
        display_num=temp_num;
      }
    }
    if(keypressed!=0 && keypressed>='A' && keypressed<='F' && keypressed!='E')
    {
      operation=keypressed;
      num1=temp_num;
      temp_num=0;
      display_num=temp_num;
    }
    
    if(keypressed!=0 && keypressed=='E')
    {
      num2=temp_num;
      switch(operation)
      {
        case'A'://ADD
          result=num1+num2;
          break;
        case'B'://SUBSTRACT
          result=num1-num2;
          break;
        case'C'://MULTIPLY
          result=num1*num2;
          break;
        case'D'://DIVIDE
          result=num1/num2;
          break;
        case'F'://REMAINDER or MODULUS
          result=num1%num2;
          break;
        default:
          result=0;
          break;
      }
      display_num=result;
    }
    if(display_num<=9999){
      commonanode_display(display_num);
    }
    else
    {
      port_drive_out(segment_data,0x0f);
    port_drive_out(led_data,0x86);
    }
    
    
  }
    
}
