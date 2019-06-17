#ifndef CUSTOMELINEEDIT_H
#define CUSTOMELINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>

class CustomeLineEdit : public QLineEdit
{
public:
    CustomeLineEdit(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *e);

public:
    static bool bUsrNameFocus;
    static bool bPasswdFocus;
};

#endif // CUSTOMELINEEDIT_H
