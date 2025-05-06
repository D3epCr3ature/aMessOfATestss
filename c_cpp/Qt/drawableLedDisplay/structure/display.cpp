
#include "display.h"

#include "json.hpp"
#include <fstream>
#include <string>

#include <QFileDialog>

bool openDisplay(struct LEDDisplay& display) {
    QString filename = QFileDialog::getOpenFileName(nullptr, QFileDialog::tr("Open display"),
                                                    QDir::currentPath(),
                                                    QFileDialog::tr("Display file (*.disp)"));
    if ( filename.isNull() ) {
        return false;
    }

    QFile file(filename);   // PATH Checked from getOpenFileName()
    QFileInfo infos(filename);

    if ( infos.suffix().compare("disp") ) {
        return false;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString fileContent = file.readAll();
    file.close();

    if ( fileContent.isEmpty() ) {
        return false;
    }

    nlohmann::json generic_json;
    try {
        // If exported with time, just erase the first line
        if (fileContent[0] == '#' || fileContent[0] == '/')
            fileContent.remove(0, fileContent.indexOf(QChar('\n')));
        std::stringstream(fileContent.toStdString()) >> generic_json;
    } catch (nlohmann::detail::exception& e) {
        return false;
    }

    // Update Window's Title & variables ONLY if file:
    //  -> Exists
    //  -> Is completely valid
    //ui->setWindowTitle(infos.fileName());
    display = generic_json.get<struct LEDDisplay>();

    return true;
}

// TODO(KBP): CLI approach
/* bool saveDisplay(const LEDDisplay& display, const std::string& path) {
    nlohmann::json jsonDisplay = display;
    std::ofstream file(path);

    QString filename = QFileDialog::getSaveFileName(nullptr, QFileDialog::tr("Save display"),
                                                    QDir::currentPath(),
                                                    QFileDialog::tr("Display file (*.disp)"));

    if ( ! (file && file.is_open()) ) {
        file.close();
        return false;
    }

    file << std::setw(4) << jsonDisplay << std::endl;
    file.close();
    return true;
}*/

// TODO(KBP): GUI Approach
bool saveDisplay(const LEDDisplay& display) {
    nlohmann::json jsonDisplay = display;

    QString filename = QFileDialog::getSaveFileName(nullptr, QFileDialog::tr("Save display"),
                                                    QDir::currentPath(),
                                                    QFileDialog::tr("Display file (*.disp)"));
    if ( filename.isNull() ) {
        return false;
    }

    std::ofstream file(filename.toStdString());

    if ( ! (file && file.is_open()) ) {
        file.close();
        return false;
    }

    file << std::setw(4) << jsonDisplay << std::endl;
    file.close();
    return true;
}
