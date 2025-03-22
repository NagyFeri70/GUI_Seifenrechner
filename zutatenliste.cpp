#include <QMessageBox>
#include <fstream>
#include <algorithm>

#include "zutatenliste.h"

ZutatenListe::ZutatenListe()
{
    InhaltLoeschen();
}

void ZutatenListe::InhaltLoeschen(void)
{
    for(auto dummy:m_mapAlleZutaten)
    {
        (*dummy.second).clear();
    }
}

string ZutatenListe::LesenZutatName(ZutatenTyp_e typ, unsigned int i)
{
    string l_string;
    vector<Zutat> *dummy;

    dummy = m_mapAlleZutaten[typ];

    l_string.clear();

    if(i < (*dummy).size())
    {
        l_string = (*dummy)[i].LeseNamen();
    }

    return(l_string);
}


bool ZutatenListe::LesenZutat(ZutatenTyp_e typ, int index, Zutat *l_zutat)
{
    bool RetVal = true;
    vector<Zutat> *dummy;

    dummy = m_mapAlleZutaten[typ];
    *l_zutat = (*dummy)[index];

    return(RetVal);
}

bool ZutatenListe::ZutatLesen(int i, Zutat *pZutat, vector<Zutat> &pZutatenListe)
{
    bool RetVal = true;

    if((i >= 0) && (i < pZutatenListe.size()))
    {
        *pZutat = pZutatenListe[i];
    }
    else
    {
        RetVal = false;
    }

    return(RetVal);
}

bool ZutatenListe::ZutatenDateiOeffnen(string Dateiname)
{
    bool RetVal = true;
    ifstream eDatei(Dateiname);

    if(!eDatei.fail())
    {
        string          inhaltzeile;
        size_t          l_pos;
        ZutatenTyp_e    zutatentyp = UNBEKANNT;
        Zutat           l_Zutat;

        InhaltLoeschen();

        getline(eDatei,inhaltzeile);
        if(string::npos == inhaltzeile.find(("-[Zutatenliste]")))
        {
            QMessageBox msgBox;
            msgBox.setText("Falsches Dateiformat.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();

            return(false);
        }

        while(getline(eDatei,inhaltzeile))
        {
            /* leere Zeilen ignorieren */
            if(0 != inhaltzeile.length())
            {
                /* Leerzeichen entfernen */
                while(string::npos != (l_pos = inhaltzeile.find(" ")))
                {
                    inhaltzeile.erase(l_pos, 1);
                }

                if(string::npos != inhaltzeile.find("-["))
                {
                    if(string::npos != inhaltzeile.find("-[Fette]"))
                    {
                        zutatentyp = FETT;
                    }
                    else if((string::npos != inhaltzeile.find("-[AetherischeOele]")))
                    {
                        zutatentyp = AETHERISCHES_OEL;
                    }
                    else if((string::npos != inhaltzeile.find("-[Tonerde]")))
                    {
                        zutatentyp = TONERDE;
                    }
                    else if((string::npos != inhaltzeile.find("-[ParfuemOel]")))
                    {
                        zutatentyp = PARFUEMOEL;
                    }
                    else if((string::npos != inhaltzeile.find("-[Sonstiges]")))
                    {
                        zutatentyp = SONSTIGES;
                    }
                    else if((string::npos != inhaltzeile.find("-[Kraeuter]")))
                    {
                        zutatentyp = KRAEUTER;
                    }
                    else if((string::npos != inhaltzeile.find("-[Flüssigkeiten]")))
                    {
                        zutatentyp = FLUESSIGKEITEN;
                    }
                    else
                    {
                        zutatentyp = UNBEKANNT;
                    }
                }
                else
                {
                    l_Zutat.EigenschaftenSetzen(zutatentyp, inhaltzeile);

                    switch(zutatentyp)
                    {
                        case FETT:
                        {
                            m_Fette.push_back(l_Zutat);
                            break;
                        }
                        case AETHERISCHES_OEL:
                        {
                            m_AetherischeOele.push_back(l_Zutat);
                            break;
                        }
                        case TONERDE:
                        {
                            m_TonErden.push_back(l_Zutat);
                            break;
                        }
                        case PARFUEMOEL:
                        {
                            m_ParfuemOele.push_back(l_Zutat);
                            break;
                        }
                        case SONSTIGES:
                        {
                            m_Sontiges.push_back(l_Zutat);
                            break;
                        }
                        case KRAEUTER:
                        {
                            m_Kraeuter.push_back(l_Zutat);
                            break;
                        }
                        case FLUESSIGKEITEN:
                        {
                            m_Fluessigkeiten.push_back(l_Zutat);
                            break;
                        }
                        default:
                        {
                            /* unbekannte Typen ignorieren */
                            break;
                        }
                    }
                }
            }
        }

        for(auto ZutatenListe:m_mapAlleZutaten)
        {
            sort((*ZutatenListe.second).begin(), (*ZutatenListe.second).end(), Sortieren);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Datei nicht gefunden.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        RetVal = false;
    }

    return(RetVal);
}

bool ZutatenListe::Sortieren(const Zutat &A, const Zutat &B)
{
    bool RetVal = true;
    string a_name, b_name;

    a_name = A.LeseNamen();
    b_name = B.LeseNamen();

    if(a_name[0] > b_name[0])
    {
        RetVal = false;
    }
    else if(a_name[0] == b_name[0])
    {
        if(a_name[1] > b_name[1])
        {
            RetVal = false;
        }
    }


    return(RetVal);
}
