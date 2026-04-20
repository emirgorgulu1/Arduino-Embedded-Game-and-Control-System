#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- 16x16 fitilli bomba ikonu ---
const unsigned char PROGMEM bombBitmap16[] = {
  0x00, 0x06, 0x00, 0x0F,
  0x00, 0x06, 0x01, 0xFC,
  0x03, 0xFE, 0x07, 0xFF,
  0x0F, 0xFF, 0x0F, 0xFF,
  0x0F, 0xFF, 0x07, 0xFF,
  0x03, 0xFE, 0x01, 0xFC,
  0x00, 0xF8, 0x00, 0x20,
  0x00, 0x00, 0x00, 0x00
};

// --- 8x8 müzik nota ikonu ---
const unsigned char PROGMEM musicNoteBitmap[] = {
  0x18, 0x1C, 0x1E, 0x1B,
  0x18, 0x18, 0x18, 0x18
};

// --- T-REX (16x12) bitmap ---
const unsigned char PROGMEM trexBitmap[] = {
  0x01, 0xE0,
  0x01, 0xF0,
  0x01, 0xF8,
  0x01, 0x98,
  0x01, 0xF8,
  0x01, 0xF0,
  0x01, 0xF0,
  0x01, 0xE0,
  0x01, 0xA0,
  0x01, 0xA0,
  0x01, 0x20,
  0x01, 0x00
};

// --- KAKTÜS (8x12) bitmap ---
const unsigned char PROGMEM cactusBitmap[] = {
  0x10,
  0x10,
  0x38,
  0x38,
  0x7C,
  0x7C,
  0x7C,
  0x38,
  0x38,
  0x38,
  0x38,
  0x38
};

