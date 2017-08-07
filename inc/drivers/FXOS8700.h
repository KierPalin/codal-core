/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef FXOS8700_H
#define FXOS8700_H

#include "CodalConfig.h"
#include "CodalComponent.h"
#include "Pin.h"
#include "I2C.h"
#include "CoordinateSystem.h"
#include "CodalUtil.h"

/**
  * I2C constants
  */
#define FXOS8700_DEFAULT_ADDR       0x3C

/**
  * FXOS8700 Register map 
  */
#define FXOS8700_STATUS_REG         0x00
#define FXOS8700_OUT_X_MSB          0x01
#define FXOS8700_OUT_X_LSB          0x02
#define FXOS8700_OUT_Y_MSB          0x03
#define FXOS8700_OUT_Y_LSB          0x04
#define FXOS8700_OUT_Z_MSB          0x05
#define FXOS8700_OUT_Z_LSB          0x06
#define FXOS8700_F_SETUP            0x09
#define FXOS8700_TRIG_CFG           0x0A
#define FXOS8700_SYSMOD             0x0B
#define FXOS8700_INT_SOURCE         0x0C
#define FXOS8700_WHO_AM_I           0x0D
#define FXOS8700_XYZ_DATA_CFG       0x0E
#define FXOS8700_HP_FILTER_CUTOFF   0x0F
#define FXOS8700_PL_STATUS          0x10
#define FXOS8700_PL_CFG             0x11
#define FXOS8700_PL_COUNT           0x12
#define FXOS8700_PL_BF_ZCOMP        0x13
#define FXOS8700_PL_THS_REG         0x14
#define FXOS8700_A_FFMT_CFG         0x15
#define FXOS8700_A_FFMT_SRC         0x16
#define FXOS8700_A_FFMT_THS         0x17
#define FXOS8700_A_FFMT_COUNT       0x18
#define FXOS8700_TRANSIENT_CFG      0x1D
#define FXOS8700_TRANSIENT_SRC      0x1E
#define FXOS8700_TRANSIENT_THS      0x1F
#define FXOS8700_TRANSIENT_COUNT    0x20
#define FXOS8700_PULSE_CFG          0x21
#define FXOS8700_PULSE_SRC          0x22
#define FXOS8700_PULSE_THSX         0x23
#define FXOS8700_PULSE_THSY         0x24
#define FXOS8700_PULSE_THSZ         0x25
#define FXOS8700_PULSE_TMLT         0x26
#define FXOS8700_PULSE_LTCY         0x27
#define FXOS8700_PULSE_WIND         0x28
#define FXOS8700_ASLP_COUNT         0x29
#define FXOS8700_CTRL_REG1          0x2A
#define FXOS8700_CTRL_REG2          0x2B
#define FXOS8700_CTRL_REG3          0x2C
#define FXOS8700_CTRL_REG4          0x2D
#define FXOS8700_CTRL_REG5          0x2E
#define FXOS8700_OFF_X              0x2F
#define FXOS8700_OFF_Y              0x30
#define FXOS8700_OFF_Z              0x31
#define FXOS8700_M_DR_STATUS        0x32
#define FXOS8700_M_OUT_X_MSB        0x33
#define FXOS8700_M_OUT_X_LSB        0x34
#define FXOS8700_M_OUT_Y_MSB        0x35
#define FXOS8700_M_OUT_Y_LSB        0x36
#define FXOS8700_M_OUT_Z_MSB        0x37
#define FXOS8700_M_OUT_Z_LSB        0x38
#define FXOS8700_CMP_X_MSB          0x39
#define FXOS8700_CMP_X_LSB          0x3A
#define FXOS8700_CMP_Y_MSB          0x3B
#define FXOS8700_CMP_Y_LSB          0x3C
#define FXOS8700_CMP_Z_MSB          0x3D
#define FXOS8700_CMP_Z_LSB          0x3E
#define FXOS8700_M_OFF_X_MSB        0x3F
#define FXOS8700_M_OFF_X_LSB        0x40
#define FXOS8700_M_OFF_Y_MSB        0x41
#define FXOS8700_M_OFF_Y_LSB        0x42
#define FXOS8700_M_OFF_Z_MSB        0x43
#define FXOS8700_M_OFF_Z_LSB        0x44
#define FXOS8700_MAX_X_MSB          0x45
#define FXOS8700_MAX_X_LSB          0x46
#define FXOS8700_MAX_Y_MSB          0x47
#define FXOS8700_MAX_Y_LSB          0x48
#define FXOS8700_MAX_Z_MSB          0x49
#define FXOS8700_MAX_Z_LSB          0x4A
#define FXOS8700_MIN_X_MSB          0x4B
#define FXOS8700_MIN_X_LSB          0x4C
#define FXOS8700_MIN_Y_MSB          0x4D
#define FXOS8700_MIN_Y_LSB          0x4E
#define FXOS8700_MIN_Z_MSB          0x4F
#define FXOS8700_MIN_Z_LSB          0x50
#define FXOS8700_TEMP               0x51
#define FXOS8700_M_THS_CFG          0x52
#define FXOS8700_M_THS_SRC          0x53
#define FXOS8700_M_THS_X_MSB        0x54
#define FXOS8700_M_THS_X_LSB        0x55
#define FXOS8700_M_THS_Y_MSB        0x56
#define FXOS8700_M_THS_Y_LSB        0x57
#define FXOS8700_M_THS_Z_MSB        0x58
#define FXOS8700_M_THS_Z_LSB        0x59
#define FXOS8700_M_THS_COUNT        0x5A
#define FXOS8700_M_CTRL_REG1        0x5B
#define FXOS8700_M_CTRL_REG2        0x5C
#define FXOS8700_M_CTRL_REG3        0x5D
#define FXOS8700_M_INT_SRC          0x5E
#define FXOS8700_A_VECM_CFG         0x5F
#define FXOS8700_A_VECM_THS_MSB     0x60
#define FXOS8700_A_VECM_THS_LSB     0x61
#define FXOS8700_A_VECM_CNT         0x62
#define FXOS8700_A_VECM_INITX_MSB   0x63
#define FXOS8700_A_VECM_INITX_LSB   0x64
#define FXOS8700_A_VECM_INITY_MSB   0x65
#define FXOS8700_A_VECM_INITY_LSB   0x66
#define FXOS8700_A_VECM_INITZ_MSB   0x67
#define FXOS8700_A_VECM_INITZ_LSB   0x68
#define FXOS8700_M_VECM_CFG         0x69
#define FXOS8700_M_VECM_THS_MSB     0x6A
#define FXOS8700_M_VECM_THS_LSB     0x6B
#define FXOS8700_M_VECM_CNT         0x6C
#define FXOS8700_M_VECM_INITX_MSB   0x6D
#define FXOS8700_M_VECM_INITX_LSB   0x6E
#define FXOS8700_M_VECM_INITY_MSB   0x6F
#define FXOS8700_M_VECM_INITY_LSB   0x70
#define FXOS8700_M_VECM_INITZ_MSB   0x71
#define FXOS8700_M_VECM_INITZ_LSB   0x72
#define FXOS8700_A_FFMT_THS_X_MSB   0x73
#define FXOS8700_A_FFMT_THS_X_LSB   0x74
#define FXOS8700_A_FFMT_THS_Y_MSB   0x75
#define FXOS8700_A_FFMT_THS_Y_LSB   0x76
#define FXOS8700_A_FFMT_THS_Z_MSB   0x77
#define FXOS8700_A_FFMT_THS_Z_LSB   0x78


