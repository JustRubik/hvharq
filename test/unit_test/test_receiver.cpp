// test_receiver.cpp

#include <iostream>

#include "..\include\config.h"
#include "..\include\helper.h"
#include "..\include\sender.h"
#include "..\include\receiver.h"

int main()
{
	Sender sd;
	Receiver rc;

	//-----------------------------------
	// Original message
	//-----------------------------------
	sd.setData("Hello");

	//-----------------------------------
	// Sender side
	//-----------------------------------
	std::vector<Frame> frames =
		sd.segmentFrame();

	std::vector<Frame> crcFrames = sd.CRC(frames);

	std::vector<Frame> ccFrames =
		sd.convolutionEncode(frames);

	//-----------------------------------
	// Receiver side
	//-----------------------------------
	std::vector<Frame> decodedFrames;

	std::vector<Frame> viterbiFrames = rc.viterbi(ccFrames);

	for (Frame frame : viterbiFrames)
	{
		if (rc.checkCRC(frame))
		{
			decodedFrames.push_back(rc.removeCRCperFrame(frame));
		}

		else
		{
			std::cout
				<< "CRC failed\n";
		}
	}

	//-----------------------------------
	// Reconstruct message
	//-----------------------------------
	// std::string recovered =
	// 	rc.combineFrames(decoded_frames);

	//-----------------------------------
	// Result
	//-----------------------------------
	std::string recovered = rc.combineFrames(decodedFrames);

	std::cout
		<< "Original : "
		<< sd.getData()
		<< '\n';

	std::cout
		<< "Recovered: "
		<< recovered
		<< '\n';

	if (sd.getData() == recovered)
	{
		std::cout
			<< "\nPASS\n";
	}
	else
	{
		std::cout
			<< "\nFAIL\n";
	}

	return 0;
}
