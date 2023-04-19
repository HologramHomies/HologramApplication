#include "video_config.h"

int video_config::getButton_id() const
{
    return button_id;
}

void video_config::setButton_id(int newButton_id)
{
    button_id = newButton_id;
}

QString video_config::getVideo_path() const
{
    return video_path;
}

void video_config::setVideo_path(const QString &newVideo_path)
{
    video_path = newVideo_path;
}

int video_config::getBrightness() const
{
    return brightness;
}

void video_config::setBrightness(int newBrightness)
{
    brightness = newBrightness;
}

int video_config::getContrast() const
{
    return contrast;
}

void video_config::setContrast(int newContrast)
{
    contrast = newContrast;
}

int video_config::getStart_pos() const
{
    return start_pos;
}

void video_config::setStart_pos(int newStart_pos)
{
    start_pos = newStart_pos;
}

int video_config::getEnd_pos() const
{
    return end_pos;
}

void video_config::setEnd_pos(int newEnd_pos)
{
    end_pos = newEnd_pos;
}

video_config::video_config(int newButton_id, QString newVideo_path, int newBrightness, int newContrast, int newStart_pos, int newEnd_pos)
{
    button_id = newButton_id;
    video_path = newVideo_path;
    brightness = newBrightness;
    contrast = newContrast;
    start_pos = newStart_pos;
    end_pos = newEnd_pos;
}
