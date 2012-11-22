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

#include "Toggle.h"

#include "ArduinoAddressBook.h"

#include <Arduino.h>
#include <limits.h> // for ULONG_MAX

#define FOREVER (ULONG_MAX / 2) // ~25 days, need some space to add current time

Toggle::Toggle(uint8_t pin) :
	FiniteStateMachine(FSM_TOGGLE, GetBuffer()), m_enabled(false)
{
	SetPin(pin);

	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

Toggle *Toggle::NewFromArray(const TinyBuffer &params)
{
	if (Validate(params))
	{
		ParamServer::Toggle toggle(params);
		return new Toggle(toggle.GetPin());
	}
	return NULL;
}

Toggle::~Toggle()
{
	digitalWrite(GetPin(), LOW);
}

uint32_t Toggle::Step()
{
	digitalWrite(GetPin(), m_enabled ? HIGH : LOW);
	return FOREVER;
}

bool Toggle::Message(const TinyBuffer &msg)
{
	if (msg.Length() == ParamServer::ToggleSubscriberMsg::GetLength())
	{
		ParamServer::ToggleSubscriberMsg message(msg);
		if (message.GetPin() == GetPin())
		{
			switch (message.GetCommand())
			{
			case 0:
				m_enabled = false;
				break;
			case 1:
				m_enabled = true;
				break;
			case 2:
			default:
				m_enabled = !m_enabled;
				break;
			}
			return true;
		}
	}
	return false;
}
