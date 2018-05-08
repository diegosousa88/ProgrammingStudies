#include <iostream>

using namespace std;

template<typename T>
class StateBase
{
public:
    void getState() 
    {
        static_cast<T *>(this)->getState();
    }
};

template<typename T>
static void callGetState(StateBase<T> state)
{
    state.getState();
}

class EnabledState : public StateBase<EnabledState>
{
public:
    void getState()
    {
        cout << "Enabled state called" << endl;
    }
};

class DisabledState : public StateBase<DisabledState>
{
public:
    void getState()
    {
        cout << "Disabled state called" << endl;
    }
};

class UndefinedState : public StateBase<UndefinedState>
{
public:
    void getState()
    {
        cout << "Undefined state called" << endl;
    }
};

int main()
{
    EnabledState enabledState;
    DisabledState disabledState;
    UndefinedState undefinedState;

    callGetState(enabledState);
    callGetState(disabledState);
    callGetState(undefinedState);

    return 0;
}