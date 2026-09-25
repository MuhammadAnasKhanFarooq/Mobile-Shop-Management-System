#include "addcustomerwindow.h"
#include "viewcustomerwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>  // Include QLabel header
#include <QDebug>  // For debugging
#include <QIcon>   // For window icon

AddCustomerWindow::AddCustomerWindow(QWidget* parent)
    : QDialog(parent), viewWindow(new ViewCustomerWindow(this)) {
    // Create input fields
    nameEdit = new QLineEdit(this);
    contactEdit = new QLineEdit(this);
    cnicEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    genderCombo = new QComboBox(this);

    // Populate gender combo box
    genderCombo->addItem("Male");
    genderCombo->addItem("Female");
    genderCombo->addItem("Other");

    // Set styles using stylesheets for font, color, and background
    QString inputStyle = R"(
        QLineEdit {
            background-color: white; /* White background */
            color: white; /* Text color set to white */
            border: 2px solid #8BC34A; /* Green border */
            border-radius: 8px;
            padding: 8px;
            font-size: 16px; /* Font size set to 16px */
            font-family: 'Times New Roman', serif; /* Font family set to Times New Roman */
        }
        QLineEdit:focus {
            border: 2px solid #66BB6A; /* Highlight border when focused */
            background-color: #F1F8E9; /* Slight light green background when focused */
            color: #388E3C; /* Dark green text when focused */
        }
        QComboBox {
            background-color: white; /* White background */
            color: white; /* Text color set to white */
            border: 2px solid #8BC34A; /* Green border */
            border-radius: 8px;
            padding: 8px;
            font-size: 16px; /* Font size set to 16px */
            font-family: 'Times New Roman', serif; /* Font family set to Times New Roman */
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox:focus {
            border: 2px solid #66BB6A; /* Highlight border when focused */
            background-color: #F1F8E9; /* Slight light green background when focused */
            color: #388E3C; /* Dark green text when focused */
        }
    )";

    // Apply styles to the widgets
    nameEdit->setStyleSheet(inputStyle);
    contactEdit->setStyleSheet(inputStyle);
    cnicEdit->setStyleSheet(inputStyle);
    addressEdit->setStyleSheet(inputStyle);
    genderCombo->setStyleSheet(inputStyle);

    // Set up the layout
    QFormLayout* formLayout = new QFormLayout(this);

    // Create labels and apply styles
    QLabel* nameLabel = new QLabel("Name:", this);
    QLabel* contactLabel = new QLabel("Contact:", this);
    QLabel* cnicLabel = new QLabel("CNIC:", this);
    QLabel* addressLabel = new QLabel("Address:", this);
    QLabel* genderLabel = new QLabel("Gender:", this);

    // Apply style to the labels
    QString labelStyle = R"(
        QLabel {
            color: white; /* White text color */
            font-family: 'Times New Roman', serif; /* Font family set to Times New Roman */
            font-size: 16px; /* Font size set to 16px */
        }
    )";

    nameLabel->setStyleSheet(labelStyle);
    contactLabel->setStyleSheet(labelStyle);
    cnicLabel->setStyleSheet(labelStyle);
    addressLabel->setStyleSheet(labelStyle);
    genderLabel->setStyleSheet(labelStyle);

    // Add input fields to the form layout with labels

    formLayout->addRow(nameLabel, nameEdit);
    formLayout->addRow(contactLabel, contactEdit);
    formLayout->addRow(cnicLabel, cnicEdit);
    formLayout->addRow(addressLabel, addressEdit);
    formLayout->addRow(genderLabel, genderCombo);

    // Create and style buttons
    QPushButton* addButton = new QPushButton("Add Customer", this);
    QPushButton* viewButton = new QPushButton("View Customers", this);

    // Button styles
    QString buttonStyle = R"(
 QPushButton {
          background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #3498DB, stop:1 #2980B9); /* Gradient background */
          color: white; /* Text color */
          font-size: 16px; /* Font size */
          font-family: 'Verdana', sans-serif; /* Font family */
          border-radius: 12px; /* Rounded corners */
          padding: 12px; /* Padding for a larger button */
          margin: 10px; /* Margin around the button */
          border: none; /* Remove border for modern look */
      }
      QPushButton:hover {
          background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                      stop:0 #5DADE2, stop:1 #3498DB); /* Lighter gradient on hover */
      }
      QPushButton:pressed {
          background-color: #1C6A8D; /* Solid color on press */
      }
  )";
    addButton->setStyleSheet(buttonStyle);
    viewButton->setStyleSheet(buttonStyle);

    // Add button actions
    connect(addButton, &QPushButton::clicked, this, &AddCustomerWindow::addCustomer);
    connect(viewButton, &QPushButton::clicked, viewWindow, &QDialog::show);

    // Add buttons to the layout
    formLayout->addWidget(addButton);
    formLayout->addWidget(viewButton);

    // Set layout to the window
    setLayout(formLayout);
    setWindowTitle("Add Customer");

    // Set window background color and apply font and color globally
    this->setStyleSheet(R"(
        background-color: #F4F6F7;
        font-family: 'Times New Roman', serif; /* Font family set to Times New Roman */
        font-size: 16px;
    )");

    // Set Fusion theme for consistent appearance across platforms
    QApplication::setStyle("Fusion");

    // Adjust window size
    resize(400, 400);

    // Add minimize and close button functionality
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowIcon(QIcon(":/images/icon.png"));
}

void AddCustomerWindow::addCustomer() {
    QString name = nameEdit->text().trimmed();
    QString contact = contactEdit->text().trimmed();
    QString cnic = cnicEdit->text().trimmed();
    QString address = addressEdit->text().trimmed();
    QString gender = genderCombo->currentText();

    // Validate inputs
    if (name.isEmpty() || contact.isEmpty() || cnic.isEmpty() || address.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("All fields must be filled.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("color: black;");
        msgBox.exec();
        return;
    }

    // Save customer details to a file
    QFile file("customer_data.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << ";" << contact << ";" << cnic << ";" << address << ";" << gender << "\n";
        file.close();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("Customer details added successfully.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();


        // Clear the inputs after successful addition
        nameEdit->clear();
        contactEdit->clear();
        cnicEdit->clear();
        addressEdit->clear();
        genderCombo->setCurrentIndex(0); // Reset gender selection
    } else {
        QMessageBox::warning(this, "File Error", "Unable to open file for saving data.");
    }
}
