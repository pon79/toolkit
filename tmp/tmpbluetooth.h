#ifndef TMPBLUETOOTH_H
#define TMPBLUETOOTH_H

#include <QObject>
#include <QDebug>
#include <QBluetoothLocalDevice>

class TmpBluetooth : public QObject
{
    Q_OBJECT
public:
    explicit TmpBluetooth(QObject *parent = nullptr);

signals:

};

#endif // TMPBLUETOOTH_H
