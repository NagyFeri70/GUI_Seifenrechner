#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qwindowdefs.h>

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

    // Seifennamen festlegen
    connect(ui->edtSeifenName, SIGNAL(editingFinished()), SLOT(edtSeifenName()));

    // Rezept bearbeiten
    connect(ui->cmdBerechnen, SIGNAL(clicked()), SLOT(cmdBerechnen()));
    connect(ui->cmdLoeschen, SIGNAL(clicked()), SLOT(cmdLoeschen()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
            StatusAusgabe("Eintrag nicht gefunden");
        }
        else
        {
            StatusAusgabe(QAuswahl.toStdString() + " -> gelöscht");
            RezeptAusgeben();
        }
    }
    else
    {
        StatusAusgabe("Nichts ausgwählt");
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
    bool DateiOK;
    DateiOK = m_ZutatenListe.ZutatenDateiOeffnen("/home/nagyferi/Dokumente/git/GUI_SeifenRechner/Zutatenliste.ing");

    if(true == DateiOK)
    {
        unsigned int i = 0;
        string l_name;

        do
        {
            l_name = m_ZutatenListe.LesenFettName(i);
            ui->cmbFette->addItem(l_name.c_str());
            i++;
        }  while(l_name.size() > 0);

        i= 0;
        do
        {
            l_name = m_ZutatenListe.LesenAetherischesOelName(i);
            ui->cmbAetherischeOele->addItem(l_name.c_str());
            i++;
        }  while(l_name.size() > 0);

        i= 0;
        do
        {
            l_name = m_ZutatenListe.LesenTonerdeName(i);
            ui->cmbTonerden->addItem(l_name.c_str());
            i++;
        }  while(l_name.size() > 0);

        i= 0;
        do
        {
            l_name = m_ZutatenListe.LesenParfuemOelName(i);
            ui->cmbParfuemOele->addItem(l_name.c_str());
            i++;
        }  while(l_name.size() > 0);
    }
}

void MainWindow::cmdFettHnzufuegenClicked()
{
    bool ok;
    int fett_in_gramm = ui->edtFettMenge->text().toInt();
    QString fett_name = ui->cmbFette->currentText();
    int fett_index = ui->cmbFette->currentIndex();

    if(!((fett_in_gramm > 0) && (fett_in_gramm <= 1000)))
    {
        StatusAusgabe("Unkorrekte Fettmenge eingegeben");
        return;
    }
    else
    {
        ok = m_SeifenRezept.FettHinzufuegen(fett_index, fett_in_gramm);

        if(true == ok)
        {
            vector <string> Ausgabe;
            char output[100];

            sprintf(output, "%dg %s hinzugefügt", fett_in_gramm, fett_name.toStdString().c_str());

            StatusAusgabe(output);

            RezeptAusgeben();
        }
        else
        {
            StatusAusgabe("Falsche Eingabe");
        }
    }
}

void MainWindow::cmdParfuemOelHinzufuegenClicked()
{
    bool ok;
    int gramm = ui->edtParfuemOele->text().toInt();
    QString name = ui->cmbParfuemOele->currentText();
    int index = ui->cmbParfuemOele->currentIndex();

    if(!((gramm > 0) && (gramm <= 1000)))
    {
        StatusAusgabe("Unkorrekte Menge eingegeben");
        return;
    }
    else
    {
        ok = m_SeifenRezept.ParfuemOelHinzufuegen(index, gramm);

        if(true == ok)
        {
            vector <string> Ausgabe;
            char output[100];

            sprintf(output, "%dg %s hinzugefügt", gramm, name.toStdString().c_str());

            StatusAusgabe(output);

            RezeptAusgeben();
        }
        else
        {
            StatusAusgabe("Falsche Eingabe");
        }
    }
}

void MainWindow::cmdTonerdeHinzufuegenClicked()
{
    bool ok;
    int gramm = ui->edtTonerden->text().toInt();
    QString name = ui->cmbTonerden->currentText();
    int index = ui->cmbTonerden->currentIndex();

    if(!((gramm > 0) && (gramm <= 1000)))
    {
        StatusAusgabe("Unkorrekte Menge eingegeben");
        return;
    }
    else
    {
        ok = m_SeifenRezept.TonerdeHinzufuegen(index, gramm);

        if(true == ok)
        {
            vector <string> Ausgabe;
            char output[100];

            sprintf(output, "%dg %s hinzugefügt", gramm, name.toStdString().c_str());

            StatusAusgabe(output);

            RezeptAusgeben();
        }
        else
        {
            StatusAusgabe("Falsche Eingabe");
        }
    }
}

void MainWindow::cmdAetherischesOelHinzufuegenClicked()
{
    bool ok;
    int gramm = ui->edtAetherischOele->text().toInt();
    QString name = ui->cmbAetherischeOele->currentText();
    int index = ui->cmbAetherischeOele->currentIndex();

    if(!((gramm > 0) && (gramm <= 1000)))
    {
        StatusAusgabe("Unkorrekte Menge eingegeben");
        return;
    }
    else
    {
        ok = m_SeifenRezept.AetherischesOelHinzufuegen(index, gramm);

        if(true == ok)
        {
            vector <string> Ausgabe;
            char output[100];

            sprintf(output, "%dg %s hinzugefügt", gramm, name.toStdString().c_str());

            StatusAusgabe(output);

            RezeptAusgeben();
        }
        else
        {
            StatusAusgabe("Falsche Eingabe");
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

void  MainWindow::StatusAusgabe(string Ausgabe)
{
    ui->lblFehlerAusgabe->setText(Ausgabe.c_str());
}
