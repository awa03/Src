#include "settings.h"

Settings* Settings::GetCurr(){
    static Settings instance;
    return &instance;
}

Settings::Settings()
{
    // Default Values
    MIN_HEIGHT = 100;
    MIN_WIDTH = 100;
    FONT_SIZE = 12;
    WINDOW_TITLE = "Sky Editor";
}

void Settings::SetMinHeight(const int& min_height){
    MIN_HEIGHT = min_height;
}
void Settings::SetMinWidth(const int& min_width){
    MIN_HEIGHT = min_width;
}

int& Settings::GetMinHeight(){
    return MIN_HEIGHT;
}

int& Settings::GetMinWidth(){
    return MIN_WIDTH;
}

std::string& Settings::GetWindowTitle(){
    return WINDOW_TITLE;
}

int& Settings::GetFontSize(){
    return FONT_SIZE;
}

QTextEdit& Settings::SetDefault(QTextEdit& textEdit){
    textEdit.setTextColor(Qt::white);
    textEdit.setStyleSheet("QTextEdit { color: white; }");
    textEdit.setFontPointSize(GetFontSize());
    return textEdit;
}

QWidget& Settings::SetDefault(QWidget& widget){
    widget.setWindowTitle(GetWindowTitle().c_str());
    widget.setMinimumHeight(GetMinHeight());
    widget.setMinimumWidth(GetMinWidth());
    return widget;
}