// --- TÜRK BAYRAĞI (64 x 32 px) (şimdilik kullanılmıyor ama dursun) ---
const unsigned char PROGMEM turkishFlag64x32[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,
  0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,
  0x80,0xFF,0xFF,0x00,0x00,0xFE,0xFF,0x01,
  0xC0,0xFF,0x1F,0x00,0x00,0xF8,0xFF,0x03,
  0xE0,0xFF,0x07,0x00,0x00,0xE0,0xFF,0x07,
  0xF0,0xFF,0x03,0x00,0x00,0xC0,0xFF,0x0F,
  0xF8,0x7F,0x03,0x00,0x00,0xC0,0xFE,0x1F,
  0xF8,0x3F,0x07,0x00,0x00,0xE0,0xFC,0x1F,
  0xFC,0x9F,0x06,0x00,0x00,0x60,0xF9,0x3F,
  0xFC,0xCF,0x0E,0x00,0x00,0x70,0xF3,0x3F,
  0xFE,0xE7,0x0C,0x3F,0x3F,0x30,0xE7,0x7F,
  0xFE,0xF3,0x1C,0x7F,0x7F,0x38,0xCF,0x7F,
  0xFE,0xF9,0x98,0xFF,0xFF,0x19,0x9F,0x7F,
  0xFF,0xFC,0x98,0xFF,0xFF,0x19,0x3F,0xFF,
  0xFF,0xFC,0x98,0xFF,0xFF,0x19,0x3F,0xFF,
  0xFF,0xFE,0x98,0xFF,0xFF,0x19,0x7F,0xFF,
  0xFF,0xFE,0x9C,0x7F,0x7F,0x39,0x7F,0xFF,
  0xFE,0xF3,0x8C,0x3F,0x3F,0x31,0xCF,0x7F,
  0xFE,0xE7,0xCC,0x00,0x00,0x33,0xE7,0x7F,
  0xFC,0xCF,0xEC,0x00,0x00,0x37,0xF3,0x3F,
  0xFC,0x9F,0x6E,0x00,0x00,0x36,0xF9,0x3F,
  0xF8,0x3F,0x67,0x00,0x00,0x66,0xFC,0x1F,
  0xF8,0x7F,0x63,0x00,0x00,0xC6,0xFE,0x1F,
  0xF0,0xFF,0x71,0x00,0x00,0x8E,0xFF,0x0F,
  0xE0,0xFF,0x38,0x00,0x00,0x1C,0xFF,0x07,
  0xC0,0xFF,0x1C,0x00,0x00,0x38,0xFF,0x03,
  0x80,0xFF,0x8F,0x00,0x00,0xF1,0xFF,0x01,
  0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,
  0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

// --- SENİN FOTON ('abc', 69x68px) ---
const unsigned char My_bitmapabc[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xf8, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xf0, 0x03,
  0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe,
  0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0xff,
  0xff, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xff,
  0xf8, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03,
  0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x07,
  0xfc, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff,
  0xe1, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xe1, 0xff, 0xff, 0x93, 0xff, 0xff, 0xf8,
  0xff, 0xff, 0xe3, 0xff, 0xff, 0x41, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xf1, 0xff,
  0xff, 0xf8, 0xff, 0xff, 0xf2, 0x3f, 0xfe, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf3, 0xff, 0xff,
  0xc3, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf2, 0x0f, 0xf0, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf4,
  0x01, 0xc0, 0x0b, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf4, 0x01, 0xc0, 0x03, 0xff, 0xff, 0xf8, 0xff,
  0xff, 0xf6, 0x00, 0xc0, 0x0b, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf4, 0x00, 0xc0, 0x03, 0xff, 0xff,
  0xf8, 0xff, 0xff, 0x84, 0x01, 0xc0, 0x02, 0x7f, 0xff, 0xf8, 0xff, 0xff, 0x8d, 0x1f, 0xcf, 0xfa,
  0x7f, 0xff, 0xf8, 0xff, 0xff, 0xe7, 0xfe, 0xcf, 0xf1, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xc7, 0xff,
  0xcf, 0xe0, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xc7, 0xfb, 0xef, 0xf0, 0xff, 0xff, 0xf8, 0xff, 0xff,
  0xe3, 0xf8, 0x87, 0xe0, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xe7, 0xf8, 0x07, 0xe1, 0xff, 0xff, 0xf8,
  0xff, 0xff, 0xf3, 0xff, 0x9f, 0xa1, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xc7, 0xff,
  0xff, 0xf8, 0xff, 0xff, 0xfd, 0xfe, 0xc3, 0xc7, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfc, 0xf0, 0x01,
  0x8f, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfc, 0x70, 0x01, 0x0f, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe,
  0xfe, 0x0f, 0x07, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe, 0x3f, 0x1c, 0x03, 0xff, 0xff, 0xf8, 0xff,
  0xff, 0xf8, 0x1f, 0xf8, 0x01, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf8, 0x0f, 0xfc, 0x01, 0xff, 0xff,
  0xf8, 0xff, 0xff, 0xf0, 0x03, 0xf0, 0x01, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 0xc0, 0x00,
  0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00,
  0x00, 0x00, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x04, 0xff, 0xff, 0xf8, 0xff, 0xff,
  0xf0, 0x00, 0x00, 0x04, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x00, 0x01, 0xc4, 0xff, 0xff, 0xf8,
  0xff, 0xff, 0xe0, 0x10, 0x01, 0xa8, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xe0, 0x38, 0x03, 0xb0, 0xff,
  0xff, 0xf8, 0xff, 0xff, 0xe0, 0x1e, 0x0e, 0xe0, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xe0, 0x1e, 0x07,
  0x80, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x0f, 0x0f, 0x01, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0,
  0x07, 0xfc, 0x01, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf0, 0x01, 0xc0, 0x01, 0xff, 0xff, 0xf8, 0xff,
  0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff,
  0xf8, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xf9, 0xfc, 0x00, 0x00, 0x03,
  0xff, 0xff, 0xf8, 0xff, 0xfe, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0x3c, 0x00,
  0x00, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 0x9e, 0x00, 0x00, 0x07, 0xbf, 0xff, 0xf8, 0xff, 0xff,
  0xce, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0x7f, 0xff, 0xf8,
  0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x06, 0xff,
  0xff, 0xf8, 0xff, 0xff, 0xff, 0x00, 0x00, 0x06, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x07, 0xff, 0xff, 0xd8
};

// PINLER
const int buttonEnterPin = 2;   // Yeşil - ENTER
const int buttonNextPin  = 3;   // Siyah - İLERİ
const int buttonBackPin  = 4;   // Sarı  - GERİ
const int buttonEscPin   = 5;   // Kırmızı - ESC

const int buzzerPin  = 6;       // patlama / bip
const int speakerPin = 9;       // hoparlör (melodiler)

const int relay1Pin = 12;
const int relay2Pin = 11;

// Röleler
const int RELAY_ON  = HIGH;
const int RELAY_OFF = LOW;

// DURUMLAR
enum State {
  STATE_SPLASH,
  STATE_MAIN_MENU,
  STATE_MELODY_MENU,
  STATE_BOMB_SET_TIME,
  STATE_BOMB_COUNTDOWN,
  STATE_BOMB_FINISHED,
  STATE_GAME_MENU,
  STATE_GAME_DINO_INTRO,
  STATE_GAME_DINO,
  STATE_GAME_TIKTAK_INTRO,
  STATE_GAME_TIKTAK,
  STATE_SETTINGS
};

State currentState = STATE_SPLASH;

// sayaclar
unsigned long lastSecondMillis  = 0;
unsigned long lastWiggleMillis  = 0;
bool wiggleState = false;

// menu indexleri
int mainMenuIndex  = 0; // 0: Melodi, 1: Bomba, 2: Oyunlar, 3: Ayarlar
int melodyIndex    = 0; // 0,1,2
int gameMenuIndex  = 0; // 0: Dino, 1: Tik Tak

// bomba sureleri
int selectedSeconds  = 3;
int remainingSeconds = 0;

// --- Ses seviyesi --- (sadece BUZZER)
int volumeLevel = 5;

// --- DINO GAME DEGISKENLERI ---
const int DINO_GROUND_Y   = 50;
const int DINO_WIDTH      = 16;
const int DINO_HEIGHT     = 12;
const int DINO_X          = 12;
float dinoY               = DINO_GROUND_Y - DINO_HEIGHT;
float dinoVy              = 0;
bool  dinoOnGround        = true;

// Kaktus
const int CACTUS_WIDTH    = 8;
const int CACTUS_HEIGHT   = 12;
float obstacleXf          = SCREEN_WIDTH;
int   obstacleX           = SCREEN_WIDTH;
const int OBSTACLE_Y      = DINO_GROUND_Y - CACTUS_HEIGHT;

// Hiz artisi icin
float obstacleSpeed       = 3.0;
const float OBSTACLE_SPEED_MIN = 3.0;
const float OBSTACLE_SPEED_MAX = 7.0;

bool gameOver             = false;
unsigned long gameScore   = 0;
unsigned long lastGameFrameMillis = 0;
const int GAME_FRAME_MS   = 20;

// --- TIK TAK OYUN DEGISKENLERI ---
const int PADDLE_WIDTH  = 22;
const int PADDLE_HEIGHT = 3;
const int PADDLE_Y      = 54;
int paddleX             = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;

float ballX, ballY;
float ballVx, ballVy;
bool  tikGameOver       = false;
unsigned long tikScore  = 0;
unsigned long lastTikFrameMillis = 0;
const int TIK_FRAME_MS  = 20;

// --- MELODILER ---

// CENDERE (melody1) AYNI
const int PROGMEM melody1Notes[] = {
  294, 294, 294,
  330, 330, 330,
  349, 349, 349,
  330, 330, 330,
  294, 294, 294,
  330, 330, 330,
  262, 262, 262,
  294
};
const int PROGMEM melody1Dur[] = {
  220, 220, 220,
  220, 220, 220,
  220, 220, 220,
  220, 220, 220,
  220, 220, 220,
  220, 220, 220,
  220, 220, 220,
  400
};
const uint8_t melody1Len = sizeof(melody1Notes) / sizeof(melody1Notes[0]);

// *** KUM GİBİ – YENİ VERSİYON: Notalar yukarı-aşağı dalga gibi ***
const int PROGMEM melody2Notes[] = {
  294, 330, 349, 392, 440, 392, 349, 330,
  294, 330, 349, 392, 392, 349, 330, 294,
  262, 294, 330, 349, 392, 349, 330, 294,
  294, 330, 349, 392, 440, 392, 349, 330
};
const int PROGMEM melody2Dur[] = {
  200, 200, 200, 250, 350, 250, 200, 300,
  200, 200, 200, 250, 250, 200, 200, 350,
  200, 200, 200, 250, 350, 250, 200, 350,
  200, 200, 200, 250, 350, 250, 200, 500
};
const uint8_t melody2Len = sizeof(melody2Notes) / sizeof(melody2Notes[0]);

// Caddelerde Rüzgar (melody3) AYNI
const int PROGMEM melody3Notes[] = {
  330,330,330,330,349,330,
  330,330,330,440,330,
  294,294,294,294,330,294,
  262,262,262,262,294,262,
  494,494,494,494,262,494,
  294,294,294,294,440,330
};
const int PROGMEM melody3Dur[] = {
  200,200,200,200,200,300,
  200,200,200,200,400,
  200,200,200,200,200,300,
  200,200,200,200,200,300,
  200,200,200,200,200,300,
  200,200,200,200,200,400
};
const uint8_t melody3Len = sizeof(melody3Notes) / sizeof(melody3Notes[0]);

const char* const melodyNames[] = {
  "Cendere",
  "Kum Gibi",
  "Caddelerde Ruzgar"
};

// buton gecmisi
bool lastEnterState = false;
bool lastNextState  = false;
bool lastBackState  = false;
bool lastEscState   = false;

// ileri deklarasyonlar
void showSplashScreen();
void showMainMenu();
void showMelodyMenu();
void drawMelodyScreen(bool playing, bool wiggle);
void showBombSetTimeScreen();
void showBombCountdownScreen();
void showBombFinishedScreen();
void showSettingsScreen();
void showGameMenu();
void showDinoIntroScreen();
void showTikTakIntroScreen();

void playMelody(int index);
void beepDouble();
void beepLong();
void playGameOverMelodyBuzzer();

void startDinoGame();
void updateDinoGame(bool enterPressed, bool escPressed);
void drawDinoGame();

void startTikTakGame();
void updateTikTakGame(bool enterPressed, bool escPressed, bool nextHeld, bool backHeld);
void drawTikTakGame();

void speakerMute(bool mute);
void playSliceWithVolume(int freq, int sliceMs);

void setup() {
  pinMode(buttonEnterPin, INPUT);
  pinMode(buttonNextPin,  INPUT);
  pinMode(buttonBackPin,  INPUT);
  pinMode(buttonEscPin,   INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  digitalWrite(relay1Pin, RELAY_OFF);
  digitalWrite(relay2Pin, RELAY_OFF);
  digitalWrite(buzzerPin, LOW);

  speakerMute(true);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {}
  }

  display.setRotation(2);

  randomSeed(analogRead(A0));
  showSplashScreen();
  currentState = STATE_SPLASH;
}

void loop() {
  bool enterNow = digitalRead(buttonEnterPin);
  bool nextNow  = digitalRead(buttonNextPin);
  bool backNow  = digitalRead(buttonBackPin);
  bool escNow   = digitalRead(buttonEscPin);

  bool enterPressed = enterNow && !lastEnterState;
  bool nextPressed  = nextNow  && !lastNextState;
  bool backPressed  = backNow  && !lastBackState;
  bool escPressed   = escNow   && !lastEscState;

  if (currentState == STATE_SPLASH) {
    if (enterPressed) {
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    }
  }
  else if (currentState == STATE_MAIN_MENU) {
    if (nextPressed) {
      mainMenuIndex = (mainMenuIndex + 1) % 4;
      showMainMenu();
    }
    if (backPressed) {
      mainMenuIndex = (mainMenuIndex + 3) % 4;
      showMainMenu();
    }
    if (enterPressed) {
      if (mainMenuIndex == 0) {
        currentState = STATE_MELODY_MENU;
        showMelodyMenu();
      } else if (mainMenuIndex == 1) {
        currentState = STATE_BOMB_SET_TIME;
        selectedSeconds = 3;
        showBombSetTimeScreen();
      } else if (mainMenuIndex == 2) {
        currentState = STATE_GAME_MENU;
        gameMenuIndex = 0;
        showGameMenu();
      } else {
        currentState = STATE_SETTINGS;
        showSettingsScreen();
      }
    }
    if (escPressed) {
      showSplashScreen();
      currentState = STATE_SPLASH;
    }
  }
  else if (currentState == STATE_GAME_MENU) {
    if (nextPressed || backPressed) {
      gameMenuIndex = (gameMenuIndex + 1) % 2;
      showGameMenu();
    }
    if (enterPressed) {
      if (gameMenuIndex == 0) {
        currentState = STATE_GAME_DINO_INTRO;
        showDinoIntroScreen();
      } else {
        currentState = STATE_GAME_TIKTAK_INTRO;
        showTikTakIntroScreen();
      }
    }
    if (escPressed) {
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    }
  }
  else if (currentState == STATE_GAME_DINO_INTRO) {
    if (enterPressed) {
      startDinoGame();
      currentState = STATE_GAME_DINO;
    }
    if (escPressed) {
      currentState = STATE_GAME_MENU;
      showGameMenu();
    }
  }
  else if (currentState == STATE_GAME_TIKTAK_INTRO) {
    if (enterPressed) {
      startTikTakGame();
      currentState = STATE_GAME_TIKTAK;
    }
    if (escPressed) {
      currentState = STATE_GAME_MENU;
      showGameMenu();
    }
  }
  else if (currentState == STATE_MELODY_MENU) {
    if (nextPressed) {
      melodyIndex = (melodyIndex + 1) % 3;
      showMelodyMenu();
    }
    if (backPressed) {
      melodyIndex = (melodyIndex + 2) % 3;
      showMelodyMenu();
    }
    if (enterPressed) {
      playMelody(melodyIndex);
      showMelodyMenu();
    }
    if (escPressed) {
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    }
  }
  else if (currentState == STATE_BOMB_SET_TIME) {
    if (nextPressed) {
      selectedSeconds++;
      if (selectedSeconds > 99) selectedSeconds = 99;
      showBombSetTimeScreen();
    }
    if (backPressed) {
      selectedSeconds--;
      if (selectedSeconds < 3) selectedSeconds = 3;
      showBombSetTimeScreen();
    }
    if (enterPressed) {
      remainingSeconds = selectedSeconds;
      currentState = STATE_BOMB_COUNTDOWN;
      lastSecondMillis = millis();
      lastWiggleMillis = millis();
      wiggleState = false;
      showBombCountdownScreen();
    }
    if (escPressed) {
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    }
  }
  else if (currentState == STATE_BOMB_COUNTDOWN) {
    if (escPressed) {
      digitalWrite(relay1Pin, RELAY_OFF);
      digitalWrite(relay2Pin, RELAY_OFF);
      currentState = STATE_BOMB_SET_TIME;
      showBombSetTimeScreen();
    }

    unsigned long wiggleInterval = 120;
    if (millis() - lastWiggleMillis >= wiggleInterval) {
      lastWiggleMillis = millis();
      wiggleState = !wiggleState;
      showBombCountdownScreen();
    }

    if (millis() - lastSecondMillis >= 1000) {
      lastSecondMillis += 1000;

      if (remainingSeconds > 0) {
        remainingSeconds--;
        showBombCountdownScreen();
        beepDouble();

        if (remainingSeconds == 0) {
          digitalWrite(relay1Pin, RELAY_ON);
          digitalWrite(relay2Pin, RELAY_ON);

          beepLong();

          display.clearDisplay();
          display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
          display.display();
          delay(180);

          currentState = STATE_BOMB_FINISHED;
          showBombFinishedScreen();
        }
      }
    }
  }
  else if (currentState == STATE_BOMB_FINISHED) {
    if (escPressed) {
      digitalWrite(relay1Pin, RELAY_OFF);
      digitalWrite(relay2Pin, RELAY_OFF);
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    } else if (enterPressed || nextPressed || backPressed) {
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    }
  }
  else if (currentState == STATE_SETTINGS) {
    if (nextPressed) {
      volumeLevel++;
      if (volumeLevel > 10) volumeLevel = 10;
      showSettingsScreen();
    }
    if (backPressed) {
      volumeLevel--;
      if (volumeLevel < 0) volumeLevel = 0;
      showSettingsScreen();
    }
    if (enterPressed || escPressed) {
      currentState = STATE_MAIN_MENU;
      showMainMenu();
    }
  }
  else if (currentState == STATE_GAME_DINO) {
    updateDinoGame(enterPressed, escPressed);
  }
  else if (currentState == STATE_GAME_TIKTAK) {
    updateTikTakGame(enterPressed, escPressed, nextNow, backNow);
  }

  lastEnterState = enterNow;
  lastNextState  = nextNow;
  lastBackState  = backNow;
  lastEscState   = escNow;

  delay(10);
}

// ---------------- SPLASH -----------------

void showSplashScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // 1) 2 saniye boyunca senin foto (69x68, ortalanmış)
  int imgW = 69;
  int imgH = 68;
  int xImg = (SCREEN_WIDTH - imgW) / 2;
  int yImg = (SCREEN_HEIGHT - imgH) / 2;
  display.drawBitmap(xImg, yImg, My_bitmapabc, imgW, imgH, SSD1306_WHITE);
  display.display();
  delay(2000);

  // 2) Kayan EMIR GORGULU + bomba animasyonu
  display.clearDisplay();
  display.setTextSize(2);

  bool splashWiggle = false;

  for (int x = -96; x <= 0; x += 4) {
    splashWiggle = !splashWiggle;
    display.clearDisplay();

    display.setCursor(x, 0);
    display.println(F("EMIR"));
    display.setCursor(x, 16);
    display.println(F("GORGULU"));

    int baseX = 96;
    int baseY = 32;
    int offsetX = splashWiggle ? 2 : -2;
    int offsetY = splashWiggle ? 1 : -1;
    display.drawBitmap(baseX + offsetX, baseY + offsetY,
                       bombBitmap16, 16, 16, SSD1306_WHITE);

    display.display();
    delay(40);
  }

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.println(F("BOMBABOMBA.COM"));
  display.display();
  delay(200);

  display.fillRect(0, 48, SCREEN_WIDTH, 16, SSD1306_BLACK);
  display.display();
  delay(200);

  display.setCursor(0, 48);
  display.println(F("BOMBABOMBA.COM"));
  display.display();
}

