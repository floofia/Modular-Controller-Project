//Serial Setup

void serial_setup(int baud)
{
Serial.begin(baud);
while (!Serial);             // Leonardo: wait for serial monitor
Serial.println("\nI2C Scanner and more!");
}
