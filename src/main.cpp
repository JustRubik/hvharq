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

void printMenu()
{
    cout << "\n========================================================\n";
    cout << "   MO PHONG GIAO THUC ARQ VA HARQ - NHOM 10\n";
    cout << "========================================================\n";
    cout << "1. KB1: Kiem tra chuc nang (p=0 va p=1)\n";
    cout << "2. KB2: HARQ vuot troi o moi truong nhieu cao (p > 0.05)\n";
    cout << "3. KB3: Danh gia toan dien theo dai p (Sweep BER)\n";
    cout << "4. KB4: Kiem tra anh huong kich thuoc dau vao (Fixed p)\n";
    cout << "5. Chay TAT CA 4 kich ban\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "========================================================\n";
    cout << "Nhap lua chon cua ban (0-5): ";
}

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
    int choice;
    do
    {
        printMenu();
        cin >> choice;

        if (choice == 0)
        {
            cout << "Thoat chuong trinh. Tam biet!\n";
            break;
        }

        if (choice < 1 || choice > 5)
        {
            cout << "Lua chon khong hop le. Vui long chon lai!\n";
            continue;
        }

        uint32_t id = 1;
        string default_msg = "Hello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulatorHello HARQ simulator";

        // XỬ LÝ LỰA CHỌN TỪ MENU
        if (choice == 1 || choice == 5)
        {
            cout << "--> Dang chay KB1...\n";

            ofstream csv;
            uint32_t id = 1;

            openCsv(csv, "../csv/results_kb1.csv");

            runCore(
                csv,
                id,
                "KB1",
                "Default",
                default_msg,
                vector<double>{0.0, 1.0});

            csv.close();
        }

        if (choice == 2 || choice == 5)
        {
            cout << "--> Dang chay KB2...\n";

            ofstream csv;
            uint32_t id = 1;

            openCsv(csv, "../csv/results_kb2.csv");

            runCore(
                csv,
                id,
                "KB2",
                "Default",
                default_msg,
                vector<double>{0.05, 0.1, 0.15, 0.2, 0.3});

            csv.close();
        }

        if (choice == 3 || choice == 5)
        {
            cout << "--> Dang chay KB3...\n";

            ofstream csv;
            uint32_t id = 1;

            openCsv(csv, "../csv/results_kb3.csv");

            runCore(
                csv,
                id,
                "KB3",
                "Default",
                default_msg,
                vector<double>{0.0001, 0.001, 0.005, 0.01, 0.05, 0.1, 0.2});

            csv.close();
        }

        if (choice == 4 || choice == 5)
        {
            cout << "--> Dang chay KB4...\n";

            ofstream csv;
            uint32_t id = 1;

            openCsv(csv, "../csv/results_kb4.csv");

            double fixed_ber = 0.02;

            string base_msg = "Hello HARQ simulator";

            vector<TestCase> test_cases_kb4 =
                {
                    {"Size_Short", base_msg},
                    {"Size_Medium",
                     base_msg + base_msg + base_msg + base_msg + base_msg},
                    {"Size_Long", ""}};

            for (int i = 0; i < 15; i++)
            {
                test_cases_kb4[2].data += base_msg;
            }

            for (size_t i = 0; i < test_cases_kb4.size(); i++)
            {
                runCore(
                    csv,
                    id,
                    "KB4",
                    test_cases_kb4[i].label,
                    test_cases_kb4[i].data,
                    vector<double>{fixed_ber});
            }

            csv.close();
        }
    } while (choice != 0);

    return 0;
}