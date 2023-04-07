#include <BleKeyboard.h>
BleKeyboard ble("Macro Pad", "Viverino1", 100);
int longPressTime = 300;

//RGB LED Decloration
int R = 27;
int G = 12;
int B = 13;

//Button Decloration
int BUTTON_1 = 15;
int BUTTON_2 = 19;
int BUTTON_3 = 23;
int BUTTON_4 = 18;

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  
  setCpuFrequencyMhz(80); 
  ble.begin();
  Serial.begin(9600);
}

bool bluetoothActive = false;
int oldInput = 0;
void loop() {
  int input = getInput();
  
  if(ble.isConnected()){
    if(!bluetoothActive){
      bluetoothActive = true;
    }

    if(input != 1111){
      if(input != oldInput){
        Serial.println("click");
        input = oldInput;
      }else{
        Serial.println("holding");
      }
    }
  }
}

int getInput(){
  int output;
  output = digitalRead(BUTTON_1) * 1000 + digitalRead(BUTTON_2) * 100 + digitalRead(BUTTON_3) * 10 + digitalRead(BUTTON_4);
  return output;
}

void handleInput(int input){
  switch(input){
    case 1111:
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
      
      break;
    case 1110:
      digitalWrite(R, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);

      ble.press(KEY_LEFT_GUI);
      ble.press(KEY_TAB);
      delay(100);
      ble.releaseAll();
      
      break;
    case 1101:
      digitalWrite(R, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(B, LOW);

      ble.press(KEY_LEFT_ALT);
      ble.press(KEY_TAB);
      delay(100);
      ble.releaseAll();
      
      break;
    case 1011:
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      break;
    case 111:
      digitalWrite(R, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
      break;
    default: break;
  }
}
