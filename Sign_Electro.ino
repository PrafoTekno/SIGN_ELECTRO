boolean registers[8];
int count_rand_array[16][8]; //uda dihidupin ga?
boolean rand_array[16][8];
int DS_Pin = 0;
int STCP_Pin[] =  {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; //blum ganti, ada 16
int SHCP_Pin[] =  {17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void setup() 
{
  Serial.begin(9600);
  // perlu pinmode inoutput???
}
void loop()
{
  //mode jalan seri
  for(int i=0;i<16;i++) //hidupkan, i=SH kebrp
  {
    for(int j=0;j<9;j++) 
    {
      registers[j]=0; //reset 
    }
    for(int j=0;j<9;j++) //j= lampu kebrp
    {
      registers[j]=1;
      delay(200);
      writereg(i);
    }
  }
  delay(5000);
  //matikan 
  for(int i=0;i<16;i++)
  { 
    for(int j=0;j<9;j++) 
    {
      registers[j]=1; //reset
    }
    for(int j=0;j<9;j++) //j= lampu kebrp
    {
      registers[j]=0;
      delay(200);
      writereg(i);
    }
  }


  // mode lampu tua
  for(int i=0;i<641;i++) //klo sudah semua bru kluar loop
  {
    while(true)
    {
      int rand_row=random(0,16);
      int rand_col=random(0,8);
      if(count_rand_array[rand_row][rand_col]<5)
      {
        rand_array[rand_row][rand_col]=!rand_array[rand_row][rand_col];
        for(int j=0;j<9;j++) //j= lampu kebrp
        {
          registers[j]=rand_array[rand_row][j]; 
        }
        writereg(rand_row);
        delay(200);
        break;
      }
    }
  }
  delay(5000);
  //matikan
  for(int j=0;j<9;j++) 
  {
    registers[j]=0;
  }
  for(int i=0;i<16;i++)
  {
    writereg(i);
  }


  // mode kelap-kelip
  for(int j=0;j<9;j++)  // on
  {
    registers[j]=1;
  }
  for(int i=0;i<16;i++)
  {
    writereg(i);
  }
  delay(1000);
  for(int j=0;j<9;j++) //off
  {
    registers[j]=0;
  }
  for(int i=0;i<16;i++)
  {
    writereg(i);
  }

}


void writereg(int x) //x=SH kebrp
{ 
  digitalWrite(SHCP_Pin[x],LOW);
  for(int i=7;i>=0;i--)
  {
    digitalWrite(STCP_Pin[x],LOW);
    digitalWrite(DS_Pin,registers[i]);
    digitalWrite(STCP_Pin[x],HIGH);
  }
  digitalWrite(SHCP_Pin[x],HIGH);
}
