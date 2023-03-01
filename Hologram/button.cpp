#include "button.h"
#include <string>

button::button(int button_id_, QString video_path_, int contrast_, int brightness_)
{
    button_id = button_id_;
    video_path = video_path_;
    brightness = brightness_;
    contrast = contrast_;

}

/***************************************
 * Video path setters and getters
 * ************************************/
QString button::get_video_path(){
    return video_path;
}

void button::set_video_path(QString video_path_){
    video_path = video_path_;
}

/***************************************
 * Button ID setters and getters
 * ************************************/
int button::get_button_id(){
    return button_id;
}

void button::set_button_id(int button_id_){
    button_id = button_id_;
}


/***************************************
 * Brightness setters and getters
 * ************************************/
int button::get_brightness(){
    return brightness;
}

void button::set_brightness(int brightness_){
    brightness = brightness_;
}

/***************************************
 * Contrast setters and getters
 * ************************************/
int button::get_contrast(){
    return contrast;
}

void button::set_contrast(int contrast_){
    contrast = contrast_;
}


