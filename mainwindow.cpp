#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qwindowdefs.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Seifenrechner)
{
    ui->setupUi(this);

    ui->lblRezept->setFont(QFont("Courier New"));
    ui->lblRezept->setTextInteractionFlags(Qt::TextSelectableByMouse);

    m_SeifenRezept.ZutatenListeSetzen(&m_ZutatenListe);

    //ui->lblFette->setText("Fette / Öle");
    //ui->lblFettName->setText("Name");
    //ui->lblFettMenge->setText("Menge in Gramm");

    connect(ui->cmdZutaten, SIGNAL(clicked()), SLOT(cmdZutatenClicked()));
    connect(ui->cmdFettHnzufuegen, SIGNAL(clicked()), SLOT(cmdFettHnzufuegenClicked()));
    connect(ui->edtSeifenName, SIGNAL(editingFinished()), SLOT(edtSeifenName()));
    connect(ui->cmdBerechnen, SIGNAL(clicked()), SLOT(cmdBerechnen()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cmdBerechnen()
{
    string Ausgabe;

    m_SeifenRezept.Berechnen();
    m_SeifenRezept.RezeptAusgabeBildschirm(&Ausgabe);

     ui->lblRezept->setText(Ausgabe.c_str());
}

void MainWindow::edtSeifenName()
{
    string Name;
    string Ausgabe;
    QString Qname = ui->edtSeifenName->text();

    Name = Qname.toStdString();

    m_SeifenRezept.NamenSetzen(Name);

    m_SeifenRezept.RezeptAusgabeBildschirm(&Ausgabe);
    ui->lblRezept->setText(Ausgabe.c_str());
}

void MainWindow::cmdZutatenClicked()
{
    bool DateiOK;
    DateiOK = m_ZutatenListe.ZutatenDateiOeffnen("../../Zutatenliste.ing");

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
        ui->lblFehlerAusgabe->setText("Unkorrekte Fettmenge eingegeben");
        return;
    }
    else
    {
        ok = m_SeifenRezept.FettHinzufuegen(fett_index, fett_in_gramm);

        if(true == ok)
        {
            char output[100];
            string Ausgabe;

            m_SeifenRezept.RezeptAusgabeBildschirm(&Ausgabe);
            ui->lblRezept->setText(Ausgabe.c_str());

            sprintf(output, "%dg %s hinzugefügt", fett_in_gramm, fett_name.toStdString().c_str());

            ui->lblFehlerAusgabe->setText(output);
        }
        else
        {
            ui->lblFehlerAusgabe->setText("Falsche Eingabe");
        }
    }

}
