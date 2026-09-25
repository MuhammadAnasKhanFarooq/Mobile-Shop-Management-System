#ifndef ADDMOBILEWINDOW_H
#define ADDMOBILEWINDOW_H

#include <QDialog>
#include "viewmobilewindow.h"

class QLineEdit;
class QPushButton;

class AddMobileWindow : public QDialog {
    Q_OBJECT

public:
    explicit AddMobileWindow(QWidget *parent = nullptr);

private:
    void addMobile();
    void toggleResize();  // Declare the toggleResize function here

    // Input fields
    QLineEdit* nameEdit;
    QLineEdit* modelEdit;
    QLineEdit* imeiEdit;
    QLineEdit* priceEdit;
    QLineEdit* stockEdit;

    ViewMobileWindow* viewWindow;
};

#endif // ADDMOBILEWINDOW_H
