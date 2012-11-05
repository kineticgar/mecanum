/*
 *        Copyright (C) 2112 Garrett Brown <gbruin@ucla.edu>
 *
 *  This Program is free software; you can redistribute it and/or modify it
 *  under the terms of the Modified BSD License.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the organization nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *  This Program is distributed AS IS in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#pragma once

#include "BBExpansionPin.h"
#include "I2CBus.h"

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

class IMU
{
public:
	IMU() : gyroInt(21), accInt(22), i2c(2) { }
	~IMU() throw() { Close(); }

	bool Open();
	bool IsOpen() { return i2c.IsOpen(); } // All three resources are opened together
	void Close() throw();

	struct Frame
	{
		int16_t x;
		int16_t y;
		int16_t z;
		int16_t xRot;
		int16_t yRot;
		int16_t zRot;
		int16_t temp;
	};
	bool GetFrame(Frame &frame);

private:
	/**
	 * Set the target of the next read or write operation.
	 */
	enum Device { ACC, GYRO };
	bool Select(Device device);

	bool InitAcc();
	bool InitGyro();

	BBExpansionPin gyroInt;
	BBExpansionPin accInt;
	I2CBus         i2c;

	boost::mutex     i2cMutex;
	boost::condition i2cCondition;
};
