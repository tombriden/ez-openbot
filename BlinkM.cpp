#include "BlinkM.h"
#include "EZB.h"

BlinkMColor::BlinkMColor(unsigned char red, unsigned char green, unsigned char blue){
	this->red = red;
	this->blue = blue;
	this->green = green;
}

void BlinkMClass::ChangeToColor(unsigned char address, unsigned char red, unsigned char green, unsigned char blue){
	unsigned char data[5];
	data[0] = address << 1;
	data[1] = 110;
	data[2] = red;
	data[3] = green;
	data[4] = blue;

	m_ezb->I2C->Start();
	m_ezb->I2C->Write(data, 5);
	m_ezb->I2C->Stop();
}

void BlinkMClass::FadeToColor(unsigned char address, unsigned char red, unsigned char green, unsigned char blue){
	unsigned char data[5];
	data[0] = address << 1;
	data[1] = 99;
	data[2] = red;
	data[3] = green;
	data[4] = blue;

	m_ezb->I2C->Start();
	m_ezb->I2C->Write(data, 5);
	m_ezb->I2C->Stop();
}

BlinkMColor BlinkMClass::GetCurrentColor(unsigned char address){

	unsigned char data[2];
	data[0] = address << 1;
	data[1] = 103;

	m_ezb->I2C->Start();
	m_ezb->I2C->Write(data, 2);
	m_ezb->I2C->Restart();
	data[0] += 1;
	m_ezb->I2C->Write(data, 1);
	unsigned char* buffer = m_ezb->I2C->ReadAutoAck(3);

	BlinkMColor color(buffer[0], buffer[1], buffer[2]);
	delete [] buffer;

	return color;
}

void BlinkMClass::StopScript(unsigned char address){
	/*List<byte> list = new List<byte> {
	                (byte) (address << 1),
	                0x6f
	            };
	            this._ezb.I2C.Start();
	            this._ezb.I2C.Write(list.ToArray());
	            this._ezb.I2C.Stop();*/
	unsigned char data[2];
	data[0] = address << 1;
	data[1] = 111;
	m_ezb->I2C->Start();
	m_ezb->I2C->Write(data, 2);
	m_ezb->I2C->Stop();
}
