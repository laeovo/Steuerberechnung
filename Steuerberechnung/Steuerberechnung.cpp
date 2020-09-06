//
//  Steuerberechnung.cpp
//  Steuerberechnung
//
//  Created by Leo Vornberger on 30.08.20.
//  Copyright © 2020 Leo Vornberger. All rights reserved.
//

#include <iostream>

#include "Steuerberechnung.hpp"

using namespace std;

Steuerberechnung::Steuerberechnung() {
    
}

void Steuerberechnung::setzeParameter() {
    this->AF = false;
    this->AJAHR = 0;
    this->ALTER1 = false;
    this->ENTSCH = 0; // TODO: Hier KUG?
    this->F = 1;
//    this->JFREIB = 0;
//    this->JHINZU = 0;
//    this->JRE4 = 0;
    this->KRV = 0;
    this->KVZ = 1.50;
    this->LZZ = MONAT;
    this->LZZFREIB = 0;
    this->LZZHINZU = 0;
    this->PKV = 0;
    this->PVS = false;
    this->PVZ = true;
    this->R = 0;
    this->RE4 = 277765;
    this->STKL = 1;
    this->VJAHR = 2059;
    this->ZTABFB = 0;
}

void Steuerberechnung::run() {
    this->MPARA();
    this->MRE4JL();
    this->VBEZBSO = 0;
    this->KENNVMT = 0;
    this->MRE4();
    this->MRE4ABZ();
    this->MBERECH();
    this->MSONST();
    this->MVMT();
    
    cout << this->LSTLZZ/100. << endl;
}

void Steuerberechnung::MPARA() {
    if (KRV < 2) {
        if (KRV == 0) {
            BBGRV = 82800;
        }
        else {
            BBGRV = 77400;
        }
        RVSATZAN = 0.093;
        TBSVORV = 0.8;
    }
    BBGKVPV = 56250;
    KVSATZAN = KVZ/2/100 + 0.07;
    KVSATZAG = 0.0055 + 0.07;
    if (PVS) {
        PVSATZAN = 0.02025;
        PVSATZAG = 0.01025;
    }
    else {
        PVSATZAN = 0.01525;
        PVSATZAG = 0.01525;
    }
    if (PVZ) {
        PVSATZAN += 0.0025;
    }
    W1STKL5 = 10898;
    W2STKL5 = 28526;
    W3STKL5 = 216400;
    GFB = 6408;
    SOLZFREI = 972;
}

void Steuerberechnung::MRE4JL() {
    switch (LZZ) {
        case JAHR:
        {
            ZRE4J = RE4 / 100.;
            ZVBEZJ = VBEZ / 100.;
            JLFREIB = LZZFREIB / 100.;
            JLHINZU = LZZHINZU / 100.;
            break;
        }
        case MONAT:
        {
            ZRE4J = RE4 * 12 / 100.;
            ZVBEZJ = VBEZ * 12 / 100.;
            JLFREIB = LZZFREIB * 12 / 100.;
            JLHINZU = LZZHINZU * 12 / 100.;
            break;
        }
        case WOCHE:
        {
            ZRE4J = round(RE4 * 360 / 7.) / 100.;
            ZVBEZJ = round(VBEZ * 360 / 7.) / 100.;
            JLFREIB = round(LZZFREIB * 360 / 7.) / 100.;
            JLHINZU = round(LZZHINZU * 360 / 7.) / 100.;
            break;
        }
        case TAG:
        {
            ZRE4J = RE4 * 360 / 100.;
            ZVBEZJ = VBEZ * 360 / 100.;
            JLFREIB = LZZFREIB * 360 / 100.;
            JLHINZU = LZZHINZU * 360 / 100.;
            break;
        }
        default:
            break;
    }
    if (!AF) {
        F = 1.000;
    }
}

