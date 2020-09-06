//
//  Steuerberechnung.hpp
//  Steuerberechnung
//
//  Created by Leo Vornberger on 30.08.20.
//  Copyright © 2020 Leo Vornberger. All rights reserved.
//

#ifndef Steuerberechnung_hpp
#define Steuerberechnung_hpp

#include <math.h>
#include <stdio.h>
#include <vector>

enum Lohnzahlungszeitraum {
    JAHR = 1,
    MONAT = 2,
    WOCHE = 3,
    TAG = 4
};

class Steuerberechnung {
public:
    Steuerberechnung();
    void setzeParameter();
    void run();
private:
    void MPARA(); // Zuweisung von Werten für bestimmte Sozialversicherungsparameter
    void MRE4JL(); // Ermittlung des Jahresarbeitslohns nach § 39b Absatz 2 Satz 2 EStG
    void MRE4(); // Ermittlung der Freibeträge nach § 39b Absatz 2 Satz 3 EStG
    void MRE4ALTE(); // Ermittlung des Altersentlastungsbetrags
    void MRE4ABZ(); // Abzug der Freibeträge nach § 39b Absatz 2 Satz 3 und 4 EStG vom Jahresarbeitslohn
    void MBERECH(); // Ermittlung der Jahreslohnsteuer auf laufende Bezüge
    void MZTABFB(); // Ermittlung der festen Tabellenfreibeträge (ohne Vorsorgepauschale)
    void MLSTJAHR(); // Ermittlung der Jahreslohnsteuer für die Lohnsteuerberechnung)
    void UPEVP(); // Ermittlung der Vorsorgepauschale
    void MVSP();
    void UPMLST();
    void UPTAB20();
    void UPLSTLZZ(); // Ermittlung des Anteils der Jahreslohnsteuer für den Lohnzahlungszeitraum
    void UPVKVLZZ(); // Ermittlung des Anteils der berücksichtigten Vorsorgeaufwendungen für den Lohnzahlungszeitraum
    void UPVKV(); // Ermittlung des Jahreswertes der berücksichtigten privaten Kranken- und Pflegeversicherungsbeiträge
    void UPANTEIL(); // Ermittlung des Anteils der berücksichtigten privaten Kranken- und Pflegeversiche- rungsbeiträge für den Lohnzahlungszeitraum
    void MSOLZ(); // Ermittlung des Solidaritätszuschlags mit Aufteilung von SOLZJ und JBMG auf den Lohnzahlungszeitraum
    void MSONST(); // Berechnung sonstiger Bezüge ohne Vergütung für mehrjährige Tätigkeit
    void MVMT(); // Berechnung der Vergütung für mehrjährige Tätigkeit
    
    // Maßgebender Prozentsatz, Höchstbetrag des Versorgungsfreibetrags und Zuschlag zu, Versorgungsfreibetrag gem. §19 Absatz 2 EStG
    double TAB1(const int J); // Satz
    int TAB2(const int J); // Höchstbetrag
    int TAB3(const int J); // Zuschlag
    // Maßgebender Prozentsatz und Höchstbetrag des Altersentlastungsbetrags gem. § 24a EStG
    double TAB4(const int K); // Satz
    int TAB5(const int K); // Höchstbetrag
    
