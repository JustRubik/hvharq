#pragma once

#include <cstdint>

#include "..\include\sender.h"
#include "..\include\receiver.h"
#include "..\include\config.h"
#include "..\include\channel.h"

namespace Protocols
{
	class Harq
	{
	private:
		uint8_t retx = 0;
	public:
		const std::uint8_t &getRetx() const;
		void setRetx(const std::uint8_t &retx);

		void runHarq(Sender &tx, Receiver &rx, Channel &channel);
	};

	class Arq
	{
	private:
		uint8_t retx = 0;

	public:
		const std::uint8_t &getRetx() const;
		void setRetx(const std::uint8_t &retx);

		void runArq(Sender &tx, Receiver &rx, Channel &channel);
	};
}
