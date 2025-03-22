#ifndef ZUTAT_H
#define ZUTAT_H

#include <string>


using namespace std;

typedef enum
{
    FETT,
    AETHERISCHES_OEL,
    TONERDE,
    PARFUEMOEL,
    SONSTIGES,
    KRAEUTER,
    FLUESSIGKEITEN,
    UNBEKANNT

} ZutatenTyp_e;


class Zutat
{
public:
    Zutat();

    bool        EigenschaftenSetzen(ZutatenTyp_e ZustatenTyp, string Eingenschaften);
    bool        MasseSetzen(int Masse);
    string      LeseNamen(void) const;

    int         MasseLesen(void)            { return(m_Masse_in_Gramm); };
    string      NamenLesen(void)            { return(m_Name); };
    float       VerseifungszahlLesen(void)  { return(m_Verseifungszahl); };

    //Zutat       operator = (const Zutat &other);

private:
    ZutatenTyp_e    m_ZutatenTyp;

    string          m_Name;
    string          m_Beschreibung;

    float           m_Verseifungszahl;
    bool            m_ist_fest;

    unsigned int    m_Masse_in_Gramm;
};

#endif // ZUTAT_H
