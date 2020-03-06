#include "tmpbluetooth.h"

TmpBluetooth::TmpBluetooth(QObject *parent) : QObject(parent)
{
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;

    // Check if Bluetooth is available on this device
    if (localDevice.isValid()) {

        qInfo() << "valid";

        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();

        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Get connected devices
        QList<QBluetoothAddress> remotes;
        remotes = localDevice.connectedDevices();
    }
    else
        qWarning() << "ERROR isValid";
}
