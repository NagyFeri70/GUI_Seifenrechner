#ifndef SEIFENREZEPT_H
#define SEIFENREZEPT_H

#include "zutatenliste.h"

class SeifenRezept : private ZutatenListe
{
public:
    SeifenRezept();

    void NamenSetzen(const string &p_Name);
    void ZutatenListeSetzen(ZutatenListe *p_ZutatenListe);
    bool FettHinzufuegen(int p_Fettnummer, int fett_in_gramm);
    bool RezeptAusgabeBildschirm(string *Ausgabe);
    void Berechnen(void);

    private:
        ZutatenListe *m_pZutatenListe;

        string m_Name;
        float  m_MengeNaOH;
        float  m_MengeWasser;
};

#endif // SEIFENREZEPT_H
