#ifndef VIDEO_CONFIG_H
#define VIDEO_CONFIG_H


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
    video_config(newButton_id, newVideo_path, newBrightness, newContrast, newStart_pos, newEnd_pos);

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
