#include <string>

#include "..\include\protocols.h"

const std::uint8_t &Protocols::Harq::getRetx() const
{
	return retx;
}
void Protocols::Harq::setRetx(const std::uint8_t &retx)
{
	this->retx += retx;
}

const std::uint8_t &Protocols::Arq::getRetx() const
{
	return retx;
}
void Protocols::Arq::setRetx(const std::uint8_t &retx)
{
	this->retx += retx;
}

void Protocols::Harq::runHarq(Sender &tx, Receiver &rx, Channel &channel)
{
	// ----------------------------------
	// Sender side
	// ----------------------------------
	std::vector<Frame> frames = tx.segmentFrame();
	frames = tx.CRC(frames);
	frames = tx.convolutionEncode(frames);

	// ----------------------------------
	// Truyền từng frame
	// ----------------------------------
	for (size_t i = 0; i < frames.size(); i++)
	{
		uint8_t retx_count = 0;
		bool ACK = false;

		while (!ACK && retx_count <= MAX_RETX)
		{
			//----------------------------------
			// Kênh truyền gây lỗi
			//----------------------------------
			Frame received_bits = channel.transmit(frames[i]);

			//----------------------------------
			// Viterbi decode
			//----------------------------------
			std::vector<Frame> temp = {received_bits};
			std::vector<Frame> decoded = rx.viterbi(temp);

			//----------------------------------
			// Kiểm tra CRC
			//----------------------------------
			if (rx.checkCRC(decoded[0]))
			{
				// ACK
				Frame payload = rx.removeCRCperFrame(decoded[0]);

				std::string msg =
					Helper::bitsToString(payload);

				rx.appendData(msg);

				ACK = true;
				rx.setFrames(1);
			}
			else
			{
				// NACK
				retx_count++;
			}
		}

		Protocols::Harq::setRetx(retx_count);
	}
}

void Protocols::Arq::runArq(
	Sender &tx,
	Receiver &rx,
	Channel &channel)
{
	//-----------------------------------
	// Sender side
	//-----------------------------------
	std::vector<Frame> frames = tx.segmentFrame();
	frames = tx.CRC(frames);

	//-----------------------------------
	// Transmission
	//-----------------------------------
	for (size_t i = 0; i < frames.size(); i++)
	{
		bool ACK = false;
		uint8_t retx_count = 0;

		while (!ACK && retx_count <= MAX_RETX)
		{
			//-----------------------------------
			// Channel
			//-----------------------------------
			Frame received = channel.transmit(frames[i]);

			//-----------------------------------
			// CRC check
			//-----------------------------------
			if (rx.checkCRC(received))
			{
				//-----------------------------------
				// ACK
				//-----------------------------------
				Frame payload =
					rx.removeCRCperFrame(received);

				rx.appendData(
					Helper::bitsToString(payload));

				ACK = true;
				rx.setFrames(1);
			}
			else
			{
				//-----------------------------------
				// NACK
				//-----------------------------------
				retx_count++;
			}
		}

		Arq::setRetx(retx_count);
	}
}