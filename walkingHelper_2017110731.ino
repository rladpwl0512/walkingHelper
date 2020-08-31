/*
 * 시각장애인 보행보조기기 (2017110731 김예지)
 */

const int TRIGGER = 9; //9번핀을 사용하는 초음파 센서의 TRIGGER 상수 정의
const int ECHO = 8;    //8번핀을 사용하는 초음파 센서의 ECHO 상수 정의
const int BUZZER = 7;  //7번핀을 사용하는 부저의 BUZZER 상수 정의 
const int RED1 = 11;   //11번 핀을 사용하는 RED1 상수 정의(PWM핀과 연결함으로써, 나중 analogWrite를 할 수 있음) 
const int RED2 = 10;   //10번 핀을 사용하는 RED2 상수 정의(PWM핀과 연결함으로써, 나중 analogWrite를 할 수 있음)
const int RED3 = 6;    //6번 핀을 사용하는 RED3 상수 정의(PWM핀과 연결함으로써, 나중 analogWrite를 할 수 있음)
const int LIGHT = 0;   //아날로그 입력 0번핀을 사용하는 조도센서 LIGHT 상수 정의

void setup() {
  Serial.begin(9600); //9600 속도로 시리얼 통신 시작 
  
  pinMode(TRIGGER, OUTPUT); //초음파가 나감 
  pinMode(ECHO, INPUT);     //어느 물체에 닿았다가 돌아오는 초음파를 받아서 반응
  pinMode(BUZZER, OUTPUT);  //HIGH: 소리가 남, LOW: 소리가 안남

}

void loop() {
  float distance; //시간을 거리로 환산한 값 저장
  unsigned long duration; //pulseIn 이용->초음파가 어떤 물체에 닿았다 돌아오는 시간 저장

  digitalWrite(TRIGGER, HIGH); //초음파를 TRIGGER을 통해 보냄
  delay(10);
  digitalWrite(TRIGGER, LOW); //초음파 신호를 한번 보낸 후 그만 보냄 

  duration = pulseIn(ECHO, HIGH); //물체에 튕겨 돌아오는 시간을 ECHO에서 받음(돌아올 때 HIGH에서 LOW) -> duration 변수에서 HIGH유지 시간 저장
  
  //거리 = 속력 x 시간 (초음파의 속력은 일상생활에서 보통 340m/s이기 때문에, 여기서도 340m/s로 계산)
  //10000을 나눔으로써 cm로 단위 환산 가능 
  //2를 나누는 이유는 초음파가 물체에 갔다가, 물체에서 튕겨 돌아오는 시간 -> 왕복한 값을 반으로 나눠줌 
  distance = ((340 * duration) / 10000) / 2; 
  
  Serial.println(distance); //distance를 시리얼 모니터에 출력 
  delay(300);

  //부저 울리는 코드 
  if(distance <= 80){ //거리값이 80cm 이하면 부저 울림 
    digitalWrite(BUZZER, HIGH); 
  }
  else{
    digitalWrite(BUZZER, LOW); 
  }

  int sensorValue; //밝기 값 변수에 담기 
  sensorValue = analogRead(LIGHT); //조도센서로부터 밝기를 읽어옴

  Serial.print("밝기 : ");      //밝기 출력
  Serial.println(sensorValue); //조도센서는 풀다운으로 구성(밝아질수록 큰값 출력)
  delay(1000);                 //변화하는 센서값 볼 수 있도록 딜레이를 줌 

  //빛의 양에 따라 LED 개수 다르게 출력
  //어두울수록 더 적은 수의 LED를 출력함(어두울 때는 작은 수의 LED만으로도 보임-피드백 반영) 
 
  if(sensorValue > 700) //밝을수록 더 많은 수의 LED 출력(밝을 때는 주위에 조명 많기 때문에 LED 잘 안보이기 때문) 
  {
    analogWrite(RED1, 255);
    analogWrite(RED2, 255);
    analogWrite(RED3, 255);
  }
  else if(sensorValue > 500) 
  {
    analogWrite(RED1, 255);
    analogWrite(RED2, 255);
    analogWrite(RED3, 0);
  }
  else //어두울수록 더 적은 수의 LED를 출력함(어두울 때는 적은 수의 LED만으로도 보임)
  {
    analogWrite(RED1, 255);
    analogWrite(RED2, 0);
    analogWrite(RED3, 0);
  }
 

}
