
void lafadza(){
static const uint8_t satu[] PROGMEM = {
                                            16,15,
                                            0x00,0x84,
                                            0x05,0x84,
                                            0x07,0x04,
                                            0x00,0x04,
                                            0x00,0x04,
                                            0x00,0x24,
                                            0x00,0xA6,
                                            0x08,0xB2,
                                            0x08,0xB2,
                                            0x18,0x92,
                                            0x38,0xD2,
                                            0x68,0xF2,
                                            0x7D,0xF0,
                                            0xF7,0x30,
                                            0x07,0x00,
};
                                            
Disp.drawFilledRect(75,0,96,15,0);    
Disp.drawBitmap(79,1, satu); 
     
 }
void lafadzb(){
   static const uint8_t dua[] PROGMEM = {
                                            16,14,
                                            0x18,0x08,
                                            0x0C,0x14,
                                            0x06,0x1C,
                                            0x06,0x70,
                                            0x06,0xC0,
                                            0x06,0x80,
                                            0x06,0xFF,
                                            0x06,0x1E,
                                            0x1B,0xF8,
                                            0xB1,0x80,
                                            0xE0,0x6C,
                                            0x00,0x7E,
                                            0x00,0x12,
                                            0x00,0x0C,
   };
Disp.drawFilledRect(0,0,20,15,0);                                            
Disp.drawBitmap(2,1, dua);
      
 }
 ///////// animasi GAMBAR MASJID
void anim_masjid(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 100)
  {
    if (s == 0 and y < 16) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
    }

  }
  if ((Tmr - lsRn) > 3000 and y == 16) {
    s = 1;
  } //10000
  if (y == 16)

  {

  }
  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }
  //fType(1);
  // masjida(y-8);
  // gambar();
  nama(16 - y);
  masjida(16 - y);
  masjidb(16 - y);

}
//====================
void masjida(uint16_t y) {
  static const uint8_t dall[] PROGMEM = {
    16, 16,
    B00100000,  B00000001,
    B01110000,  B00000011,
    B01110000,  B00000111,
    B00100000,  B00001111,
    B00100000,  B00011111,
    B01110000,  B00011111,
    B11111000,  B00001111,
    B01110000,  B00000111,
    B01110111,  B11111111,
    B01110000,  B00000000,
    B01110111,  B11111111,
    B01110111,  B01111110,
    B01110110,  B00111100,
    B01110110,  B00111100,
    B01110110,  B00111100,
    B11111111,  B11111111
  };
  Disp.drawBitmap(1, y, dall);
  DoSwap = true;
}
void masjidb(uint16_t y) {
  static const uint8_t eall[] PROGMEM = {
    16, 16,
    B00000000,  B00011100,
    B10000000,  B00100010,
    B11000000,  B00001011,
    B11100000,  B00000010,
    B11110000,  B00001100,
    B11110000,  B00001000,
    B11100000,  B00111110,
    B11000000,  B00011100,
    B11111111,  B11011100,
    B00000000,  B00011100,
    B11111111,  B11011100,
    B11111101,  B11011100,
    B01111000,  B11011100,
    B01111000,  B11011100,
    B01111000,  B11011100,
    B11111111,  B11111110
  };
  Disp.drawBitmap(17, y, eall);
  DoSwap = true;
}

void nama(uint16_t y) {
  Disp.setFont(bmz6x7);
  dwCtr(38, y + -1,"SELAMAT");
  Disp.setFont(bmz6x7);
  dwCtr(38, y + 8, "DATANG");
  DoSwap = true;
}
