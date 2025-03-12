#include "seifenrezept.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

SeifenRezept::SeifenRezept() : ZutatenListe()
{
    m_pZutatenListe = NULL;
    m_Name.clear();
}

void SeifenRezept::Berechnen(void)
{
    int i;

    m_MengeWasser = 0.0f;
    m_MengeNaOH   = 0.0f;

    for(i = 0; i < m_Fette.size(); i++)
    {
        m_MengeWasser += m_Fette[i].MasseLesen();
        m_MengeNaOH   += m_Fette[i].MasseLesen() * m_Fette[i].VerseifungszahlLesen();
    }

    m_MengeWasser *= 1.0/3.0;
}

void SeifenRezept::NamenSetzen(const string &p_Name)
{
    m_Name = p_Name;
}

void SeifenRezept::ZutatenListeSetzen(ZutatenListe *p_ZutatenListe)
{
    m_pZutatenListe = p_ZutatenListe;
}

bool SeifenRezept::RezeptAusgabeBildschirm(vector<string> *Ausgabe)
{
    bool RetVal = true;
    float AnteilNaOH;
    int i, masse_gerundet;
    char ch[250] = { 0 };
    string Masse;

    Ausgabe->clear();

    Ausgabe->push_back(m_Name + "\n");

    for(i = 0; i < m_Fette.size(); i++)
    {
        sprintf(ch, "%4d", m_Fette[i].MasseLesen());
        Masse = ch;

        Ausgabe->push_back(Masse + " g " + m_Fette[i].NamenLesen());
    }

    if((m_MengeNaOH > 1.0f) && (m_MengeWasser > 1.0f))
    {
        masse_gerundet = (int)(m_MengeWasser + 0.5f);
        sprintf(ch, "%4d", masse_gerundet);
        Masse = ch;
        Ausgabe->push_back("\n" + Masse + " g " + "Wasser" + "\n");

        for(i = 4; i <= 8; i++)
        {            
            AnteilNaOH = m_MengeNaOH * (100.0f -(float)i) * 0.01f;
            masse_gerundet = (int)(AnteilNaOH + 0.5f);
            sprintf(ch, "%4d g NaOH - %d %% Überfettung", masse_gerundet, i);
            Masse = ch;
            Ausgabe->push_back(Masse);
        }
    }


    return RetVal;
}


bool SeifenRezept::FettHinzufuegen(int p_Fettnummer, int fett_in_gramm)
{
    bool RetVal = true;
    Zutat l_zutat;
    int i;
    bool found = false;

    if(NULL != m_pZutatenListe)
    {
        m_pZutatenListe->LesenFett(p_Fettnummer, &l_zutat);

        l_zutat.MasseSetzen(fett_in_gramm);

        BerechnungLoeschen();

        for(i = 0; i < m_Fette.size(); i++)
        {
            if(l_zutat.LeseNamen() == m_Fette[i].LeseNamen())
            {
                found = true;
                break;
            }
        }

        if(false == found)
        {
            m_Fette.push_back(l_zutat);
        }
        else
        {
            m_Fette[i] = l_zutat;
        }

    }
    else
    {
        RetVal = false;
    }

    return(RetVal);
}

bool SeifenRezept::ZutatLoeschen(const string &p_string)
{
    bool RetVal = false;
    int i;

    for(i = 0; i < m_Fette.size(); i++)
    {
        if(string::npos != (p_string.find(m_Fette[i].LeseNamen())))
        {
            BerechnungLoeschen();

            m_Fette.erase(m_Fette.begin() + i);
            RetVal = true;
        }
    }

    return(RetVal);
}

void SeifenRezept::BerechnungLoeschen(void)
{
    m_MengeNaOH = 0.0f;
    m_MengeWasser = 0.0f;
}
