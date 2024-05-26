//Note: This is a not clean code, this is only a pratical test
//where we don't want use any library or dependence of other's code blocks!!!

//The idea is to make the code so basic that you can let it change and see what happens!

#define VFD_in 5// 
#define VFD_clk 6 // 
#define VFD_cs 7 // 
#define VFD_rst 10 // 

#define delay_tcsh _delay_us(16)

unsigned char char0, char1, char2;

void send_data(unsigned char a) {
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask
  
  data = a;
  //This don't send the strobe signal, to be used in burst data send
  for (mask = 00000001; mask > 0; mask <<= 1) { //iterate through bit mask
    PIND = (0 << VFD_clk);
    if (data & mask) { // if bitwise AND resolves to true
      PORTD = (1 << VFD_in);
      Serial.print(bitRead(PORTD,5));
    }
    else { //if bitwise and resolves to false
      PORTD = (0 << VFD_in); // send 0
      Serial.print(bitRead(PORTD,5));
    }
    _delay_us(48); //delay
    PIND = (1 << VFD_clk);
    _delay_us(48); //delay
//    PIND &= ~(0 << VFD_clk);
//   _delay_us(48); //delay
  }
  Serial.println();
  delayMicroseconds(5);
}
void sendCommandVFD(unsigned char a) {
  unsigned char data = 0x00;
  unsigned char mask = 1; //our bitmask

  data = a;
  PIND = (1 << VFD_clk);
  PIND &= ~(1 << VFD_cs);
  _delay_us(48); //delay
          for (mask = 00000001; mask > 0; mask <<= 1) { //iterate through bit mask
            PIND = (0 << VFD_clk);
                  if (data & mask) { // if bitwise AND resolves to true
                    PORTD = (1 << VFD_in);
                  }
                  else { //if bitwise and resolves to false
                    PORTD = (0 << VFD_in); // send 0
                  }
            _delay_us(48); //delay
            PIND = (1 << VFD_clk);
            _delay_us(48); //delay
//            PIND &= ~(0 << VFD_clk);
//            _delay_us(48); //delay
          }
 _delay_us(48); //delay         
 PIND = (1 << VFD_cs);
}
void M35500_init(void) {
  digitalWrite(VFD_rst, LOW); //Reset happen at Low value!
  delay(300);
  digitalWrite(VFD_rst, HIGH); //Reset happen at Low value!
  delayMicroseconds(800); //power_up delay
  //
  // Configure VFD display (grids)
  sendCommandVFD(0b11101101);//     (Command 0) Display data setting 111x1100 is 10 digits and 16 or less segments(This means send 2Bytes or 3Bytes).
  _delay_us(48); //delay
  sendCommandVFD(0b11000111);//     (Command 1) Display ON and 15/16 duty setting.
 _delay_us(48); //delay
  sendCommandVFD(0b10101010);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(48); //delay
  sendCommandVFD(0b10000000);//     (Command 3) Port data settings Port selection: 0: P3-P0 & 1: P7-P4 Last four bits is output port.
  _delay_us(48); //delay  
}
void allOn(){
    //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0xFF;   //Here we send all "1". Is necessary 13 bits by digit, I sent 16 to be more easy, but you can specify it by correct way.
  char1 = 0xFF;
  char2 = 0x00;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
PIND = (1 << VFD_clk);
_delay_us(50); //delay 
PIND &= ~(1 << VFD_cs); 
_delay_us(50); //delay 

send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
_delay_us(8); //delay
//send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
//send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;

send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
//
delayMicroseconds(45);
PIND = (1 << VFD_cs);
}
void M35500clear(){
    //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0x00;
  char1 = 0x00;
  char2 = 0x00;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
PIND = (1 << VFD_clk);
_delay_us(50); //delay 
PIND &= ~(1 << VFD_cs); 
_delay_us(50); //delay 

send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
_delay_us(8); //delay
//
//send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
//send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;

send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
//
delayMicroseconds(45);
PIND = (1 << VFD_cs);
}
void msgHELLO(){
  //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0xFF;
  char1 = 0xFF;
  char2 = 0xFF;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
PIND = (1 << VFD_clk);
_delay_us(50); //delay 
PIND &= ~(1 << VFD_cs); 
_delay_us(50); //delay 

send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
_delay_us(8); //delay
//
//send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
//send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
char0=0b00000000;
char1=0b00010000;
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 1
send_data(0b10011100);   send_data(0b00000010);  send_data(0b00000000);   //  digito 2
send_data(0b10110100);   send_data(0b00000100);  send_data(0b00000000);   //  digito 3
send_data(0b10010000);   send_data(0b00000100);  send_data(0b00000000);   //  digito 4
send_data(0b10010000);   send_data(0b00000100);  send_data(0b00000000);   //  digito 5
send_data(0b10111000);   send_data(0b00000110);  send_data(0b00000000);   //  digito 6
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 7
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 8
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 9
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 10


//
delayMicroseconds(15);
PIND = (1 << VFD_cs);
}
void msg35500(){
  //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0xFF;
  char1 = 0xFF;
  char2 = 0xFF;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
PIND = (1 << VFD_clk);
_delay_us(50); //delay 
PIND &= ~(1 << VFD_cs); 
_delay_us(50); //delay 

send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
_delay_us(8); //delay
//
//send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
//send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
char0=0b00000000;
char1=0b00010000;
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 1
send_data(0b00101100);   send_data(0b00000110);  send_data(0b00000000);   //  digito 2
send_data(0b00110100);   send_data(0b00000110);  send_data(0b00000000);   //  digito 3
send_data(0b00110100);   send_data(0b00000110);  send_data(0b00000000);   //  digito 4
send_data(0b10111000);   send_data(0b00000110);  send_data(0b00000000);   //  digito 5
send_data(0b10111000);   send_data(0b00000110);  send_data(0b00000000);   //  digito 6
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 7
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 8
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 9
send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 10


//
delayMicroseconds(15);
PIND = (1 << VFD_cs);
}
void clearVFD(void) {
  /*
    Here I clean all registers
    Could be done only on the number of grid
    to be more fast. The 12 * 3 bytes = 36 registers
  */
  sendCommandVFD(0b11101101); // cmd 0
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  for (int i = 0; i < 30; i++) {
    send_data(0b00000000); // data
  }

  PIND = (1 << VFD_cs);
  delayMicroseconds(4);
}
void setup() {
  pinMode( VFD_in, OUTPUT);// 7: If 0 write LCD, if 1 read of LCD
  pinMode( VFD_clk, OUTPUT);// 8: if 0 is a command, if 1 is a data0
  pinMode( VFD_cs, OUTPUT);// 9: Must be pulsed to LCD fetch data of bus
  pinMode( VFD_rst, OUTPUT);// 10: if 0 is a command, if 1 is a data0
  
  digitalWrite(VFD_rst, HIGH);

  pinMode( 13, OUTPUT); //Pin of pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  M35500_init();
}
void loop() {
      for (uint8_t i = 0; i<3; i++){
        allOn();
        delay(1000);
        M35500clear();
        delay(200);
      }
//
 msgHELLO();
 delay(1500);
 msg35500();
 delay(1000);
 sendCommandVFD(0b11000111);//     (Command 1) Display ON and 15/16 duty setting.
 delay(500);
 sendCommandVFD(0b11000011);//     (Command 1) Display ON and 15/16 duty setting.
 delay(500);
 sendCommandVFD(0b11000111);//     (Command 1) Display ON and 15/16 duty setting.
 delay(500);
}
