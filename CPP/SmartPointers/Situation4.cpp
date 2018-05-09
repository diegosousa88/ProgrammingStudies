#include <iostream>
#include <thread>
#include <memory>

using namespace std;

struct User
{
    User(const std::string &name, const unsigned int &phoneNumber)
    {
        m_name = name;
        m_phoneNumber = phoneNumber;

        cout << "User " << m_name << " was created with phone number " << m_phoneNumber << "." << endl;
    }

    ~User()
    {
        cout << "User " << m_name << " of phone number " << m_phoneNumber << " was destroyed." << endl;
    }

    void Call()
    {
        cout << m_name << " is being called on phone number " << m_phoneNumber << endl;
    }

    std::string m_name;
    unsigned int m_phoneNumber;
};

void myThreadWorkload(weak_ptr<User> userAsWeakPointerInsideThread)
{
    cout << "My thread started. User's reference count is " << userAsWeakPointerInsideThread.use_count() << endl;
    cout << "Waiting 2 seconds to release shared pointer..." << endl;
    // Waits 2 seconds to check if weak pointer expires.
    this_thread::sleep_for(chrono::seconds(2s));
    if (userAsWeakPointerInsideThread.expired())
        cout << "Shared pointer that refers to weak pointer expires" << endl;
}

int main()
{
    thread myThread;
    {
        shared_ptr<User> userAsSharedPointer = make_shared<User>("Diego", 551234567);
        myThread = thread(myThreadWorkload
            // It is important to cast shared pointer to weak in order to release shared pointer when this scope ends.
            // Otherwise, shared pointer will be retained.
            , weak_ptr<User>(userAsSharedPointer));
    }
    cout << "Shared pointer block ends and it was released" << endl;

    // Waits thread end its execution.
    myThread.join();

    return 0;
}