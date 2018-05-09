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

int main()
{
    weak_ptr<User> userAsWeakPointer;
    {
        shared_ptr<User> userAsSharedPointer = make_shared<User>("Diego", 551234567);
        // Coping User struct release at the end of this scope to weak pointer.
        userAsWeakPointer = userAsSharedPointer;
    }

    // .expired member function checks if User's pointer was released, in this case, released by the end of scope above.
    if (userAsWeakPointer.expired())
        cout << "User smart pointer expires" << endl;
    else
    {
        shared_ptr<User> newUserAsSharedPointer = userAsWeakPointer.lock();
        newUserAsSharedPointer->Call();
    }

    // Weak pointer also has .use_count member function.
    // In this case, here we have 0 references.
    cout << userAsWeakPointer.use_count() << endl;

    return 0;
}