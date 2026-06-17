#include "..\include\receiver.h"
#include "..\include\config.h"
#include "..\include\helper.h"

const std::string &Receiver::getData() const
{
	return data;
}

void Receiver::setData(const std::string &data)
{
	this->data = data;
}

const size_t &Receiver::getFrames() const
{
	return total_frames_rx;
}

void Receiver::setFrames(const size_t &frames)
{
	this->total_frames_rx += frames;
}

void Receiver::appendData(const std::string &data)
{
	this->data.append(data);
}

bool Receiver::checkCRC(Frame &frame)
{
	if (frame.size() < 8)
		return false;

	Frame payload(
		frame.begin(),
		frame.end() - 8);

	uint8_t crc_calc = Helper::computeCRC8(payload);

	uint8_t crc_recv = 0;

	for (size_t i = frame.size() - 8; i < frame.size(); ++i)
	{
		crc_recv <<= 1;
		crc_recv |= frame[i];
	}

	return crc_calc == crc_recv;
}

Frame Receiver::removeCRCperFrame(Frame &frame)
{
	return Frame(
		frame.begin(),
		frame.end() - 8);
}

std::vector<Frame> Receiver::removeCRC(std::vector<Frame> &frames)
{
	std::vector<Frame> outputs;

	outputs.reserve(frames.size());

	for (Frame &frame : frames)
	{
		outputs.push_back(frame);
	}

	return outputs;
}

std::vector<Frame> Receiver::viterbi(
	std::vector<Frame> &inputs)
{
	std::vector<Frame> outputs;

	outputs.reserve(inputs.size());

	const int NUM_STATES = 4;
	const int INF = 1e9;

	for (Frame &input : inputs)
	{
		int steps = input.size() / 2;

		std::vector<std::vector<int>> metric(
			steps + 1,
			std::vector<int>(NUM_STATES, INF));

		std::vector<std::vector<int>> prev_state(
			steps + 1,
			std::vector<int>(NUM_STATES, -1));

		std::vector<std::vector<Bit>> prev_bit(
			steps + 1,
			std::vector<Bit>(NUM_STATES, 0));

		// encoder starts at state 00
		metric[0][0] = 0;

		for (int t = 0; t < steps; ++t)
		{
			Bit r1 = input[2 * t];
			Bit r2 = input[2 * t + 1];

			for (int state = 0; state < NUM_STATES; ++state)
			{
				if (metric[t][state] == INF)
					continue;

				Bit m1 = (state >> 1) & 1;
				Bit m0 = state & 1;

				for (Bit bit = 0; bit <= 1; ++bit)
				{
					Bit x0 = bit;
					Bit x1 = m1;
					Bit x2 = m0;

					// generators 111 and 101
					Bit y1 = x0 ^ x1 ^ x2;
					Bit y2 = x0 ^ x2;

					int branch_metric =
						(r1 != y1) +
						(r2 != y2);

					int next_state =
						(bit << 1) | m1;

					int new_metric =
						metric[t][state] + branch_metric;

					if (new_metric < metric[t + 1][next_state])
					{
						metric[t + 1][next_state] = new_metric;
						prev_state[t + 1][next_state] = state;
						prev_bit[t + 1][next_state] = bit;
					}
				}
			}
		}

		// find best final state
		int best_state = 0;

		for (int state = 1; state < NUM_STATES; ++state)
		{
			if (metric[steps][state] <
				metric[steps][best_state])
			{
				best_state = state;
			}
		}

		// traceback
		Frame output(steps);

		int state = best_state;

		for (int t = steps; t > 0; --t)
		{
			output[t - 1] = prev_bit[t][state];
			state = prev_state[t][state];
		}

		outputs.push_back(output);
	}

	return outputs;
}

std::string Receiver::combineFrames(std::vector<Frame> &frames)
{
	std::string out;
	for (Frame &frame : frames)
	{
		out.append(Helper::bitsToString(frame));
	}

	return out;
}