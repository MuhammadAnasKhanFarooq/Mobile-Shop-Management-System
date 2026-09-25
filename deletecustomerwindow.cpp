#include "deletecustomerwindow.h"
#include <QFile>
#include <QApplication> // Include QApplication header for setStyle
#include <QLabel> // Ensure QLabel is included

DeleteCustomerWindow::DeleteCustomerWindow(QWidget *parent)
    : QDialog(parent) {
    // Create input field for CNIC
    cnicEdit = new QLineEdit(this);

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
    cnicEdit->setStyleSheet(inputStyle);

    // Apply CSS to style the labels
    QString labelStyle = R"(
        QLabel {
            color: white; /* Set label text color to white */
            font-family: 'Arial', sans-serif; /* Change font to Arial */
            font-size: 18px; /* Set font size */
            font-weight: bold; /* Make the font bold */
        }
    )";

    // Set up the layout
    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow("Customer CNIC:", cnicEdit);

    // Apply label styles directly by accessing the label
    QWidget* labelWidget = formLayout->itemAt(0, QFormLayout::LabelRole)->widget();
    QLabel* label = qobject_cast<QLabel*>(labelWidget); // Corrected the casting issue
    if (label) {
        label->setStyleSheet(labelStyle); // Style the label
    }

    QPushButton* deleteButton = new QPushButton("Delete Customer", this);
    deleteButton->setStyleSheet(R"(
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
    )");
    connect(deleteButton, &QPushButton::clicked, this, &DeleteCustomerWindow::deleteCustomer);
    formLayout->addWidget(deleteButton);

    setLayout(formLayout); // Ensure the layout is set for this dialog
    setWindowTitle("Delete Customer");

    // Set window background color
    this->setStyleSheet("background-color: #F4F6F7;");

    // Set Fusion theme for consistent appearance across platforms
    QApplication::setStyle("Fusion");

    // Adjust window size
    resize(400, 200);
}

void DeleteCustomerWindow::deleteCustomer() {
    QString cnic = cnicEdit->text().trimmed();

    // Validate the CNIC input
    if (cnic.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("All fields must be filled.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("color: black;");
        msgBox.exec();
        return;
    }
    QFile file("customer_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "File Error", "Unable to open file for reading.");
        return;
    }

    QStringList updatedRecords;
    QTextStream in(&file);
    bool recordDeleted = false;

    // Read and filter records
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList details = line.split(";");
        if (details.size() == 5) {
            QString fileCnic = details[2]; // CNIC is in the third position
            if (fileCnic == cnic) {
                recordDeleted = true; // Mark the record as found and deleted
                continue; // Skip this record
            }
        }
        updatedRecords.append(line); // Add other records to the updated list
    }
    file.close();

    // If no record was deleted, inform the user
    if (!recordDeleted) {
        QMessageBox::warning(this, "Not Found", "No customer record found with the provided CNIC.");
        return;
    }

    // Write the updated records back to the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, "File Error", "Unable to open file for writing.");
        return;
    }

    QTextStream out(&file);
    for (const QString& record : updatedRecords) {
        out << record << "\n";
    }
    file.close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Success");
    msgBox.setText("Detele customer details successfully.");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();


    // Clear the input field
    cnicEdit->clear();

    accept(); // Close the dialog if necessary
}
