//Serial Setup

void serial_setup(int baud)
{
Serial.begin(baud);
while (Serial.available());             
Serial.setTimeout(3000);
//Serial.println("\nI2C Scanner and more!");
Serial.println();
Serial.println();
}
