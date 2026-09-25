#include "deletemobilewindow.h"
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QLabel>

DeleteMobileWindow::DeleteMobileWindow(QWidget *parent)
    : QDialog(parent) {
    // Create input field for IMEI
    imeiEdit = new QLineEdit(this);

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
    imeiEdit->setStyleSheet(inputStyle);

    // Apply label style
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
    formLayout->addRow("IMEI:", imeiEdit);

    // Apply the label style
    QWidget* labelWidget = formLayout->itemAt(0, QFormLayout::LabelRole)->widget();
    QLabel* label = qobject_cast<QLabel*>(labelWidget);
    if (label) {
        label->setStyleSheet(labelStyle);
    }

    // Create and style delete button
    QPushButton* deleteButton = new QPushButton("Delete Mobile", this);
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
    connect(deleteButton, &QPushButton::clicked, this, &DeleteMobileWindow::deleteMobile);
    formLayout->addWidget(deleteButton);

    setLayout(formLayout);
    setWindowTitle("Delete Mobile");

    // Set window background color
    this->setStyleSheet("background-color: #F4F6F7;");

    // Set Fusion theme for consistent appearance across platforms
    QApplication::setStyle("Fusion");

    // Adjust window size
    resize(400, 150);
}

void DeleteMobileWindow::deleteMobile() {
    QString imei = imeiEdit->text().trimmed();

    // Validate input
    if (imei.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("IMEI Field Must Be Filled");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("color: black;");
        msgBox.exec();
        return;
    }

    QFile file("mobile_data.txt");
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
            QString fileImei = details[2];

            // Check if this is the record to delete
            if (fileImei == imei) {
                recordDeleted = true;
                continue; // Skip adding this record to the updated list
            }
        }
        updatedRecords.append(line); // Add other records to the updated list
    }
    file.close();

    if (!recordDeleted) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("IMEI Not Found ");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("color: black;");
        msgBox.exec();
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

    // Show success message
    QMessageBox msgBox;
    msgBox.setText("Delete Mobile Successfully ");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setStyleSheet("color: black;");
    msgBox.exec();
    return;

    // Clear input after success
    imeiEdit->clear();

    accept();
}
