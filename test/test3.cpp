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

// Struct hỗ trợ để lặp qua các chuỗi test khác nhau
struct TestCase {
    string label;
    string data;
};

int main()
{
    cout << "Simulating Kich ban 3 & 3.5, wait for a few seconds..." << endl;

    // Xuất ra file csv mới để không ghi đè kịch bản cũ
    ofstream csv("./csv/results_kb3_kb35.csv");

    // Bổ sung các cột: scenario, message_label, msg_length để dễ vẽ đồ thị
    csv << "ID,"
        << "scenario,"
        << "scheme,"
        << "message_label,"
        << "msg_length,"
        << "BER,"
        << "state,"
        << "total_frames,"
        << "retransmission,"
        << "time(ms),"
        << "efficiency,"
        << "throughput\n";

    uint32_t id = 1;

    // =========================================================================
    // KỊCH BẢN 3: KIỂM TRA TÍNH ĐỘC LẬP VỚI MẪU DỮ LIỆU (DATA PATTERN)
    // =========================================================================
    cout << "--> Running Kich ban 3: Data Pattern Independence..." << endl;

    // 10 mức BER khác nhau để quét dải nhiễu
    vector<double> ber_list_kb3 = {
        0.001, 0.005, 0.01, 0.015, 0.02, 
        0.025, 0.03, 0.04, 0.06, 0.08
    };

    // Tạo 2 chuỗi có CÙNG ĐỘ DÀI (100 ký tự) nhưng NỘI DUNG KHÁC NHAU
    string msg_pattern_1 = "";
    string msg_pattern_2 = "";
    for(int i = 0; i < 50; i++) {
        msg_pattern_1 += "01"; // Chuỗi xen kẽ
        msg_pattern_2 += "AA"; // Chuỗi ký tự cố định
    }

    vector<TestCase> test_cases_kb3 = {
        {"Pattern_01", msg_pattern_1},
        {"Pattern_AA", msg_pattern_2}
    };

    for (double ber : ber_list_kb3)
    {
        for (auto& tc : test_cases_kb3)
        {
            //-----------------------------------------
            // ARQ - Kịch bản 3
            //-----------------------------------------
            for (int i = 0; i < NUM_ITERATIONS; i++)
            {
                Sender tx; Receiver rx; Channel channel(ber); Protocols::Arq arq;
                
                tx.setData(tc.data);
                size_t total_frames = tx.segmentFrame().size();

                std::chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
                arq.runArq(tx, rx, channel);
                std::chrono::_V2::system_clock::time_point stop = chrono::high_resolution_clock::now();

                double time_ms = chrono::duration<double, milli>(stop - start).count();
                bool state = (tx.getData() == rx.getData());
                double efficiency = (double)tc.data.size() * 8 / (double)((total_frames + arq.getRetx()) * FRAME_SIZE);
                double throughput = time_ms > 0 ? ((double)tc.data.size() * 8) / time_ms : 0;

                csv << id++ << ",KB3,ARQ," << tc.label << "," << tc.data.size() << "," << ber << ","
                    << state << "," << total_frames << "," << (int)arq.getRetx() << ","
                    << time_ms << "," << efficiency << "," << throughput << '\n';
            }

            //-----------------------------------------
            // HARQ - Kịch bản 3
            //-----------------------------------------
            for (int i = 0; i < NUM_ITERATIONS; i++)
            {
                Sender tx; Receiver rx; Channel channel(ber); Protocols::Harq harq;

                tx.setData(tc.data);
                size_t total_frames = tx.segmentFrame().size();

                std::chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
                harq.runHarq(tx, rx, channel);
                std::chrono::_V2::system_clock::time_point stop = chrono::high_resolution_clock::now();

                double time_ms = chrono::duration<double, milli>(stop - start).count();
                bool state = (tx.getData() == rx.getData());
                double efficiency = (double)tc.data.size() * 8 / (double)((total_frames + harq.getRetx()) * FRAME_SIZE);
                double throughput = time_ms > 0 ? ((double)tc.data.size() * 8) / time_ms : 0;

                csv << id++ << ",KB3,HARQ," << tc.label << "," << tc.data.size() << "," << ber << ","
                    << state << "," << total_frames << "," << (int)harq.getRetx() << ","
                    << time_ms << "," << efficiency << "," << throughput << '\n';
            }
        }
    }

    // =========================================================================
    // KỊCH BẢN 3.5: KIỂM TRA SỰ PHỤ THUỘC VÀO KÍCH THƯỚC ĐẦU VÀO (INPUT SIZE)
    // =========================================================================
    cout << "--> Running Kich ban 3.5: Input Size Dependence..." << endl;

    double fixed_ber = 0.02; // Giữ nguyên một mức nhiễu cố định để dễ so sánh

    // Tạo các chuỗi có KÍCH THƯỚC KHÁC NHAU
    string base_msg = "Hello HARQ simulator";
    vector<TestCase> test_cases_kb35 = {
        {"Size_Short", base_msg},                                              // 20 bytes
        {"Size_Medium", base_msg + base_msg + base_msg + base_msg + base_msg}, // 100 bytes
        {"Size_Long", "" }                                                     // 300 bytes (tạo bằng loop)
    };
    for(int i = 0; i < 15; i++) test_cases_kb35[2].data += base_msg;

    for (auto& tc : test_cases_kb35)
    {
        // //-----------------------------------------
        // // ARQ - Kịch bản 3.5
        // //-----------------------------------------
        // for (int i = 0; i < NUM_ITERATIONS; i++)
        // {
        //     Sender tx; Receiver rx; Channel channel(fixed_ber); Protocols::Arq arq;
        //     tx.setData(tc.data);
        //     size_t total_frames = tx.segmentFrame().size();

        //     auto start = chrono::high_resolution_clock::now();
        //     arq.runArq(tx, rx, channel);
        //     auto stop = chrono::high_resolution_clock::now();

        //     double time_ms = chrono::duration<double, milli>(stop - start).count();
        //     bool state = (tx.getData() == rx.getData());
        //     double efficiency = (double)tc.data.size() * 8 / (double)((total_frames + arq.getRetx()) * FRAME_SIZE);
        //     double throughput = time_ms > 0 ? ((double)tc.data.size() * 8) / time_ms : 0;

        //     csv << id++ << ",KB3.5,ARQ," << tc.label << "," << tc.data.size() << "," << fixed_ber << ","
        //         << state << "," << total_frames << "," << (int)arq.getRetx() << ","
        //         << time_ms << "," << efficiency << "," << throughput << '\n';
        // }

        //-----------------------------------------
        // HARQ - Kịch bản 3.5
        //-----------------------------------------
        for (int i = 0; i < NUM_ITERATIONS; i++)
        {
            Sender tx; Receiver rx; Channel channel(fixed_ber); Protocols::Harq harq;
            tx.setData(tc.data);
            size_t total_frames = tx.segmentFrame().size();

            std::chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();
            harq.runHarq(tx, rx, channel);
            std::chrono::_V2::system_clock::time_point stop = chrono::high_resolution_clock::now();

            double time_ms = chrono::duration<double, milli>(stop - start).count();
            bool state = (tx.getData() == rx.getData());
            double efficiency = (double)tc.data.size() * 8 / (double)((total_frames + harq.getRetx()) * FRAME_SIZE);
            double throughput = time_ms > 0 ? ((double)tc.data.size() * 8) / time_ms : 0;

            csv << id++ << ",KB3.5,HARQ," << tc.label << "," << tc.data.size() << "," << fixed_ber << ","
                << state << "," << total_frames << "," << (int)harq.getRetx() << ","
                << time_ms << "," << efficiency << "," << throughput << '\n';
        }
    }

    csv.close();

    cout << "Simulation completed.\n";
    cout << "Results saved to results_kb3_kb35.csv\n";
    return 0;
}