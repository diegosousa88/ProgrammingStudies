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
    // Creating User struct as shared pointer.
    shared_ptr<User> userAsSharedPointer = make_shared<User>("Diego", 551234567);
    userAsSharedPointer->Call();
 
    // Coping User struct as weak pointer.
    weak_ptr<User> userAsWeakPointer = userAsSharedPointer;
    // This line below will cause an error. Weak pointers does not allow direct access to object instance.
    // userAsWeakPointer->Call();

    // .lock member function will allow me to recreate weak pointer to shared pointer to use it.
    // In this point I have two shared pointers pointing to the same block of memory.
    shared_ptr<User> newUserAsSharedPointer = userAsWeakPointer.lock();
    newUserAsSharedPointer->Call();

    // .reset member function will release shared pointer, so now I just have only one shared pointer in use.
    newUserAsSharedPointer.reset();

    cout << userAsSharedPointer.use_count() << endl;

    return 0;
}