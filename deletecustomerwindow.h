#ifndef DELETECUSTOMERWINDOW_H
#define DELETECUSTOMERWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox> // For displaying error messages
#include <QFile>

class DeleteCustomerWindow : public QDialog {
    Q_OBJECT

public:
    explicit DeleteCustomerWindow(QWidget *parent = nullptr);

private slots:
    void deleteCustomer(); // Slot to handle deleting customer

private:
    QLineEdit* cnicEdit; // Input for customer CNIC
};

#endif // DELETECUSTOMERWINDOW_H
