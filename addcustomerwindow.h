#ifndef ADDCUSTOMERWINDOW_H
#define ADDCUSTOMERWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include "viewcustomerwindow.h"

class AddCustomerWindow : public QDialog {
    Q_OBJECT

public:
    explicit AddCustomerWindow(QWidget* parent = nullptr);

private slots:
    void addCustomer();

private:
    QLineEdit* nameEdit;
    QLineEdit* contactEdit;
    QLineEdit* cnicEdit;
    QLineEdit* addressEdit;
    QComboBox* genderCombo;
    ViewCustomerWindow* viewWindow;

    bool isFullScreenMode; // Track the full-screen state
};

#endif // ADDCUSTOMERWINDOW_H