void Steuerberechnung::MRE4() {
    if (ZVBEZJ == 0) {
        FVBZ = 0;
        FVB = 0.00;
        FVBZSO = 0;
        FVBSO = 0.00;
    }
    else {
        if (VJAHR < 2006) {
            J = 1;
        }
        else {
            if (VJAHR < 2040) {
                J = VJAHR - 2004;
            }
            else {
                J = 36;
            }
        }
        if (LZZ == JAHR) {
            VBEZB = VBEZM * ZMVB + VBEZS;
            HFVB = TAB2(J) / 12 * ZMVB; // TAB2(J) ist immer durch 12 teilbar
            FVBZ = ceil(TAB3(J) / 12. * ZMVB);
        }
        else {
            VBEZB = VBEZM * 12 + VBEZS;
            HFVB = TAB2(J);
            FVBZ = TAB3(J);
        }
        FVB = ceil(VBEZB * TAB1(J)) / 100;
        if (FVB > HFVB) {
            FVB = HFVB;
        }
        if (FVB > ZVBEZJ) {
            FVB = ZVBEZJ;
        }
        FVBSO = FVB + ceil(VBEZBSO * TAB1(J)) / 100;
        if (FVBSO > TAB2(J)) {
            FVBSO = TAB2(J);
        }
        HFVBZSO = (VBEZB + VBEZBSO) / 100. - FVBSO;
        FVBZSO = FVBZ + ceil(VBEZBSO / 100.);
        if (FVBZSO > HFVBZSO) {
            FVBZSO = ceil(HFVBZSO);
        }
        if (FVBZSO > TAB3(J)) {
            FVBZSO = TAB3(J);
        }
        HFVBZ = VBEZB/100. - FVB;
        if (FVBZ > HFVBZ) {
            FVBZ = ceil(HFVBZ);
        }
    }
    MRE4ALTE();
}

void Steuerberechnung::MRE4ALTE() {
    if (!ALTER1) {
        ALTE = 0;
    }
    else {
        if (AJAHR < 2006) {
            K = 1;
        }
        else {
            if (AJAHR < 2040) {
                K = AJAHR - 2004;
            }
            else {
                K = 36;
            }
        }
        BMG = ZRE4J - ZVBEZJ;
        ALTE = ceil(BMG * TAB4(K));
        HBALTE = TAB5(K);
        if (ALTE > HBALTE) {
            ALTE = HBALTE;
        }
    }
}

void Steuerberechnung::MRE4ABZ() {
    ZRE4 = ZRE4J - FVB - ALTE - JLFREIB + JLHINZU;
    cout << "ZRE4 = " << ZRE4 << " Euro (Auf Jahr hochgerechnetes RE4)" << endl;
    if (ZRE4 < 0) {
        ZRE4 = 0;
    }
    ZRE4VP = ZRE4J;
    if (KENNVMT == 2) {
        ZRE4VP -= ENTSCH / 100.;
    }
    ZVBEZ = ZVBEZJ - FVB;
    if (ZVBEZ < 0) {
        ZVBEZ = 0;
    }
}

void Steuerberechnung::MBERECH() {
    MZTABFB();
    VFRB = (ANP + FVB + FVBZ) * 100;
    cout << "Verbrauchter Freibetrag: " << VFRB << " Cent" << endl;
    MLSTJAHR();
//    WVFRB = (ZVE - GFB) * 100;
//    if (WVFRB < 0) {
//        WVFRB = 0;
//    }
    LSTJAHR = ST * F;
    cout << "LSTJAHR = " << LSTJAHR << " Euro" << endl;
    UPLSTLZZ();
    UPVKVLZZ();
    if (ZKF > 0) {
        ZTABFB += KFB;
        cout << "Feste Tabellenfreibeträge (ohne Vorsorgepauschale) = " << ZTABFB << " Euro" << endl;
        MRE4ABZ();
        MLSTJAHR();
        JBMG = ST * F;
        cout << "Jahres-LSt für Soli-Berechnung: " << JBMG << " Euro" << endl;
    }
    else {
        JBMG = LSTJAHR;
        cout << "Jahres-LSt für Soli-Berechnung: " << JBMG << " Euro" << endl;
    }
    MSOLZ();
}

