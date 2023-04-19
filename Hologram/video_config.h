#ifndef VIDEO_CONFIG_H
#define VIDEO_CONFIG_H

#include <QString>

class video_config
{
private:
    int button_id;
    QString video_path;
    int brightness;
    int contrast;
    int start_pos;
    int end_pos;

public:
    video_config(int newButton_id, QString newVideo_path, int newBrightness, int newContrast, int newStart_pos, int newEnd_pos);
    ~video_config();

    int getButton_id() const;
    void setButton_id(int newButton_id);
    QString getVideo_path() const;
    void setVideo_path(const QString &newVideo_path);
    int getBrightness() const;
    void setBrightness(int newBrightness);
    int getContrast() const;
    void setContrast(int newContrast);
    int getStart_pos() const;
    void setStart_pos(int newStart_pos);
    int getEnd_pos() const;
    void setEnd_pos(int newEnd_pos);
};

#endif // VIDEO_CONFIG_H
