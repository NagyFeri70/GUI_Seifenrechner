#include <fstream>
#include <algorithm>

#include "zutatenliste.h"

ZutatenListe::ZutatenListe()
{
    InhaltLoeschen();
}

void ZutatenListe::InhaltLoeschen(void)
{
    m_Fette.clear();
    m_AetherischeOele.clear();
    m_ParfuemOele.clear();
    m_TonErden.clear();
    m_Sontiges.clear();
}

string ZutatenListe::LesenFettName(unsigned int i)
{
    string l_string;

    l_string.clear();

    if(i < m_Fette.size())
    {
        l_string = m_Fette[i].LeseNamen();
    }

    return(l_string);
}

bool ZutatenListe::LesenFett(int i, Zutat *pZutat)
{
    bool RetVal = true;

    if((i >= 0) && (i < m_Fette.size()))
    {
        *pZutat = m_Fette[i];
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
                        zutatentyp = SONTIGES;
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
                        case SONTIGES:
                        {
                            m_Sontiges.push_back(l_Zutat);
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

        sort(m_Fette.begin(), m_Fette.end(), Sortieren);
        sort(m_AetherischeOele.begin(), m_AetherischeOele.end(), Sortieren);
        sort(m_TonErden.begin(), m_TonErden.end(), Sortieren);
        sort(m_ParfuemOele.begin(), m_ParfuemOele.end(), Sortieren);
        sort(m_Sontiges.begin(), m_Sontiges.end(), Sortieren);
    }
    else
    {
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
