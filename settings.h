#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include <QTextEdit>
#include <QWidget>

class Settings
{
private:
    Settings();

public:
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    static Settings* GetCurr();
    void SetMinWidth(const int& min_width);
    void SetMinHeight(const int& min_height);

    std::string& GetWindowTitle();

    int& GetMinHeight();
    int& GetMinWidth();
    int& GetFontSize();

    QTextEdit& SetDefault(QTextEdit& TextEdit);
    QWidget& SetDefault(QWidget& Widget);

private:
    std::string WINDOW_TITLE;
    int MIN_WIDTH;
    int MIN_HEIGHT;
    int FONT_SIZE;
};

#endif // SETTINGS_H
