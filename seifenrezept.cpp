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

    Ausgabe->clear();

    Ausgabe->push_back(m_Name + "\n");

    for(auto zutatenliste:m_mapAlleZutaten)
    {
        for(Zutat l_zutat:(*zutatenliste.second))
        {
            sprintf(ch, "%4d", l_zutat.MasseLesen());

            string Masse(ch);
            Ausgabe->push_back(Masse + " g " + l_zutat.NamenLesen());
        }
    }

    if((m_MengeNaOH > 1.0f) && (m_MengeWasser > 1.0f))
    {
        masse_gerundet = (int)(m_MengeWasser + 0.5f);
        sprintf(ch, "%4d", masse_gerundet);

        string Masse(ch);
        Ausgabe->push_back("\n" + Masse + " g " + "Wasser" + "\n");

        for(i = 4; i <= 8; i++)
        {            
            AnteilNaOH = m_MengeNaOH * (100.0f -(float)i) * 0.01f;
            masse_gerundet = (int)(AnteilNaOH + 0.5f);
            sprintf(ch, "%4d g NaOH - %d %% Überfettung", masse_gerundet, i);

            string Masse(ch);;
            Ausgabe->push_back(Masse);
        }
    }


    return RetVal;
}

bool  SeifenRezept::ZutatHinzufuegen(ZutatenTyp_e typ, int index, int masse_in_gramm)
{
    bool RetVal = true;
    Zutat l_zutat;

    if(NULL != m_pZutatenListe)
    {
        m_pZutatenListe->LesenZutat(typ, index, &l_zutat);

        RetVal = ZutatHinzufuegen(typ, l_zutat, masse_in_gramm);
    }
    else
    {
        RetVal = false;
    }


    return(RetVal);
}


 bool  SeifenRezept::ZutatHinzufuegen(ZutatenTyp_e typ, Zutat &l_zutat, int masse_in_gramm)
{
     bool RetVal = true;
     vector<Zutat> *dummy;
     bool found = false;
     int i = 0;

     BerechnungLoeschen();

     l_zutat.MasseSetzen(masse_in_gramm);

     dummy = m_mapAlleZutaten[typ];

     for(Zutat &p_zutat:(*dummy))
     {
         if(p_zutat.LeseNamen() == l_zutat.LeseNamen())
         {
             found = true;
             break;
         }

         i++;
     }

     if(false == found)
     {
         (*dummy).push_back(l_zutat);
     }
     else
     {
         (*dummy)[i] = l_zutat;
     }

     return(RetVal);
}

bool SeifenRezept::ZutatLoeschen(const string &p_string)
{
    bool RetVal = false;

    for(auto zutatenliste:m_mapAlleZutaten)
    {
        RetVal = ZutatLoeschen(p_string, zutatenliste.second);
        if(true == RetVal)
        {
            return(RetVal);
        }
    }

    return(RetVal);
}

bool SeifenRezept::ZutatLoeschen(const string &p_string, vector<Zutat> *ZutatenListe)
{
    bool RetVal = false;
    int i = 0;

    for(Zutat &l_zutat:(*ZutatenListe))
    {
        if(string::npos != (p_string.find(l_zutat.LeseNamen())))
        {
            BerechnungLoeschen();

            ZutatenListe->erase(ZutatenListe->begin() + i);
            RetVal = true;
            break;
        }

        i++;
    }

    return(RetVal);
}


void SeifenRezept::BerechnungLoeschen(void)
{
    m_MengeNaOH = 0.0f;
    m_MengeWasser = 0.0f;
}
