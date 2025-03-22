#ifndef SEIFENREZEPT_H
#define SEIFENREZEPT_H

#include "zutatenliste.h"
#include <vector>

using namespace std;

class SeifenRezept : private ZutatenListe
{
public:
    SeifenRezept();

    void NamenSetzen(const string &p_Name);
    void ZutatenListeSetzen(ZutatenListe *p_ZutatenListe);
    bool RezeptAusgabeBildschirm(vector<string> *Ausgabe);
    void Berechnen(void);
    bool ZutatLoeschen(const string &p_string);

    bool ZutatHinzufuegen(ZutatenTyp_e typ, int index, int masse_in_gramm);

    private:
        ZutatenListe *m_pZutatenListe;

        string m_Name;
        float  m_MengeNaOH;
        float  m_MengeWasser;

        void BerechnungLoeschen(void);
        bool ZutatHinzufuegen(ZutatenTyp_e typ, Zutat &l_zutat, int masse_in_gramm);

        bool ZutatLoeschen(const string &p_string, vector<Zutat> *ZutatenListe);
};

#endif // SEIFENREZEPT_H
