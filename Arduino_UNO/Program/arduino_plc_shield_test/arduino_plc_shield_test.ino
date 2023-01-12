/*
  OpenPLC Arduino UNO Test Brnch Board Test Program.

  Document and source code.
  https://github.com/kaz19610303/OpenPLC
  
  modified 31 Nov 2022
  by Kazuaki Ueno
  NExt Step LLC
  https://nest-step.asia/

  This example code is in the public domain.
*/

// 入出力ピン 設定
#define OUT_0 7
#define OUT_1 8
#define OUT_2 12
#define OUT_3 13

#define INPUT_0 2
#define INPUT_1 3
#define INPUT_2 4
#define INPUT_3 5
#define INPUT_4 6

#define ANALOG_OUT_0 9
#define ANALOG_OUT_1 10
#define ANALOG_OUT_2 11

#define ANALOG_INPUT_0 A0
#define ANALOG_INPUT_1 A1
#define ANALOG_INPUT_2 A2
#define ANALOG_INPUT_3 A3
#define ANALOG_INPUT_4 A4
#define ANALOG_INPUT_5 A5

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  
  // initialize pin to input or output.
  pinMode(OUT_0, OUTPUT);
  pinMode(OUT_1, OUTPUT);
  pinMode(OUT_2, OUTPUT);
  pinMode(OUT_3, OUTPUT);

  pinMode(ANALOG_OUT_0, OUTPUT);
  pinMode(ANALOG_OUT_1, OUTPUT);
  pinMode(ANALOG_OUT_2, OUTPUT);

  pinMode(INPUT_0, INPUT);
  pinMode(INPUT_1, INPUT);
  pinMode(INPUT_2, INPUT);
  pinMode(INPUT_3, INPUT);
  pinMode(INPUT_4, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  uint16_t analog_value_0;
  uint16_t analog_value_1;
  uint16_t analog_value_2;
  uint16_t analog_value_3;
  uint16_t analog_value_4;
  uint16_t analog_value_5;

  uint8_t analog_out_value_0;
  uint8_t analog_out_value_1;
  uint8_t analog_out_value_2;

  uint8_t input_value_0;
  uint8_t input_value_1;
  uint8_t input_value_2;
  uint8_t input_value_3;
  uint8_t input_value_4;

  uint8_t output_value_0;
  uint8_t output_value_1;
  uint8_t output_value_2;
  uint8_t output_value_3;

  uint8_t InputValue_hex ;

  // Analog input
  analog_value_0 = analogRead(ANALOG_INPUT_0);
  analog_value_1 = analogRead(ANALOG_INPUT_1);
  analog_value_2 = analogRead(ANALOG_INPUT_2);
  analog_value_3 = analogRead(ANALOG_INPUT_3);
  analog_value_4 = analogRead(ANALOG_INPUT_4);
  analog_value_5 = analogRead(ANALOG_INPUT_5);

  // Digital input
  input_value_0 = digitalRead(INPUT_0);
  input_value_1 = digitalRead(INPUT_1);
  input_value_2 = digitalRead(INPUT_2);
  input_value_3 = digitalRead(INPUT_3);
  input_value_4 = digitalRead(INPUT_4);

  // Digital output data set
  output_value_0 = input_value_0 ;
  output_value_1 = input_value_1 ;
  output_value_2 = input_value_2 ;
  output_value_3 = input_value_3 || input_value_4;

  // Analog output data set
  analog_out_value_0 =  map(analog_value_0 + analog_value_3, 0, 1023*2, 0, 255);
  analog_out_value_1 =  map(analog_value_1 + analog_value_4, 0, 1023*2, 0, 255);
  analog_out_value_2 =  map(analog_value_2 + analog_value_5, 0, 1023*2, 0, 255);

  // Analog data write
  analogWrite(ANALOG_OUT_0, analog_out_value_0);
  analogWrite(ANALOG_OUT_1, analog_out_value_1);
  analogWrite(ANALOG_OUT_2, analog_out_value_2);

  // Digital data write
  digitalWrite(OUT_0,output_value_0);
  digitalWrite(OUT_1,output_value_1);
  digitalWrite(OUT_2,output_value_2);
  digitalWrite(OUT_3,output_value_3);

  // Digital output data to HEX
  InputValue_hex = 0;
  InputValue_hex |= input_value_4 << 4 ;
  InputValue_hex |= input_value_3 << 3 ;
  InputValue_hex |= input_value_2 << 2 ;
  InputValue_hex |= input_value_1 << 1 ;
  InputValue_hex |= input_value_0 ;
  
  Serial.print("Degital Input (hex): ");
  Serial.println(InputValue_hex,HEX);
  Serial.println("");
  
  Serial.print("Analog input 0 : ");
  Serial.println(analog_value_0);
  Serial.print("Analog input 1 : ");
  Serial.println(analog_value_1);
  Serial.print("Analog input 2 : ");
  Serial.println(analog_value_2);
  Serial.print("Analog input 3 : ");
  Serial.println(analog_value_3);
  Serial.print("Analog input 4 : ");
  Serial.println(analog_value_4);
  Serial.print("Analog input 5 : ");
  Serial.println(analog_value_5);
  Serial.println("");

  // 0.5sec deleay
  delay(500);
}
