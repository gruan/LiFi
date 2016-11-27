#include "TransmissionEncode.h"

int TransmissionEncode::noEncoding(char bit) const
{
  if (bit == '1') {
    return m_brightnessOn;
  } else if (bit == '0') {
    return m_brightnessOff;
  } else {
    return m_errBrightness;
  }
}

int TransmissionEncode::nrziEncoding(char currBit, char lastBit) const
{
  // Error. The character should only be '0', or '1'.
  if (currBit != '0' && currBit != '1')
    return m_errBrightness;

  // Bit was received.

  // This bit is the first bit received.
  if (lastBit == m_specialChar) {
    if (currBit == '0')
      return m_brightnessOff;
    else
      return m_brightnessOn;
  }

  // This bit is not the first bit received.
  if (currBit == lastBit)
    return m_brightnessOff;
  else
    return m_brightnessOn;
}

int TransmissionEncode::ruanEncoding(char currBit, char lastBit)
{
  // Error. The character should only be '0', or '1'.
  if (currBit != '0' && currBit != '1')
    return m_errBrightness;

  // Bit was received.

  // No repetition. This is the same as a noEncoding scheme.
  if (currBit != lastBit) {
    m_repBrightnessFlag = true;
    return noEncoding(currBit);
  }

  // Repetition. Alternate between the noEncoding brightness and a specified repeat brightness.
  int brightness = m_errBrightness;
  if (m_repBrightnessFlag)
    brightness = m_brightnessRepeat;
  else
    brightness = noEncoding(currBit);

  m_repBrightnessFlag = !m_repBrightnessFlag;
  return brightness;
}
