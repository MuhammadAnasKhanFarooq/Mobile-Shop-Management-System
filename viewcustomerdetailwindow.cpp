#include "viewcustomerdetailwindow.h"
#include "ui_viewcustomerdetailwindow.h"  // Correctly include the generated UI header

ViewCustomerDetailWindow::ViewCustomerDetailWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewCustomerDetailWindow)  // Initialize the ui pointer here
{
    ui->setupUi(this);  // Set up the UI components
}

ViewCustomerDetailWindow::~ViewCustomerDetailWindow()
{
    delete ui;  // Clean up the UI object
}