// -------------- MENU EKRANLARI -------------

void showMainMenu() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("MENU"));

  display.setTextSize(1);
  display.setCursor(0, 24);

  if (mainMenuIndex == 0) display.println(F("> Melodi cal"));
  else                    display.println(F("  Melodi cal"));

  if (mainMenuIndex == 1) display.println(F("> Bomba patlat"));
  else                    display.println(F("  Bomba patlat"));

  if (mainMenuIndex == 2) display.println(F("> Oyunlar"));
  else                    display.println(F("  Oyunlar"));

  if (mainMenuIndex == 3) display.println(F("> Ayarlar"));
  else                    display.println(F("  Ayarlar"));

  display.display();
}

void showGameMenu() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Oyunlar"));

  display.setTextSize(1);
  display.setCursor(0, 24);

  if (gameMenuIndex == 0) {
    display.println(F("> Dino Oyun"));
    display.println(F("  Tik Tak"));
  } else {
    display.println(F("  Dino Oyun"));
    display.println(F("> Tik Tak"));
  }

  display.display();
}

void showDinoIntroScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Dino"));

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(F("Yesil: ziplama"));
  display.println(F("ESC  : oyun menusu"));
  display.println(F(""));
  display.println(F("ENTER: oyunu baslat"));

  display.display();
}

void showTikTakIntroScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Tik Tak"));

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(F("Siyah: saga"));
  display.println(F("Sari : sola"));
  display.println(F("ESC  : oyun menusu"));
  display.println(F(""));
  display.println(F("ENTER: oyunu baslat"));

  display.display();
}

void drawMelodyScreen(bool playing, bool wiggleAnim) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Melodi sec:"));

  if (melodyIndex == 2) {
    display.setTextSize(1);
    display.setCursor(0, 16);
    display.println(F("Caddelerde"));
    display.setCursor(0, 28);
    display.println(F("Ruzgar"));
  } else {
    display.setTextSize(2);
    display.setCursor(0, 16);
    display.println(melodyNames[melodyIndex]);
  }

  if (playing) {
    int baseX = 100;
    int baseY = 18;
    int offsetX = wiggleAnim ? 2 : -2;
    display.drawBitmap(baseX + offsetX, baseY,
                       musicNoteBitmap, 8, 8, SSD1306_WHITE);
  }

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.println(F("Siyah: ileri"));
  display.println(F("Sari : geri"));
  display.println(F("Yesil: cal  ESC: menu"));

  display.display();
}

void showMelodyMenu() {
  drawMelodyScreen(false, false);
}

void showBombSetTimeScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Bomba : sure sn"));

  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(selectedSeconds);
  display.print(F(" sn"));

  int iconX = 80;
  int iconY = 14;
  display.drawBitmap(iconX, iconY, bombBitmap16, 16, 16, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println(F("Siyah: +   Sari: -"));
  display.println(F("Yesil: baslat"));
  display.println(F("ESC: menu"));

  display.display();
}

void showBombCountdownScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Geri sayim:"));

  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(remainingSeconds);
  display.print(F(" sn"));

  int baseX = 80;
  int baseY = 14;
  int offsetX = wiggleState ? 2 : -2;
  int offsetY = wiggleState ? 1 : -1;
  display.drawBitmap(baseX + offsetX, baseY + offsetY,
                     bombBitmap16, 16, 16, SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.println(F("ESC: iptal / geri"));

  display.display();
}

void showBombFinishedScreen() {
  digitalWrite(buzzerPin, HIGH);

  for (int i = 0; i < 10; i++) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);
    int xOffset = (i % 2 == 0) ? 4 : 14;
    int yOffset = 8;

    display.setCursor(xOffset, yOffset);
    display.println(F("PATLADI"));

    display.display();
    delay(130);
  }

  digitalWrite(buzzerPin, LOW);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println(F("PATLADI"));

  display.setTextSize(1);
  display.setCursor(10, 40);
  display.println(F("Bombalar ACiK"));
  display.println(F("ESC: kapat + menu"));

  display.display();
}

void showSettingsScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(F("Ayarlar"));

  display.setTextSize(1);
  display.setCursor(0, 24);
  display.print(F("Buzzer: "));
  display.print(volumeLevel);
  display.println(F(" / 10"));

  display.setCursor(0, 40);
  display.println(F("Siyah: arttir"));
  display.println(F("Sari : azalt"));
  display.println(F("ESC/Ent: menu"));

  display.display();
}

