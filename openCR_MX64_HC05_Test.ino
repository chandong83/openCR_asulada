#include <Dynamixel.h>

//다이나믹셀 클래스
Dynamixel Dxl;

//다이나믹셀 ID
#define motor_left_ID  1
#define motor_right_ID 2

//다이나믹셀 레지스터
#define DXL_TORQUE 24
#define DXL_LED 25
#define DXL_GOAL_POSITION 30
#define DXL_MOVING_SPEED 32
#define DXL_PRESENT_POSOTION 36

//모터 속도
#define MOTOR_SPEED_LEFT  511//1023
#define MOTOR_SPEED_RIGHT 1535//2047

//토크 켜기
void EnableTorque()
{
  Dxl.writeByte(motor_left_ID, DXL_TORQUE, 1 );
  Dxl.writeByte(motor_right_ID, DXL_TORQUE, 1 );
  
  Dxl.writeByte(motor_left_ID, DXL_LED, 1 );
  Dxl.writeByte(motor_right_ID, DXL_LED, 1 );
}

//토그 끄기
void DisalbeTorque()
{
  Dxl.writeByte(motor_left_ID, DXL_TORQUE, 0 );
  Dxl.writeByte(motor_right_ID, DXL_TORQUE, 0);
  
  Dxl.writeByte(motor_left_ID, DXL_LED,0 );
  Dxl.writeByte(motor_right_ID, DXL_LED,0 );
}
// 앞으로
void Forward()
{
  Dxl.writeWord(motor_left_ID, DXL_MOVING_SPEED, MOTOR_SPEED_LEFT);  
  Dxl.writeWord(motor_right_ID, DXL_MOVING_SPEED, MOTOR_SPEED_RIGHT);
}

// 뒤로
void Backward()
{
  Dxl.writeWord(motor_left_ID, DXL_MOVING_SPEED, MOTOR_SPEED_RIGHT);
  Dxl.writeWord(motor_right_ID, DXL_MOVING_SPEED, MOTOR_SPEED_LEFT);
}

// 왼쪽으로 돌기
void turnLeft()
{
  Dxl.writeWord(motor_left_ID, DXL_MOVING_SPEED, MOTOR_SPEED_RIGHT);  
  Dxl.writeWord(motor_right_ID, DXL_MOVING_SPEED, MOTOR_SPEED_RIGHT);
}

// 오른쪽으로 돌기
void turnRight()
{
  Dxl.writeWord(motor_left_ID, DXL_MOVING_SPEED, MOTOR_SPEED_LEFT);
  Dxl.writeWord(motor_right_ID, DXL_MOVING_SPEED, MOTOR_SPEED_LEFT);
}

// 정지
void Stop()
{
  Dxl.writeWord(motor_left_ID, DXL_MOVING_SPEED, 0);
  Dxl.writeWord(motor_right_ID, DXL_MOVING_SPEED, 0);
}


void setup() {
  
  Serial.begin(115200);  //시리얼 모니터
  Serial2.begin(9600); //UART2 STM32F746 D5,D6

  Dxl.begin(4); //500Kbps
  
  EnableTorque();  
}

void loop() {  
   uint8_t ch;

  if( Serial.available() )
  {
   //시리얼 모니터로 토크 제어
    ch = Serial.read();
    if( ch == '1' ) 
    {
      EnableTorque();
    }
    else if( ch == '2' ) 
    {
      DisalbeTorque();
    }
  }
  
  if(Serial2.available() )
  {    
//HC-05 블루투스로 
    ch = Serial2.read();
    Serial.println(ch);
    if( ch == 'w' ) 
    {
      Forward();
    }
    else if( ch == 's' ) 
    {      
      Backward();
    }
    else if( ch == 'a' ) 
    {
      turnLeft();
    }
    else if( ch == 'd' ) 
    {
      turnRight();
    }
    else if( ch == '1' ) 
    {      
      Stop();
    }
  }
}
