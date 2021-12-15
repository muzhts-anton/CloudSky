#ifndef FRAGMENTTHEMESTYLE_H
#define FRAGMENTTHEMESTYLE_H

#include <QMap>
#include <QString>

namespace themestyle {

enum class Type {
    STACKEDWIDGET,
    BUTTON,
    LINEEDIT,
    LABEL,
    SPINBOX,
};

namespace theme {

    const QString maincolor("rgb(193,243,255);"); // ligthblue #c1f3ff
    const QString secondcolor("rgb(189,144,255);"); // ~pink #bd90ff
    const QString fontcolor("white;");
    const QString backraoundcolor("rgb(154,154,154);"); // ~grey

    const QString fontsize("14px;");

    const QString padding("10px;");

} // namespace theme

const QMap<Type, QString> fixed = {
    { Type::STACKEDWIDGET, "QStackedWidget { background-color:" + theme::maincolor + "}\n"},
    { Type::BUTTON, "QPushButton { background-color:" + theme::secondcolor + "border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "}\n" },
    { Type::LABEL, "QLabel { color:" + theme::backraoundcolor + "}\n" },
    { Type::LINEEDIT, "QLineEdit { background-color:" + theme::backraoundcolor + "color:" + theme::fontcolor + "}\n" },
    { Type::SPINBOX, "QSpinBox { background-color:" + theme::backraoundcolor + "color:" + theme::fontcolor + "}\n" }
};

const QMap<Type, QString> active = {
    { Type::LINEEDIT, "QLineEdit:active { border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "}\n" },
    { Type::SPINBOX, "QSpinBox:active { border: none; border-radius: 7px; padding:" + theme::padding + "color:" + theme::fontcolor + "}\n"}
};

} // themestyle

#endif // FRAGMENTTHEMESTYLE_H
