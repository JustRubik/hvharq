#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

#include "../include/config.h"
#include "../include/helper.h"
#include "../include/sender.h"
#include "../include/receiver.h"
#include "../include/channel.h"
#include "../include/protocols.h"

using namespace std;

// Cấu trúc hỗ trợ KB4
struct TestCase
{
	string label;
	string data;
};

void openCsv(ofstream &csv, string filename)
{
	csv.open(filename.c_str(), ios::app);

	csv.seekp(0, ios::end);

	if (csv.tellp() == 0)
	{
		csv << "ID,scenario,scheme,message_label,msg_length,BER,state,total_frames,retransmission,time(ms),efficiency,throughput\n";
	}
}

void runArqExperiment(
	ofstream &csv,
	uint32_t &id,
	string scenario,
	string label,
	string msg,
	double ber)
{
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		Sender tx;
		Receiver rx;
		Channel channel(ber);
		Protocols::Arq arq;

		tx.setData(msg);

		size_t total_frames = tx.segmentFrame().size();

		auto start = chrono::high_resolution_clock::now();

		arq.runArq(tx, rx, channel);

		auto stop = chrono::high_resolution_clock::now();

		double time_ms =
			chrono::duration<double, milli>(stop - start).count();

		bool state = (tx.getData() == rx.getData());

		double efficiency =
			(double)(msg.size() * 8) / ((total_frames + arq.getRetx()) * FRAME_SIZE);

		double throughput =
			(time_ms > 0)
				? (msg.size() * 8.0 / time_ms)
				: 0;

		csv << id++ << ","
			<< scenario << ","
			<< "ARQ,"
			<< label << ","
			<< msg.size() << ","
			<< ber << ","
			<< state << ","
			<< total_frames << ","
			<< (int)arq.getRetx() << ","
			<< time_ms << ","
			<< efficiency << ","
			<< throughput
			<< '\n';
	}
}

void runHarqExperiment(
	ofstream &csv,
	uint32_t &id,
	string scenario,
	string label,
	string msg,
	double ber)
{
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		Sender tx;
		Receiver rx;
		Channel channel(ber);
		Protocols::Harq harq;

		tx.setData(msg);

		size_t total_frames = tx.segmentFrame().size();

		auto start = chrono::high_resolution_clock::now();

		harq.runHarq(tx, rx, channel);

		auto stop = chrono::high_resolution_clock::now();

		double time_ms =
			chrono::duration<double, milli>(stop - start).count();

		bool state = (tx.getData() == rx.getData());

		double efficiency =
			(double)(msg.size() * 8) / ((total_frames + harq.getRetx()) * FRAME_SIZE);

		double throughput =
			(time_ms > 0)
				? (msg.size() * 8.0 / time_ms)
				: 0;

		csv << id++ << ","
			<< scenario << ","
			<< "HARQ,"
			<< label << ","
			<< msg.size() << ","
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

void runCore(
	ofstream &csv,
	uint32_t &id,
	string scenario,
	string label,
	string msg,
	vector<double> ber_list)
{
	for (size_t i = 0; i < ber_list.size(); i++)
	{
		double ber = ber_list[i];

		runArqExperiment(
			csv,
			id,
			scenario,
			label,
			msg,
			ber);

		runHarqExperiment(
			csv,
			id,
			scenario,
			label,
			msg,
			ber);
	}
}

int main()
{
	string default_msg = "Hello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulator";

	cout << "--> Dang chay KB5...\n";

	ofstream csv;
	uint32_t id = 1;

	openCsv(csv, "./csv/results_kb5_fs80.csv");

	double fixed_ber = 1e-4;

	string base_msg = "Hello HARQ simulator";

	vector<TestCase> test_cases_kb5 =
		{
			{"Size_Short", base_msg},
			{"Size_Medium",
			 base_msg + base_msg + base_msg + base_msg + base_msg},
			{"Size_Long", ""}};

	for (int i = 0; i < 15; i++)
	{
		test_cases_kb5[2].data += base_msg;
	}

	for (size_t i = 0; i < test_cases_kb5.size(); i++)
	{
		runCore(
			csv,
			id,
			"KB5",
			test_cases_kb5[i].label,
			test_cases_kb5[i].data,
			vector<double>{fixed_ber});
	}

	csv.close();
	cout << "Hoan thanh KB5\n";

	return 0;
}