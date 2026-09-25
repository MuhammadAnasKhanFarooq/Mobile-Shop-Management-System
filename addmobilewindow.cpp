#include "addmobilewindow.h"
#include "viewmobilewindow.h"

#include <QRegularExpressionValidator>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>  // Include QLabel header
#include <QDebug>  // For debugging
#include <QIcon>   // For window icon

AddMobileWindow::AddMobileWindow(QWidget *parent)
    : QDialog(parent), viewWindow(new ViewMobileWindow(this)) {
    // Create input fields
    nameEdit = new QLineEdit(this);
    modelEdit = new QLineEdit(this);
    imeiEdit = new QLineEdit(this);
    priceEdit = new QLineEdit(this);
    stockEdit = new QLineEdit(this);

    // Validators for alphanumeric fields
    QRegularExpressionValidator* alphanumericValidator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9]+"), this);
    priceEdit->setValidator(alphanumericValidator);  // Price can now be alphanumeric
    imeiEdit->setValidator(alphanumericValidator);   // IMEI can now be alphanumeric

    // Validator for Stock (numeric only)
    QRegularExpressionValidator* numericValidator = new QRegularExpressionValidator(QRegularExpression("\\d+"), this);
    stockEdit->setValidator(numericValidator);

    // Set styles using stylesheets for font, color, and background
    QString inputStyle = R"(
        QLineEdit {
            background-color: #E8F5E9; /* Light green background */
            color: white; /* Text color set to white */
            border: 2px solid #8BC34A; /* Green border */
            border-radius: 8px;
            padding: 8px;
            font-size: 16px; /* Font size set to 16px */
            font-family: 'Times New Roman', serif; /* Font family set to Times New Roman */
        }
        QLineEdit:focus {
            border: 2px solid #66BB6A; /* Highlight border when focused */
            background-color: white;
            color: #388E3C; /* Dark green text when focused */
        }
    )";

    nameEdit->setStyleSheet(inputStyle);
    modelEdit->setStyleSheet(inputStyle);
    imeiEdit->setStyleSheet(inputStyle);
    priceEdit->setStyleSheet(inputStyle);
    stockEdit->setStyleSheet(inputStyle);

    // Set up the layout
    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow("Mobile Name :", nameEdit);
    formLayout->addRow("Model :", modelEdit);
    formLayout->addRow("IMEI :", imeiEdit);
    formLayout->addRow("Price :", priceEdit);
    formLayout->addRow("Stock :", stockEdit);

    // Apply CSS to style the labels
    QString labelStyle = R"(
        QLabel {
            color: white; /* Set label text color to white */
            font-family: 'Arial', sans-serif; /* Change font to Arial */
            font-size: 18px; /* Set font size */
            font-weight: bold; /* Make the font bold */
        }
    )";

    // Apply the style to all labels in the form layout
    for (int i = 0; i < formLayout->rowCount(); ++i) {
        QLabel* label = qobject_cast<QLabel*>(formLayout->itemAt(i, QFormLayout::LabelRole)->widget());
        if (label) {
            label->setStyleSheet(labelStyle);
        }
    }

    // Create and style buttons
    QPushButton* addButton = new QPushButton("Add Mobile", this);
    QPushButton* viewButton = new QPushButton("View Mobiles", this);

    // Button styles
    QString buttonStyle = R"(
        QPushButton {
            background-color: #3498DB;
            color: white;
            font-size: 16px;
            font-family: 'Verdana', sans-serif;
            border-radius: 12px;
            padding: 12px;
            margin: 10px;
        }
        QPushButton:hover {
            background-color: #2980B9;
        }
        QPushButton:pressed {
            background-color: #1C6A8D;
        }
    )";
    addButton->setStyleSheet(buttonStyle);
    viewButton->setStyleSheet(buttonStyle);

    // Add button actions
    connect(addButton, &QPushButton::clicked, this, &AddMobileWindow::addMobile);
    connect(viewButton, &QPushButton::clicked, viewWindow, &QDialog::show);

    // Add buttons to the layout
    formLayout->addWidget(addButton);
    formLayout->addWidget(viewButton);

    // Set layout to the window
    setLayout(formLayout);
    setWindowTitle("Add Mobile");

    // Set Fusion theme for consistent appearance across platforms
    QApplication::setStyle("Fusion");

    // Adjust window size
    resize(400, 400);

    // Add minimize, close, and resize button functionality
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
    setWindowIcon(QIcon(":/images/icon.png")); // Set custom window icon (optional)
}

// Function to toggle between full screen and small screen
void AddMobileWindow::toggleResize() {
    // Toggle fullscreen mode
    if (windowState() & Qt::WindowFullScreen) {
        setWindowState(windowState() & ~Qt::WindowFullScreen); // Exit fullscreen
    } else {
        setWindowState(windowState() | Qt::WindowFullScreen); // Enter fullscreen
    }
}

void AddMobileWindow::addMobile() {
    QString name = nameEdit->text().trimmed();
    QString model = modelEdit->text().trimmed();
    QString imei = imeiEdit->text().trimmed();
    QString price = priceEdit->text().trimmed();
    QString stock = stockEdit->text().trimmed();

    if (name.isEmpty() || model.isEmpty() || imei.isEmpty() || price.isEmpty() || stock.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("All fields must be filled.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("color: black;");
        msgBox.exec();
        return;
    }

    bool isPriceValid, isStockValid;
    double priceValue = price.toDouble(&isPriceValid);

    if (!isPriceValid || priceValue <= 0) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: #2C3E50;
                color: white;
                font-size: 14px;
                font-family: 'Arial', sans-serif;
            }
            QPushButton {
                background-color: #3498DB;
                color: white;
                border-radius: 6px;
                padding: 6px 12px;
            }
            QPushButton:hover {
                background-color: #2980B9;
            }
        )");
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Price must be a valid positive number.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }

    // No need to declare stockValue again, it was already declared previously
    int stockValue = stock.toInt(&isStockValid);

    if (!isStockValid || stockValue <= 0) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: #2C3E50;
                color: white;
                font-size: 14px;
                font-family: 'Arial', sans-serif;
            }
            QPushButton {
                background-color: #3498DB;
                color: white;
                border-radius: 6px;
                padding: 6px 12px;
            }
            QPushButton:hover {
                background-color: #2980B9;
            }
        )");
        msgBox.setWindowTitle("Input Error");
        msgBox.setText("Stock must be a valid positive integer.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }

    QFile file("mobiles.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << "," << model << "," << imei << "," << price << "," << stock << "\n";
        file.close();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("Mobile details added successfully.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

        // Clear the input fields after saving
        nameEdit->clear();
        modelEdit->clear();
        imeiEdit->clear();
        priceEdit->clear();
        stockEdit->clear();
    }
}
