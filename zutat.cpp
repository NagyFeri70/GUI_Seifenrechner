#include <iostream>
#include <sstream>
#include "zutat.h"

Zutat::Zutat()
{
    m_ZutatenTyp = UNBEKANNT;
    m_Name.clear();
    m_Beschreibung.clear();
    m_Verseifungszahl = 0.0f;
    m_ist_fest  = false;
    m_Masse_in_Gramm = 0;
}

string Zutat::LeseNamen(void) const
{
    return(m_Name);
}

bool Zutat::MasseSetzen(int Masse)
{
    bool RetVal = true;

    if(Masse > 0)
    {
        m_Masse_in_Gramm = Masse;
    }
    else
    {
        RetVal = false;
    }

    return(RetVal);
}

bool Zutat::EigenschaftenSetzen(ZutatenTyp_e ZutatenTyp, string Eingenschaften)
{
    bool RetVal = true;
    istringstream is;

    is.clear();
    is.str(Eingenschaften);

    getline(is, this->m_Name, ';');
    m_Beschreibung.clear();
    m_Verseifungszahl = 0.0f;
    m_ist_fest  = false;

    m_ZutatenTyp = ZutatenTyp;

    switch(m_ZutatenTyp)
    {
        case FETT:
        {
            size_t l_pos;
            string value;

            getline(is, value, ';');
            /* Leerzeichen entfernen */
            while(string::npos != (l_pos = value.find(".")))
            {
                value.replace(l_pos, 1, ",");
            }
            this->m_Verseifungszahl = atof(value.c_str());

            getline(is, value, ';');
            if(0 == value.compare("fest"))
            {
                this->m_ist_fest = true;
            }
            else
            {
                this->m_ist_fest = false;
            }

            break;
        }
        case AETHERISCHES_OEL:
        {

            break;
        }
        case TONERDE:
        {

            break;
        }
        case PARFUEMOEL:
        {

            break;
        }
        case SONTIGES:
        {

            break;
        }
        default:
        {
            /* unbekannte Typen ignorieren */
            break;
        }
    }

    return(RetVal);
}
