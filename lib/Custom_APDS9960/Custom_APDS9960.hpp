#ifndef __CUSTOM_APDS9960_HPP
#define __CUSTOM_APDS9960_HPP

#include "Adafruit_APDS9960.h"

class Custom_APDS9960 : public Adafruit_APDS9960 {
	public:
		boolean begin(uint16_t iTimeMS, apds9960AGain_t aGain, uint8_t addr, TwoWire *theWire) {

		if (i2c_dev)
			delete i2c_dev;
		i2c_dev = new Adafruit_I2CDevice(addr, theWire);
		if (!i2c_dev->begin()) {
			return false;
		}

		/* Make sure we're actually connected */
		uint8_t x = read8(APDS9960_ID);
		if (x != 0xAB || x != 0xA8) {
			return false;
		}

		/* Set default integration time and gain */
		setADCIntegrationTime(iTimeMS);
		setADCGain(aGain);

		// disable everything to start
		enableGesture(false);
		enableProximity(false);
		enableColor(false);

		disableColorInterrupt();
		disableProximityInterrupt();
		clearInterrupt();

		/* Note: by default, the device is in power down mode on bootup */
		enable(false);
		delay(10);
		enable(true);
		delay(10);

		// default to all gesture dimensions
		setGestureDimensions(APDS9960_DIMENSIONS_ALL);
		setGestureFIFOThreshold(APDS9960_GFIFO_4);
		setGestureGain(APDS9960_GGAIN_4);
		setGestureProximityThreshold(50);
		resetCounts();

		_gpulse.GPLEN = APDS9960_GPULSE_32US;
		_gpulse.GPULSE = 9; // 10 pulses
		this->write8(APDS9960_GPULSE, _gpulse.get());

		return true;
	}
}





#endif