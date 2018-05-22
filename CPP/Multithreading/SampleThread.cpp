#include <iostream>
#include <thread>

using namespace std;

void sendMessage()
{
    cout << "This code is running on thread " << hash<thread::id>{}(this_thread::get_id()) << endl;
    this_thread::sleep_for(chrono::seconds(10s));
}

int main(int argc, char *argv[])
{
    thread myThread { sendMessage };
    myThread.join();
    sendMessage();

    cin.get();
    return 0;
}