void Steuerberechnung::MZTABFB() {
    ANP = 0;
    if (ZVBEZ >= 0) {
        if (ZVBEZ < FVBZ) {
            FVBZ = ZVBEZ;
        }
    }
    if (STKL < 6) {
        if (ZVBEZ > 0) {
            if (ZVBEZ - FVBZ < 102) {
                ANP = ceil(ZVBEZ - FVBZ);
            }
            else {
                ANP = 102;
            }
        }
    }
    else {
        FVBZ = 0;
        FVBZSO = 0;
    }
    if (STKL < 6) {
        if (ZRE4 > ZVBEZ) {
            if (ZRE4 - ZVBEZ < 1000) {
                ANP = ceil(ANP + ZRE4 - ZVBEZ);
            }
            else {
                ANP += 1000;
            }
        }
    }
    KZTAB = 1;
    switch(STKL) {
        case 1:
        {
            SAP = 36;
            KFB = ZKF * 7812;
            break;
        }
        case 2:
        {
            EFA = 1908;
            SAP = 36;
            KFB = ZKF * 7812;
            break;
        }
        case 3:
        {
            KZTAB = 2;
            SAP = 36;
            KFB = ZKF * 7812;
            break;
        }
        case 4:
        {
            SAP = 36;
            KFB = ZKF * 3906;
            break;
        }
        case 5:
        {
            SAP = 36;
            KFB = 0;
            break;
        }
        default:
        {
            KFB = 0;
            break;
        }
    }
    ZTABFB = EFA + ANP + SAP + FVBZ;
}

void Steuerberechnung::MLSTJAHR() {
    UPEVP();
    if (KENNVMT != 1) {
        ZVE = ZRE4 - ZTABFB - VSP;
        cout << "Zu versteuerndes Einkommen = " << ZVE << " Euro" << endl;
        UPMLST();
    }
    else {
        ZVE = ZRE4 - ZTABFB - VSP - VMT/100 - VKAPA/100;
        cout << "ZVE = " << ZVE << " Euro" << endl;
        if (ZVE < 0) {
            cout << "ZVE < 0!" << endl;
            ZVE = (ZVE + VMT/100 + VKAPA/100) / 5;
            cout << "ZVE = " << ZVE << " Euro" << endl;
            UPMLST();
            ST = ST * 5;
            cout << "Tarifliche ESt = " << ST << " Euro" << endl;
        }
        else {
            UPMLST();
            STOVMT = ST;
            cout << "STOVMT = " << STOVMT << " Euro" << endl;
            ZVE = ZVE + (VMT/100 + VKAPA/100) / 5;
            cout << "ZVE = " << ZVE << " Euro" << endl;
            UPMLST();
            ST = (ST - STOVMT) * 5 + STOVMT;
            cout << "Tarifliche ESt = " << ST << " Euro" << endl;
        }
    }
}

void Steuerberechnung::UPEVP() {
    if (KRV > 1) {
        VSP1 = 0;
    }
    else {
        if (ZRE4VP > BBGRV) {
            ZRE4VP = BBGRV;
        }
        VSP1 = TBSVORV * ZRE4VP;
        VSP1 *= RVSATZAN;
    }
    VSP2 = 0.12 * ZRE4VP;
    if (STKL == 3) {
        VHB = 3000;
    }
    else {
        VHB = 1900;
    }
    if (VSP2 > VHB) {
        VSP2 = VHB;
    }
    VSPN = ceil(VSP1 + VSP2);
    MVSP();
    if (VSPN > VSP) {
        VSP = VSPN;
        cout << "VSP = " << VSP << " Euro" << endl;
    }
}

void Steuerberechnung::MVSP() {
    if (ZRE4VP > BBGKVPV) {
        ZRE4VP = BBGKVPV;
    }
    if (PKV > 0) {
        if (STKL == 6) {
            VSP3 = 0;
        }
        else {
            VSP3 = PKPV * 12 / 100.;
            if (PKV == 2) {
                VSP3 -= ZRE4VP * (KVSATZAG + PVSATZAG);
            }
        }
    }
    else {
        VSP = ceil(VSP3 + VSP1);
        cout << "VSP = " << VSP << " Euro" << endl;
    }
}

