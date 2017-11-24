/*
 * Copyright (c) 2017 Evan Kale
 * Email: EvanKale91@gmail.com
 * Web: www.youtube.com/EvanKale
 * Social: @EvanKale91
 *
 * This file is part of Blipper.
 *
 * Blipper is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/sleep.h>
#include <avr/power.h>

//Pin definition
#define LED PB3
#define BLIP PB4
#define TRIGGER_1 PB0

#define NO_TRIGGER -1

#define LED_BLINK_DURATION_MS 500
#define BLIP_PULSE_DURATION_US 200

//Stores the pin state every time interrupt is called
volatile byte prevPinState = 0b11111111;

//Stores the trigger number that triggered the interrupt
volatile byte activatedTrigger = NO_TRIGGER;

//Pin change interrupt function
ISR(PCINT0_vect)
{
  //PINB XOR prevPinState to get list of triggers that changed state
  byte changedPins = PINB ^ prevPinState;

  //If a trigger changed state and is a down-press,
  // then set activatedTrigger to that trigger.
  if (bitRead(changedPins, TRIGGER_1) && !bitRead(PINB, TRIGGER_1))
  {
    activatedTrigger = TRIGGER_1;
  }
  else
  {
    activatedTrigger = NO_TRIGGER;
  }

  //Store PINB as prev pin state
  prevPinState = PINB;
}

void setup ()
{
  pinMode (LED, OUTPUT);
  pinMode (BLIP, OUTPUT);
  pinMode (TRIGGER_1, INPUT_PULLUP);

  //Pin Change Mask Register:
  //- Set trigger pins to trigger pin change interrupt
  PCMSK |= bit(TRIGGER_1);

  //General Interrupt Flag Register:
  //- Clear pin change interrupt flag
  GIFR |= bit(PCIF);

  //General Interrupt Mask Register:
  //- Enable pin change interrupt
  GIMSK |= bit(PCIE);
}

void loop ()
{
  if (activatedTrigger == TRIGGER_1)
  {
    outputBlip(3);
    blinkLED(2);
  }
  //Enter sleep mode when idle to save power
  goToSleep();
}

//Sends blip signal through BLIP pin
void outputBlip(byte numPulses)
{
  int blipDuration = BLIP_PULSE_DURATION_US / 2;
  for (byte i = 0; i < numPulses; ++i)
  {
    digitalWrite(BLIP, HIGH);
    delayMicroseconds(blipDuration);
    digitalWrite(BLIP, LOW);
    delayMicroseconds(blipDuration);
  }
}

//Blinks LED through LED pin
void blinkLED(byte numPulses)
{
  int delayDuration = (LED_BLINK_DURATION_MS / numPulses) / 2;
  for (byte i = 0; i < numPulses; ++i)
  {
    digitalWrite(LED, HIGH);
    delay(delayDuration);
    digitalWrite(LED, LOW);
    delay(delayDuration);
  }
}

void goToSleep()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA = 0;            // turn off ADC
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  sleep_enable();
  sleep_cpu();
  sleep_disable();
  power_all_enable();    // power everything back on
}
