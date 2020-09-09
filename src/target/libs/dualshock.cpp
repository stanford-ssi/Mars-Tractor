/** @file dualshock.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date July 2020
 */

#include <dualshock.hpp>

Dualshock::Dualshock(const std::string& joystickPath, const std::string& touchpadPath,
                     const std::string& motionPath) // TODO: Check if parameters leak memory.
{
    const char* jsPath = joystickPath.c_str();
    const char* tpPath = touchpadPath.c_str();
    const char* moPath = motionPath.c_str();

    this->jfd = open(jsPath, O_RDWR | O_NONBLOCK);
    this->tfd = open(tpPath, O_RDONLY | O_NONBLOCK);
    this->mfd = open(moPath, O_RDONLY | O_NONBLOCK);

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
    saveRumble();
}

Dualshock::Dualshock()
{
    int fd = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
    int num = 0;
    int numPaths = 0;

    char name[256] = "Unknown";

    while (fd != -1)
    {
        ioctl(fd, EVIOCGNAME(sizeof(name)), name);

        // is it the one im lookin for
        if (this->isPath(name, fd))
        {
            numPaths++;
            if (numPaths == 3)
            {
                generateMaps();
                saveRumble();
                return;
            }
        }
        else
        {
            close(fd);
        }

        // get next path
        std::string path = "/dev/input/event";
        num++;
        path = path + std::to_string(num);

        const char* fullPath = path.c_str();
        fd = open(fullPath, O_RDWR | O_NONBLOCK);
    }

    throw std::logic_error("No controller found.");
}

bool Dualshock::isPath(char name[256], int fd)
{

    std::string str = name;
    std::string tpName = "Wireless Controller Touchpad";
    std::string jsName = "Wireless Controller";
    std::string moName = "Wireless Controller Motion Sensors";

    if (str == jsName)
    {
        jfd = fd;
    }
    else if (str == tpName)
    {
        tfd = fd;
    }
    else if (str == moName)
    {
        mfd = fd;
    }
    else
    {
        return false;
    }
    return true;
}

Dualshock::~Dualshock()
{
    // this->isPolling = false;
    freeRumble();
    this->stopPolling();
    close(jfd);
    close(tfd);
}

void Dualshock::startPolling()
{
    // error checking in case the controller is not connected and the coder tries to begin polling
    this->isPolling = true;
    this->jsThread = std::thread(&Dualshock::readJoystick, this);
    this->moThread = std::thread(&Dualshock::readMotion, this);
}

void Dualshock::stopPolling()
{
    this->isPolling = false;
    if (this->jsThread.joinable()) this->jsThread.join();
    if (this->moThread.joinable()) this->moThread.join();
    // this->jsThread.join();
}
void Dualshock::writeMotion(std::string id, std::string code, int value)
{
    char type = code[code.length() - 1];
    switch (type)
    {
    case ('X'):
        motions[id].setX(value);
        break;
    case ('Y'):
        motions[id].setY(value);
        break;
    case ('Z'):
        motions[id].setZ(value);
        break;
    default:
        break;
    }
}

void Dualshock::readMotion()
{
    input_event mo;
    int maxL = 32768;
    int maxR = 2097152;

    while (this->isPolling)
    {
        int size = read(this->mfd, &mo, sizeof(mo));
        if (size != sizeof(mo)) continue;

        std::string id = codes2[mo.code];

        switch (mo.type)
        {
        case EV_ABS:
        {
            if (id.length() == 1) // left
            {
                int value = 180 * (mo.value + maxL) / maxL; // sets value to degrees
                writeMotion("A", id, value);
            }
            else // right
            {
                int value = 180 * (mo.value + maxR) / (maxR);
                writeMotion("B", id, value);
            }
        }
        default:
            break;
        }
        this->printOut();
    }
}
/*
void Dualshock::readTouchpad()
{
    input_event tp;

    size_t tpBytes;
    tpBytes = read(tfd, tp, sizeof(*tp));

    if (tpBytes == sizeof(*tp))
    {
        //updatevalues
    }
}
*/
void Dualshock::readJoystick()
{
    input_event js;

    while (this->isPolling)
    {
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
            else // the event is a genuine axis
            {
                writeAxes(id, type, js.value);
            }
        }
        default:
            break;
        }
        // this->printOut();
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
        value = -value; // inverted for you
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

void Dualshock::writeAxes(const std::string& id, char type, float value)
{
    float triggerValue = (float)value / (float)255;
    float axisValue = ((float)value - (float)127.5) / (float)127.5; // makes it from -1 to 1

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
    // create button unorderedmap
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

    for (int i = 0; i < axisNames.size(); i++)
    {
        Motion motion = Motion();
        motions[motionNames[i]] = motion;
    }
}

