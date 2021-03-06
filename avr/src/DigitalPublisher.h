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

#include "FiniteStateMachine.h"
#include "ParamServer.h"

#include <stdint.h> // for uint8_t

/**
 * Broadcast the state of a digital pin over serial at the given frequency
 * (approximately).
 *
 * Parameters:
 * ---
 * uint8  Pin # IsDigital
 * uint32 Delay
 * ---
 *
 * Publish:
 * ---
 * uint8  pin
 * uint16 value
 * ---
 *
 * Subscribe:
 * ---
 * uint8  pin
 * ---
 */
class DigitalPublisher : public FiniteStateMachine
{
public:
	DigitalPublisher(uint8_t pin, uint32_t delay /* ms */);

	static DigitalPublisher *NewFromArray(const TinyBuffer &params);

	virtual ~DigitalPublisher() { }

	virtual uint32_t Step();

	/**
	 * By specifying a long delay, this publisher becomes a service. When a
	 * message is sent to it (and the message's pin matches its pin), it will
	 * emit the digital value to the serial port on command.
	 */
	virtual bool Message(const TinyBuffer &msg);

private:
	ParamServer::DigitalPublisher m_params;
};
