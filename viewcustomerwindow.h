#ifndef VIEWCUSTOMERWINDOW_H
#define VIEWCUSTOMERWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class ViewCustomerWindow : public QDialog {
    Q_OBJECT

public:
    explicit ViewCustomerWindow(QWidget *parent = nullptr);

private:
    QTableWidget* customerTable; // Table to display customer details
    void loadCustomerData();     // Function to load customer data from file
};

#endif // VIEWCUSTOMERWINDOW_H