void Steuerberechnung::UPMLST() {
    if (ZVE < 1) {
        ZVE = 0;
        X = 0;
    }
    else {
        X = floor(ZVE / KZTAB);
    }
    if (STKL < 5) {
        UPTAB20();
    }
    else {
//        MST5bis6();
    }
}

void Steuerberechnung::UPTAB20() {
    if (X < GFB + 1) {
        ST = 0;
    }
    else if (X < 14533) {
        Y = (X - GFB) / 10000;
        RW = Y * 972.87;
        RW += 1400;
        ST = RW * Y;
    }
    else if (X < 57052) {
        Y = (X-14532) / 10000.;
        RW = Y * 212.02;
        RW += 2397;
        RW *= Y;
        ST = RW + 972.79;
    }
    else if (X < 270501) {
        ST = X * 0.42 - 8963.74;
    }
    else {
        ST = X * 0.45 - 17078.74;
    }
    ST *= KZTAB;
}

void Steuerberechnung::UPLSTLZZ() {
    JW = LSTJAHR * 100;
    cout << "JW = " << JW << " Cent" << endl;
    UPANTEIL();
    LSTLZZ = ANTEIL1;
}

void Steuerberechnung::UPVKVLZZ() {
    UPVKV();
    JW = VKV;
    cout << "JW = " << JW << " Cent" << endl;
    UPANTEIL();
    VKVLZZ = ANTEIL1;
}

void Steuerberechnung::UPVKV() {
    cout << "UPVKV()" << endl;
    if (PKV > 0) {
        if (VSP2 > VSP3) {
            VKV = VSP2 * 100;
        }
        else {
            VKV = VSP3 * 100;
        }
    }
    else {
        VKV = 0;
    }
}

void Steuerberechnung::UPANTEIL() {
    switch (LZZ) {
        case JAHR:
            ANTEIL1 = JW;
            break;
        case MONAT:
            ANTEIL1 = floor(JW / 12.);
            break;
        case WOCHE:
            ANTEIL1 = floor(JW * 7 / 360.);
            break;
        case TAG:
            ANTEIL1 = floor(JW / 360.);
            break;
    }
}

void Steuerberechnung::MSOLZ() {
    SOLZFREI *= KZTAB;
    if (JBMG > SOLZFREI) {
        int SOLZJcent = floor(100 * JBMG * 0.055);
        SOLZJ = SOLZJcent / 100.;
        SOLZMIN = (JBMG - SOLZFREI) * 20. / 100;
        if (SOLZMIN < SOLZJ) {
            SOLZJ = SOLZMIN;
        }
        JW = SOLZJ * 100;
        UPANTEIL();
        SOLZLZZ = ANTEIL1;
    }
    else {
        SOLZLZZ = 0;
    }
    if (R > 0) {
        // TODO: Kirchensteuer
    }
    else {
        BK = 0;
    }
}

void Steuerberechnung::MSONST() {
//    LZZ = JAHR;
//    if (ZMVB == 0) {
//        ZMVB = 12;
//    }
//    if (SONSTB == 0) {
//        VKVSONST = 0;
//        LSTSO = 0;
//        STS = 0;
//        SOLZS = 0;
//        BKS = 0;
//    }
}

void Steuerberechnung::MVMT() {
    
}

double Steuerberechnung::TAB1(const int J) {
    if (J <= 16) {
        return 0.400 - (J-1) * 0.016;
    }
    else {
        return 0.160 - (J-16) * 0.008;
    }
}

int Steuerberechnung::TAB2(const int J) {
    if (J <= 16) {
        return 3000 - (J-1) * 120;
    }
    else {
        return 1200 - (J-16) * 60;
    }
}

int Steuerberechnung::TAB3(const int J) {
    if (J <= 16) {
        return 900 - (J-1) * 36;
    }
    else {
        return 360 - (J-16) * 18;
    }
}

double Steuerberechnung::TAB4(const int K) {
    if (K <= 16) {
        return 0.400 - (K-1) * 0.016;
    }
    else {
        return 0.160 - (K-16) * 0.008;
    }
}

int Steuerberechnung::TAB5(const int K) {
    if (K <= 16) {
        return 1900 - (J-1) * 76;
    }
    else {
        return 760 - (J-16) * 38;
    }
}
