#ifndef ZUTATENLISTE_H
#define ZUTATENLISTE_H

#include <map>
#include <vector>
#include "zutat.h"

using namespace std;

class ZutatenListe
{
public:
    ZutatenListe();

    bool    ZutatenDateiOeffnen(string Dateiname);

    bool    LesenFett(int i, Zutat *pZutat);
    bool    LesenAetherischesOel(int i, Zutat *pZutat);
    bool    LesenTonerde(int i, Zutat *pZutat);
    bool    LesenParfuemOel(int i, Zutat *pZutat);

    string  LesenTonerdeName(unsigned int i);
    string  LesenFettName(unsigned int i);
    string  LesenAetherischesOelName(unsigned int i);
    string  LesenParfuemOelName(unsigned int i);

protected:

    vector<Zutat> m_Fette;
    vector<Zutat> m_AetherischeOele;
    vector<Zutat> m_ParfuemOele;
    vector<Zutat> m_TonErden;
    vector<Zutat> m_Sontiges;
    vector<Zutat> m_Kraeuter;
    vector<Zutat> m_Fluessigkeiten;


    vector<Zutat> *m_pAlleZutaten[7] = {
                                            &m_Fette,
                                            &m_AetherischeOele,
                                            &m_ParfuemOele,
                                            &m_TonErden,
                                            &m_Sontiges,
                                            &m_Kraeuter,
                                            &m_Fluessigkeiten,
                                        };

    void        InhaltLoeschen(void);
    bool        ZutatLesen(int i, Zutat *pZutat, vector<Zutat> &pZutatenListe);

    static bool Sortieren(const Zutat &A, const Zutat &B);
};

#endif // ZUTATENLISTE_H
