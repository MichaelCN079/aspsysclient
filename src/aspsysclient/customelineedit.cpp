#include "customelineedit.h"

bool CustomeLineEdit::bUsrNameFocus = false;
bool CustomeLineEdit::bPasswdFocus = false;

CustomeLineEdit::CustomeLineEdit(QWidget *parent):QLineEdit(parent)
{

}

void CustomeLineEdit::mousePressEvent(QMouseEvent *e)
{
    if (objectName() == "usrNameEdit")
    {
        bUsrNameFocus = true;
        bPasswdFocus = false;
    }
    else if (objectName() == "passwdEdit")
    {
        bUsrNameFocus = false;
        bPasswdFocus = true;
    }
}
