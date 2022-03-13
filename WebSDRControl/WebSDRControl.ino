#define R1_CLK  4
#define R1_DT   3
#define R1_SW   2

#define R2_CLK  8
#define R2_DT   7
#define R2_SW   6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Tuning
  pinMode(R1_SW,INPUT_PULLUP);
  pinMode(R1_DT,INPUT_PULLUP);
  pinMode(R1_CLK,INPUT_PULLUP);

  // Filter bw
  pinMode(R2_SW,INPUT_PULLUP);
  pinMode(R2_DT,INPUT_PULLUP);
  pinMode(R2_CLK,INPUT_PULLUP);
  
}

//******* TUNING ENCODER ********

unsigned char R1_flag;
unsigned char R1_Last_RoB_Status;
unsigned char R1_Current_RoB_Status;


void rotary1Deal(void)
{
  R1_Last_RoB_Status = digitalRead(R1_CLK);

  while(!digitalRead(R1_DT)){
    R1_Current_RoB_Status = digitalRead(R1_CLK);
    R1_flag = 1;
  }

  if(R1_flag == 1){
    R1_flag = 0;
    if((R1_Last_RoB_Status == 0)&&(R1_Current_RoB_Status == 1)){
       Serial.println("+");
    }
    if((R1_Last_RoB_Status == 1)&&(R1_Current_RoB_Status == 0)){
       Serial.println("-");
    }

  }
}


//******* FILTER BW ENCODER ********

unsigned char R2_flag;
unsigned char R2_Last_RoB_Status;
unsigned char R2_Current_RoB_Status;


void rotary2Deal(void)
{
  R2_Last_RoB_Status = digitalRead(R2_CLK);

  while(!digitalRead(R2_DT)){
    R2_Current_RoB_Status = digitalRead(R2_CLK);
    R2_flag = 1;
  }

  if(R2_flag == 1){
    R2_flag = 0;
    if((R2_Last_RoB_Status == 0)&&(R2_Current_RoB_Status == 1)){
       Serial.println("W");
    }
    if((R2_Last_RoB_Status == 1)&&(R2_Current_RoB_Status == 0)){
       Serial.println("w");
    }

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  rotary1Deal();
  rotary2Deal();
  // add handling for demodulation mode, ....
  delay(2);
}
