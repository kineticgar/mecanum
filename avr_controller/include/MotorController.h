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

#include "AVRController.h"

class MotorController
{
public:
	MotorController() : m_avr(NULL) { }
	~MotorController() throw() { }

	bool Connect(AVRController *avr);
	bool IsConnected() const { return m_avr != NULL; }

	void SetSpeed(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);

private:
	/**
	 * This object is noncopyable.
	 */
	MotorController(const MotorController &other);
	MotorController& operator=(const MotorController &rhs);

	AVRController *m_avr;
};
