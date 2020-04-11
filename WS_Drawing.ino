// =========================================
// Drawing Content Block====================
// =========================================
/*void anim_JB(int DrawAdd)
  {
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 100)
  {
    if (s == 0 and y < 15) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
    }
  }
  if ((Tmr - lsRn) > 3000 and y == 15) {
    s = 1;
  } //10000
  if (y == 7)
  {
    // Disp.drawRect(1,2,94,13);
  }
  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }
  fType(2);
  drawGreg_TS(y - 15);
  }*/
void drawAzzan(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;
  uint8_t           ct_limit = 16; //harus angka genap
  static uint8_t    ct;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 500 and ct <= ct_limit)
  {
    lsRn = Tmr;
    if ((ct % 2) == 0)
    { Disp.drawRect(1, 2, 94, 13);
      fType(0);
      dwCtr(0, 0, "ADZAN");
      fType(1);
      if (jumat) {
        dwCtr(0, 8, sholatN(8));
      }
      else      {
        dwCtr(0, 8, sholatN(SholatNow));
      }
      digitalWrite (BUZZ, HIGH);
    }
    else
    {
      digitalWrite (BUZZ, LOW);
    }
    DoSwap = true;
    ct++;
  }
  if ((Tmr - lsRn) > 2000 and (ct > ct_limit))
  { dwDone(DrawAdd);
    ct = 0;
    digitalWrite (BUZZ, LOW);
  }
}

void drawIqomah(int DrawAdd)  // Countdown Iqomah (9 menit)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  static int        ct;
  int               mnt, scd, cn_l ;
  char              locBuff[6];

  cn_l  = (Iqomah[SholatNow] * 60);
  Disp.drawRect(1, 2, 94, 13);
  if ((Tmr - lsRn) > 1000 and ct <= cn_l)
  {
    lsRn = Tmr;
    mnt = floor((cn_l - ct) / 60);
    scd = (cn_l - ct) % 60;
    if (mnt > 0) {
      sprintf(locBuff, "%d:%02d MENIT", mnt, scd);
    }
    else    {
      sprintf(locBuff, "%d DETIK", scd);
    }
    dwCtr(0, -1, "IQOMAH");
    fType(0);
    dwCtr(0, 9, locBuff);
    if (ct > (cn_l - 6)) digitalWrite (BUZZ, HIGH); // Buzzer on 2 seccon before Iqomah
    ct++;
    DoSwap = true;

  }
  if (ct > cn_l)
  {
    dwDone(DrawAdd);
    ct = 0;
    digitalWrite (BUZZ, LOW);
  }
}

void drawSholat_S(int sNum, int c) // Box Sholah Time
{

  char  Buff[10];

  
  char  BuffTime1[4];

  char  BuffTime3[4];
  char  BuffShol[7];
  float   stime   = sholatT[sNum];
  uint8_t shour   = floor(stime);
  uint8_t sminute = floor((stime - (float)shour) * 60);
  uint8_t ssecond = floor((stime - (float)shour - (float)sminute / 60) * 3600);
  sprintf(Buff, "%2d-%2d-%4d", now.day(), now.month(), now.year());
  sprintf(BuffTime1, "%02d", shour);

  sprintf(BuffTime3, "%02d", sminute);
  //Disp.drawRect(c+1,1,94,15);
  fType(0); dwCtr(4, 0, sholatN(sNum));
  fType(0); dwCtr(54, 0, BuffTime1);
  Disp.drawFilledRect(81, 1, 82, 2, 1);
  Disp.drawFilledRect(81, 4, 82, 5, 1);
  fType(0); dwCtr(84, 0, BuffTime3);
  Disp.setFont(bmz5x7);
  Disp.drawText(35, 9, Buff);
  DoSwap = true;
}

