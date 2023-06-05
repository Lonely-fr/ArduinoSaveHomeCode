#include <Keypad.h>
const int buzzerPin = 10;              // Пин пьезодинамика
const int redLEDpin = 2;               // Пин красного диода
const int blueLEDpin = 3;              // Пин синего диода
const int yellowLEDpin = 4;            // Пин желтого диода
const int inputPin1 = 5;               // Пин входных данных 1
const int inputPin2 = 6;               // Пин входных данных 2
const int inputPin3 = 7;               // Пин входных данных 3
const int externalStatePin = 8;        // Пин состояния внешней платы
const int alarmStatePin1 = 9;          // Пин состояния тревоги 1
const int alarmStatePin2 = 11;         // Пин состояния тревоги 2
const int button1Pin = 12;             // Пин кнопки 1
const int button2Pin = 13;             // Пин кнопки 2
const int yellowSilentPin = 52;        // Пин диода "Тихий режим"

bool led12State = false;               // Состояние LED "Пожарные датчики"
bool led13State = false;               // Состояние LED "СКУД"
bool silentMode = false;               // Флаг режима "Тихий"

const byte ROWS = 4;                   // Количество строк клавиатуры
const byte COLS = 4;                   // Количество столбцов клавиатуры
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};  // Пины строк клавиатуры
byte colPins[COLS] = {A4, A5, A6, A7};  // Пины столбцов клавиатуры
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);  // Объект Keypad

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDpin, OUTPUT);
  pinMode(blueLEDpin, OUTPUT);
  pinMode(yellowLEDpin, OUTPUT);
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  pinMode(externalStatePin, OUTPUT);
  pinMode(alarmStatePin1, OUTPUT);
  pinMode(alarmStatePin2, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(yellowSilentPin, OUTPUT);
}

void loop() {
  digitalWrite(redLEDpin, led12State);      // Устанавливаем состояние LED "Пожарные датчики"
  digitalWrite(blueLEDpin, led13State);     // Устанавливаем состояние LED "СКУД"
  
  // Обработка кнопки 1
  if (digitalRead(button1Pin) == LOW) {
    led12State = !led12State;               // Инвертируем состояние LED "Пожарные датчики"
  }
  
  // Обработка кнопки 2
  if (digitalRead(button2Pin) == LOW) {
    led13State = !led13State;               // Инвертируем состояние LED "СКУД"
  }

  // Обработка входных данных
  int inputState1 = digitalRead(inputPin1);
  int inputState2 = digitalRead(inputPin2);
  int inputState3 = digitalRead(inputPin3);
  
  // Управление состоянием внешней платы
  digitalWrite(externalStatePin, inputState1);

  // Управление состоянием тревоги 1
  digitalWrite(alarmStatePin1, inputState2);

  // Управление состоянием тревоги 2
  digitalWrite(alarmStatePin2, inputState3);
  
  // Обработка Keypad
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key == 'A') {
      silentMode = !silentMode;             // Инвертируем состояние режима "Тихий"
      digitalWrite(yellowSilentPin, silentMode ? HIGH : LOW); // Устанавливаем состояние диода "Тихий режим"
    }
    // Ваш код для обработки нажатия клавиши Keypad
    // Можете добавить логику ввода пароля и перехода в режим "Тихий"
  }
  
  // Другой код и логика программы
}
