#ifndef ZUTATENLISTE_H
#define ZUTATENLISTE_H

#include <vector>
#include "zutat.h"

using namespace std;

class ZutatenListe
{
public:
    ZutatenListe();

    bool    ZutatenDateiOeffnen(string Dateiname);
    string  LesenFettName(unsigned int i);
    string  LesenAetherischesOelName(unsigned int i);
    bool    LesenFett(int i, Zutat *pZutat);
    bool    LesenAetherischesOel(int i, Zutat *pZutat);

protected:
    vector<Zutat> m_Fette;
    vector<Zutat> m_AetherischeOele;
    vector<Zutat> m_ParfuemOele;
    vector<Zutat> m_TonErden;
    vector<Zutat> m_Sontiges;
    vector<Zutat> m_Kraeuter;
    vector<Zutat> m_Fluessigkeiten;

    void        InhaltLoeschen(void);
    bool        ZutatLesen(int i, Zutat *pZutat, vector<Zutat> &pZutatenListe);

    static bool Sortieren(const Zutat &A, const Zutat &B);
};

#endif // ZUTATENLISTE_H
