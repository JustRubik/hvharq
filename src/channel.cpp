#include "..\include\channel.h"

Frame Channel::transmit(const Frame &frame)
{
	Frame output = frame;

	for (Bit &bit : output)
	{
		if (error(gen))
			bit ^= 1;
	}

	return output;
}