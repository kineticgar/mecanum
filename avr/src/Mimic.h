#ifndef MIMIC_H
#define MIMIC_H

#include "FiniteStateMachine.h"

#include <stdint.h> // for uint8_t

/**
 * This FSM has a destination pin mimic a source pin. Whenever the source
 * pin changes, the destination pin assumes that value. The maximum amount of
 * jitter is specified by the delay.
 */
class Mimic : public FiniteStateMachine
{
public:
	Mimic(uint8_t source, uint8_t dest, unsigned long delay /* ms */);

	/*
	 * When this FSM is destructed, the destination pin is left at whatever
	 * value the source pin was on the previous step.
	 */
	virtual ~Mimic() { }

	virtual void Step();

	virtual unsigned long Delay() const { return m_delay; }

private:
	uint8_t m_source;
	uint8_t m_dest;
	unsigned long m_delay; // ms
};

#endif // MIMIC_H