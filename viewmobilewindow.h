#ifndef VIEWMOBILEWINDOW_H
#define VIEWMOBILEWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>       // For file handling
#include <QTextStream> // For writing/reading text files
#include <QMessageBox> // For error handling

class ViewMobileWindow : public QDialog {
    Q_OBJECT

public:
    explicit ViewMobileWindow(QWidget *parent = nullptr);

    // Function to update the table with new mobile details
    void addMobileDetails(const QString& name, const QString& model, const QString& imei, double price, int stock);

private:
    QTableWidget* mobileTable;  // Table to display mobile details
    void loadMobileData();      // Function to load mobile data from file
};

#endif // VIEWMOBILEWINDOW_H
