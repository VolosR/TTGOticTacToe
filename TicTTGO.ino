#include <TFT_eSPI.h> 
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI(); 

 int fromTop=60;
 int fromLeft=10;
 int space=5;
 int boxSize=35 ;
 int playGround=3*boxSize+2*space;

 int i=0;
 int j=0;

 bool player=0;
 int dd[3][3]={0};
 char sign[2]={'x','o'};

void setup(void) {
  
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("TicTacTOe",5,12,4);
  pinMode(0,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);
  
  tft.drawFastVLine(fromLeft+boxSize+space/2,fromTop,playGround,TFT_WHITE);
   tft.drawFastVLine(1+fromLeft+boxSize+space/2,fromTop,playGround,TFT_WHITE);
  tft.drawFastVLine(fromLeft+boxSize*2+space+space/2,fromTop,playGround,TFT_WHITE);
  tft.drawFastVLine(1+fromLeft+boxSize*2+space+space/2,fromTop,playGround,TFT_WHITE);
  tft.drawFastHLine(fromLeft,fromTop+boxSize+space/2,playGround,TFT_WHITE);
   tft.drawFastHLine(fromLeft,1+fromTop+boxSize+space/2,playGround,TFT_WHITE);
  tft.drawFastHLine(fromLeft,fromTop+boxSize*2+space+space/2,playGround,TFT_WHITE);
  tft.drawFastHLine(fromLeft,1+fromTop+boxSize*2+space+space/2,playGround,TFT_WHITE);
  
  tft.drawRect((fromLeft+(i*boxSize)+(i*space)),(fromTop+(j*boxSize)+(j*space)),boxSize,boxSize,TFT_RED); 
 }

void loop() {

if(digitalRead(0)==0)
  {
  tft.drawRect((fromLeft+(i*boxSize)+(i*space)),(fromTop+(j*boxSize)+(j*space)),boxSize,boxSize,TFT_BLACK);  
  i=i+1;
  if(i>2)
      {
      i=0;
      j++;
      }
  if(j>2)
  j=0;
  tft.drawRect((fromLeft+(i*boxSize)+(i*space)),(fromTop+(j*boxSize)+(j*space)),boxSize,boxSize,TFT_RED);  
  delay(300);
  }

  if(digitalRead(35)==0)
  {
    tft.drawString(String(sign[player]),10+fromLeft+(i*boxSize)+(space*i),6+fromTop+(j*boxSize)+j*space,4);
    if(player==0)
    dd[i][j]=1;

     if(player==1)
     dd[i][j]=4;
    
    player=!player;
    checkWiner();
    delay(300);
    }

 }

 void checkWiner()
 {
  for(int m=0;m<3;m++)
  {
  int score=0;
  int hscore=0;
  for(int n=0;n<3;n++)
    {
    score=score+dd[m][n];
    hscore=hscore+dd[n][m];
    
    if(score==3 || score==12)
     {
      tft.drawFastVLine(fromLeft+(m*space)+(boxSize*m)+boxSize/2,fromTop,playGround,TFT_RED);
      tft.drawFastVLine(fromLeft+1+(m*space)+(boxSize*m)+boxSize/2,fromTop,playGround,TFT_RED);
     }

     if(hscore==3 || hscore==12)
     {
      tft.drawFastHLine(fromLeft,fromTop+(m*space)+(boxSize*m)+boxSize/2,playGround,TFT_RED);
      tft.drawFastHLine(fromLeft,fromTop+1+(m*space)+(boxSize*m)+boxSize/2,playGround,TFT_RED);
     }
    }

  if(dd[0][0]+dd[1][1]+dd[2][2]==3 || dd[0][0]+dd[2][2]+dd[1][1]==12 ){
  tft.drawLine(fromLeft,fromTop,fromLeft+playGround, fromTop+playGround,TFT_RED);
  
  }

  if(dd[0][2]+dd[1][1]+dd[2][0]==3 || dd[0][2]+dd[2][0]+dd[1][1]==12 )
  {
  tft.drawLine(fromLeft+playGround,fromTop,fromLeft, fromTop+playGround,TFT_RED);
 
  }

  }
 }
