#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "seifenrezept.h"
#include "zutatenliste.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Seifenrechner;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::Seifenrechner *ui;

    ZutatenListe m_ZutatenListe;
    SeifenRezept m_SeifenRezept;

private slots:
    void cmdZutatenClicked();
    void cmdFettHnzufuegenClicked();
    void edtSeifenName();
    void cmdBerechnen();
};
#endif // MAINWINDOW_H
