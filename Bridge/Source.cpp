#include <iostream>

// La interfaz de "implementación" declara métodos comunes a
// todas las clases concretas de implementación.
class Device {
public:
    virtual bool isEnabled() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() = 0;
    virtual void setVolume(int percent) = 0;
    virtual int getChannel() = 0;
    virtual void setChannel(int channel) = 0;
};

// Todos los dispositivos siguen la misma interfaz.
class Tv : public Device {
private:
    bool enabled;
    int volume;
    int channel;

public:
    Tv() {
        enabled = false;
        volume = 50;
        channel = 1;
    }

    bool isEnabled() override {
        return enabled;
    }

    void enable() override {
        enabled = true;
    }

    void disable() override {
        enabled = false;
    }

    int getVolume() override {
        return volume;
    }

    void setVolume(int percent) override {
        volume = percent;
    }

    int getChannel() override {
        return channel;
    }

    void setChannel(int channel) override {
        this->channel = channel;
    }
};

class Radio : public Device {
private:
    bool enabled;
    int volume;
    int channel;

public:
    Radio() {
        enabled = false;
        volume = 30;
        channel = 100;
    }

    bool isEnabled() override {
        return enabled;
    }

    void enable() override {
        enabled = true;
    }

    void disable() override {
        enabled = false;
    }

    int getVolume() override {
        return volume;
    }

    void setVolume(int percent) override {
        volume = percent;
    }

    int getChannel() override {
        return channel;
    }

    void setChannel(int channel) override {
        this->channel = channel;
    }
};

// La "abstracción" define la interfaz para la parte de "control" de las dos jerarquías de clase.
// Mantiene una referencia a un objeto de la jerarquía de "implementación" y delega todo el trabajo real a este objeto.
class RemoteControl {
protected:
    Device* device;

public:
    RemoteControl(Device* device) {
        this->device = device;
    }

    void togglePower() {
        if (device->isEnabled()) {
            device->disable();
        }
        else {
            device->enable();
        }
    }

    void volumeDown() {
        device->setVolume(device->getVolume() - 10);
    }

    void volumeUp() {
        device->setVolume(device->getVolume() + 10);
    }

    void channelDown() {
        device->setChannel(device->getChannel() - 1);
    }

    void channelUp() {
        device->setChannel(device->getChannel() + 1);
    }
};

// Puedes extender clases de la jerarquía de abstracción independientemente de las clases de dispositivo.
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(Device* device) : RemoteControl(device) {}

    void mute() {
        device->setVolume(0);
    }
};

int main() {
    Tv tv;
    RemoteControl remote(&tv);
    remote.togglePower();

    Radio radio;
    AdvancedRemoteControl advancedRemote(&radio);
    advancedRemote.mute();

    return 0;
}
