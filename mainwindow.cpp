#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmobilewindow.h"
#include "deletemobilewindow.h"
#include "addcustomerwindow.h"
#include "deletecustomerwindow.h"
#include <QLabel>
#include <QVBoxLayout>  // Include QVBoxLayout for vertical layout

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the title label and style it
    QLabel* titleLabel = new QLabel("<h1><b>Mobile Management System:</b></h1>");

    // Styling the QLabel to center it, add a border, background color, and padding
    titleLabel->setStyleSheet("QLabel {"
                              "font-size: 20px;"
                              "color: white;"  // Text color
                              "background-color: #00ff00;"  // Background color
                              "border: 2px solid #2980B9;"  // Border color
                              "padding: 10px;"  // Padding inside the label
                              "text-align: center;"  // Center the text inside the label
                              "border-radius: 8px;"  // Rounded corners
                              "}");

    titleLabel->setAlignment(Qt::AlignCenter);  // Ensure the text is centered

    // Create a layout to arrange the widgets
    QVBoxLayout* layout = new QVBoxLayout();

    // Add the titleLabel to the layout
    layout->addWidget(titleLabel);

    // Updated button CSS for green background
    QString buttonStyle = R"(
        QPushButton {
            background-color: #28a745;  /* Green background */
            color: white;
            font-size: 16px;
            font-family: Arial, Helvetica, sans-serif;
            border-radius: 10px;
            padding: 10px;
        }
        QPushButton:hover {
            background-color: #218838;  /* Darker green on hover */
        }
        QPushButton:pressed {
            background-color: #1e7e34;  /* Even darker green when pressed */
        }
    )";

    // Apply styles to buttons
    ui->addMobileButton->setStyleSheet(buttonStyle);
    ui->addCustomerButton->setStyleSheet(buttonStyle);
    ui->deleteMobileButton->setStyleSheet(buttonStyle);
    ui->deleteCustomerButton->setStyleSheet(buttonStyle);

    // Add the buttons to the layout
    layout->addWidget(ui->addMobileButton);
    layout->addWidget(ui->addCustomerButton);
    layout->addWidget(ui->deleteMobileButton);
    layout->addWidget(ui->deleteCustomerButton);

    // Center the buttons in the layout
    layout->setAlignment(Qt::AlignCenter);

    // Set the main layout as the central widget layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Set the main window's background color and image
    this->setStyleSheet("background-color: #F8F9FA; background-image: url(C:/Users/M. Anas Khan Farooq/Desktop/wajih/MobileShopManagementSystem/image.jpg);");

    // Connecting buttons to the corresponding functions
    connect(ui->addMobileButton, &QPushButton::clicked, this, &MainWindow::openAddMobileWindow);
    connect(ui->addCustomerButton, &QPushButton::clicked, this, &MainWindow::openAddCustomerWindow);
    connect(ui->deleteMobileButton, &QPushButton::clicked, this, &MainWindow::openDeleteMobileWindow);
    connect(ui->deleteCustomerButton, &QPushButton::clicked, this, &MainWindow::openDeleteCustomerWindow);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openAddMobileWindow() {
    AddMobileWindow* addMobileWindow = new AddMobileWindow(this);
    addMobileWindow->exec();
}

void MainWindow::openDeleteMobileWindow() {
    DeleteMobileWindow* deleteMobileWindow = new DeleteMobileWindow(this);
    deleteMobileWindow->exec();
}

void MainWindow::openAddCustomerWindow() {
    AddCustomerWindow* addCustomerWindow = new AddCustomerWindow(this);
    addCustomerWindow->exec();
}

void MainWindow::openDeleteCustomerWindow() {
    DeleteCustomerWindow* deleteCustomerWindow = new DeleteCustomerWindow(this);
    deleteCustomerWindow->exec();
}