// ---------------- SES FONKSIYONLARI -------------

void beepDouble() {
  int onDur = map(volumeLevel, 0, 10, 5, 80);
  int offDur = 60;

  for (int i = 0; i < 2; i++) {
    if (volumeLevel > 0) {
      digitalWrite(buzzerPin, HIGH);
      delay(onDur);
      digitalWrite(buzzerPin, LOW);
    }
    delay(offDur);
  }
}

void beepLong() {
  if (volumeLevel <= 0) return;
  int dur = map(volumeLevel, 0, 10, 80, 500);
  digitalWrite(buzzerPin, HIGH);
  delay(dur);
  digitalWrite(buzzerPin, LOW);
}

void playGameOverMelodyBuzzer() {
  if (volumeLevel <= 0) return;

  int tones[] = {700, 900, 1100, 900, 700};
  int durs[]  = {120, 120, 180, 180, 260};

  for (int i = 0; i < 5; i++) {
    int baseDur = durs[i];
    int dur = map(volumeLevel, 0, 10, baseDur / 4, baseDur);
    tone(buzzerPin, tones[i]);
    delay(dur);
    noTone(buzzerPin);
    delay(40);
  }
}

void speakerMute(bool mute) {
  if (mute) {
    noTone(speakerPin);
    pinMode(speakerPin, INPUT);
  } else {
    pinMode(speakerPin, OUTPUT);
    digitalWrite(speakerPin, LOW);
  }
}

