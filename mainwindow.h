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

    void RezeptAusgeben(void);
    void StatusAusgabe(string Ausgabe);

private slots:
    // Zutatenliste oeffnen
    void cmdZutatenClicked();

    // Seifennamen festlegen
    void edtSeifenName();

    // Rezept bearbeiten
    void cmdBerechnen();
    void cmdLoeschen();

    // Zutat hinzufuegen
    void cmdFettHnzufuegenClicked();
    void cmdAetherischesOelHinzufuegenClicked();
    void cmdTonerdeHinzufuegenClicked();
    void cmdParfuemOelHinzufuegenClicked();
};
#endif // MAINWINDOW_H