Button Dualshock::getButton(const std::string& id)
{
    if (!buttons.count(id))
    {
        throw std::invalid_argument("Invalid ID.");
    }
    return buttons[id];
}

bool Dualshock::getButtonState(const std::string& id)
{
    if (!buttons.count(id))
    {
        throw std::invalid_argument("Invalid ID.");
    }
    Button button = buttons[id];
    return button.getState();
}

Motion Dualshock::getMotion(const std::string& id)
{
    if (!motions.count(id))
    {
        throw std::invalid_argument("Invalid ID.");
    }
    return motions[id];
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
        std::cout << name << " : " << state.getX() << ", " << state.getY() << " | ";
    }
    for (int i = 0; i < triggerNames.size(); i++)
    {
        std::string name = triggerNames[i];
        Trigger state = Dualshock::getTrigger(name);
        std::cout << name << " : " << state.getValue() << " | ";
    }
    for (int i = 0; i < motionNames.size(); i++)
    {
        std::string name = motionNames[i];
        Motion state = Dualshock::getMotion(name);
        std::cout << name << " : " << state.getX() << ", " << state.getY() << ", " << state.getZ()
                  << " | ";
    }
    std::cout << std::endl;
    std::cout << "---------------------------------------------------------------------------------"
                 "-------------------------"
              << std::endl;
}

Axis Dualshock::getAxis(const std::string& id)
{
    if (!axes.count(id))
    {
        throw std::invalid_argument("Invalid ID;");
    }
    Axis axis = this->axes[id];
    return axis;
}

Trigger Dualshock::getTrigger(const std::string& id)
{
    if (!triggers.count(id))
    {
        throw std::invalid_argument("Invalid ID;");
    }
    Trigger trigger = this->triggers[id];
    return trigger;
}

float Dualshock::getTriggerValue(const std::string& id)
{
    if (!triggers.count(id))
    {
        throw std::invalid_argument("Invalid ID;");
    }
    return triggers[id].getValue();
}

void Dualshock::rumble(int duration)
{
    input_event play;
    input_event stop;
    play.type = EV_FF;
    play.code = this->effect.id;
    play.value = 1;

    write(jfd, (const void*)&play, sizeof(play));

    sleep(duration);

    /* Stop an this->effect */
    stop.type = EV_FF;
    stop.code = this->effect.id;
    stop.value = 0;

    write(jfd, &stop, sizeof(stop));
}

void Dualshock::saveRumble()
{
    this->effect.type = FF_PERIODIC;
    this->effect.id = -1;
    this->effect.u.periodic.waveform = FF_SINE;
    this->effect.u.periodic.period = 1000;      /* 0.1 second */
    this->effect.u.periodic.magnitude = 0x7fff; /* 0.5 * Maximum magnitude */
    this->effect.u.periodic.offset = 0;
    this->effect.u.periodic.phase = 0;
    this->effect.direction = 0x4000; /* Along X axis */
    this->effect.u.periodic.envelope.attack_length = 1000;
    this->effect.u.periodic.envelope.attack_level = 0x7fff;
    this->effect.u.periodic.envelope.fade_length = 1000;
    this->effect.u.periodic.envelope.fade_level = 0x7fff;
    this->effect.trigger.button = 0;
    this->effect.trigger.interval = 0;
    this->effect.replay.length = 20000; /* 20 seconds */
    this->effect.replay.delay = 1000;

    int check = ioctl(jfd, EVIOCSFF, &this->effect);
    std::cout << check << "|" << this->effect.id << std::endl;
}

void Dualshock::freeRumble()
{
    int check = ioctl(jfd, EVIOCRMFF, this->effect.id);
    std::cout << check << std::endl;
}

std::string Dualshock::serialize()
{
    Json::Value gamepad;

    gamepad["x_button"] = getButtonState("X");
    gamepad["dpad_down"] = getButtonState("");
    gamepad["dpad_up"] = getButtonState("UP");
    gamepad["dpad_down"] = getButtonState("DOWN");
    gamepad["dpad_left"] = getButtonState("LEFT");
    gamepad["dpad_right"] = getButtonState("RIGHT");
    gamepad["home"] = getButtonState("PS");
    gamepad["o_button"] = getButtonState("O");
    gamepad["triangle_button"] = getButtonState("TRIANGLE");
    gamepad["square_button"] = getButtonState("SQUARE");
    gamepad["left_bumper"] = getButtonState("LB");
    gamepad["right_bumper"] = getButtonState("RB");
    gamepad["left_trigger"] = getButtonState("LT");
    gamepad["right_trigger"] = getButtonState("RT");
    gamepad["share"] = getButtonState("SHARE");
    gamepad["options"] = getButtonState("OPTIONS");
    gamepad["left_stick_pressed"] = getButtonState("LJSB");
    gamepad["right_stick_pressed"] = getButtonState("RJSB");

    return "";
}