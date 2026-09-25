#ifndef VIEWMOBILEDETAILWINDOW_H
#define VIEWMOBILEDETAILWINDOW_H

#include <QDialog>  // Change this to QDialog if you don't need QDockWidget

namespace Ui {
class ViewMobileDetailWindow;
}

class ViewMobileDetailWindow : public QDialog  // Use QDialog as base class
{
    Q_OBJECT

public:
    explicit ViewMobileDetailWindow(QWidget *parent = nullptr);
    ~ViewMobileDetailWindow();

private:
    Ui::ViewMobileDetailWindow *ui;
};

#endif // VIEWMOBILEDETAILWINDOW_H
