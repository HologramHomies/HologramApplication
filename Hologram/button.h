#ifndef BUTTON_H
#define BUTTON_H

#include <QString>

class button
{
private:
    int button_id;
    QString video_path;
    int brightness;
    int contrast;

public:
    // Constructor
    button(int, QString, int, int);

    // Button ID
    int get_button_id();
    void set_button_id(int);

    // Video Path
    QString get_video_path();
    void set_video_path(QString);

    // Brightness
    int get_brightness();
    void set_brightness(int);

    // Contrast
    int get_contrast();
    void set_contrast(int);
};
#endif // BUTTON_H
