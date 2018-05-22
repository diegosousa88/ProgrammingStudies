#include <iostream>
#include <thread>

using namespace std;


void addToBaseValueMultipleTimes(int &baseValue, int &value, int times)
{
    int lastBaseValue;
    cout << "This code is running on thread " << hash<thread::id>{}(this_thread::get_id()) << endl;
    for (int i = 0; i < times; ++i)
    {
        this_thread::sleep_for(chrono::seconds(2s));
        lastBaseValue = baseValue;
        baseValue += value;
        cout << lastBaseValue << " summed with " << value << endl;
    }
}

void changeValueAdded(int &valueAdded)
{
    cin >> valueAdded;
}

int main(int argc, char *argv[])
{
    int baseValue = 10;
    int valueAdded = 2;
    thread additionThread { addToBaseValueMultipleTimes, ref(baseValue), ref(valueAdded), 5 };
    thread changeValueThread { changeValueAdded, ref(valueAdded) };
    // cin >> valueAdded;
    // if (valueAdded != 2)
    //     cout << "Value added changed to " << valueAdded << " while sum loop was running" << endl;
    additionThread.join();
    changeValueThread.detach();

    if (valueAdded != 2)
        cout << "Value added changed to " << valueAdded << " while sum loop was running" << endl;

    cout << "This code is running on thread " << hash<thread::id>{}(this_thread::get_id()) << endl;
    cout << "Current value of base value is " << baseValue << endl; 

    return 0;
}