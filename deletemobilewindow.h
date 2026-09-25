#ifndef DELETEMOBILEWINDOW_H
#define DELETEMOBILEWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox> // For displaying error messages
#include <QFile>

class DeleteMobileWindow : public QDialog {
    Q_OBJECT

public:
    explicit DeleteMobileWindow(QWidget *parent = nullptr);

private slots:
    void deleteMobile();  // Slot to handle deleting mobile details

private:
    QLineEdit* nameEdit;   // Input for mobile name
    QLineEdit* modelEdit;  // Input for mobile model
    QLineEdit* imeiEdit;   // Input for mobile IMEI
    QLineEdit* stockEdit;  // Input for stock count
};

#endif // DELETEMOBILEWINDOW_H
