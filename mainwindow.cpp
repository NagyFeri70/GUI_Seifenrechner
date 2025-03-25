#include <QMessageBox>
#include <QFileDialog>
#include "./ui_mainwindow.h"
#include <qwindowdefs.h>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Seifenrechner)
{
    ui->setupUi(this);

    ui->lstRezept->setFont(QFont("Courier New"));

    m_SeifenRezept.ZutatenListeSetzen(&m_ZutatenListe);

    // Zutatenliste oeffnen
    connect(ui->cmdZutaten, SIGNAL(clicked()), SLOT(cmdZutatenClicked()));

    // Zutat hinzufuegen
    connect(ui->cmdFettHnzufuegen, SIGNAL(clicked()), SLOT(cmdFettHnzufuegenClicked()));
    connect(ui->cmdAethOelHinzufuegen, SIGNAL(clicked()),  SLOT(cmdAetherischesOelHinzufuegenClicked()));
    connect(ui->cmdTonerdenHinufuegen, SIGNAL(clicked()), SLOT(cmdTonerdeHinzufuegenClicked()));
    connect(ui->cmdParfuemOelHinzufuegen, SIGNAL(clicked()), SLOT(cmdParfuemOelHinzufuegenClicked()));
    connect(ui->cmdKraeuterHinzufuegen, SIGNAL(clicked()), SLOT(cmdKraeuterHinzufuegenClicked()));
    connect(ui->cmdFuessigkeitenhHnzufuegen, SIGNAL(clicked()), SLOT(cmdFluessigkeitenHinzufuegenClicked()));
    connect(ui->cmdSontigesHinzufuegen, SIGNAL(clicked()), SLOT(cmdSontigesHinzufuegenClicked()));

    connect(ui->cmdDrucken, SIGNAL(clicked()), SLOT(cmdDruckenClicked()));

    connect(ui->cmdSpeichern, SIGNAL(clicked()), SLOT(cmdRezeptSpeichern()));
    connect(ui->cmdSeifenrezeptOeffnen, SIGNAL(clicked()), SLOT(cmdSeifenrezeptOeffnenClicked()));



    // Seifennamen festlegen
    connect(ui->edtSeifenName, SIGNAL(editingFinished()), SLOT(edtSeifenName()));

    // Rezept bearbeiten
    connect(ui->cmdBerechnen, SIGNAL(clicked()), SLOT(cmdBerechnen()));
    connect(ui->cmdLoeschen, SIGNAL(clicked()), SLOT(cmdLoeschen()));

    ZutatenDateiOeffnen("/home/nagyferi/Dokumente/git/GUI_SeifenRechner/Zutatenliste.ing");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cmdDruckenClicked()
{
    QMessageBox::critical(this, "Fehler", "Das ist ein Fehler");
}

void MainWindow::cmdRezeptSpeichern()
{
    bool ok;
    QString DateiName = QFileDialog::getSaveFileName(this,
                                                     tr("Datei zum Speichern auswählen"),
                                                     "/home/nagyferi/Dokumente/git/GUI_SeifenRechner",
                                                     tr("Seifenrezept (*.srzpt)"));

    ok = m_SeifenRezept.RezeptSpeichern(DateiName.toStdString());

    if(false == ok)
    {
         QMessageBox::critical(this, "Fehler", "Rezept konnte nicht gepeichert werden");
    }
}

void MainWindow::cmdSeifenrezeptOeffnenClicked()
{
    bool ok;
    QString DateiName = QFileDialog::getOpenFileName(this,
                                                     tr("Datei zum Speichern auswählen"),
                                                     "/home/nagyferi/Dokumente/git/GUI_SeifenRechner",
                                                     tr("Seifenrezept (*.srzpt)"));

    ok = m_SeifenRezept.RezeptOeffnen(DateiName.toStdString());

    if(false == ok)
    {
        QMessageBox::critical(this, "Fehler", "Rezept konnte nicht gepeichert werden");
    }
    else
    {
        ui->edtSeifenName->setText(m_SeifenRezept.NamenLesen().c_str());
        RezeptAusgeben();
    }
}

void MainWindow::cmdLoeschen()
{
    QString QAuswahl;
    bool ist_geloescht;

    if(NULL != ui->lstRezept->currentItem())
    {
        QAuswahl = ui->lstRezept->currentItem()->text();

        ist_geloescht = m_SeifenRezept.ZutatLoeschen(QAuswahl.toStdString());

        if(false == ist_geloescht)
        {

        }
        else
        {
            RezeptAusgeben();
        }
    }
}


void MainWindow::cmdBerechnen()
{
    m_SeifenRezept.Berechnen();

    RezeptAusgeben();
}

void MainWindow::edtSeifenName()
{
    string Name;
    QString Qname = ui->edtSeifenName->text();

    Name = Qname.toStdString();

    m_SeifenRezept.NamenSetzen(Name);

    RezeptAusgeben();
}


void MainWindow::cmdZutatenClicked()
{
    string Dateiname("test");

    ZutatenDateiOeffnen(Dateiname);
}

void MainWindow::ZutatenDateiOeffnen(string Dateiname)
{
    bool DateiOK;
    DateiOK = m_ZutatenListe.ZutatenDateiOeffnen(Dateiname);

    if(true == DateiOK)
    {
        ZutatZuComcoBox(FETT, ui->cmbFette);
        ZutatZuComcoBox(AETHERISCHES_OEL, ui->cmbAetherischeOele);
        ZutatZuComcoBox(TONERDE, ui->cmbTonerden);
        ZutatZuComcoBox(PARFUEMOEL, ui->cmbParfuemOele);
        ZutatZuComcoBox(KRAEUTER, ui->cmbKraeuter);
        ZutatZuComcoBox(FLUESSIGKEITEN, ui->cmbFluessigkeiten);
        ZutatZuComcoBox(SONSTIGES, ui->cmbSonstiges);
    }
    else
    {
        QMessageBox::critical(this, "Fehler", "Fehler beim Öffnen der Datei");
    }
}

void MainWindow::ZutatZuComcoBox(ZutatenTyp_e typ, QComboBox *ComboBox)
{
    unsigned int i = 0;
    string l_name;

    do
    {
        l_name = m_ZutatenListe.LesenZutatName(typ, i);
        ComboBox->addItem(l_name.c_str());
        i++;

    }  while(l_name.size() > 0);

}


void MainWindow::cmdFluessigkeitenHinzufuegenClicked()
{
    ZutatZuRezept(FLUESSIGKEITEN, ui->edtFluessigkeiten, ui->cmbFluessigkeiten);
}

void MainWindow::cmdSontigesHinzufuegenClicked()
{
    ZutatZuRezept(SONSTIGES, ui->edtSontiges, ui->cmbSonstiges);
}

void MainWindow::cmdKraeuterHinzufuegenClicked()
{
    ZutatZuRezept(KRAEUTER, ui->edtKraeuter, ui->cmbKraeuter);
}

void MainWindow::cmdFettHnzufuegenClicked()
{
    ZutatZuRezept(FETT, ui->edtFettMenge, ui->cmbFette);
}

void MainWindow::cmdParfuemOelHinzufuegenClicked()
{
    ZutatZuRezept(PARFUEMOEL, ui->edtParfuemOele, ui->cmbParfuemOele);
}

void MainWindow::cmdTonerdeHinzufuegenClicked()
{
    ZutatZuRezept(TONERDE, ui->edtTonerden, ui->cmbTonerden);
}

void MainWindow::cmdAetherischesOelHinzufuegenClicked()
{
    ZutatZuRezept(AETHERISCHES_OEL, ui->edtAetherischOele, ui->cmbAetherischeOele);

}

void MainWindow::ZutatZuRezept(ZutatenTyp_e typ, QLineEdit *LineEdit, QComboBox *ComboBox)
{
    bool ok;
    int masse_in_gramm = LineEdit->text().toInt();
    int index = ComboBox->currentIndex();

    if(!((masse_in_gramm > 0) && (masse_in_gramm <= 1000)))
    {
        return;
    }
    else
    {
        ok = m_SeifenRezept.ZutatHinzufuegen(typ, index, masse_in_gramm);

        if(true == ok)
        {
            RezeptAusgeben();
        }
    }
}

void MainWindow::RezeptAusgeben(void)
{
    int i;
    vector <string> l_Ausgabe;

    m_SeifenRezept.RezeptAusgabeBildschirm(&l_Ausgabe);

    ui->lstRezept->clear();

    for(i = 0; i < l_Ausgabe.size(); i++)
    {
        ui->lstRezept->addItem(l_Ausgabe[i].c_str());
    }
}

