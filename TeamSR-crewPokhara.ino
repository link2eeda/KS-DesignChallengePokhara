#define Trigpin 7
#define Echopin 8
#define low_led 9
#define high_led 10
float distance;
int duration;
int ll = 700;


const int LED_YELLOW  = 10; 
const int LED_BLUE    = 11; 
const int LED_GREEN   = 12; 
const int LED_RED     = 13; 

const int BUTTON_YELLOW = 2;  
const int BUTTON_BLUE   = 3; 
const int BUTTON_GREEN  = 4;  
const int BUTTON_RED    = 5;  

const int PIEZO         = 6;  

const int STATE_START_GAME        = 0;  
const int STATE_PICK_RND_SEQUENCE = 1; 
const int STATE_SHOW_RND_SEQUENCE = 2;  
const int STATE_READ_PLAYER_GUESS = 3;  
const int STATE_VERIFY_GUESS      = 4;  
const int STATE_GUESS_CORRECT     = 5;  
const int STATE_GUESS_INCORRECT   = 6; 

const int MAX_DIFFICULTY_LEVEL    = 9; 


int randomSequence[MAX_DIFFICULTY_LEVEL];

// Array used to store the player's guess
int playerGuess[MAX_DIFFICULTY_LEVEL];
// A counter to record the number of button presses made by the player
int numButtonPresses;

// The current state the game is in
int currentState;
int nextState;

// The difficulty level (1..MAX_DIFFICULTY_LEVEL)
// (Do not set to zero!)
int difficultyLevel;


void setup() {
  pinMode (Trigpin, OUTPUT);
  pinMode (low_led, OUTPUT);
  pinMode (high_led, OUTPUT);
  pinMode (Echopin, INPUT);
  Serial.begin(9600);
  Serial.println ("Welcome To Distance Meter");
  Serial.println ("Coded By Jevins Annson");
  digitalWrite (low_led, LOW);
  digitalWrite (high_led, LOW);

  // Initialise input buttons
  for(int i=BUTTON_YELLOW; i<=BUTTON_RED; i++) {
    pinMode(i, INPUT);
  }
  // Initialise LEDs
  for(int i=LED_YELLOW; i<=LED_RED; i++) {
    pinMode(i, OUTPUT);
  }
  // Set initial difficulty level to 1 random flash && put game in start state
  difficultyLevel = 1;
  currentState = STATE_START_GAME;
  nextState = currentState;
  numButtonPresses = 0;
}

void loop() {
  digitalWrite(Trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigpin, LOW);
  duration = pulseIn(Echopin, HIGH);
  distance = duration * 0.034 / 2;
  delay (ll);
  Serial.println (" ");
  Serial.print ("Distance = ");
  Serial.print (distance);
  Serial.print (" CM");
  Serial.println (" ");

  if (distance>=30)
  {
    Serial.println ("Nobody Is Infront Of the Sensor");
    digitalWrite (low_led, HIGH);
    delay (500);
    digitalWrite (low_led, LOW);
    delay (500);
    digitalWrite (low_led, HIGH);
  }
  else 
  {
    Serial.println ("Someone Is Infront Of the Sensor");
    digitalWrite (high_led, HIGH);
    delay (100);
    digitalWrite (high_led, LOW);
    delay (100);
    digitalWrite (high_led, HIGH);
    delay (100);
  }

  
}


void soundCorrectGuess() {
  tone(PIEZO, 700, 100);
  delay(100);
  tone(PIEZO, 800, 100);
  delay(100);
  tone(PIEZO, 900, 100);
  delay(100);
  tone(PIEZO, 1000, 100);
  delay(100);
  tone(PIEZO, 1100, 100);
  delay(100);
  tone(PIEZO, 1200, 100);
  delay(100);
}
// Flash the LED on the given pin
void flashLED(int ledPinNum, bool playSound) {
  digitalWrite(ledPinNum, HIGH);
  if( playSound )
    playSoundForLED(ledPinNum);
  delay(1000);
  digitalWrite(ledPinNum, LOW);
  delay(500);
}

void playSoundForLED(int ledPinNum) {
  int pitch = 0;
  switch(ledPinNum) {
    case LED_YELLOW: pitch = 200; break;
    case LED_BLUE: pitch = 250; break;
    case LED_GREEN: pitch = 300; break;
    case LED_RED: pitch = 350; break;
  }
  tone(PIEZO, pitch, 800);
}
// Get a random LED pin number
int rndLEDPin() {
  return random(LED_YELLOW, LED_RED + 1);
}
