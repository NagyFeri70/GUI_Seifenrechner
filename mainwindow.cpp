
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
    bool DateiOK;
    DateiOK = m_ZutatenListe.ZutatenDateiOeffnen("/home/nagyferi/Dokumente/git/GUI_SeifenRechner/Zutatenliste.ing");

    if(true == DateiOK)
    {
        ZutatZuComcoBox(FETT, ui->cmbFette);
        ZutatZuComcoBox(AETHERISCHES_OEL, ui->cmbAetherischeOele);
        ZutatZuComcoBox(TONERDE, ui->cmbTonerden);
        ZutatZuComcoBox(PARFUEMOEL, ui->cmbParfuemOele);
        ZutatZuComcoBox(KRAEUTER, ui->cmbKraeuter);
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

void MainWindow::cmdKraeuterHinzufuegenClicked()
{
    bool ok;
    int fett_in_gramm = ui->edtKraeuter->text().toInt();
    int fett_index = ui->cmbKraeuter->currentIndex();

    if(!((fett_in_gramm > 0) && (fett_in_gramm <= 1000)))
    {
        return;
    }
    else
    {
        ok = m_SeifenRezept.ZutatHinzufuegen(KRAEUTER, fett_index, fett_in_gramm);

        if(true == ok)
        {
            RezeptAusgeben();
        }
    }
}

void MainWindow::cmdFettHnzufuegenClicked()
{
    bool ok;
    int fett_in_gramm = ui->edtFettMenge->text().toInt();
    int fett_index = ui->cmbFette->currentIndex();

    if(!((fett_in_gramm > 0) && (fett_in_gramm <= 1000)))
    {
        return;
    }
    else
    {
        ok = m_SeifenRezept.ZutatHinzufuegen(FETT, fett_index, fett_in_gramm);

        if(true == ok)
        {
            RezeptAusgeben();
        }
    }
}

void MainWindow::cmdParfuemOelHinzufuegenClicked()
{
    bool ok;
    int gramm = ui->edtParfuemOele->text().toInt();
    int index = ui->cmbParfuemOele->currentIndex();

    if(!((gramm > 0) && (gramm <= 1000)))
    {
        return;
    }
    else
    {
        ok = m_SeifenRezept.ZutatHinzufuegen(PARFUEMOEL, index, gramm);

        if(true == ok)
        {
            RezeptAusgeben();
        }
    }
}

void MainWindow::cmdTonerdeHinzufuegenClicked()
{
    bool ok;
    int gramm = ui->edtTonerden->text().toInt();
    int index = ui->cmbTonerden->currentIndex();

    if(!((gramm > 0) && (gramm <= 1000)))
    {
        return;
    }
    else
    {
        ok = m_SeifenRezept.ZutatHinzufuegen(TONERDE, index, gramm);

        if(true == ok)
        {
            RezeptAusgeben();
        }
    }
}

void MainWindow::cmdAetherischesOelHinzufuegenClicked()
{
    bool ok;
    int gramm = ui->edtAetherischOele->text().toInt();
    int index = ui->cmbAetherischeOele->currentIndex();

    if(!((gramm > 0) && (gramm <= 1000)))
    {
        return;
    }
    else
    {
        ok = m_SeifenRezept.ZutatHinzufuegen(AETHERISCHES_OEL, index, gramm);

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

