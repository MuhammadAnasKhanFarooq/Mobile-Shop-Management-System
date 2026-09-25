#include "viewcustomerwindow.h"

ViewCustomerWindow::ViewCustomerWindow(QWidget *parent)
    : QDialog(parent) {
    // Set up the table
    customerTable = new QTableWidget(this);
    customerTable->setColumnCount(5);
    customerTable->setHorizontalHeaderLabels({"Name", "Contact", "CNIC", "Address", "Gender"});
    customerTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Read-only table
    customerTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Apply table styling
    customerTable->setStyleSheet(R"(
        QTableWidget {
            background-color: #ECF0F1;
            font-family: 'Arial', sans-serif;
            font-size: 14px;
            color: white;
        }
        QTableWidget::item {
            padding: 8px;
        }
        QHeaderView::section {
            background-color: #3498DB;
            color: white;
            padding: 8px;
            font-weight: bold;
        }
        QTableWidget::item:selected {
            background-color: #1ABC9C;
            color: white;
        }
    )");

    // Set up the layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(customerTable);

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
            background-color: #A93226;
        }
    )";
    closeButton->setStyleSheet(buttonStyle);
    connect(closeButton, &QPushButton::clicked, this, &ViewCustomerWindow::close);
    layout->addWidget(closeButton);

    setLayout(layout);
    setWindowTitle("View Customers");

    // Load customer data from file
    loadCustomerData();
}

void ViewCustomerWindow::loadCustomerData() {
    QFile file("customer_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList details = line.split(";");
            if (details.size() == 5) {
                int row = customerTable->rowCount();
                customerTable->insertRow(row);

                customerTable->setItem(row, 0, new QTableWidgetItem(details[0])); // Name
                customerTable->setItem(row, 1, new QTableWidgetItem(details[1])); // Contact
                customerTable->setItem(row, 2, new QTableWidgetItem(details[2])); // CNIC
                customerTable->setItem(row, 3, new QTableWidgetItem(details[3])); // Address
                customerTable->setItem(row, 4, new QTableWidgetItem(details[4])); // Gender
                customerTable->setColumnWidth(2, 150); // CNIC column, adjust width as needed
               customerTable->setSelectionBehavior(QAbstractItemView::SelectItems); // Allow selecting individual cells
                customerTable->setSelectionMode(QAbstractItemView::SingleSelection); // Allow selecting a single cell

            }
        }
        file.close();
    } else {
        QMessageBox::warning(this, "File Error", "Unable to open file for loading data.");
    }
}