/**
  * MMA8653 constants
  */
#define FXOS8700_WHOAMI_VAL      0xC7

namespace codal
{
    struct FXOSRawSample
    {
        int16_t         ax;
        int16_t         ay;
        int16_t         az;
        int16_t         cx;
        int16_t         cy;
        int16_t         cz;
    };

    // Forward declare our sibling classes that may register themselves for a callback when data is ready.
    class FXOS8700Accelerometer;
    class FXOS8700Magnetometer;

    /**
     * Class definition for an FXSO8700 hybrid Accelerometer/Magnetometer
     */
    class FXOS8700 : CodalComponent
    {
        I2C&            i2c;                    // The I2C interface to use.
        Pin             &int1;                  // Data ready interrupt.
        uint16_t        address;                // I2C address of this accelerometer.
        uint16_t        samplePeriod;           // The time between samples, in milliseconds.
        uint8_t         sampleRange;            // The sample range of the accelerometer in g.
        Sample3D        accelerometerSample;    // Scaled but non-transformed data from the sensor.
        Sample3D        magnetometerSample;     // Scaled but non-transformed data from the sensor.

        FXOS8700Accelerometer  *accelerometerAPI;      // Handle on an instance of higher level interface (if there is one)
        FXOS8700Magnetometer   *magnetometerAPI;       // Handle on an instance of higher level interface (if there is one)

