# Robot Autónomo con 3 Sensores Ultrasonicos

Este proyecto es un **robot autónomo** diseñado para detectar obstáculos utilizando **tres sensores ultrasónicos** (izquierdo, central y derecho) y reaccionar en consecuencia mediante **movimientos diferenciados** de sus ruedas.  

## Características principales

- **Evitación de obstáculos**:  
  - Sensor central detecta objetos → retrocede y gira 180°.  
  - Sensor izquierdo detecta objetos → gira pivotando la rueda izquierda hacia atrás.  
  - Sensor derecho detecta objetos → gira pivotando la rueda derecha hacia atrás.  

- **Lecturas rápidas de sensores**:  
  - Implementación optimizada para lecturas más veloces y reactivas.  

- **Velocidad ajustable por motor**:  
  - Motor izquierdo y derecho pueden configurarse individualmente para compensar diferencias físicas entre motores.  

- **Indicadores y mensajes**:  
  - LED integrado se enciende cuando se detecta un obstáculo.  
  - Consola Serial muestra distancias y estados del robot de forma clara y legible.  

- **Movimientos controlados**:  
  - Avance, retroceso, pivotes individuales, giro de 180°.  
  - Pivot con una rueda activa hacia atrás para maniobras precisas.  

## Pines usados

### Sensores ultrasónicos
- Izquierdo: TRIG = A3, ECHO = A2  
- Central: TRIG = A1, ECHO = A0  
- Derecho: TRIG = A5, ECHO = A4  

### Motores
- ENA = 3 (PWM motor izquierdo)  
- IN1 = 5, IN2 = 4 (motor izquierdo)  
- IN3 = 6, IN4 = 7 (motor derecho)  
- ENB = 8 (PWM motor derecho)  

## Requisitos

- Arduino UNO (o compatible)  
- 2 motores DC con driver L298N  
- 3 sensores ultrasónicos HC-SR04  
- Cables y alimentación adecuados  

## Uso

1. Conectar los sensores y motores según los pines indicados.  
2. Subir el código `.ino` al Arduino mediante el IDE oficial.  
3. Abrir la consola Serial a 115200 baudios para monitorear las distancias y movimientos.  
4. El robot se moverá autónomamente evitando obstáculos según la lógica programada.  

---

**Este proyecto es ideal para**: aprendizaje de robótica, sistemas de evasión de obstáculos, control de motores con Arduino y programación de robots autónomos con sensores ultrasónicos.
