#ifndef RANDOMPULSE_H
#define RANDOMPULSE_H

#include <QObject>

#include "PulseModeEnum.h"

class RandomPulse : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pulse READ getPulse WRITE setPulse NOTIFY pulseChanged)
public:
    RandomPulse();
    QString getPulse();
    void setPulse(QString &newText);

    QString pulse;

    int generatePulse(PulseMode mode, int lastValue);

signals:
    void pulseChanged();
};

#endif // RANDOMPULSE_H
