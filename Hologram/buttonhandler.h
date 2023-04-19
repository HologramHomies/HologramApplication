#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H
#include <QObject>
#include <QThread>

class ButtonHandler : public QObject
{
    Q_OBJECT
public:
    ButtonHandler(QObject* parent = nullptr);
    void listenToButtons();

signals:
    void buttonPressed(int buttonId);

};

#endif // BUTTONHANDLER_H
