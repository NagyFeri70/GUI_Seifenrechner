#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./ui_mainwindow.h"
#include <qwindowdefs.h>
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

    void ZutatZuRezept(ZutatenTyp_e typ, QLineEdit *LineEdit, QComboBox *ComboBox);
    void ZutatZuComcoBox(ZutatenTyp_e typ, QComboBox *ComboBox);

private slots:
    // Zutatenliste oeffnen
    void cmdZutatenClicked();

    // Drucken
    void cmdDruckenClicked();

    // Rezept speichern
    void cmdRezeptSpeichern();


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
    void cmdKraeuterHinzufuegenClicked();
    void cmdFluessigkeitenHinzufuegenClicked();
    void cmdSontigesHinzufuegenClicked();
};
#endif // MAINWINDOW_H