void drawSholat(int DrawAdd)
{
  // check RunSelector
  //    int DrawAdd = 0b0000000000000100;
  if (!dwDo(DrawAdd)) return;

  static uint8_t    x;
  static uint8_t    s; // 0=in, 1=out
  static uint8_t    sNum;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  uint8_t           c = 31;
  uint8_t    first_sNum = 0;
  int               DrawWd = DWidth - c;

  if ((Tmr - lsRn) > 10)
  {
    if (s == 0 and x < (DrawWd / 2)) {
      x++;
      lsRn = Tmr;
    }
    if (s == 1 and x > 0) {
      x--;
      lsRn = Tmr;
    }
  }

  if ((Tmr - lsRn) > 2000 and x == (DrawWd / 2)) {
    s = 1;
  }
  if (x == 0 and s == 1)
  {
    if (sNum < 7) {
      sNum++;
    }
    else
    {
      dwDone(DrawAdd);
      sNum = 0;
    }
    s = 0;
  }

  if (Prm.SI == 0) {
    first_sNum = 1;
  }
  else {
    first_sNum = 0;
  }
  if (Prm.SI == 0 and sNum == 0) {
    sNum = 1;
  }
  if (Prm.ST == 0 and sNum == 2) {
    sNum = 3;
  }
  if (Prm.SU == 0 and sNum == 3) {
    sNum = 4;
  }


  if (  (((sNum == first_sNum) and s == 0) or
         ((sNum == 7) and s == 1))
        and x <= 20) {
    drawSmallTS(int(x / 2));
  }
  else {
    drawSmallTS(10);
  }
  drawSholat_S(sNum, c);

  Disp.drawFilledRect(c, 0, c + DrawWd / 2 - x, 7, 0);
  Disp.drawFilledRect(DrawWd / 2 + x + c, 0, 98, 7, 0);
  DoSwap = true;
}

void drawGreg_DS(uint16_t y)   //Draw Date
{
  char  Buff[20];
  sprintf(Buff, "%d %s %d", now.day(), MonthName(now.month()), now.year());
  dwCtr(0, y, Buff);
  DoSwap = true;
}

void drawSmallTS(int x)
{

  char BuffH1[3];
  char BuffH2[3];
  char BuffM1[3];
  char BuffM2[3];

  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  sprintf(BuffH1, "%01d", now.hour() % 10 / 1);
  sprintf(BuffH2, "%01d", now.hour() % 100 / 10);
  sprintf(BuffM1, "%01d", now.minute() % 10 / 1);
  sprintf(BuffM2, "%01d", now.minute() % 100 / 10);
  Disp.setFont(bmz6x16);
  Disp.drawText((x - 20) + 10, 0, BuffH2);
  Disp.drawText((x - 20) + 17, 0, BuffH1);
  Disp.drawText((x - 20) + 28, 0, BuffM2);
  Disp.drawText((x - 20) + 35, 0, BuffM1);
  //Disp.setFont(SmallCap4x6);
  //Disp.drawText((x-20)+43,0,BuffD);
  if (Tmr - lsRn < 500)Disp.drawCircle(15, 4, 1);
  if (Tmr - lsRn < 500)Disp.drawCircle(15, 11, 1);
  if (Tmr - lsRn < 500)Disp.drawCircle(15, 4, 0);
  if (Tmr - lsRn < 500)Disp.drawCircle(15, 11, 0);
  //   Disp.drawLine((x-10)+32,0,(x-10)+32,17,1);
  if (Tmr - lsRn > 1000) lsRn = Tmr;

  DoSwap = true;


}


void drawGreg_TS(uint16_t y)   // Draw Time
{
  char  Buff[20];
  sprintf(Buff, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  dwCtr(0, y, Buff);
  DoSwap = true;
}

void anim_DT(int DrawAdd)
{

  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();



  if ((Tmr - lsRn) > 100)
  {
    if (s == 0 and y < 7) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
    }
  }

  if ((Tmr - lsRn) > 7000 and y == 7) {
    s = 1;
  }
  if (y == 7)
  {

    Disp.drawRect(1, 2, 94, 13);

  }

  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }

  Disp.setFont(bmz6x7);
  drawGreg_TS(y - 8);
  fType(0);
  drawGreg_DS(16 - y);


}

