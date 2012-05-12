#ifndef _DIGITAL
#define _DIGITAL

class EZB;

class DigitalClass{
public:
	enum DigitalPortEnum{
		D0 = 0,
		D1 = 1,
		D2 = 2,
		D3 = 3,
		D4 = 4,
		D5 = 5,
		D6 = 6,
		D7 = 7,
		D8 = 8,
		D9 = 9,
		D10 = 10,
		D11 = 11,
		D12 = 12,
		D13 = 13,
		D14 = 14,
		D15 = 15,
		D16 = 16,
		D17 = 17,
		D18 = 18,
		D19 = 19,
	};

	int MinPoolTimeMS;

	DigitalClass(EZB* ezb);
	bool GetDigitalPort(DigitalPortEnum digitalPort);
	//
	// Summary:
	//     Query the status of a digital port as an Integer (0 false, 1 true)
	int GetDigitalPortAsInt(DigitalPortEnum digitalPort);
	//
	// Summary:
	//     Does not query the EZ-B Controller. This returns the status of the port after
	//     you had SetDigitalPort().
	bool GetLastDigitalPortSet(DigitalPortEnum digitalPort);
	//
	// Summary:
	//     Set the status of a digital port. TRUE will output +5, FALSE will short to
	//     GND
	//
	// Returns:
	//     True if successful
	void SetDigitalPort(DigitalPortEnum digitalPort, bool status);
private:
	EZB* m_ezb;

};

#endif
