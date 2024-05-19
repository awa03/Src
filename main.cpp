#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QMenu>
#include <QWidgetAction>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;

    QVBoxLayout* layout = new QVBoxLayout(&window);
    QLabel* label = new QLabel("Sky Editor");
    label->setAlignment(Qt::AlignCenter);

    QLabel* subLabel = new QLabel("A lightweight editor from Heaven");
    subLabel->setAlignment(Qt::AlignCenter);

    QFont headFont;
    headFont.setBold(true);
    headFont.setPointSize(20);
    label->setFont(headFont);

    QFont subHeadFont;
    subHeadFont.setItalic(true);
    subHeadFont.setPointSize(10);
    subLabel->setFont(subHeadFont);

    QTextEdit* textEdit = new QTextEdit();

    QString currentFilePath;
    int defaultFontSize = 12; // Default font size

    QMenuBar* menuBar = new QMenuBar(&window);
    QMenu* fileMenu = menuBar->addMenu("&File");
    QMenu* settingsMenu = menuBar->addMenu("&Settings");

    QAction* openAction = new QAction("&Open File", &window);
    fileMenu->addAction(openAction);

    QMenu* fontSizeSubMenu = settingsMenu->addMenu("Font Size");

    QAction* smallFontAction = new QAction("&Small", &window);
    QAction* mediumFontAction = new QAction("&Medium", &window);
    QAction* largeFontAction = new QAction("&Large", &window);

    fontSizeSubMenu->addAction(smallFontAction);
    fontSizeSubMenu->addAction(mediumFontAction);
    fontSizeSubMenu->addAction(largeFontAction);

    settingsMenu->addSeparator();

    // Create buttons
    QPushButton* plusButton = new QPushButton("+", &window);
    QPushButton* minusButton = new QPushButton("-", &window);

    // Create actions for the buttons using QWidgetAction
    QWidgetAction* plusWidgetAction = new QWidgetAction(&window);
    plusWidgetAction->setDefaultWidget(plusButton);

    QWidgetAction* minusWidgetAction = new QWidgetAction(&window);
    minusWidgetAction->setDefaultWidget(minusButton);

    // Add actions to the settings menu
    settingsMenu->addAction(plusWidgetAction);
    settingsMenu->addAction(minusWidgetAction);

    // Add tab spacing action
    QAction* setTabWidthAction = new QAction("&Set Tab Width", &window);
    settingsMenu->addAction(setTabWidthAction);

    QObject::connect(openAction, &QAction::triggered, [&window, textEdit, &currentFilePath]() mutable {
        QString filePath = QFileDialog::getOpenFileName(&window, "Open File", "", "All Files (*.*)");
        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QString contents = QString::fromUtf8(file.readAll());
                textEdit->setPlainText(contents);
                file.close();
                currentFilePath = filePath;
            }
        }
    });

    QObject::connect(smallFontAction, &QAction::triggered, [&textEdit]() {
        QFont font = textEdit->font();
        font.setPointSize(10); // Small font size
        textEdit->setFont(font);
    });

    QObject::connect(mediumFontAction, &QAction::triggered, [&textEdit]() {
        QFont font = textEdit->font();
        font.setPointSize(14); // Medium font size
        textEdit->setFont(font);
    });

    QObject::connect(largeFontAction, &QAction::triggered, [&textEdit]() {
        QFont font = textEdit->font();
        font.setPointSize(18); // Large font size
        textEdit->setFont(font);
    });

    QObject::connect(plusButton, &QPushButton::clicked, [&textEdit]() {
        QFont font = textEdit->font();
        font.setPointSize(font.pointSize() + 1);
        textEdit->setFont(font);
    });

    QObject::connect(minusButton, &QPushButton::clicked, [&textEdit]() {
        QFont font = textEdit->font();
        font.setPointSize(font.pointSize() - 1);
        textEdit->setFont(font);
    });

    // Connect tab width action
    QObject::connect(setTabWidthAction, &QAction::triggered, [&textEdit, &window]() {
        bool ok;
        int tabWidth = QInputDialog::getInt(&window, "Set Tab Width", "Enter Tab Width:", 4, 1, 16, 1, &ok);
        if (ok) {
            QTextOption option = textEdit->document()->defaultTextOption();
            option.setTabStopDistance(tabWidth * textEdit->fontMetrics().lineWidth());
            textEdit->document()->setDefaultTextOption(option);
        }
    });

    QAction* saveAction = new QAction("&Save File", &window);
    fileMenu->addAction(saveAction);

    QObject::connect(saveAction, &QAction::triggered, [&window, textEdit, &currentFilePath]() mutable {
        if (!currentFilePath.isEmpty()) {
            QFile file(currentFilePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << textEdit->toPlainText();
                file.close();
            }
        }
    });

    // Key Press

    layout->setMenuBar(menuBar);
    layout->addWidget(label);
    layout->addWidget(subLabel);
    layout->addWidget(textEdit);

    window.show();
    return a.exec();
}

