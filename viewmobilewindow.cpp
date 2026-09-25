#include "viewmobilewindow.h"

#include <QFile>
#include <QTextStream>

ViewMobileWindow::ViewMobileWindow(QWidget *parent)
    : QDialog(parent) {
    mobileTable = new QTableWidget(this);
    mobileTable->setColumnCount(5);
    mobileTable->setColumnWidth(2, 200); // Set the width for the IMEI column to 200 pixels
    mobileTable->setSelectionBehavior(QAbstractItemView::SelectItems); // Allow selecting individual cells
    mobileTable->setSelectionMode(QAbstractItemView::SingleSelection); // Allow selecting a single cell
    mobileTable->setHorizontalHeaderLabels({"Name", "Model", "IMEI", "Price", "Stock"});
    mobileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mobileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mobileTable->setAlternatingRowColors(true);  // Add alternating row colors for better readability

    // Styling the table
    QString tableStyle = R"(
        QTableWidget {
            background-color: #FFFFFF;
            border: 1px solid #BDC3C7;
            font-family: 'Arial', sans-serif;
            font-size: 14px;
            color: white;
        }
        QTableWidget::item {
            padding: 8px;
        }
        QTableWidget::item:selected {
            background-color: #3498DB;
            color: white;
        }
        QHeaderView::section {
            background-color: #2980B9;
            color: white;
            padding: 10px;
            font-size: 16px;
        }
    )";
    mobileTable->setStyleSheet(tableStyle);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mobileTable);

    // Create and style the close button
    QPushButton* closeButton = new QPushButton("Close", this);
    QString buttonStyle = R"(
        QPushButton {
            background-color: #E74C3C;
            color: white;
            font-size: 16px;
            font-family: 'Arial', sans-serif;
            border-radius: 12px;
            padding: 12px;
            margin-top: 10px;
        }
        QPushButton:hover {
            background-color: #C0392B;
        }
        QPushButton:pressed {
            background-color: #992D22;
        }
    )";
    closeButton->setStyleSheet(buttonStyle);
    connect(closeButton, &QPushButton::clicked, this, &ViewMobileWindow::close);
    layout->addWidget(closeButton);

    setLayout(layout);
    setWindowTitle("View Mobiles");

    // Load mobile data into the table
    loadMobileData();
}

void ViewMobileWindow::loadMobileData() {
    QFile file("mobile_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList details = line.split(";");
            if (details.size() == 5) {
                int row = mobileTable->rowCount();
                mobileTable->insertRow(row);

                mobileTable->setItem(row, 0, new QTableWidgetItem(details[0]));
                mobileTable->setItem(row, 1, new QTableWidgetItem(details[1]));
                mobileTable->setItem(row, 2, new QTableWidgetItem(details[2]));
                mobileTable->setItem(row, 3, new QTableWidgetItem(details[3]));
                mobileTable->setItem(row, 4, new QTableWidgetItem(details[4]));
            }
        }
        file.close();
    } else {
        QMessageBox::warning(this, "File Error", "Unable to open file for loading data.");
    }
}