void playSliceWithVolume(int freq, int sliceMs) {
  if (sliceMs <= 0) return;
  if (freq <= 0) {
    delay(sliceMs);
    return;
  }

  unsigned long totalMicros = (unsigned long)sliceMs * 1000UL;
  int period = 1000000L / freq;
  int onMicros = period / 2;
  int offMicros = period - onMicros;
  if (onMicros < 1) onMicros = 1;
  if (offMicros < 1) offMicros = 1;

  unsigned long start = micros();
  while ((micros() - start) < totalMicros) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(onMicros);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(offMicros);
  }
}

void playMelody(int index) {
  const int* notes;
  const int* durations;
  uint8_t length;

  if (index == 0) {
    notes     = melody1Notes;
    durations = melody1Dur;
    length    = melody1Len;
  } else if (index == 1) {
    notes     = melody2Notes;   // Kum Gibi (yeni)
    durations = melody2Dur;
    length    = melody2Len;
  } else {
    notes     = melody3Notes;
    durations = melody3Dur;
    length    = melody3Len;
  }

  const int step = 20;
  bool iconWiggle = false;

  speakerMute(false);

  while (true) {
    for (uint8_t i = 0; i < length; i++) {

      if (digitalRead(buttonEscPin) == HIGH || digitalRead(buttonBackPin) == HIGH) {
        speakerMute(true);
        drawMelodyScreen(false, false);
        return;
      }

      int freq = pgm_read_word_near(notes + i);
      int dur  = pgm_read_word_near(durations + i);

      iconWiggle = !iconWiggle;
      drawMelodyScreen(true, iconWiggle);

      unsigned long elapsed = 0;
      while (elapsed < (unsigned long)dur) {
        if (digitalRead(buttonEscPin) == HIGH || digitalRead(buttonBackPin) == HIGH) {
          speakerMute(true);
          drawMelodyScreen(false, false);
          return;
        }
        int d = dur - elapsed;
        if (d > step) d = step;

        playSliceWithVolume(freq, d);

        elapsed += d;
      }

      unsigned long restElapsed = 0;
      const int restTotal = 30;
      while (restElapsed < restTotal) {
        if (digitalRead(buttonEscPin) == HIGH || digitalRead(buttonBackPin) == HIGH) {
          speakerMute(true);
          drawMelodyScreen(false, false);
          return;
        }
        int d = restTotal - restElapsed;
        if (d > step) d = step;
        delay(d);
        restElapsed += d;
      }
    }
  }

  speakerMute(true);
}

// ---------------- DINO OYUNU ----------------

void startDinoGame() {
  randomSeed(analogRead(A0) + millis());

  dinoY        = DINO_GROUND_Y - DINO_HEIGHT;
  dinoVy       = 0;
  dinoOnGround = true;

  obstacleXf = SCREEN_WIDTH + random(20, 80);
  obstacleX  = (int) obstacleXf;

  gameOver  = false;
  gameScore = 0;

  obstacleSpeed = OBSTACLE_SPEED_MIN;
  lastGameFrameMillis = millis();

  drawDinoGame();
}

void updateDinoGame(bool enterPressed, bool escPressed) {
  if (escPressed) {
    currentState = STATE_GAME_MENU;
    showGameMenu();
    return;
  }

  if (gameOver) {
    if (enterPressed) {
      startDinoGame();
    }
    return;
  }

  if (enterPressed && dinoOnGround) {
    dinoVy = -8.0;
    dinoOnGround = false;
    digitalWrite(buzzerPin, HIGH);
    delay(20);
    digitalWrite(buzzerPin, LOW);
  }

  unsigned long now = millis();
  if (now - lastGameFrameMillis < (unsigned long)GAME_FRAME_MS) {
    return;
  }
  lastGameFrameMillis = now;

  if (!dinoOnGround) {
    dinoVy += 0.55;
    dinoY  += dinoVy;
    if (dinoY >= DINO_GROUND_Y - DINO_HEIGHT) {
      dinoY = DINO_GROUND_Y - DINO_HEIGHT;
      dinoVy = 0;
      dinoOnGround = true;
    }
  }

  obstacleSpeed = OBSTACLE_SPEED_MIN + (float)gameScore / 400.0;
  if (obstacleSpeed > OBSTACLE_SPEED_MAX) obstacleSpeed = OBSTACLE_SPEED_MAX;

  obstacleXf -= obstacleSpeed;
  obstacleX = (int) obstacleXf;

  if (obstacleX < -CACTUS_WIDTH) {
    obstacleXf = SCREEN_WIDTH + random(20, 80);
    obstacleX  = (int) obstacleXf;
  }

  int dinoTop    = (int)dinoY;
  int dinoBottom = dinoTop + DINO_HEIGHT;
  int dinoLeft   = DINO_X;
  int dinoRight  = DINO_X + DINO_WIDTH;

  int obsTop    = OBSTACLE_Y;
  int obsBottom = OBSTACLE_Y + CACTUS_HEIGHT;
  int obsLeft   = obstacleX;
  int obsRight  = obstacleX + CACTUS_WIDTH;

  bool overlapX = (dinoRight >= obsLeft) && (dinoLeft <= obsRight);
  bool overlapY = (dinoBottom >= obsTop) && (dinoTop <= obsBottom);

  if (overlapX && overlapY) {
    gameOver = true;
    beepLong();
  } else {
    gameScore++;
  }

  drawDinoGame();
}

