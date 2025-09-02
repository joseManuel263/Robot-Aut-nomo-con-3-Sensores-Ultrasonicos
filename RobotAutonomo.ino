// --- Pines sensores ultrasonicos ---
#define TRIG_LEFT   A3
#define ECHO_LEFT   A2
#define TRIG_CENTER A1
#define ECHO_CENTER A0
#define TRIG_RIGHT  A5
#define ECHO_RIGHT A4

#define OBSTACLE_DIST 20

// --- Velocidades individuales ---
const int SPEED_LEFT = 130;
const int SPEED_RIGHT = 128;

// Pines motores
const int ENA = 3; 
const int IN1 = 5; 
const int IN2 = 4; 
const int IN3 = 6; 
const int IN4 = 7; 
const int ENB = 8;

bool goesForward = false;

// Distancias
int distLeft = 100;
int distCenter = 100;
int distRight = 100;

// Duraciones
const int TURN_90 = 400;
const int TURN_180 = 800;
const int BACK_DELAY = 400;

void setup() {
  pinMode(TRIG_LEFT, OUTPUT); pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_CENTER, OUTPUT); pinMode(ECHO_CENTER, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT); pinMode(ECHO_RIGHT, INPUT);

  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("🤖 Robot autónomo con 3 sensores (pivot rueda hacia atrás)");

  analogWrite(ENA, SPEED_LEFT);
  analogWrite(ENB, SPEED_RIGHT);
  delay(100);
}

void loop() {
  distLeft = readPingFast(TRIG_LEFT, ECHO_LEFT);
  distCenter = readPingFast(TRIG_CENTER, ECHO_CENTER);
  distRight = readPingFast(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("Izq: "); Serial.print(distLeft);
  Serial.print(" cm | Cen: "); Serial.print(distCenter);
  Serial.print(" cm | Der: "); Serial.print(distRight); Serial.println(" cm");

  if (distCenter <= OBSTACLE_DIST) {
    digitalWrite(LED_BUILTIN, HIGH);
    moveBackward();
    delay(BACK_DELAY);
    rotate180();
  } 
  else if (distLeft <= OBSTACLE_DIST) {
    digitalWrite(LED_BUILTIN, HIGH);
    pivotRightBackwards(); // Rueda hacia atrás
  } 
  else if (distRight <= OBSTACLE_DIST) {
    digitalWrite(LED_BUILTIN, HIGH);
    pivotLeftBackwards();  // Rueda hacia atrás
  } 
  else {
    digitalWrite(LED_BUILTIN, LOW);
    moveForward();
  }
}

// --- Lectura ultrasónica rápida ---
int readPingFast(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 10000);
  int cm = duration * 0.0343 / 2;
  if (cm == 0) cm = 250;
  return cm;
}

// --- Movimiento ---
void moveStop() {
  goesForward = false;
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void moveForward() {
  if (!goesForward) { goesForward = true; Serial.println("▶️ Avanzando..."); }
  analogWrite(ENA, SPEED_LEFT);
  analogWrite(ENB, SPEED_RIGHT);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  goesForward = false;
  Serial.println("⏪ Retrocediendo...");
  analogWrite(ENA, SPEED_LEFT);
  analogWrite(ENB, SPEED_RIGHT);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

// --- Pivot con rueda hacia atrás ---
void pivotRightBackwards() {
  Serial.println("↪️ Pivot derecha (rueda trasera)");
  analogWrite(ENA, SPEED_LEFT);
  analogWrite(ENB, SPEED_RIGHT);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); // rueda izquierda hacia atrás
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);  // rueda derecha parada
  delay(TURN_90);
  moveStop();
}

void pivotLeftBackwards() {
  Serial.println("↩️ Pivot izquierda (rueda trasera)");
  analogWrite(ENA, SPEED_LEFT);
  analogWrite(ENB, SPEED_RIGHT);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);  // rueda izquierda parada
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); // rueda derecha hacia atrás
  delay(TURN_90);
  moveStop();
}

void rotate180() {
  Serial.println("🔄 Giro 180°");
  analogWrite(ENA, SPEED_LEFT);
  analogWrite(ENB, SPEED_RIGHT);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  delay(TURN_180);
  moveStop();
}