    bool AF = false; // true, wenn die Anwendung des Faktorverfahrens gewählt wurde (nur in Steuerklasse IV)
    int AJAHR = 0; // Auf die Vollendung des 64. Lebensjahres folgendes Kalenderjahr (erforderlich, wenn ALTER1=1)
    double ALTE = 0; // Altersentlastungsbetrag in Euro, Cent (2 Dezimalstellen)
    bool ALTER1 = false; // true, wenn das 64. Lebensjahr vor Beginn des Kalenderjahres vollendet wurde, in dem der Lohnzahlungszeitraum endet (§ 24a EStG), sonst false
    int ANP = 0; // Arbeitnehmer-Pauschbetrag/Werbungskosten-Pauschbetrag in Euro
    int ANTEIL1 = 0; // Auf den Lohnzahlungszeitraum entfallender Anteil von Jahreswerten auf ganze Cent abgerundet
    int BBGKVPV = 0; // Beitragsbemessungsgrenze in der gesetzlichen Krankenversicherung und der sozialen Pflegeversicherung in Euro
    int BBGRV = 0; // Allgemeine Beitragsbemessungsgrenze in der allgemeinen Rentenversicherung in Euro
    int BK = 0; // Bemessungsgrundlage für die Kirchenlohnsteuer in Cent
    double BMG = 0; // Bemessungsgrundlage für Altersentlastungsbetrag in Euro, Cent (2 Dezimalstellen)
    int EFA = 0; // Entlastungsbetrag für Alleinerziehende in Euro
    int ENTSCH = 0; // In VKAPA und VMT enthaltene Entschädigungen nach § 24 Nummer 1 EStG in Cent
    double F = 0; // eingetragener Faktor mit drei Nachkommastellen
    double FVB = 0; // Versorgungsfreibetrag in Euro, Cent (2 Dezimalstellen)
    double FVBSO = 0; // Versorgungsfreibetrag in Euro, Cent (2 Dezimalstellen) für die Berechnung der Lohnsteuer für den sonstigen Bezug
    int FVBZ = 0; // Zuschlag zum Versorgungsfreibetrag in Euro
    int FVBZSO = 0; // Zuschlag zum Versorgungsfreibetrag in Euro für die Berechnung der Lohnsteuer beim sonstigen Bezug
    int GFB = 0; // Grundfreibetrag in Euro
    int HBALTE = 0; // Maximaler Altersentlastungsbetrag in Euro
    int HFVB = 0; // Maßgeblicher maximaler Versorgungsfreibetrag in Euro
    double HFVBZ = 0; // Maßgeblicher maximaler Zuschlag zum Versorgungsfreibetrag in Euro, Cent (2 Dezimalstellen)
    double HFVBZSO = 0; // Maßgeblicher maximaler Zuschlag zum Versorgungsfreibetrag in Euro, Cent (2 Dezimalstellen) für die Berechnung der Lohnsteuer für den sonstigen Bezug
    int J = 0; // Nummer der Tabellenwerte für Versorgungsparameter
    int JBMG = 0; // Jahressteuer nach § 51a EStG, aus der Solidaritätszuschlag und Bemessungsgrundlage für die Kirchenlohnsteuer ermittelt werden, in Euro
    double JLFREIB = 0; // Auf einen Jahreslohn hochgerechneter LZZFREIB in Euro, Cent (2 Dezimalstellen)
    double JLHINZU = 0; // Auf einen Jahreslohn hochgerechneter LZZHINZU in Euro, Cent (2 Dezimalstellen)
    int JW = 0; // Jahreswert, dessen Anteil für einen Lohnzahlungszeitraum in UPANTEIL errechnet werden soll, in Cent
    int K = 0; // Nummer der Tabellenwerte für Parameter bei Altersentlastungsbetrag
    int KENNVMT = 0; // Merker für Berechnung Lohnsteuer für mehrjährige Tätigkeit. 0 = normale StBerechnung, 1 = StBerechnung für mehrjährige Tätigkeit, 2 = Ermittlung der Vorsorgepauschale ohne Entschädigungen i.S.d. §24 Nummer 1 EStG
    int KFB = 0; // Summe der Freibeträge für Kinder in Euro
    int KRV = 0; // Merker für die Vorsorgepauschale. 0 = Der AN ist in der gesetzlichen Rentenversicherung oder einer berufsständischen Versorgungseinrichtung pflichtversichert oder bei Befreiung von der Versicherungspflicht freiwillig versichert; es gilt die allgemeine Beitragsbemessungsgrenze (BBG West). 1 = der Arbeitnehmer ist in der gesetzlichen Rentenversicherung oder einer berufsständischen Versorgungseinrichtung pflichtversichert oder bei Befreiung von der Versicherungspflicht freiwillig versichert; es gilt die Beitragsbemessungsgrenze Ost (BBG Ost). 2 = wenn nicht 0 oder 1
    double KVSATZAG = 0; // Beitragssatz des Arbeitgebers zur Krankenversicherung unter Berücksichtigung des durchschnittlichen Zusatzbeitragssatzes für die Ermittlung des Arbeitgeberzuschusses (5 Dezimalstellen)
    double KVSATZAN = 0; // Beitragssatz des Arbeitnehmers zur Krankenversicherung (5 Dezimalstellen)
    double KVZ = 0; // Kassenindividueller Zusatzbeitragssatz bei einem gesetzlich krankenversicherten Arbeitnehmer in Prozent (bspw. 1,10 für 1,10 %) mit 2 Dezimalstellen. Es ist der volle Zusatzbeitragssatz anzugeben. Die Aufteilung in Arbeitnehmer- und Arbeitgeberanteil erfolgt im Programmablauf. Siehe i.Ü. auch Erläuterungen unter Pkt. 2.4.
    int KZTAB = 0; // Kennzahl für die Einkommensteuer-Tarifarten: 1 = Grundtarif, 2 = Splittingverfahren
    int LSTJAHR = 0; // Jahreslohnsteuer in Euro
    int LSTLZZ = 0; // Für den Lohnzahlungszeitraum einzubehaltende Lohnsteuer in Cent
    Lohnzahlungszeitraum LZZ = MONAT; // Lohnzahlungszeitraum: 1 = Jahr, 2 = Monat, 3 = Woche, 4 = Tag
    int LZZFREIB = 0; // Der als elektronisches Lohnsteuerabzugsmerkmal für den Arbeitgeber nach § 39e EStG festgestellte oder in der Bescheinigung für den Lohnsteuerabzug 2020 eingetragene Freibetrag für den Lohnzahlungszeitraum in Cent
    int LZZHINZU = 0; // Der als elektronisches Lohnsteuerabzugsmerkmal für den Arbeitgeber nach § 39e EStG festgestellte oder in der Bescheinigung für den Lohnsteuerabzug 2020 eingetragene Hinzurechnungsbetrag für den Lohnzahlungszeitraum in Cent
    int PKPV = 0; // Dem Arbeitgeber mitgeteilte Beiträge des Arbeitnehmers für eine private Basiskranken- bzw. Pflege-Pflichtversicherung im Sinne des § 10 Absatz 1 Nummer 3 EStG in Cent; der Wert ist unabhängig vom Lohnzahlungszeitraum immer als Monatsbetrag anzugeben
    int PKV = 0; // 0 = gesetzlich krankenversicherte Arbeitnehmer, 1 = ausschließlich privat krankenversicherte Arbeitnehmer ohne Arbeitgeberzuschuss, 2 = ausschließlich privat krank
    bool PVS = 0; // true, wenn bei der sozialen Pflegeversicherung die Besonderheiten in Sachsen zu berücksichtigen sind bzw. zu berücksichtigen wären
    double PVSATZAG = 0; // Beitragssatz des Arbeitgebers zur Pflegeversicherung (5 Dezimalstellen)
    double PVSATZAN = 0; // Beitragssatz des Arbeitnehmers zur Pflegeversicherung (5 Dezimalstellen)
    bool PVZ = 0; // true, wenn der Arbeitnehmer den Zuschlag zur sozialen Pflegeversicherung zu zahlen hat
    int R = 0; // Religionsgemeinschaft des Arbeitnehmers lt. elektronischer Lohnsteuerabzugsmerkmale oder der Bescheinigung für den Lohnsteuerabzug 2020 (bei keiner Religionszugehörigkeit = 0)
    int RE4 = 0; // Steuerpflichtiger Arbeitslohn für den Lohnzahlungszeitraum vor Berücksichtigung des Versorgungsfreibetrags und des Zuschlags zum Versorgungsfreibetrag, des Altersentlastungsbetrags und des als elektronisches Lohnsteuerabzugsmerkmal festgestellten oder in der Bescheinigung für den Lohnsteuerabzug 2020 für den Lohnzahlungszeitraum eingetragenen Freibetrags bzw. Hinzurechnungsbetrags in Cent
    double RVSATZAN = 0; // Beitragssatz des Arbeitnehmers in der allgemeinen gesetzlichen Rentenversicherung (vier Dezimalstellen)
    double RW = 0; // Rechenwert in Gleitkommadarstellung
    int SAP = 0; // Sonderausgaben-Pauschbetrag in Euro
    int SOLZFREI = 0; // Freigrenze für den Solidaritätszuschlag in Euro
    double SOLZJ = 0; // Solidaritätszuschlag auf die Jahreslohnsteuer in Euro, Cent (2 Dezimalstellen)
    int SOLZLZZ = 0; // Für den Lohnzahlungszeitraum einzubehaltender Solidaritätszuschlag in Cent
    double SOLZMIN = 0; // Zwischenwert für den Solidaritätszuschlag auf die Jahreslohnsteuer in Euro, Cent (2 Dezimalstellen)
    int SONSTB = 0; // Sonstige Bezüge (ohne Vergütung aus mehrjähriger Tätigkeit) einschließlich Sterbegeld bei Versorgungsbezügen sowie Kapitalauszahlungen/Abfindungen, soweit es sich nicht um Bezüge für mehrere Jahre handelt, in Cent (ggf. 0)
    int ST = 0; // Tarifliche Einkommensteuer in Euro
    int STKL = 0; // Steuerklasse
    int STOVMT = 0; // Zwischenfeld zur Ermittlung der Steuer auf Vergütungen für mehrjährige Tätigkeit in Euro
    double TBSVORV = 0; // Teilbetragssatz der Vorsorgepauschale für die Rentenversicherung (zwei Dezimalstellen)
    int VBEZ = 0; // In RE4 enthaltene Versorgungsbezüge in Cent (ggf. 0) ggf. unter Berücksichtigung einer geänderten Bemessungsgrundlage nach § 19 Absatz 2 Satz 10 und 11 EStG
    int VBEZB = 0; //  Bemessungsgrundlage für den Versorgungsfreibetrag in Cent
    int VBEZBSO = 0; // Bemessungsgrundlage für den Versorgungsfreibetrag in Cent für den sonstigen Bezug;
    int VBEZM = 0; // Versorgungsbezug im Januar 2005 bzw. für den ersten vollen Monat, wenn der Versorgungsbezug erstmalig nach Januar 2005 gewährt wurde, in Cent
    int VBEZS = 0; // Voraussichtliche Sonderzahlungen von Versorgungsbezügen im Kalenderjahr des Versorgungsbeginns bei Versorgungsempfängern ohne Sterbegeld, Kapitalauszahlungen/Abfindungen in Cent
    int VFRB = 0; // Verbrauchter Freibetrag bei Berechnung des laufenden Arbeitslohns, in Cent
    double VHB = 0; //Höchstbetrag der Mindestvorsorgepauschale für die Kranken- und Pflegeversicherung in Euro, Cent (2 Dezimalstellen)
    int VJAHR = 0; // Jahr, in dem der Versorgungsbezug erstmalig gewährt wurde; werden mehrere Versorgungsbezüge gezahlt, wird aus Vereinfachungsgründen für die Berechnung das Jahr des ältesten erstmaligen Bezugs herangezogen; auf die Möglichkeit der getrennten Abrechnung verschiedenartiger Bezüge (§ 39e Absatz 5a EStG) wird im Übrigen verwiesen
    int VKAPA = 0; // Entschädigungen/Kapitalauszahlungen/Abfindungen/Nachzahlungen bei Versorgungsbezügen für mehrere Jahre in Cent (ggf. 0)
    int VKV = 0; // Jahreswert der berücksichtigten Beiträge zur privaten Basis- Krankenversicherung und privaten Pflege-Pflichtversicherung (ggf. auch die Mindestvorsorgepauschale) in Cent
    int VKVLZZ = 0; // Für den Lohnzahlungszeitraum berücksichtigte Beiträge des Arbeitnehmers zur privaten Basis-Krankenversicherung und privaten Pflege-Pflichtversicherung (ggf. auch die Mindestvorsorgepauschale) in Cent beim laufenden Arbeitslohn. Für Zwecke der Lohnsteuerbescheinigung sind die einzelnen Ausgabewerte außerhalb des eigentlichen Lohnsteuerberechnungsprogramms zu addieren; hinzuzurechnen sind auch die Ausgabewerte VKVSONST.
    int VMT = 0; // Entschädigungen und Vergütung für mehrjährige Tätigkeit ohne Kapitalauszahlungen und ohne Abfindungen bei Versorgungsbezügen in Cent (ggf. 0)
    double VSP = 0; // Vorsorgepauschale mit Teilbeträgen für die Rentenversicherung sowie die gesetzliche Kranken- und soziale Pflegeversicherung nach fiktiven Beträgen oder ggf. für die private Basiskrankenversicherung und private Pflege-Pflichtversicherung in Euro, Cent (2 Dezimalstellen)
    double VSP1 = 0; // Zwischenwert 1 bei der Berechnung der Vorsorgepauschale in Euro, Cent (2 Dezimalstellen)
    double VSP2 = 0; // Zwischenwert 2 bei der Berechnung der Vorsorgepauschale in Euro, Cent (2 Dezimalstellen)
    double VSP3 = 0; // Vorsorgepauschale mit Teilbeträgen für die gesetzliche Kranken- und soziale Pflegeversicherung nach fiktiven Beträgen oder ggf. für die private Basiskrankenversicherung und private Pflege- Pflichtversicherung in Euro, Cent (2 Dezimalstellen)
    double VSPN = 0; // Vorsorgepauschale mit Teilbeträgen für die Rentenversicherung sowie der Mindestvorsorgepauschale für die Kranken- und Pflegeversicherung in Euro, Cent (2 Dezimalstellen)
    int W1STKL5 = 0; // Erster Grenzwert in Steuerklasse V/VI in Euro
    int W2STKL5 = 0; // Zweiter Grenzwert in Steuerklasse V/VI in Euro
    int W3STKL5 = 0; // Dritter Grenzwert in Steuerklasse V/VI in Euro
    int WVFRB = 0; // Für die weitergehende Berücksichtigung des Steuerfreibetrags nach dem DBA Türkei verfügbares ZVE über dem Grundfreibetrag bei der Berechnung des laufenden Arbeitslohns, in Cent
    double X = 0; // Zu versteuerndes Einkommen gem. § 32a Absatz 1 und 5 EStG in Euro, Cent (2 Dezimalstellen)
    double Y = 0; // Gem. § 32a Absatz 1 EStG (6 Dezimalstellen)
    double ZKF = 0; // Zahl der Freibeträge für Kinder (eine Dezimalstelle, nur bei Steuerklassen I, II, III und IV)
    int ZMVB = 0; // Zahl der Monate, für die im Kalenderjahr Versorgungsbezüge gezahlt werden [nur erforderlich bei Jahresberechnung (LZZ = 1)]
    double ZRE4 = 0; // Auf einen Jahreslohn hochgerechnetes RE4 in Euro, Cent (2 Dezimalstellen) nach Abzug der Freibeträge nach § 39b Absatz 2 Satz 3 und 4 EStG
    double ZRE4J = 0; // Auf einen Jahreslohn hochgerechnetes RE4 in Euro, Cent (2 Dezimalstellen)
    double ZRE4VP = 0; // Auf einen Jahreslohn hochgerechnetes RE4, ggf. nach Abzug der Entschädigungen i.S.d. § 24 Nummer 1 EStG in Euro, Cent (2 Dezimalstellen)
    double ZTABFB = 0; // Feste Tabellenfreibeträge (ohne Vorsorgepauschale) in Euro, Cent (2 Dezimalstellen)
    double ZVBEZ = 0; // Auf einen Jahreslohn hochgerechnetes VBEZ abzüglich FVB in Euro, Cent (2 Dezimalstellen)
    double ZVBEZJ = 0; // Auf einen Jahreslohn hochgerechnetes VBEZ in Euro, Cent (2 Dezimalstellen)
    double ZVE = 0; // Zu versteuerndes Einkommen in Euro, Cent (2 Dezimalstellen)
};

#endif /* Steuerberechnung_hpp */
