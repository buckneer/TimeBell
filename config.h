byte numDigits = 4;
byte digitPins[] = {1, 4, 5, 12};
byte segmentPins[] = {2, 6, 10, 8, 7, 3, 11, 9};
bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
bool updateWithDelays = false; // Default 'false' is Recommended
bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected
const unsigned int relay = 13;

int ON = LOW;
int OFF = HIGH;

const long interval = 1000;
unsigned int longPressDuration = 3000;




// Times
const int winterTimes[][2] = {
  {8, 0}, 
  {8, 40}, 
  {8, 45}, 
  {9, 25}, 
  {9, 40}, 
  {10, 20}, 
  {10, 25}, 
  {11, 5},
  {11, 10}, 
  {11, 45}, 
  {11, 50}, 
  {12, 20}, 
  {12, 25}, 
  {12, 55}, 
  {13, 10}, 
  {13, 45},
  {13, 50}, 
  {14, 25}, 
  {14, 40}, 
  {15, 15}, 
  {15, 20}, 
  {15, 55}, 
  {16, 0}, 
  {16, 30},
  {16, 35},
  {17, 5}, 
  {17, 10}, 
  {17, 40},
};

const int summerTimes[][2] = {
  {8, 0}, {8, 40}, {8, 45}, {9, 25}, {9, 40}, {10, 20}, {10, 25}, {11, 5},
  {11, 10}, {11, 45}, {11, 50}, {12, 25}, {12, 30}, {13, 0}, {13, 15}, {13, 55},
  {14, 0}, {14, 40}, {14, 55}, {15, 35}, {15, 40}, {16, 20}, {16, 25}, {17, 0},
  {17, 5}, {17, 40}, {17, 45}, {18, 15}
};