#include "seifenrezept.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

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

    for(i = 0; i < m_Fluessigkeiten.size(); i++)
    {
        m_MengeWasser -= m_Fluessigkeiten[i].MasseLesen();
    }

    m_MengeWasser *= 1.0/3.0;
    if(m_MengeWasser < 0.0f)
    {
        m_MengeWasser = 0.0f;
    }
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

bool SeifenRezept::RezeptOeffnen(string Dateiname)
{
    bool RetVal = true;
    ifstream datei(Dateiname);

    if(!datei.fail())
    {
        string          inhaltzeile;
        bool            name_found = false;
        Zutat           zutat;
        ZutatenTyp_e    Typ;
        vector<Zutat>  *Liste;

        InhaltLoeschen();

        getline(datei,inhaltzeile);
        if(string::npos == inhaltzeile.find(DateiKennung.c_str()))
        {
            return(false);
        }

        while(getline(datei,inhaltzeile))
        {
            if(0 != inhaltzeile.length())
            {
                if(string::npos != inhaltzeile.find("-["))
                {
                    if(string::npos != inhaltzeile.find(DateiNamensKennung))
                    {
                        name_found = true;
                    }
                    else
                    {
                        for(auto &Kennzeichnung:m_mapDateiInhaltsKennzeichnung)
                        {
                            if(string::npos != inhaltzeile.find(Kennzeichnung.second))
                            {
                                name_found = false;
                                Typ = Kennzeichnung.first;
                                Liste = m_mapAlleZutaten[Kennzeichnung.first];
                                break;
                            }
                        }
                    }
                }
                else
                {
                    if(true == name_found)
                    {
                        m_Name = inhaltzeile;
                    }
                    else
                    {
                        zutat.EigenschaftenSetzen(Typ, inhaltzeile, true);
                        (*Liste).push_back(zutat);
                    }
                }
            }
        }

        datei.close();
    }
    else
    {
        RetVal = false;
    }

    return(RetVal);
}

bool SeifenRezept::RezeptSpeichern(string Dateiname)
{
    bool RetVal = true;
    ofstream datei(Dateiname, ios::out);

    if(!datei.fail())
    {
        datei << DateiKennung << endl << endl;
        datei << DateiNamensKennung << endl;
        datei << m_Name << endl << endl;

        for(auto &Kennzeichnung:m_mapDateiInhaltsKennzeichnung)
        {
            vector<Zutat> * Zutaten = m_mapAlleZutaten[Kennzeichnung.first];

            datei << Kennzeichnung.second << endl;

            for(auto &Zutat:(*Zutaten))
            {
                datei << Zutat.LeseNamen();

                if(FETT == Kennzeichnung.first)
                {
                    datei << ";" << Zutat.VerseifungszahlLesen();

                    if(true == Zutat.IstFest())
                    {
                        datei << ";" << "fest";
                    }
                    else
                    {
                        datei << ";" << "fluessig";
                    }
                }

                datei << ";" << Zutat.MasseLesen();

                datei << endl;
            }

            datei << endl;

        }

        datei.close();
    }
    else
    {
        RetVal = false;
    }

    return(RetVal);
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
