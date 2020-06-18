#include "dualshock.h"

Dualshock::Dualshock(const char *joystickPath, const char *touchpadPath, const char *motionPath)//TODO: Check if parameters leak memory.
{
    this->jfd = open(joystickPath, O_RDONLY | O_NONBLOCK);
    this->tfd = open(touchpadPath, O_RDONLY | O_NONBLOCK);
    this->mfd = open(motionPath, O_RDONLY | O_NONBLOCK);

    if (this->jfd == -1)
    {
        throw std::invalid_argument("Invalid joystickPath. Check for typos or check file "
                                    "permissions");
    }
    if (this->tfd == -1)
    {
        throw std::invalid_argument("Invalid touchpadPath. Check for typos or check file "
                                    "permissions");
    }
    if (this->mfd == -1)
    {
        throw std::invalid_argument("Invalid motionPath. Check for typos or check file "
                                    "permissions");
    }
    
    generateMaps();
}

Dualshock::~Dualshock()
{
    this->isPolling = false;
    //jsThread->join();
    //delete jsThread;
    //jsThread = nullptr;
    //Stops filestream from /dev/input
    close(jfd);
    close(tfd);
}

void Dualshock::startPolling()
{
    //error checking in case the controller is not connected and the coder tries to begin polling
    this->isPolling = true;
    //jsThread = new std::thread(&Dualshock::stopPolling, this);
    //jsThread = new std::thread(&Dualshock::readJoystick, this);
    this->readJoystick();
}

void Dualshock::stopPolling()
{
    this->isPolling = false;
}

void Dualshock::readJoystick()
{
    input_event js;

    while (this->isPolling)
    {
        //std::cout << this->jfd << &this->jfd << sizeof(this->jfd) << std::endl;
        int size = read(this->jfd, &js, sizeof(js));
        if (size != sizeof(js)) continue;

        std::string id = codes[js.code];

        switch (js.type)
        {
            case EV_KEY:
            {
                buttons[id].setState(js.value);
                break;
            }
            case EV_ABS:
            {
                char type = id[id.length() - 1];
                id = id.substr(0, id.length() - 1);
                if (id[0] == 'D') // if the event is a dpad
                {
                    writeDPAD(type, js.value);
                }
                else //the event is a genuine axis
                {
                    writeAxes(id, type, js.value);
                }  
            }
            default:
                break;
        }
        this->printOut();
    }
}

void Dualshock::writeDPAD(char type, int value)
{
    std::string direction1;
    std::string direction2;

    if (type == 'X')
    {
        direction1 = "RIGHT";
        direction2 = "LEFT";
    }
    else
    {
        value = -value; //inverted for you
        direction1 = "UP";
        direction2 = "DOWN";
    }

    switch (value)
    {
        case 1:
            buttons[direction1].setState(true);
            buttons[direction2].setState(false);
            break;
        case 0:
            buttons[direction1].setState(false);
            buttons[direction2].setState(false);
            break;
        case -1:
            buttons[direction1].setState(false);
            buttons[direction2].setState(true);
            break;
        default:
            break;
    }
}

void Dualshock::writeAxes(std::string id, char type, float value)
{
    float triggerValue = (float)value / (float)255;
    float axisValue = ((float)value - (float)127.5)/ (float)127.5; //makes it from -1 to 1

    switch (type) 
    {
        case 'X':
            axes[id].setX(axisValue);    
            break;
        case 'Y':
            axes[id].setY(-axisValue);
            break;
        case 'Z':
            triggers[id].setValue(triggerValue);
            break;
        default:
            break;
    }
}

void Dualshock::generateMaps()
{
    //create button unorderedmap
    for (int i = 0; i < buttonNames.size(); i++)
    {
        Button button = Button();
        buttons[buttonNames[i]] = button;
    }

    for (int i = 0; i < triggerNames.size(); i++)
    {
        Trigger trigger = Trigger();
        triggers[triggerNames[i]] = trigger;
    }
    for (int i = 0; i < axisNames.size(); i++)
    {
        Axis axis = Axis();
        axes[axisNames[i]] = axis;
    }

    
}

bool Dualshock::getButtonState(std::string id)
{
    Button button = buttons[id];
    return button.getState();
}

void Dualshock::printOut()
{
    for (int i = 0; i < buttonNames.size(); i++)
    {
        std::string name = buttonNames[i];
        bool state = Dualshock::getButtonState(name);
        std::cout << name << " : " << state << " | ";
    }
    for (int i = 0; i < axisNames.size(); i++)
    {
        std::string name = axisNames[i];
        Axis state = Dualshock::getAxis(name);
        std::cout << name << " : " << state.getX() << ", " << state.getY() <<" | ";
    }
    for (int i = 0; i < triggerNames.size(); i++)
    {
        std::string name = triggerNames[i];
        Trigger state = Dualshock::getTrigger(name);
        std::cout << name << " : " << state.getValue() << " | ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
}

Axis Dualshock::getAxis(std::string id)
{
    Axis axis = this->axes[id];
    return axis;
}

Trigger Dualshock::getTrigger(std::string id)
{
    Trigger trigger = this->triggers[id];
    return trigger;
}

/*
void Dualshock::readTouchpad(input_event *tp)
{
    size_t tpBytes;
    tpBytes = read(tfd, tp, sizeof(*tp));
    
    if (tpBytes == sizeof(*tp))
    {
        //updatevalues
    }
}*/