// wired connections
#define HG7881_B_IA 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 3 // D11 --> Motor B Input B --> MOTOR B -

// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 50  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

void setup()
{
  Serial.begin( 9600 );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
}

void loop()
{
  boolean isValidInput;
  // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Avanti veloce" );
  Serial.println( "2) Avanti" );
  Serial.println( "3) Soft Stop (Ruote libere)" );
  Serial.println( "4) Indietro" );
  Serial.println( "5) Indietro veloce" );
  Serial.println( "6) Hard stop (Ruote bloccate)" );
  Serial.println( "-----------------------------" );
  do
  {
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while ( !Serial.available() )
      ; // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch ( c )
    {
      case '1': // 1) Fast forward
        Serial.println( "Avanti veloce..." );
        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_B_PWM, 255 - PWM_FAST ); // PWM speed = fast
        isValidInput = true;
        break;

      case '2': // 2) Forward
        Serial.println( "Avanti..." );
        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_B_PWM, 255 - PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;

      case '3': // 3) Soft stop (preferred)
        Serial.println( "Soft Stop (Ruote libere)..." );
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        isValidInput = true;
        break;

      case '4': // 4) Reverse
        Serial.println( "Indietro..." );
        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;

      case '5': // 5) Fast reverse
        Serial.println( "Indietro veloce..." );
        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_B_PWM, PWM_FAST ); // PWM speed = fast
        isValidInput = true;
        break;

      case '6': // 6) Hard stop (use with caution)
        Serial.println( "Hard stop (Ruote bloccate)..." );
        digitalWrite( MOTOR_B_DIR, HIGH );
        digitalWrite( MOTOR_B_PWM, HIGH );
        isValidInput = true;
        break;

      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while ( isValidInput == true );

  // repeat the main loop and redraw the menu...
}