void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd)
{


  // check RunSelector
  static uint16_t   x;
  if (!dwDo(DrawAdd)) return;
  if (reset_x != 0) {
    x = 0;
    reset_x = 0;
  }
  //  if (azzan !=0) { x=0; azzan = 0;}

  static uint16_t   lsRn;
  int fullScroll = Disp.textWidth(msg) + DWidth;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > Speed)
  { lsRn = Tmr;
    if (x < fullScroll) {
      ++x;
    }
    else {
      dwDone(DrawAdd);
      x = 0; return;
    }
    if (dDT == 1)
    {
      Disp.setFont(bmz5x7);
      Disp.drawText(DWidth - x, 9, msg);
      lafadza();
      lafadzb();

      Disp.setFont(bmz5x7);
      if (x <= 6)                     {
        drawGreg_TS(x - 8);
      }

      else if (x >= (fullScroll - 6))   {
        drawGreg_TS((fullScroll - x) - 12);
      }
      else                          { //Disp.drawRect(24,1,70,7);
        drawGreg_TS(0);
      }
    }
    else if (dDT == 2)
    {
      Disp.setFont(bmz5x7);

      if (x <= 6)                     {
        drawGreg_TS(x - 6);
      }
      else if (x >= (fullScroll - 6))   {
        drawGreg_TS((fullScroll - x) - 6);
      }
      else                          { //Disp.drawRect(1,5,62,5);
        drawGreg_TS(0);
      }
      Disp.setFont(bmz6x7);
      Disp.drawText(DWidth - x, 8 , msg);
      lafadza();
      lafadzb();

    }
    else
    {
      Disp.setFont(bmz6x7);
      Disp.drawText(DWidth - x, 3, msg);
      lafadza();
      lafadzb();
    }
    DoSwap = true;
  }
}

void blinkBlock(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint16_t   lsRn;
  static uint16_t   ct, ct_l;
  uint16_t          Tmr = millis();

  if (jumat)       {
    ct_l = 1 * 60;
  }
  else            {
    ct_l = 3 * 60;
  }
  //    jumat =false;

  if ((Tmr - lsRn) > 1000)
  { lsRn = Tmr;

    if ((ct % 2) == 0)
    {

      Disp.drawFilledRect(DWidth - 3, DHeight - 3, DWidth - 2, DHeight - 2);
    }
    DoSwap = true;
    ct++;
  }
  if (ct > ct_l)
  { dwDone(DrawAdd);
    azzan = false;
    jumat = false;
    ct = 0;
  }
  Disp.drawText(1, 7, String(ct_l - ct));
}

// =========================================
// Drawing Tools============================
// =========================================
boolean dwDo(int DrawAdd)
{ if (RunSel == DrawAdd) {
    return true;
  }
  else return false;
}

void dwDone(int DrawAdd)
{ RunFinish = DrawAdd;
  RunSel = 0;
}

void dwCtr(int x, int y, const char* Msg)
{ int   tw = Disp.textWidth(Msg);
  int   th = Disp.textHeight();
  int   c = int((DWidth - x - tw) / 2);
  Disp.drawFilledRect(x + c - 1, y, x + tw + c, y + th, 0);
  Disp.drawText(x + c, y, Msg);
}

void Buzzer(uint8_t state)
{
  if (state == 1 and Prm.BZ == 1)
  { //tone(BUZZ, 500, 400);
    digitalWrite (BUZZ, HIGH);
    delay(50);
    digitalWrite (BUZZ, LOW);
  }
  else
  { //noTone(BUZZ);
    digitalWrite (BUZZ, LOW);
    delay(50);
  }
}

void fType(int x)
{
  if (x == 0) Disp.setFont(SystemFont5x7);
  else Disp.setFont(bmz4x6);
}
