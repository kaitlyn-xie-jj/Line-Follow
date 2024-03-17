#include "facefuture.h" // 包含头文件
// 常量定义
const int FINISH_TIME = 10000; //巡线时间
const int LINE_SPEEDMAX = 195;//巡线速度上限 145//195
const int KP_DEFAULT = 245;//226//243
const int KD_DEFAULT = 1382;//1185//1380
const int KP_SPEED = 1.8;//变速比例

int START_TIME;
int ERROR_SPEED;
int LINE_SPEED;
const int LEFT_MOTOR = 1;
const int RIGHT_MOTOR = 1;
const int MOTOR_SPEED_RANGE = 510;

const int ledChannel = 5;     // 使用 0 号 LED PWM 通道
const int freq = 50;          // 频率 50 Hz
const int resolution = 12;    // 16 位分辨率
const int gpioPin = 11;       // GPIO 20 端口
int minDuty = (1000 * pow(2, resolution)) / 20000; // 计算 1000 微秒对应的占空比
int maxDuty = (2000 * pow(2, resolution)) / 20000; // 计算 2000 微秒对应的占空比
int medDuty = (1500 * pow(2, resolution)) / 20000;
int tryDuty = (1660 * pow(2, resolution)) / 20000;
void setup()

{
    Set_MotorsDir(LEFT_MOTOR, LEFT_MOTOR, RIGHT_MOTOR, RIGHT_MOTOR, 1); 
    Serial.begin(115200);
    InitButton();
    InitMotor();
    InitGreyscale();
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(gpioPin, ledChannel);
    ledcWrite(ledChannel, medDuty);
    delay(500);
    ledcWrite(ledChannel, maxDuty);
    delay(500);
    ledcWrite(ledChannel, minDuty);
    delay(500);
}

void loop()
{
    START_TIME = 0;
    /////////////////////测光值/////////////////////////////////////
    if (GetButton(1))
    {    
     GreycaleCalibration(); //测值
     
      /*while (1) {
      
      Serial.println(WSR_GetLinePosiotion());
      //ledcWrite(ledChannel, maxDuty);//涵道启动
      }*/
    
     //传感器平滑读数
     /*while(1){
        for(int i = 0;i<14;i++)
        {
          Serial.print(GetGreyscalevalue(i));
          Serial.print(" ");
        }
        Serial.println(WSR_GetLinePosiotion());
        Serial.println("");
        delay(100);
      }*/
      
    }
    ///////////////////////////////////////////////////////////////



    /////////////////////慢速///////////////////////////////////////
    if (GetButton(2))
    {
      /*START_TIME = millis();
      SetLinefollow_PD(KP_DEFAULT,KD_DEFAULT);
      while(millis() - START_TIME < FINISH_TIME)
      {
        LineFollow(120);//速度 100-150
      }
      while (true){MotorRun(0, 0);}*/
      
    }
    ///////////////////////////////////////////////////////////////



     /////////////////////高变速/////////////////////////////////////
    if (GetButton(3))
    {  
      ledcWrite(ledChannel, tryDuty);
      delay(500);
      int SPEED_HIGHLAND = 0;
      SetLinefollow_PD(KP_DEFAULT,KD_DEFAULT);
      START_TIME = millis();
      while(millis() - START_TIME < FINISH_TIME)
      {
        ERROR_SPEED = abs(WSR_GetLinePosiotion()) * KP_SPEED;
        LINE_SPEED = LINE_SPEEDMAX - ERROR_SPEED;
        if(LINE_SPEED < 147){LINE_SPEED = 147;} //126                  //巡线速度下限//147
        if(LINE_SPEED > 168){SPEED_HIGHLAND = SPEED_HIGHLAND++;}  //变速准备速度//168
        if(SPEED_HIGHLAND > 25){SPEED_HIGHLAND = 0;}              //最快速度持续时间
        LINE_SPEED = LINE_SPEED - (SPEED_HIGHLAND * 2.5);
        LineFollow(LINE_SPEED);
      }
      while (true){MotorRun(0, 0);ledcWrite(ledChannel, minDuty);}
    
    }
    ///////////////////////////////////////////////////////////////
    ////////////////////////////END////////////////////////////////
}
