#include <iostream>
#include <fstream>
#include <chrono>

#include "../include/config.h"
#include "../include/helper.h"
#include "../include/sender.h"
#include "../include/receiver.h"
#include "../include/channel.h"
#include "../include/protocols.h"

using namespace std;

int main()
{
	cout << "Simulating, wait for a few seconds..." << endl;

	ofstream csv("./csv/test2.csv");

	csv << "ID,"
		<< "scheme,"
		<< "BER,"
		<< "frame_size,"
		<< "crc_size,"
		<< "state,"
		<< "total_frames,"
		<< "retransmission,"
		<< "time(ms),"
		<< "efficiency,"
		<< "throughput\n";

	uint32_t id = 1;

	vector<double> BER_list =
		{
			0.0001,
			0.001,
			0.2,
			0.3,
			0.4};

	string message =
		"Hello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulator"; // Hello HARQ simulator x10

	//-----------------------------------------
	// chạy với từng BER
	//-----------------------------------------
	for (double ber : BER_list)
	{
		//-----------------------------------------
		// ARQ
		//-----------------------------------------
		for (int i = 0; i < NUM_ITERATIONS; i++)
		{
			Sender tx;
			Receiver rx;
			Channel channel(ber);
			Protocols::Arq arq;

			tx.setData(message);

			size_t total_frames =
				tx.segmentFrame().size();

			std::chrono::_V2::system_clock::time_point start =
				chrono::high_resolution_clock::now();

			arq.runArq(tx, rx, channel);

			std::chrono::_V2::system_clock::time_point stop =
				chrono::high_resolution_clock::now();

			double time_ms =
				chrono::duration<double, milli>(stop - start).count();

			bool state =
				(tx.getData() == rx.getData());

			double efficiency =
				(double)message.size() * 8 /
				(double)((total_frames + arq.getRetx()) * FRAME_SIZE);

			double throughput =
				((double)message.size() * 8) / time_ms;

			csv
				<< id++ << ","
				<< "ARQ,"
				<< ber << ","
				<< state << ","
				<< total_frames << ","
				<< (int)arq.getRetx() << ","
				<< time_ms << ","
				<< efficiency << ","
				<< throughput
				<< '\n';
		}

		//-----------------------------------------
		// HARQ
		//-----------------------------------------
		for (int i = 0; i < NUM_ITERATIONS; i++)
		{
			Sender tx;
			Receiver rx;
			Channel channel(ber);
			Protocols::Harq harq;

			tx.setData(message);

			size_t total_frames =
				tx.segmentFrame().size();

			auto start =
				chrono::high_resolution_clock::now();

			harq.runHarq(tx, rx, channel);

			auto stop =
				chrono::high_resolution_clock::now();

			double time_ms =
				chrono::duration<double, milli>(stop - start).count();

			bool state =
				(tx.getData() == rx.getData());

			double efficiency =
				(double)message.size() * 8 /
				(double)((total_frames + harq.getRetx()) * FRAME_SIZE);

			double throughput =
				((double)message.size() * 8) / time_ms;

			csv
				<< id++ << ","
				<< "HARQ,"
				<< ber << ","
				<< state << ","
				<< total_frames << ","
				<< (int)harq.getRetx() << ","
				<< time_ms << ","
				<< efficiency << ","
				<< throughput
				<< '\n';
		}
	}

	csv.close();

	cout << "Simulation completed.\n";
	cout << "Results saved to results.csv\n";

	return 0;
}