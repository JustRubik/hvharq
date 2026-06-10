#include <iostream>

#include "../include/config.h"
#include "../include/helper.h"
#include "../include/sender.h"
#include "../include/receiver.h"
#include "../include/channel.h"
#include "../include/protocols.h"

int main()
{
	Protocols::Arq arq;
	Sender tx;
	Receiver rx;
	Channel channel(BER);

	tx.setData("HelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubikHelloHieuRubik"); // HelloHieuRubik x20

	std::cout << "Input message:\n"
			  << tx.getData() << "\n\n";

	std::vector<Frame> frames = tx.segmentFrame();

	std::cout << "Segmented frames:\n";
	for (Frame &frame : frames)
	{
		for (Bit &bit : frame)
			std::cout << static_cast<int>(bit);
		std::cout << "\n";
	}

	std::cout << '\n';

	frames = tx.CRC(frames);

	std::cout << "Frames after CRC:\n";
	for (Frame &frame : frames)
	{
		// Helper::printBits(frame);

		for (Bit &bit : frame)
			std::cout << static_cast<int>(bit);
		std::cout << "\n";
	}

	std::cout << '\n';

	frames = tx.convolutionEncode(frames);

	std::cout << "Frames after convolution encode:\n";
	for (Frame &frame : frames)
	{
		for (Bit &bit : frame)
			std::cout << static_cast<int>(bit);
		std::cout << "\n";
	}

	std::cout << '\n';

	//-----------------------------------
	// Arq
	//-----------------------------------
	arq.runArq(tx, rx, channel);

	std::cout << "Recovered message:\n";
	std::cout << rx.getData() << '\n';

	if (tx.getData() == rx.getData())
	{
		std::cout << "\nPASS\n";
	}
	else
	{
		std::cout << "\nFAIL\n";
	}

	std::cout << static_cast<int>(arq.getRetx()) << "\n";

	return 0;
}