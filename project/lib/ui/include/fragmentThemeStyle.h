#ifndef FRAGMENTTHEMESTYLE_H
#define FRAGMENTTHEMESTYLE_H

#include <QMap>
#include <QString>

namespace themestyle {

enum class Type {
    STACKEDWIDGET,
    MAINBUTTON,
    SECONDBUTTON,
    LINEEDIT,
    CAPITALLABEL,
    LOWERLABEL,
    SPINBOX,
};

namespace theme {

    const QString maincolor("rgb(193,243,255);"); // ligthblue #c1f3ff
    const QString secondcolor("rgb(189,144,255);"); // ~pink #bd90ff
    const QString thirdcolor("rgb(255,125,98);"); // ~orange #FF7D62
    const QString attentioncolor("red;");
    const QString fontcolor("white;");
    const QString backraoundcolor("rgb(154,154,154);"); // ~grey

    const QString lowerfontsize("14px;");
    const QString capitalfontsize("24px;");

    const QString padding("10px;");

} // namespace theme

const QMap<Type, QString> fixed = {
    { Type::STACKEDWIDGET, "QStackedWidget { background-color:" + theme::maincolor + "}\n" },
    { Type::MAINBUTTON, "QPushButton { background-color:" + theme::secondcolor + "border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "font-size:" + theme::lowerfontsize + "}\n" },
    { Type::SECONDBUTTON, "QPushButton { background-color:" + theme::backraoundcolor + "border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "font-size:" + theme::lowerfontsize + "}\n" },
    { Type::LOWERLABEL, "QLabel { color:" + theme::backraoundcolor + "font-size:" + theme::lowerfontsize + "}\n" },
    { Type::CAPITALLABEL, "QLabel { color:" + theme::secondcolor + "font-size:" + theme::capitalfontsize + "color:" + theme::thirdcolor + "font-weight: bold;" + "}\n" },
    { Type::LINEEDIT, "QLineEdit { background-color:" + theme::backraoundcolor + "color:" + theme::fontcolor + "font-size:" + theme::lowerfontsize + "}\n" },
    { Type::SPINBOX, "QSpinBox { background-color:" + theme::backraoundcolor + "color:" + theme::fontcolor + "font-size:" + theme::lowerfontsize + "}\n" }
};

const QMap<Type, QString> active = {
    { Type::LINEEDIT, "QLineEdit:active { border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "font-size:" + theme::lowerfontsize + "}\n" },
    { Type::SPINBOX, "QSpinBox:active { border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "font-size:" + theme::lowerfontsize + "}\n" }
};

} // themestyle

#endif // FRAGMENTTHEMESTYLE_H