void drawDinoGame() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Dino Oyun"));

  display.setCursor(80, 0);
  display.print(F("Skor:"));
  display.print(gameScore / 5);

  display.drawLine(0, DINO_GROUND_Y, SCREEN_WIDTH, DINO_GROUND_Y, SSD1306_WHITE);

  display.drawBitmap(DINO_X, (int)dinoY, trexBitmap, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);

  display.drawBitmap(obstacleX, OBSTACLE_Y, cactusBitmap, CACTUS_WIDTH, CACTUS_HEIGHT, SSD1306_WHITE);

  display.display();
}

// ---------------- TIK TAK OYUNU ----------------

void startTikTakGame() {
  randomSeed(analogRead(A0) + millis());

  paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;

  ballX = SCREEN_WIDTH / 2;
  ballY = 12;
  ballVx = (random(0, 2) == 0) ? -1.5 : 1.5;
  ballVy = 1.8;

  tikGameOver = false;
  tikScore    = 0;

  lastTikFrameMillis = millis();
  drawTikTakGame();
}

void updateTikTakGame(bool enterPressed, bool escPressed, bool nextHeld, bool backHeld) {
  if (escPressed) {
    currentState = STATE_GAME_MENU;
    showGameMenu();
    return;
  }

  if (tikGameOver) {
    if (enterPressed) {
      startTikTakGame();
    }
    return;
  }

  if (nextHeld) {
    paddleX += 4;
    if (paddleX > SCREEN_WIDTH - PADDLE_WIDTH) paddleX = SCREEN_WIDTH - PADDLE_WIDTH;
  }
  if (backHeld) {
    paddleX -= 4;
    if (paddleX < 0) paddleX = 0;
  }

  unsigned long now = millis();
  if (now - lastTikFrameMillis < (unsigned long)TIK_FRAME_MS) {
    return;
  }
  lastTikFrameMillis = now;

  ballX += ballVx;
  ballY += ballVy;

  if (ballX <= 0) {
    ballX = 0;
    ballVx = -ballVx;
  }
  if (ballX >= SCREEN_WIDTH - 3) {
    ballX = SCREEN_WIDTH - 3;
    ballVx = -ballVx;
  }
  if (ballY <= 6) {
    ballY = 6;
    ballVy = -ballVy;
  }

  if ((ballY + 3) >= PADDLE_Y && (ballY + 3) <= (PADDLE_Y + PADDLE_HEIGHT)) {
    if ((ballX + 1) >= paddleX && (ballX + 1) <= (paddleX + PADDLE_WIDTH)) {
      ballY = PADDLE_Y - 3;
      ballVy = -fabs(ballVy);

      float center = paddleX + PADDLE_WIDTH / 2.0;
      float diff   = (ballX + 1) - center;
      ballVx = diff / (PADDLE_WIDTH / 2.0) * 2.0;

      float speed = sqrt(ballVx * ballVx + ballVy * ballVy);
      if (speed < 4.0) {
        ballVx *= 1.05;
        ballVy *= 1.05;
      }

      tikScore++;
    }
  }

  if (ballY > SCREEN_HEIGHT) {
    tikGameOver = true;
    playGameOverMelodyBuzzer();
  }

  drawTikTakGame();
}

void drawTikTakGame() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Tik Tak"));

  display.setCursor(80, 0);
  display.print(F("Skor:"));
  display.print(tikScore);

  display.drawLine(0, PADDLE_Y + PADDLE_HEIGHT + 2,
                   SCREEN_WIDTH, PADDLE_Y + PADDLE_HEIGHT + 2,
                   SSD1306_WHITE);

  display.fillRect(paddleX, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);

  display.fillRect((int)ballX, (int)ballY, 3, 3, SSD1306_WHITE);

  if (tikGameOver) {
    display.setCursor(20, 24);
    display.println(F("GAME OVER"));
    display.setCursor(4, 36);
    display.println(F("ENTER: yeniden  ESC: menu"));
  }

  display.display();
}