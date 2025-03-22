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

    bool    LesenZutat(ZutatenTyp_e typ, int index, Zutat *l_zutat);
    string  LesenZutatName(ZutatenTyp_e typ, unsigned int i);

protected:

    vector<Zutat> m_Fette;
    vector<Zutat> m_AetherischeOele;
    vector<Zutat> m_ParfuemOele;
    vector<Zutat> m_TonErden;
    vector<Zutat> m_Sontiges;
    vector<Zutat> m_Kraeuter;
    vector<Zutat> m_Fluessigkeiten;

    map<ZutatenTyp_e, vector<Zutat> *> m_mapAlleZutaten =
                        {
                            { FETT,             &m_Fette            },
                            { AETHERISCHES_OEL, &m_AetherischeOele  },
                            { TONERDE,          &m_TonErden         },
                            { PARFUEMOEL,       &m_ParfuemOele      },
                            { KRAEUTER,         &m_Kraeuter         },
                            { FLUESSIGKEITEN,   &m_Fluessigkeiten   },
                            { SONSTIGES,         &m_Sontiges         }
                        };

    void        InhaltLoeschen(void);
    bool        ZutatLesen(int i, Zutat *pZutat, vector<Zutat> &pZutatenListe);

    static bool Sortieren(const Zutat &A, const Zutat &B);
};

#endif // ZUTATENLISTE_H
