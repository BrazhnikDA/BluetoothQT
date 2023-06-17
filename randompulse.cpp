#include "randompulse.h"

RandomPulse::RandomPulse()
{

}

QString RandomPulse::getPulse()
{
    return this->pulse;
}

void RandomPulse::setPulse(QString &newText)
{
    this->pulse = newText;
}

int RandomPulse::generatePulse(PulseMode mode, int lastValue)
{
    switch (mode) {
    case StateOfRest:
        return (lastValue - 2) + rand() % (lastValue + 2);
        break;
    case LightActivity:
        return 1;
        break;
    case NormalActivity:
        return 2;
        break;
    case Workout:
        return 3;
        break;
    case HeavyTraining:
        return 4;
        break;

    }
}