        public:

        /**
          * Constructor.
          * Create a software abstraction of an accelerometer.
          *
          * @param _i2c an instance of I2C used to communicate with the onboard accelerometer.
          * @param _int1 a pin connected to the INT1 interrupt source of the sensor.
          * @param address the default I2C address of the accelerometer. Defaults to: FXOS8700_DEFAULT_ADDR.
          *
         */
        FXOS8700(I2C &_i2c, Pin &_int1, uint16_t address = FXOS8700_DEFAULT_ADDR);

        /**
          * Configures the accelerometer for G range and sample rate defined
          * in this object. The nearest values are chosen to those defined
          * that are supported by the hardware. The instance variables are then
          * updated to reflect reality.
          *
          * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the accelerometer could not be configured.
          */
        int configure();

        /**
          * Reads the acceleration data from the accelerometer, and stores it in our buffer.
          * This only happens if the accelerometer indicates that it has new data via int1.
          *
          * On first use, this member function will attempt to add this component to the
          * list of fiber components in order to constantly update the values stored
          * by this object.
          *
          * This technique is called lazy instantiation, and it means that we do not
          * obtain the overhead from non-chalantly adding this component to fiber components.
          *
          * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the read request fails.
          */
        int updateSample();

        /**
          * Attempts to set the sample rate of the accelerometer to the specified value (in ms).
          *
          * @param period the requested time between samples, in milliseconds.
          *
          * @return DEVICE_OK on success, DEVICE_I2C_ERROR is the request fails.
          *
          * @code
          * // sample rate is now 20 ms.
          * accelerometer.setPeriod(20);
          * @endcode
          *
          * @note The requested rate may not be possible on the hardware. In this case, the
          * nearest lower rate is chosen.
          */
        int setPeriod(int period);

        /**
          * Reads the currently configured sample rate of the accelerometer.
          *
          * @return The time between samples, in milliseconds.
          */
        int getPeriod();

        /**
          * Attempts to set the sample range of the accelerometer to the specified value (in g).
          *
          * @param range The requested sample range of samples, in g.
          *
          * @return DEVICE_OK on success, DEVICE_I2C_ERROR is the request fails.
          *
          * @code
          * // the sample range of the accelerometer is now 8G.
          * accelerometer.setRange(8);
          * @endcode
          *
          * @note The requested range may not be possible on the hardware. In this case, the
          * nearest lower range is chosen.
          */
        int setRange(int range);

        /**
          * Reads the currently configured sample range of the accelerometer.
          *
          * @return The sample range, in g.
          */
        int getRange();

        /**
          * Attempts to read the 8 bit ID from the accelerometer, this can be used for
          * validation purposes.
          *
          * @return the 8 bit ID returned by the accelerometer, or DEVICE_I2C_ERROR if the request fails.
          *
          * @code
          * accelerometer.whoAmI();
          * @endcode
          */
        int whoAmI();

        /**
          * Reads the accelerometer data from the latest update retrieved from the accelerometer.
          * Data is provided in ENU format, relative to the device package (and makes no attempt
          * to align axes to the device).
          *
          * @return The force measured in each axis, in milli-g.
          *
          */
        Sample3D getAccelerometerSample();

        /**
          * Reads the magnetometer data from the latest update retrieved from the magnetometer.
          * Data is provided in ENU format, relative to the device package (and makes no attempt
          * to align axes to the device).
          *
          * @return The magnetic force measured in each axis, in micro-teslas.
          *
          */
        Sample3D getMagnetometerSample();

        /**
          * A periodic callback invoked by the fiber scheduler idle thread.
          *
          * Internally calls updateSample().
          */
        virtual void idleCallback();

        /**
         * Register a higher level driver for our accelerometer functions
         *
         * @param a A pointer to an instance of the FXOS8700Accelerometer class to inform when new data is available.
         */
        void setAccelerometerAPI(FXOS8700Accelerometer *a);

        /**
         * Register a higher level driver for our magnetometer functions
         *
         * @param a A pointer to an instance of the FXOS8700Magnetometer class to inform when new data is available.
         */
        void setMagnetometerAPI(FXOS8700Magnetometer *m);

        /**
          * Destructor.
          */
        ~FXOS8700();

    };
}

#endif
