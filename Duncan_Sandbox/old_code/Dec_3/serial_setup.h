/* SDSMT
 * #11ModularGameController
 * written by Duncan McGonagle
 * libraries used Adafruit Seesaw
 * This example shows how to blink a pin on a seesaw.
 * It is written to use the built-in LED on the ATtiny817 breakout with seesaw.
 * Future Iteration: Use this code as a base to intialize individual pinsf
 */

/* Sets the baud rate and timeout for the serial
*/
void serial_setup(int baud)
{
Serial.begin(baud);
while (Serial.available());             
Serial.setTimeout(3000);
//Serial.println("\nI2C Scanner and more!");
Serial.println();
Serial.println();
}
