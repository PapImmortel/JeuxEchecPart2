 
#pragma warning( disable : 4996 ) 
 
#include "G2D.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
  
 
#define ECRAN_ACCUEIL 0
#define ECRAN_OPTIONS 1
#define INIT_PARTIE 2
#define ECRAN_JEU 3
#define ECRAN_Victoire_Blanc 4
#define ECRAN_Victoire_Noir 5
#define ECRAN_Pat 6


struct _plateau {
    string Map1 ="M M M M "
        " M M M M"
        "M M M M "
        " M M M M"
        "M M M M "
        " M M M M"
        "M M M M "
        " M M M M"
        ;

    string textureMur = "[77777777]"
        "[77777777]"
        "[77777777]"
        "[77777777]"
        "[77777777]"
        "[77777777]"
        "[77777777]"
        "[77777777]";
    string textureSol = "[66666666]"
        "[66666666]"
        "[66666666]"
        "[66666666]"
        "[66666666]"
        "[66666666]"
        "[66666666]"
        "[66666666]";
    string texturePossible = "[        ]"
        "[   GG   ]"
        "[  G  G  ]"
        "[ G GG G ]"
        "[ G GG G ]"
        "[  G  G  ]"
        "[   GG   ]"
        "[        ]";

    string positionPiece = "22222222"
        "22222222"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "11111111";

    void setPositionPiece(int x, int y, string valeur) { positionPiece.replace((8 - y - 1) * 8 + x,1,valeur); }
    int getPositionPiece(V2 pos) {
        int valeur = positionPiece[(8 - pos.y - 1) * 8 + pos.x] - 48;
        return valeur;
    }
    string getPlateau() { return positionPiece; }
    void resetPlateau(){positionPiece = "22222222"
        "22222222"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "11111111";
    }

};
struct _Piece {
    int couleur;
    V2 pos;
    bool estVivant;
    int typePiece;
    V2 Size;
    float Zoom;
    int IdTex;
    string Texture;
    bool noMove;
    int TimeDead = -1   ;

    _Piece(V2 _Pos, int _couleur) {
        pos = _Pos;
        couleur = _couleur;
        estVivant = true;
        noMove = true;
    }
    void setNoMove(bool _noMove) { noMove = _noMove; }
    int getNoMove() { return noMove; }
    void setTypePiece(int _typePiece) { typePiece = _typePiece; }
    void setEstVivant(bool _estVivant) { estVivant = _estVivant; }
    bool getEstVivant() { return estVivant; }
    void setCoord(V2 Coord) { pos = Coord; }
    V2 getCoord() { return pos; }
    int getCouleur() { return couleur; }
    void setZoomSize(float _Zoom) {Zoom = _Zoom;}
    void setIdTex(int _idTex) {
        IdTex = _idTex;
    }
    void setTexture(string _Texture) {
        Texture = _Texture;
    }
    int getTypePiece() { return typePiece; }
};
struct _Cavalier : public _Piece {
    string CavalierNoir =

        "[                       KKKKK                ]"
        "[                      KJ!!!JK               ]"
        "[                     KJ!!J!!JK              ]"
        "[                     KJ!JTJ!JK              ]"
        "[                      KJTB!JJK              ]"
        "[                      KTTB!TTK              ]"
        "[                      KTTTTTKK              ]"
        "[                    KKKKTTTKKKKK            ]"
        "[                   KNKKKKKKEEKNEK           ]"
        "[                   KKE?EEE??KNOJJK          ]"
        "[                  KOK?NNNN??KNO!JK          ]"
        "[                 KO?K?NNNN??KN?O!JK         ]"
        "[                 KNEKEKKKKKKKKN?O!EK        ]"
        "[      KKKKKKK     KKKKE?N??EKKKK??KK        ]"
        "[    KK!!!!!!!KK  K?O!KE?N??EK KEKKK         ]"
        "[   K!!!*!!*!!!*KK?K?EKE?N??EK  KO!KK        ]"
        "[  K*!****!**!**JK??KK K????EKK K?K?EK       ]"
        "[ KK**JKKJ*****JJJK?K K????EEEEKKKK?EK       ]"
        "[KF!OOK/FJ*JJ*JJ*JJKK KKKKKKEN?*K?EKKKK      ]"
        "[ KKNNOKKKJJJJJJ*JJJJK!KKKKKEKK?KKKEK*JK     ]"
        "[  KN?EO!!JKFJFJJJJJKKK!KKKKKOOKNKKKK***K    ]"
        "[  KN?E!JE!KF//JFFJJFFK!KKKSSKOK???EKK***K   ]"
        "[  K??E!K?EKFF//F/JF/FJ!SSS+WKOOK?EKEEK**K   ]"
        "[   KOOOK?K//FF////F/SSS+WWW++KGKKKNNEEKJJK  ]"
        "[   KNE!FEK///FF//SSS+WWW++GSS?KK?N?EEEEKJK  ]"
        "[   K?E!KK1F//FSSS+WWW++GSSSN?KK?NOOO!!EKJK  ]"
        "[   KE/FFK11FSS+WWW++GSSSFKNNN?EKOOO!!EEKJK  ]"
        "[   K/KF1K11S+WW++GSSSFJJJJKEEEKKEE!!EEEKK   ]"
        "[    KKKKKKSWW+GSSS/JJJ!**!KKKKEK?NEE?EEKK   ]"
        "[        KKSSSSSKKKJ!!*JJJ!JK?EEK????EEKJK   ]"
        "[        K??N???EEK*JJJFFJ!JK??EEKEEEEKKJK   ]"
        "[        KOON?O!!EKJFFF/FJ*KKE?EEKKKKKKJJJK  ]"
        "[       K1K?OO!EEKFF///FJJ*KE?EEEKF//FKJJJK  ]"
        "[      K111KN??KKFF///FFJ*JK?N??EKFF/FKJJJJK ]"
        "[     K11111KKKF11FFFFFJKKKKNNN?K/FFFFKJJJJJK]"
        "[     KFFKKKKKKKKKKFFFKK   KKKKKKK/FFFFKJJJJK]"
        "[     KFFK        KFFFK      K111KKKFF//KJKK ]"
        "[     K111KKK      KFFK      K111K1FKF//KK   ]"
        "[      KK11KSK     KFFK      K11K  1FKFFK    ]"
        "[       K111SK     K//FK    K111K   1KFFK    ]"
        "[        KKSSK     K//FK    K111K    KFFK    ]"
        "[          KK       KF1K   K1111K    KFFK    ]"
        "[                   KF1KKK KSS1K    KFFFK    ]"
        "[            KKKKKKKKF1KKKKKSSSKKKKKKFFFKKK  ]"
        "[        KKKKKKKKKKKKFFFKKKKKKKKKKKKFFFKKKK  ]"
        "[       KKKKKKKKKKKKFGGKKKKKKKKKKKKKSSSKKK   ]"
        "[       KKKKKKKKKKKKSSGFKKKKKKKKKKKKSSSKKK   ]"
        "[        KKKKKKKKKKKSSSKKKKKKKKKKKKKKKKK     ]"
        "[             KKKKKKKKKKKKKKKK               ]";

    string CavalierBlanc =
        "[                       KKKKK                ]"
        "[                      KJ!!!JK               ]"
        "[                     KJ!!J!!JK              ]"
        "[                     KJ!JTJ!JK              ]"
        "[                      KJTK!JJK              ]"
        "[                      KTTK!TTK              ]"
        "[                      KTTTTTKK              ]"
        "[                    KKKKTTTKKKKK            ]"
        "[                   KXKKKKKKRRKXRK           ]"
        "[                   KKRZRRRZZKXOJJK          ]"
        "[                  KOKZXXXXZZKXO!JK          ]"
        "[                 KOZKZXXXXZZKXZO!JK         ]"
        "[                 KXRKRKKKKKKKKXZO!RK        ]"
        "[      KKKKKKK     KKKKRZXZZRKKKKZZKK        ]"
        "[    KK!!!!!!!KK  KZO!KRZXZZRK KRKKK         ]"
        "[   K!!!*!!*!!!*KKZKZRKRZXZZRK  KO!KK        ]"
        "[  K*!****!**!**JKZZKK KZZZZRKK KZKZRK       ]"
        "[ KK**JKKJ*****JJJKZK KZZZZRRRRKKKKZRK       ]"
        "[KF!OOK/FJ*JJ*JJ*JJKK KKKKKKRXZ*KZRKKKK      ]"
        "[ KKXXOKKKJJJJJJ*JJJJK!KKKKKRKKZKKKRK*JK     ]"
        "[  KXZRO!!JKFJFJJJJJKKK!KKKKKOOKXKKKK***K    ]"
        "[  KXZR!JR!KF//JFFJJFFK!KKKSSKOKZZZRKK***K   ]"
        "[  KZZR!KZRKFF//F/JF/FJ!SSS+WKOOKZRKRRK**K   ]"
        "[   KOOOKZK//FF////F/SSS+WWW++KGKKKXXRRKJJK  ]"
        "[   KXR!FRK///FF//SSS+WWW++GSSZKKZXZRRRRKJK  ]"
        "[   KZR!KK1F//FSSS+WWW++GSSSXZKKZXOOO!!RKJK  ]"
        "[   KR/FFK11FSS+WWW++GSSSFKXXXZRKOOO!!RRKJK  ]"
        "[   K/KF1K11S+WW++GSSSFJJJJKRRRKKRR!!RRRKK   ]"
        "[    KKKKKKSWW+GSSS/JJJ!**!KKKKRKZXRRZRRKK   ]"
        "[        KKSSSSSKKKJ!!*JJJ!JKZRRKZZZZRRKJK   ]"
        "[        KZZXZZZRRK*JJJFFJ!JKZZRRKRRRRKKJK   ]"
        "[        KOOXZO!!RKJFFF/FJ*KKRZRRKKKKKKJJJK  ]"
        "[       K1KZOO!RRKFF///FJJ*KRZRRRKF//FKJJJK  ]"
        "[      K111KXZZKKFF///FFJ*JKZXZZRKFF/FKJJJJK ]"
        "[     K11111KKKF11FFFFFJKKKKXXXZK/FFFFKJJJJJK]"
        "[     KFFKKKKKKKKKKFFFKK   KKKKKKK/FFFFKJJJJK]"
        "[     KFFK        KFFFK      K111KKKFF//KJKK ]"
        "[     K111KKK      KFFK      K111K1FKF//KK   ]"
        "[      KK11KSK     KFFK      K11K  1FKFFK    ]"
        "[       K111SK     K//FK    K111K   1KFFK    ]"
        "[        KKSSK     K//FK    K111K    KFFK    ]"
        "[          KK       KF1K   K1111K    KFFK    ]"
        "[                   KF1KKK KSS1K    KFFFK    ]"
        "[            KKKKKKKKF1KKKKKSSSKKKKKKFFFKKK  ]"
        "[        KKKKKKKKKKKKFFFKKKKKKKKKKKKFFFKKKK  ]"
        "[       KKKKKKKKKKKKFGGKKKKKKKKKKKKKSSSKKK   ]"
        "[       KKKKKKKKKKKKSSGFKKKKKKKKKKKKSSSKKK   ]"
        "[        KKKKKKKKKKKSSSKKKKKKKKKKKKKKKKK     ]"
        "[             KKKKKKKKKKKKKKKK               ]";

    _Cavalier(V2 _Pos, int _couleur) : _Piece(_Pos, _couleur)
    {
        setZoomSize(1.5);
        setTypePiece(2);
        if (_couleur == 1)
            setTexture(CavalierBlanc);
        else
            setTexture(CavalierNoir);
    }

};
struct _Dame : public _Piece {
    string reineBlanche =
        "[             K             ]"
        "[            KUK            ]"
        "[           KUVUK           ]"
        "[         KKKUVUKKK         ]"
        "[        KYOUUUUUOYK        ]"
        "[       KOUUUUUUUUYOK       ]"
        "[      KOYOOOYYYYOYOK       ]"
        "[      KOYYOOOOYOOYYOK      ]"
        "[      KOYOTTTOOTTOYOK      ]"
        "[     KOYOTTTTTTTTTOYOK     ]"
        "[     KOYYTBWTTTWBWYYOK     ]"
        "[     KOYYTBBTTTBBWYYOK     ]"
        "[      KOYHHTTTTTHHYOK      ]"
        "[     KOYYOTTTTTTTOYYOK     ]"
        "[    KOYYYYOTTRRTOYYYYOK    ]"
        "[   KOYOWOOOOTTTOOOOWOYOK   ]"
        "[   KOYOWWWTTTTTTTWWWOYOK   ]"
        "[  KOYYOOXWWWWTWWWWXOOYYOK  ]"
        "[  KOYOXXXIWWWWWWWIXXXOYOK  ]"
        "[   KOXXXXIIIIWIIIIXXXXOK   ]"
        "[    KXXXOIIIIIIIIIOXXXK    ]"
        "[   KXXXOYOIIIIIIIOYOXXXK   ]"
        "[  KXXXOYYOIIIIIIIOYYOXXXK  ]"
        "[ KTTTKKOOKHIIIIIHKOOKKTTTK ]"
        "[ KTTTK KKHHHIIIHHHKK  KTTTK]"
        "[  KKK  KHHHHHIHHHHHK   KKK ]"
        "[       KHHXHHHHHXHHK       ]"
        "[      KHHXXXHHHXXXHHK      ]"
        "[      KHZXXXXHXXXXZHK      ]"
        "[      KHZXXXZHZXXXZHK      ]"
        "[      KZXXXZXXXZXXXZK      ]"
        "[      KZXXXZXXXZXXXZK      ]"
        "[     KZXXXZXXXXXZXXXZK     ]"
        "[    KZXXXXZXXXXXZXXXXZK    ]"
        "[    KZXXXXZXXXXXZXXXXZK    ]"
        "[   KZXXXXZXXXXXXXZXXXXZK   ]"
        "[   KZXXXXZXXXXXXXZXXXXZK   ]"
        "[  KZXXXXZXXXXXXXXXZXXXXZK  ]"
        "[ KZXXXXZXXXXXXXXXXXZXXXXZK ]"
        "[ KZXXXZXXXXXXXXXXXXXZXXXZK ]"
        "[KZXXXZXXXXXXXXXXXXXXXZXXXZK]"
        "[KZXXZXXXXXXXXXXXXXXXXXZXXZK]"
        "[ KZXZXXXXXXXXXXXXXXXXXZXZK ]"
        "[  KZZZZZXXXXXXXXXXXZZZZZK  ]"
        "[   KKKKKZZZZZZZZZZZKKKKK   ]"
        "[        KKKKKKKKKKK        ]";


    string reineNoire =
        "[             K             ]"
        "[            KUK            ]"
        "[           KUVUK           ]"
        "[         KKKUVUKKK         ]"
        "[        KLFUUUUUFLK        ]"
        "[       KFUUUUUUUULFK       ]"
        "[      KFLFFFLLLLFLFK       ]"
        "[      KFLLFFFFLFFLLFK      ]"
        "[      KFLFTTTFFTTFLFK      ]"
        "[     KFLFTTTTTTTTTFLFK     ]"
        "[     KFLLTQVTTTVQTLLFK     ]"
        "[     KFLLTQQTTTQQTLLFK     ]"
        "[      KFLCCTTTTTCCLFK      ]"
        "[     KFLLFTTTTTTTFLLFK     ]"
        "[    KFLLLLFTTRRTFLLLLFK    ]"
        "[   KFLFWFFFFTTTFFFFWFLFK   ]"
        "[   KFLFWWWTTTTTTTWWWFLFK   ]"
        "[  KFLLFFNWWWWTWWWWNFFLLFK  ]"
        "[  KFLFNNNEWWWWWWWENNNFLFK  ]"
        "[   KFNNNNEEEEWEEEENNNNFK   ]"
        "[    KNNNFEEEEEEEEEFNNNK    ]"
        "[   KNNNFLFEEEEEEEFLFNNNK   ]"
        "[  KNNNFLLFEEEEEEEFLLFNNNK  ]"
        "[ KTTTKKFFKCEEEEECKFFKKTTTK ]"
        "[ KTTTK KKCCCEEECCCKK KTTTK ]"
        "[  KKK  KCCCCCECCCCCK  KKK  ]"
        "[       KCCNCCCCCNCCK       ]"
        "[      KCCNNNCCCNNNCCK      ]"
        "[      KCBNNNNCNNNNBCK      ]"
        "[      KCBNNNBCBNNNBCK      ]"
        "[      KBNNNBNNNBNNNBK      ]"
        "[      KBNNNBNNNBNNNBK      ]"
        "[     KBNNNBNNNNNBNNNBK     ]"
        "[    KBNNNNBNNNNNBNNNNBK    ]"
        "[    KBNNNNBNNNNNBNNNNBK    ]"
        "[   KBNNNNBNNNNNNNBNNNNBK   ]"
        "[   KBNNNNBNNNNNNNBNNNNBK   ]"
        "[  KBNNNNBNNNNNNNNNBNNNNBK  ]"
        "[ KBNNNNBNNNNNNNNNNNBNNNNBK ]"
        "[ KBNNNBNNNNNNNNNNNNNBNNNBK ]"
        "[KBNNNBNNNNNNNNNNNNNNNBNNNBK]"
        "[KBNNBNNNNNNNNNNNNNNNNNBNNBK]"
        "[ KBNBNNNNNNNNNNNNNNNNNBNBK ]"
        "[  KBBBBBNNNNNNNNNNNBBBBBK  ]"
        "[   KKKKKKBBBBBBBBBBBKKKK   ]"
        "[         KKKKKKKKKKK       ]"
        ;

    _Dame(V2 _Pos, int _couleur) : _Piece(_Pos, _couleur)
    {
        setZoomSize(1.7);
        setTypePiece(4);
        if (_couleur == 1)
            setTexture(reineBlanche);
        else
            setTexture(reineNoire);
    }

};
struct _Roi : public _Piece {
    string roiNoir =
        "[  K  KKKKKKK  K  ]"
        "[ KOKKPOPPPOPKKOK ]"
        "[ KOOPOOOPOOOPOOK ]"
        "[ KOOOOOOOOOOOOOK ]"
        "[ KWAWAAWAWAAWAWK ]"
        "[ KOOOOOOOOOOOOOK ]"
        "[ KJTWRTTTTTRWTJK ]"
        "[ KJTWKTTTTTKWTJK ]"
        "[KJTTWWTTTTTWWTTJK]"
        "[KJTTTTJJJJJTTTTJK]"
        "[KJJJTJTTTTTJTJJJK]"
        "[ KJJTJTTJTTJTJJK ]"
        "[  KJJJJJJJJJJJK  ]"
        "[  KKJJJJJJJJJSK  ]"
        "[ Y KSSSSCSSSSKK  ]"
        "[YAY KKKSCSKKKWK  ]"
        "[ YKPWWWSCSWWWPK  ]"
        "[ GKPPPWSCSWPPPK  ]"
        "[ YPPPPWBCBWPPPK  ]"
        "[ G KPPWMMMWPPKK  ]"
        "[ G KPPWBCBWPPTK  ]"
        "[ G KPPWBCBWPPK   ]"
        "[ G KPPWBCBWPPK   ]"
        "[ G KPPWBCBWPPK   ]"
        "[ G KKKWBCBWKKK   ]"
        "[      KKKKK      ]";

    string roiBlanc = "[  K  KKKKKKK  K  ]"
        "[ KYKKRYRRRYRKKYK ]"
        "[ KYYRYYYRYYYRYYK ]"
        "[ KYYYYYYYYYYYYYK ]"
        "[ KWAWAAWAWAAWAWK ]"
        "[ KYYYYYYYYYYYYYK ]"
        "[ KGTWDTTTTTDWTGK ]"
        "[ KGTWDTTTTTDWTGK ]"
        "[KGTTWWTTTTTWWTTGK]"
        "[KGTTTTGGGGGTTTTGK]"
        "[KGGGTGTTTTTGTGGGK]"
        "[ KGGTGTTGTTGTGGK ]"
        "[  KGGGGGGGGGGGK  ]"
        "[  KKGGGGGGGGGSK  ]"
        "[ Y KSSSSCSSSSKK  ]"
        "[YAY KKKSCSKKKWK  ]"
        "[ YKRWWWSCSWWWRK  ]"
        "[ GKRRRWSCSWRRRK  ]"
        "[ YRRRRWBCBWRRRK  ]"
        "[ G KRRWMMMWRRKK  ]"
        "[ G KRRWBCBWRRTK  ]"
        "[ G KRRWBCBWRRK   ]"
        "[ G KRRWBCBWRRK   ]"
        "[ G KRRWBCBWRRK   ]"
        "[ G KKKWBCBWKKK   ]"
        "[      KKKKK      ]";

    _Roi(V2 _Pos, int _couleur) : _Piece(_Pos, _couleur)
    {
        setZoomSize(2.8);
        setTypePiece(5);
        if (_couleur == 1)
            setTexture(roiBlanc);
        else
            setTexture(roiNoir);
    }

};
struct _Tour : public _Piece {
    string tourBlanche =
        "[            YY            ]"
        "[            II            ]"
        "[           IIII           ]"
        "[           IIII           ]"
        "[          IIIIII          ]"
        "[          J2222J          ]"
        "[      Y   J2JJ2J   Y      ]"
        "[      I   J2JJ2J   I      ]"
        "[      I   J2222J   I      ]"
        "[     III  J2222J  III     ]"
        "[     III  J2JJ2J  III     ]"
        "[    IIIII J2JJ2J IIIII    ]"
        "[    J222J J2222J J222J    ]"
        "[    J2J2JJJJJJJJJJ2J2J    ]"
        "[  Y J2J2J22222222J2J2J Y  ]"
        "[  I J2J2J222JJ222J2J2J I  ]"
        "[  I J222J22JNNJ22J222J I  ]"
        "[ IIIJ222J22JNNJ22J222JIII ]"
        "[ IIIJ222J222JJ222J222JIII ]"
        "[IIIII222J22222222J222IIII ]"
        "[J222J222J22222222J222J222J]"
        "[J222J2JJJ2JJJ2JJJJJJJJ222J]"
        "[J222JJJ2JJJ2JJJ2JJJ2JJ222J]"
        "[J222J2222222222222222J222J]"
        "[J2J2J2222222222222222J2J2J]"
        "[J2J2J2222222222222222J2J2J]"
        "[J2J2J2222222112222222J2J2J]"
        "[J222J2222221//1222222J222J]"
        "[J222J222221////122222J222J]"
        "[J222J222221//1/122222J222J]"
        "[J222J222221//1/122222J222J]"
        "[J222J222221//1/122222J222J]"
        "[J222J222221////122222J222J]"
        "[J222J222221////122222J222J]"
        "[JJJJJJJJJJ111111JJJJJJJJJJ]"
        ;

    string tourNoire = "[            YY            ]"
        "[            ??            ]"
        "[           ????           ]"
        "[           ????           ]"
        "[          ??????          ]"
        "[          J++++J          ]"
        "[      Y   J+JJ+J   Y      ]"
        "[      ?   J+JJ+J   ?      ]"
        "[      ?   J++++J   ?      ]"
        "[     ???  J++++J  ???     ]"
        "[     ???  J+JJ+J  ???     ]"
        "[    ????? J+JJ+J ?????    ]"
        "[    J+++J J++++J J+++J    ]"
        "[    J+J+JJJJJJJJJJ+J+J    ]"
        "[  Y J+J+J++++++++J+J+J Y  ]"
        "[  ? J+J+J+++JJ+++J+J+J ?  ]"
        "[  ? J+++J++JVVJ++J+++J ?  ]"
        "[ ???J+++J++JVVJ++J+++J??? ]"
        "[ ???J+++J+++JJ+++J+++J??? ]"
        "[?????+++J++++++++J+++???? ]"
        "[J+++J+++J++++++++J+++J+++J]"
        "[J+++J+JJJ+JJJ+JJJJJJJJ+++J]"
        "[J+++JJJ+JJJ+JJJ+JJJ+JJ+++J]"
        "[J+++J++++++++++++++++J+++J]"
        "[J+J+J++++++++++++++++J+J+J]"
        "[J+J+J++++++++++++++++J+J+J]"
        "[J+J+J+++++++11+++++++J+J+J]"
        "[J+++J++++++1331++++++J+++J]"
        "[J+++J+++++133331+++++J+++J]"
        "[J+++J+++++133131+++++J+++J]"
        "[J+++J+++++133131+++++J+++J]"
        "[J+++J+++++133131+++++J+++J]"
        "[J+++J+++++133331+++++J+++J]"
        "[J+++J+++++133331+++++J+++J]"
        "[JJJJJJJJJJ111111JJJJJJJJJJ]";

    _Tour(V2 _Pos, int _couleur) : _Piece(_Pos, _couleur)
    {
        setZoomSize(2.1);
        setTypePiece(1);
        if (_couleur == 1)
            setTexture(tourBlanche);
        else
            setTexture(tourNoire);
    }
};
struct _Fou : public _Piece {
    string fouBlanc =
        "[                   KKKKKKKKK                                                ]"
        "[                 KKRRRRRK888KKKKK                 KKKKKK                    ]"
        "[                KRRRRRRRRK8KRRRRKKK           KKKKKKKKKKKK                  ]"
        "[               KRRRKRRRRRRKRRRRRK88K      KKKKKKKKKKKKKKKKK                 ]"
        "[               KRRK8KRRRRRRRRRRRRKKKK   KK88KKKKKKKKKKKKK88K                ]"
        "[              KRRRK88KRRRRRRRRRRRRRRK  KKKKKKKKKKKK8KKKKKKKK                ]"
        "[              KRRRK8KRRRRRRRRRKRRRRRRKKKKKKKKKKKKK8KKKKKKKKKK               ]"
        "[             KRRRRRKRRRRRRRRRK8KRRRRRKKKKKKKKKKKKKKKKKKKKKKKK               ]"
        "[             KRRRRRRRRRRRRRRK888KRRRRKKKKKKKKKKKKKKKKKKKKKKKKK              ]"
        "[             KRRRRRRRRRRRRRRRKKKRRRRRKKKK8KKKKKKKKKKKKKK8KKKKK              ]"
        "[            KRRRRRRRRRRKRRRRRRRRRRRRRKKKK8KKKKKKKKKKKKKK8KKKKK              ]"
        "[            KRRRRRRRRRK8KRRRRRRRRRRRRKKKKKKKKKKKKKKKKKKKKKKKKKK             ]"
        "[            KKKRRRRRKKK88KRRRRRRRRRRRRKKKKKKKK8KKKKKKKKKKKKKKKK             ]"
        "[            K88KRRKK   KKRRRRRRRKKKRRRKKKKKKKKK8KKKKKKKKKKKKKKK             ]"
        "[            KK8KRK       KRRRRRK888KRRKKKKKKKKKKKKKKK  KKKKKK8K             ]"
        "[            KRKKRK       KRRRRRRK8KRRRKKK8KKKKKKKKKK      KKKKK             ]"
        "[            KRRRRK       KRRRRRKKKKKKKKKKKKKKKKKKKK       KKKKK             ]"
        "[             KRRK         KRRKK8888888K888888KKKKKK        KKK              ]"
        "[             KRK          KRK888888888888888888KKK          K               ]"
        "[              K            KK888888888888888888KK          KOK              ]"
        "[             KOK           KK8KKKKK888888KKKKK8K           KOK              ]"
        "[            KOOOK           K8KKKKKK8888KKKKKK8K            K               ]"
        "[             KKK            KKKKKKKK8888KKKKKK8K                            ]"
        "[                            K8KKKOKK8888KKOKKK8K                            ]"
        "[                            K8KKKKKK8888KKKKKK8K                            ]"
        "[                            K8K888KK8888KK888K8K                            ]"
        "[                            K888888888888888888K                            ]"
        "[                             K8888888888888888K                             ]"
        "[                             K8KKK88888888KKK8K                             ]"
        "[                             K88K!KK8888KK!K88K                             ]"
        "[                              K8K!K!KKKK!K!K8K                              ]"
        "[   KK                         K88KK!K!!K!KK88K                         KK   ]"
        "[  KGGK                         K888KKKKKK888K                         KGGK  ]"
        "[ KGGGGK KK                      KK888888K8KK                      KK KGGGGK ]"
        "[KGGGGGGKGGK             KKKKK     KKK88KKK     KKKKK             KGGKGGGGGGK]"
        "[KGGGGGGKGK             KRRRRRK    KKKKKKKK    KKKKKKK             KGKGGGGGGK]"
        "[ KKGGGGGGKK           KRRRRRRRKKKKRRKKKKKKKKKKKKKKKKKK           KKGGGGGGKK ]"
        "[   KKKKKKKK           KRRKKKKKKKKRRRRKKKKKKKRRKKKKKKKK           KRKKKKKK   ]"
        "[   KKKKKKKK            KKKKKKKKKRRRRRKKKKKKKKRRRRRRKK            KRRRRRRK   ]"
        "[    KKKKKKK           KKKKKKKKKRRRKRRKKKKKKKKKRRRRRRRK           KRRRRRK    ]"
        "[    KKKRKKKK         KKKKKKKKKOKRKKKRRKKKRKKKOKRRRRRRRK         KRRKRRRK    ]"
        "[    KKKKKKKK        KKKKKKRKKKOOKKKRRRKKKKRKOOKRRRKRRRRK        KRRRRRRK    ]"
        "[     KKKKKKKK      KKKKKKKKKKKKKKKOKRKKKKOKRKKKRRRRRRRRRK      KRRRRRRK     ]"
        "[     KKKKKKKKK   KKKKRKKKKKKKKKKKKOOKKRKOOKRRRRRRRRRRRRRRKK   KRRRRRRRK     ]"
        "[      KKKKKRKKKKKKKKKKKKKKKKKKKKKKKKKKRRKKKRRRRRRRRRRRRRRRRKKKRRRRRRKK      ]"
        "[      KKKKKKKKKKKKKKKKKKKKKKKKKRKKKKKKRRRRRRRRRRRRRRRRKRRRRRRRRRRRRRRK      ]"
        "[       KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKRRRRRRRRKRRRKKRRRRRRRRRKRRRRRRK       ]"
        "[        KKKKKKKKKKKKKKKKK  KKKKKKKKKKKRRRRRRRRRRRK  KRRRRRRRRRRRRRRK        ]"
        "[         KKKKKKKRKKKKKKK   KKKKKKKRKKKRRRRRRRRRRRK   KRRRRRRRRRRRRK         ]"
        "[          KKKKKKKKKKKKK    KKKKKKKKKKKRRRRRRRRRRK     KRRRKRRRRRRK          ]"
        "[           KKKKKKKKKKK     KKKKKKKKKKKKRRRRRRRRRK      KKKKKKKKKK           ]"
        "[                           KKKKKKKKKKKKRRRRRRRRRK                           ]"
        "[                           KKKKRKKKKKKKRRKRRRRRRK                           ]"
        "[                          KKKKKKKKKKKKKRRRRRRRRRRK                          ]"
        "[                          KKKKKKKKKKKKKRRRRRKRRRRK                          ]"
        "[                          KKKKKKKKKKKKKRRRRRRRRRRK                          ]"
        "[                         KKKRKKKKKKKRKKRRRRRRRRRRRK                         ]"
        "[                         KKKKKKKKKKKKKKRRRRRRRRKRRK                         ]"
        "[                         KKKKKKKKKKKKKKRRRRRRRRRRRRK                        ]"
        "[                         KKKKKKKKKKKKKKRRRRRRRRRRRRK                        ]"
        "[                        KKKKKKKKKRKKKKKRRRKRRRRRRRRK                        ]"
        "[                        KKRKKKKKKKKKKKRRRRRRRRRRRRRRK                       ]"
        "[                        KKKKKKKKKKKKKKRRRRRRRRRRKRRRRK                      ]"
        "[                       KKKKKKKKKKKKKKKRRRRRRRRRRRRRRRK                      ]"
        "[                       KKKKKKKKKKKKKKKRRRRRRKKRRRRRRRK                      ]"
        "[                       KKKKRKKKKKKKKKKRRRRRKKKKRRRRRK                       ]"
        "[                       KKKKRKKKKKKKRKKRRRRRKKKKKRRRRK                       ]"
        "[                       KKKKRRKKKKKRRKKKRRRKKKKKKKRRRK                       ]"
        "[                       KKKKRRKKKKRRRRKKKRKKKKRKKKKRK                        ]"
        "[                       KKKKRRRKKKRRRRKKKRKKKKKKKKKK                         ]"
        "[                       KKKKKRRKKKRRKRKKKKKKKKKKKKKOK                        ]"
        "[                        K  KRRRKRRRRRKKKOKKKKKKKKOOOK                       ]"
        "[                       KOK KRRKOKRRRRKKOOOKKKKKKKKKKK                       ]"
        "[                       KOK KRRKOKRRRRRKKKKKKKRKKKKKKKK                      ]"
        "[                        K  KRRRKRRRRRRKKRKKKKKKKKKKKRKK                     ]"
        "[                          KRRRRRRRRRRKKKKKKKKKKKKKKKKKKK                    ]"
        "[                          KRRRRRKRRRK     KKKKKKKKKKKKKK                    ]"
        "[                          KRRRRRRRRRK       KKKKKRKKKKKK                    ]"
        "[                          KRKRRRRRRK         KKKKKKKKKKK                    ]"
        "[                         KRRRRRRRRRK          KKKKKKKKKK                    ]"
        "[                         KRRRRRRRRK           KKKKKKKKK                     ]"
        "[                         KRRRRRRKRK          KKKKKKKRKK                     ]"
        "[                        KRRRRRRRRRK          KKKKKKKKK                      ]"
        "[                        KRKRRRRRRK          KKRKKKKKKK                      ]"
        "[                        KRRRRKRRRK          KKKKKKKKKK                      ]"
        "[                 KKK   KRRRRRRRRRK          KKKKKKKKK   KK                  ]"
        "[                KKKKK  KRRRRRRRRK          KKKKKKKRKK  KRRK                 ]"
        "[               KKKKK  KRRRRRRKRRK          KKKKKKKKKK   KRRK                ]"
        "[               KKKKK  KRRRRRRRRRK         KRKKKKKKKKKK  KRRK                ]"
        "[               KKKKKKKKKKRRRRRRK         KRRRRKKKKKKK  KRRRK                ]"
        "[               KKKKKKKKKKKKKKKKK         KRRRRRRRRRRRKKRRRRK                ]"
        "[                KKKKKKKKKKKKKKK          KRRRRRRRRRRRRRRRRK                 ]"
        "[                 KKKKKKKKKKKKKK           KRRRRRRRRRRRRRRK                  ]"
        "[                  KKKKKKKKKKKK             KKKRRRRRRRRRKK                   ]"
        "[                    KKKKKKKKK                 KKKKKKKKK                     ]"
        ;

    string fouNoir =
        "[                   KKKKKKKKK                                                ]"
        "[                 KKBBBBBK888KKKKK                 KKKKKK                    ]"
        "[                KBBBBBBBBK8KBBBBKKK           KKKKKKKKKKKK                  ]"
        "[               KBBBKBBBBBBKBBBBBK88K      KKKKKKKKKKKKKKKKK                 ]"
        "[               KBBK8KBBBBBBBBBBBBKKKK   KK88KKKKKKKKKKKKK88K                ]"
        "[              KBBBK88KBBBBBBBBBBBBBBK  KKKKKKKKKKKK8KKKKKKKK                ]"
        "[              KBBBK8KBBBBBBBBBKBBBBBBKKKKKKKKKKKKK8KKKKKKKKKK               ]"
        "[             KBBBBBKBBBBBBBBBK8KBBBBBKKKKKKKKKKKKKKKKKKKKKKKK               ]"
        "[             KBBBBBBBBBBBBBBK888KBBBBKKKKKKKKKKKKKKKKKKKKKKKKK              ]"
        "[             KBBBBBBBBBBBBBBBKKKBBBBBKKKK8KKKKKKKKKKKKKK8KKKKK              ]"
        "[            KBBBBBBBBBBKBBBBBBBBBBBBBKKKK8KKKKKKKKKKKKKK8KKKKK              ]"
        "[            KBBBBBBBBBK8KBBBBBBBBBBBBKKKKKKKKKKKKKKKKKKKKKKKKKK             ]"
        "[            KKKBBBBBKKK88KBBBBBBBBBBBBKKKKKKKK8KKKKKKKKKKKKKKKK             ]"
        "[            K88KBBKK   KKBBBBBBBKKKBBBKKKKKKKKK8KKKKKKKKKKKKKKK             ]"
        "[            KK8KBK       KBBBBBK888KBBKKKKKKKKKKKKKKK  KKKKKK8K             ]"
        "[            KBKKBK       KBBBBBBK8KBBBKKK8KKKKKKKKKK      KKKKK             ]"
        "[            KBBBBK       KBBBBBKKKKKKKKKKKKKKKKKKKK       KKKKK             ]"
        "[             KBBK         KBBKK8888888K888888KKKKKK        KKK              ]"
        "[             KBK          KBK888888888888888888KKK          K               ]"
        "[              K            KK888888888888888888KK          KOK              ]"
        "[             KOK           KK8KKKKK888888KKKKK8K           KOK              ]"
        "[            KOOOK           K8KKKKKK8888KKKKKK8K            K               ]"
        "[             KKK            KKKKKKKK8888KKKKKK8K                            ]"
        "[                            K8KKKOKK8888KKOKKK8K                            ]"
        "[                            K8KKKKKK8888KKKKKK8K                            ]"
        "[                            K8K888KK8888KK888K8K                            ]"
        "[                            K888888888888888888K                            ]"
        "[                             K8888888888888888K                             ]"
        "[                             K8KKK88888888KKK8K                             ]"
        "[                             K88K!KK8888KK!K88K                             ]"
        "[                              K8K!K!KKKK!K!K8K                              ]"
        "[   KK                         K88KK!K!!K!KK88K                         KK   ]"
        "[  KGGK                         K888KKKKKK888K                         KGGK  ]"
        "[ KGGGGK KK                      KK888888K8KK                      KK KGGGGK ]"
        "[KGGGGGGKGGK             KKKKK     KKK88KKK     KKKKK             KGGKGGGGGGK]"
        "[KGGGGGGKGK             KBBBBBK    KKKKKKKK    KKKKKKK             KGKGGGGGGK]"
        "[ KKGGGGGGKK           KBBBBBBBKKKKBBKKKKKKKKKKKKKKKKKK           KKGGGGGGKK ]"
        "[   KKKKKKKK           KBBKKKKKKKKBBBBKKKKKKKBBKKKKKKKK           KBKKKKKK   ]"
        "[   KKKKKKKK            KKKKKKKKKBBBBBKKKKKKKKBBBBBBKK            KBBBBBBK   ]"
        "[    KKKKKKK           KKKKKKKKKBBBKBBKKKKKKKKKBBBBBBBK           KBBBBBK    ]"
        "[    KKKBKKKK         KKKKKKKKKOKBKKKBBKKKBKKKOKBBBBBBBK         KBBKBBBK    ]"
        "[    KKKKKKKK        KKKKKKBKKKOOKKKBBBKKKKBKOOKBBBKBBBBK        KBBBBBBK    ]"
        "[     KKKKKKKK      KKKKKKKKKKKKKKKOKBKKKKOKBKKKBBBBBBBBBK      KBBBBBBK     ]"
        "[     KKKKKKKKK   KKKKBKKKKKKKKKKKKOOKKBKOOKBBBBBBBBBBBBBBKK   KBBBBBBBK     ]"
        "[      KKKKKBKKKKKKKKKKKKKKKKKKKKKKKKKKBBKKKBBBBBBBBBBBBBBBBKKKBBBBBBKK      ]"
        "[      KKKKKKKKKKKKKKKKKKKKKKKKKBKKKKKKBBBBBBBBBBBBBBBBKBBBBBBBBBBBBBBK      ]"
        "[       KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKBBBBBBBBKBBBKKBBBBBBBBBKBBBBBBK       ]"
        "[        KKKKKKKKKKKKKKKKK  KKKKKKKKKKKBBBBBBBBBBBK  KBBBBBBBBBBBBBBK        ]"
        "[         KKKKKKKBKKKKKKK   KKKKKKKBKKKBBBBBBBBBBBK   KBBBBBBBBBBBBK         ]"
        "[          KKKKKKKKKKKKK    KKKKKKKKKKKBBBBBBBBBBK     KBBBKBBBBBBK          ]"
        "[           KKKKKKKKKKK     KKKKKKKKKKKKBBBBBBBBBK      KKKKKKKKKK           ]"
        "[                           KKKKKKKKKKKKBBBBBBBBBK                           ]"
        "[                           KKKKBKKKKKKKBBKBBBBBBK                           ]"
        "[                          KKKKKKKKKKKKKBBBBBBBBBBK                          ]"
        "[                          KKKKKKKKKKKKKBBBBBKBBBBK                          ]"
        "[                          KKKKKKKKKKKKKBBBBBBBBBBK                          ]"
        "[                         KKKBKKKKKKKBKKBBBBBBBBBBBK                         ]"
        "[                         KKKKKKKKKKKKKKBBBBBBBBKBBK                         ]"
        "[                         KKKKKKKKKKKKKKBBBBBBBBBBBBK                        ]"
        "[                         KKKKKKKKKKKKKKBBBBBBBBBBBBK                        ]"
        "[                        KKKKKKKKKBKKKKKBBBKBBBBBBBBK                        ]"
        "[                        KKBKKKKKKKKKKKBBBBBBBBBBBBBBK                       ]"
        "[                        KKKKKKKKKKKKKKBBBBBBBBBBKBBBBK                      ]"
        "[                       KKKKKKKKKKKKKKKBBBBBBBBBBBBBBBK                      ]"
        "[                       KKKKKKKKKKKKKKKBBBBBBKKBBBBBBBK                      ]"
        "[                       KKKKBKKKKKKKKKKBBBBBKKKKBBBBBK                       ]"
        "[                       KKKKBKKKKKKKBKKBBBBBKKKKKBBBBK                       ]"
        "[                       KKKKBBKKKKKBBKKKBBBKKKKKKKBBBK                       ]"
        "[                       KKKKBBKKKKBBBBKKKBKKKKBKKKKBK                        ]"
        "[                       KKKKBBBKKKBBBBKKKBKKKKKKKKKK                         ]"
        "[                       KKKKKBBKKKBBKBKKKKKKKKKKKKKOK                        ]"
        "[                        K  KBBBKBBBBBKKKOKKKKKKKKOOOK                       ]"
        "[                       KOK KBBKOKBBBBKKOOOKKKKKKKKKKK                       ]"
        "[                       KOK KBBKOKBBBBBKKKKKKKBKKKKKKKK                      ]"
        "[                        K  KBBBKBBBBBBKKBKKKKKKKKKKKBKK                     ]"
        "[                          KBBBBBBBBBBKKKKKKKKKKKKKKKKKKK                    ]"
        "[                          KBBBBBKBBBK     KKKKKKKKKKKKKK                    ]"
        "[                          KBBBBBBBBBK       KKKKKBKKKKKK                    ]"
        "[                          KBKBBBBBBK         KKKKKKKKKKK                    ]"
        "[                         KBBBBBBBBBK          KKKKKKKKKK                    ]"
        "[                         KBBBBBBBBK           KKKKKKKKK                     ]"
        "[                         KBBBBBBKBK          KKKKKKKBKK                     ]"
        "[                        KBBBBBBBBBK          KKKKKKKKK                      ]"
        "[                        KBKBBBBBBK          KKBKKKKKKK                      ]"
        "[                        KBBBBKBBBK          KKKKKKKKKK                      ]"
        "[                 KKK   KBBBBBBBBBK          KKKKKKKKK   KK                  ]"
        "[                KKKKK  KBBBBBBBBK          KKKKKKKBKK  KBBK                 ]"
        "[               KKKKK  KBBBBBBKBBK          KKKKKKKKKK   KBBK                ]"
        "[               KKKKK  KBBBBBBBBBK         KBKKKKKKKKKK  KBBK                ]"
        "[               KKKKKKKKKKBBBBBBK         KBBBBKKKKKKK  KBBBK                ]"
        "[               KKKKKKKKKKKKKKKKK         KBBBBBBBBBBBKKBBBBK                ]"
        "[                KKKKKKKKKKKKKKK          KBBBBBBBBBBBBBBBBK                 ]"
        "[                 KKKKKKKKKKKKKK           KBBBBBBBBBBBBBBK                  ]"
        "[                  KKKKKKKKKKKK             KKKBBBBBBBBBKK                   ]"
        "[                    KKKKKKKKK                 KKKKKKKKK                     ]"
        ;

    _Fou(V2 _Pos, int _couleur) : _Piece(_Pos, _couleur)
    {
        setZoomSize(0.80);
        setTypePiece(3);
        if (_couleur == 1)
            setTexture(fouBlanc);
        else
            setTexture(fouNoir);
    }
};
struct _Pion : public _Piece {
    string pionBlanc ="[       KKKKKK                     ]"          
        "[      K445445KK                   ]"
        "[     K44545445KK                  ]"
        "[    K445554544KK                  ]"
        "[    KKK444KTTTK                   ]"
        "[    K45454TKKTK                   ]"
        "[    KK45KKTWKTKK        KKKKKK    ]"
        "[     K4KTKTTTTTK       K4GSSSGK   ]"
        "[     K4KTTTTTTK       K4GSSSSSGK  ]"
        "[      KTKTTTTJK      KGSWKKKKKWGK ]"
        "[     KTTTKTTTTK      KGWK     KW4 ]"
        "[    KLTTTTKTTWJK    K4WK       KSK]"
        "[   KJATTTTTTTTKJK   KGWK       KGK]"
        "[  KJLLATTTTTALKJK   KSWK        4K]"
        "[ KJLJLA9TTTTT9KJK   K8WK        KK]"
        "[ KJLAJLA99TTT9JKKK  KWSK         K]"
        "[KJLAALLLL99T9ALKLK K8WG          K]"
        "[KJKJLLJLLJA99JLKAKKKGSK           ]"
        "[KKJJKJKJLLLJLAJKTTTTKK            ]"
        "[KJLJJLJLLLAALLJKTTTTK             ]"
        "[KLAALKJLLLALLLJKTTTTK             ]"
        "[KLAL9LJJLLLLLLKKGTTTK             ]"
        "[KLL9ALJJLLLALJKG8KTTK             ]"
        "[KLAALLJJJLLALLGWGKTTK             ]"
        "[KLL99JJJJJLJJGWGKTTJ              ]"
        "[KLAAJLLJJLLJG8SKLTTJ              ]"
        "[KLAAJLJTTJJTTJJJJTJ               ]"
        "[KLLJLLJTTTTTTTJKKK                ]"
        "[ KLKLKTTTTTTTTK                   ]"
        "[ KKKKKKKTTTTTKK                   ]"
        "[ KJJLJJKKKKKKJK                   ]"
        "[ KJLLLLKWS4KJLJK                  ]"
        "[ KJLLALK8GKJLLJK                  ]"
        "[ KJLLALJKKJJLLJK                  ]"
        "[ KJLLALLJLLJLLJK                  ]"
        "[ KJLLJALLLLJLLJK                  ]"
        "[ KJJLJLJJALJJLLK                  ]"
        "[  KJKJKJ%KKJJKKK                  ]"
        "[  KJJJ%%%%JJ%%K                   ]"
        "[  KJJ%%%U%JJ%UK                   ]"
        "[  KJJ%%%U%JJ%UK                   ]"
        "[   KJ%%%UUJJU%K                   ]"
        "[   KJ%%UU%J%U%K                   ]"
        "[   KJJ%U%%J%U%K                   ]"
        "[   KJ%J%%JJ%%%K                   ]"
        "[   K%%%%%JJ%U%K                   ]"
        "[  KJ%%%%%JJ%%%K                   ]"
        "[  KJ%%%U%JKKKKKK                  ]"
        "[  KJ%%%U%JKGSGGK                  ]"
        "[  KKKKKKKKKKK4GK                  ]"
        "[  KGS8SGGKKK4KGK                  ]"
        "[  KKKKK4GK4G8GK                   ]"
        "[  K4SGGKGK4S8SK                   ]"
        "[  KG8SGKKK4GSGK                   ]"
        "[  KG8SGK K4GSGK                   ]"
        "[  K48SGK KKGSGK                   ]"
        "[  K4GSGK K4GGSKKKK                ]"
        "[  KKGSGK K44SGSS8GK               ]"
        "[  KKSGSKKKKKK44GS8SK              ]"
        "[ KKGGSGSS8GKKKKKKKKK              ]"
        "[ KKG4G4GGS8SK   KKK               ]"
        "[  KKKKKKKKKKK                     ]"
        
        ;

    string pionNoir = 
        "[       KKKKKK                     ]"          
        "[      K445445KK                   ]"
        "[     K44545445KK                  ]"
        "[    K445554544KK                  ]"
        "[    KKK444KTTTK                   ]"
        "[    K45454TKKTK                   ]"
        "[    KK45KKTWKTKK        KKKKKK    ]"
        "[     K4KTKTTTTTK       K4GSSSGK   ]"
        "[     K4KTTTTTTK       K4GSSSSSGK  ]"
        "[      KTKTTTTJK      KGSWKKKKKWGK ]"
        "[     KTTTKTTTTK      KGWK     KW4 ]"
        "[    K?TTTTKTTWEK    K4WK       KSK]"
        "[   KENTTTTTTTTKEK   KGWK       KGK]"
        "[  KE??NTTTTTALKEK   KSWK        4K]"
        "[ KE?E?N9TTTTT9KEK   K8WK        KK]"
        "[ KE?NE?N99TTT9EKKK  KWSK         K]"
        "[KE?NN????99T9N?K?K K8WG          K]"
        "[KEKE??E??EN99E?KNKKKGSK           ]"
        "[KKEEKEKE???E?NEKTTTTKK            ]"
        "[KE?EE?E???NN??EKTTTTK             ]"
        "[K?NN?KE???N???EKTTTTK             ]"
        "[K?N?9?EE??????KKGTTTK             ]"
        "[K??9N?EE???N?EKG8KTTK             ]"
        "[K?NN??EEE??N??GWGKTTK             ]"
        "[K??99EEEEE?EEGWGKTTE              ]"
        "[K?NNE??EE??EG8SK?TTE              ]"
        "[K?NNE?ETTEETTEEEETE               ]"
        "[K??E??ETTTTTTTEKKK                ]"
        "[ K?K?KTTTTTTTTK                   ]"
        "[ KKKKKKKTTTTTKK                   ]"
        "[ KEE?EEKKKKKKEK                   ]"
        "[ KE????KWS4KE?EK                  ]"
        "[ KE??N?K8GKE??EK                  ]"
        "[ KE??N?EKKEE??EK                  ]"
        "[ KE??N??E??E??EK                  ]"
        "[ KE??EN????E??EK                  ]"
        "[ KEE?E?EEN?EE??K                  ]"
        "[  KJKJKJ%KKJJKKK                  ]"
        "[  KJJJ%%%%JJ%%K                   ]"
        "[  KJJ%%%U%JJ%UK                   ]"
        "[  KJJ%%%U%JJ%UK                   ]"
        "[   KJ%%%UUJJU%K                   ]"
        "[   KJ%%UU%J%U%K                   ]"
        "[   KJJ%U%%J%U%K                   ]"
        "[   KJ%J%%JJ%%%K                   ]"
        "[   K%%%%%JJ%U%K                   ]"
        "[  KJ%%%%%JJ%%%K                   ]"
        "[  KJ%%%U%JKKKKKK                  ]"
        "[  KJ%%%U%JKGSGGK                  ]"
        "[  KKKKKKKKKKK4GK                  ]"
        "[  KGS8SGGKKK4KGK                  ]"
        "[  KKKKK4GK4G8GK                   ]"
        "[  K4SGGKGK4S8SK                   ]"
        "[  KG8SGKKK4GSGK                   ]"
        "[  KG8SGK K4GSGK                   ]"
        "[  K48SGK KKGSGK                   ]"
        "[  K4GSGK K4GGSKKKK                ]"
        "[  KKGSGK K44SGSS8GK               ]"
        "[  KKSGSKKKKKK44GS8SK              ]"
        "[ KKGGSGSS8GKKKKKKKKK              ]"
        "[ KKG4G4GGS8SK   KKK               ]"
        "[  KKKKKKKKKKK                     ]"

        ;

    _Pion(V2 _Pos, int _couleur) : _Piece(_Pos, _couleur)
    {
        setZoomSize(1.2);
        setTypePiece(0);
        if (_couleur == 1)
            setTexture(pionBlanc);
        else
            setTexture(pionNoir);
    }
};
struct _Titre
{
    string titre =
        "[                                                                                         ]"
        "[   3OOOOOOOOOO    3OOOOO    3OOOOO    3OOOOOOOOOOOOOO   3OOOOOOOOOOO    3OOOOOOOOOOO     ]"
        "[  3OOOOOOOOOOO    3OOOOO    3OOOOO    3OOOOOOOOOOOOOO   3OOOOOOOOOOO    3OOOOOOOOOOO     ]"
        "[ 3OOOOOOO33333    3OOOOO    3OOOOO    3OOOOOOO          3OOOOO          3OOOOO           ]"
        "[ 3OOOOOOO         3OOOOO33333OOOOO    3OOOOOOO          3OOOOO          3OOOOO           ]"
        "[ 3OOOOOOO         3OOOOOOOOOOOOOOO    3OOOOOOOOOOOO     3OOOOOOOOOOO    3OOOOOOOOOOO     ]"
        "[ 3OOOOOOO         3OOOOOOOOOOOOOOO    3OOOOOOOOOOOO     3OOOOOOOOOOO    3OOOOOOOOOOO     ]"
        "[ 3OOOOOOO         3OOOOO    3OOOOO    3OOOOOOO                 OOOOO           OOOOO     ]"
        "[ 3OOOOOOO33333    3OOOOO    3OOOOO    3OOOOOOO          3333333OOOOO    3333333OOOOO     ]"
        "[  3OOOOOOOOOOO    3OOOOO    3OOOOO    3OOOOOOOOOOOOOO   3OOOOOOOOOOO    3OOOOOOOOOOO     ]"
        "[   33OOOOOOOOO    3OOOOO    3OOOOO    3OOOOOOOOOOOOOO   3OOOOOOOOOOO    3OOOOOOOOOOO     ]";

    string BG =
        "[QQQQQ]"
        "[QQQQQ]"
        "[QQQQQ]";

    string BG2 =
        "[WWWWW]"
        "[WWWWW]"
        "[WWWWW]";

    string pionBlanc =
        "[       KKKKKK                     ]"
        "[      K445445KK                   ]"
        "[     K44545445KK                  ]"
        "[    K445554544KK                  ]"
        "[    KKK444KTTTK                   ]"
        "[    K45454TKKTK                   ]"
        "[    KK45KKTWKTKK        KKKKKK    ]"
        "[     K4KTKTTTTTK       K4GSSSGK   ]"
        "[     K4KTTTTTTK       K4GSSSSSGK  ]"
        "[      KTKTTTTJK      KGSWKKKKKWGK ]"
        "[     KTTTKTTTTK      KGWK     KW4 ]"
        "[    KLTTTTKTTWJK    K4WK       KSK]"
        "[   KJATTTTTTTTKJK   KGWK       KGK]"
        "[  KJLLATTTTTALKJK   KSWK        4K]"
        "[ KJLJLA9TTTTT9KJK   K8WK        KK]"
        "[ KJLAJLA99TTT9JKKK  KWSK         K]"
        "[KJLAALLLL99T9ALKLK K8WG          K]"
        "[KJKJLLJLLJA99JLKAKKKGSK           ]"
        "[KKJJKJKJLLLJLAJKTTTTKK            ]"
        "[KJLJJLJLLLAALLJKTTTTK             ]"
        "[KLAALKJLLLALLLJKTTTTK             ]"
        "[KLAL9LJJLLLLLLKKGTTTK             ]"
        "[KLL9ALJJLLLALJKG8KTTK             ]"
        "[KLAALLJJJLLALLGWGKTTK             ]"
        "[KLL99JJJJJLJJGWGKTTJ              ]"
        "[KLAAJLLJJLLJG8SKLTTJ              ]"
        "[KLAAJLJTTJJTTJJJJTJ               ]"
        "[KLLJLLJTTTTTTTJKKK                ]"
        "[ KLKLKTTTTTTTTK                   ]"
        "[ KKKKKKKTTTTTKK                   ]"
        "[ KJJLJJKKKKKKJK                   ]"
        "[ KJLLLLKWS4KJLJK                  ]"
        "[ KJLLALK8GKJLLJK                  ]"
        "[ KJLLALJKKJJLLJK                  ]"
        "[ KJLLALLJLLJLLJK                  ]"
        "[ KJLLJALLLLJLLJK                  ]"
        "[ KJJLJLJJALJJLLK                  ]"
        "[  KJKJKJ%KKJJKKK                  ]"
        "[  KJJJ%%%%JJ%%K                   ]"
        "[  KJJ%%%U%JJ%UK                   ]"
        "[  KJJ%%%U%JJ%UK                   ]"
        "[   KJ%%%UUJJU%K                   ]"
        "[   KJ%%UU%J%U%K                   ]"
        "[   KJJ%U%%J%U%K                   ]"
        "[   KJ%J%%JJ%%%K                   ]"
        "[   K%%%%%JJ%U%K                   ]"
        "[  KJ%%%%%JJ%%%K                   ]"
        "[  KJ%%%U%JKKKKKK                  ]"
        "[  KJ%%%U%JKGSGGK                  ]"
        "[  KKKKKKKKKKK4GK                  ]"
        "[  KGS8SGGKKK4KGK                  ]"
        "[  KKKKK4GK4G8GK                   ]"
        "[  K4SGGKGK4S8SK                   ]"
        "[  KG8SGKKK4GSGK                   ]"
        "[  KG8SGK K4GSGK                   ]"
        "[  K48SGK KKGSGK                   ]"
        "[  K4GSGK K4GGSKKKK                ]"
        "[  KKGSGK K44SGSS8GK               ]"
        "[  KKSGSKKKKKK44GS8SK              ]"
        "[ KKGGSGSS8GKKKKKKKKK              ]"
        "[ KKG4G4GGS8SK   KKK               ]"
        "[  KKKKKKKKKKK                     ]";

    string pionNoire =
        "[                     KKKKKK       ]"
        "[                   KK544544K      ]"
        "[                  KK54454544K     ]"
        "[                  KK445455544K    ]"
        "[                   KTTTK444KKK    ]"
        "[                   KTKKT45454K    ]"
        "[    KKKKKK        KKTKWTKK45KK    ]"
        "[   KGSSSG4K       KTTTTTKTK4K     ]"
        "[  KGSSSSSG4K       KTTTTTTK4K     ]"
        "[ KGWKKKKKWSGK      KJTTTTKTK      ]"
        "[ 4WK     KWGK      KTTTTKTTTK     ]"
        "[KSK       KW4K    KJWTTKTTTTLK    ]"
        "[KSK       KWGK   KJKTTTTTTTTAJK   ]"
        "[K4        KWSK   KJKLATTTTTALLJK  ]"
        "[KK        KW8K   KJK9TTTTT9ALJLJK ]"
        "[K         KSWK  KKKJ9TTT99ALJALJK ]"
        "[K          GW8K KLKLA9T99LLLLAALJK]"
        "[           KSGKKKAKLJ99AJLLJLLJKJK]"
        "[            KKTTTTKJALJLLLJKJKJJKK]"
        "[             KTTTTKJLLAALLLJLJJLJK]"
        "[             KTTTTKJLLLALLLJKLAALK]"
        "[             KTTTGKKLLLLLLJJL9LALK]"
        "[             KTTK8GKJLALLLJJLA9LLK]"
        "[             KTTKGWGLLALLJJJLLAALK]"
        "[              JTTKGWGJJLJJJJJ99LLK]"
        "[              JTTLKS8GJLLJJLLJAALK]"
        "[               JTJJJJTTJJTTJLJAALK]"
        "[                KKKJTTTTTTTJLLJLLK]"
        "[                   KTTTTTTTTKLKLK ]"
        "[                   KKTTTTTKKKKKKK ]"
        "[                   KJKKKKKKJJLJJK ]"
        "[                  KJLJK4SWKLLLLJK ]"
        "[                  KJLLJKG8KLALLJK ]"
        "[                  KJLLJJKKJLALLJK ]"
        "[                  KJLLJLLJLLALLJK ]"
        "[                  KJLLJLLLLAJLLJK ]"
        "[                  KLLJJLAJJLJLJJK ]"
        "[                  KKKJJKK%JKJKJK  ]"
        "[                   K%%JJ%%%%JJJK  ]"
        "[                   UK%JJ%U%%%JJK  ]"
        "[                   UK%JJ%U%%%JJK  ]"
        "[                   K%UJJUU%%%JK   ]"
        "[                   K%U%J%UU%%JK   ]"
        "[                   K%U%J%%U%JJK   ]"
        "[                   K%%%JJ%%J%JK   ]"
        "[                   K%U%JJ%%%%%K   ]"
        "[                   K%%%JJ%%%%%JK  ]"
        "[                  KKKKKKJ%U%%%JK  ]"
        "[                  KGGSGKJ%U%%%JK  ]"
        "[                  KG4KKKKKKKKKKK  ]"
        "[                  KGK4KKKGGS8SGK  ]"
        "[                   KG8G4KG4KKKKK  ]"
        "[                   KS8S4KGKGGS4K  ]"
        "[                   KGSG4KKKGS8GK  ]"
        "[                   KGSG4K KGS8GK  ]"
        "[                   KGSGKK KGS84K  ]"
        "[                KKKKSGG4K KGSG4K  ]"
        "[               KG8SSGS44K KGSGKK  ]"
        "[              KS8SG44KKKKKKSGSKK  ]"
        "[              KKKKKKKKKG8SSGSGGKK ]"
        "[               KKK   KS8SGG4G4GKK ]"
        "[                     KKKKKKKKKKK  ]";

    string WinN =

        "[   WWWWW      WWWWW   WWWWWW    WWWWW   WWWWW      WWWWW       WWWWW       WWWWW    WWWWW    WWWWWWWWW      WWWWW   ]"
        "[    WWWWW    WWWWW  WWWWWWWWWW  WWWWW   WWWWW       WWWWW     WWWWWWW     WWWWW     WWWWW    WWWWWWWWWW     WWWWW   ]"
        "[      WWWW  WWWWW   WWW    WWW  WWWWW   WWWWW        WWWWW   WWWWWWWWW   WWWWW      WWWWW    WWWWW WWWWW    WWWWW   ]"
        "[       WWWWWWWW     WWW    WWW  WWWWW   WWWWW         WWWWW WWWW   WWWW WWWWW       WWWWW    WWWWW  WWWWW   WWWWW   ]"
        "[        WWWWWW      WWW    WWW  WWWWW   WWWWW          WWWWWWWW     WWWWWWWW        WWWWW    WWWWW   WWWWW  WWWWW   ]"
        "[        WWWWWW      WWW    WWW  WWWWW   WWWWW           WWWWWW       WWWWWW         WWWWW    WWWWW    WWWWW WWWWW   ]"
        "[        WWWWWW      WWWWWWWWWW  WWWWWWWWWWWWW            WWWW         WWWW          WWWWW    WWWWW     WWWWWWWWWW   ]"
        "[        WWWWWW        WWWWWW    WWWWWWWWWWWWW             WW           WW           WWWWW    WWWWW      WWWWWWWWW   ]";

    string WinB =

        "[   KKKKK      KKKKK   KKKKKK    KKKKK   KKKKK      KKKKK       KKKKK       KKKKK    KKKKK    KKKKKKKKK      KKKKK   ]"
        "[    KKKKK    KKKKK  KKKKKKKKKK  KKKKK   KKKKK       KKKKK     KKKKKKK     KKKKK     KKKKK    KKKKKKKKKK     KKKKK   ]"
        "[      KKKK  KKKKK   KKK    KKK  KKKKK   KKKKK        KKKKK   KKKKKKKKK   KKKKK      KKKKK    KKKKK KKKKK    KKKKK   ]"
        "[       KKKKKKKK     KKK    KKK  KKKKK   KKKKK         KKKKK KKKK   KKKK KKKKK       KKKKK    KKKKK  KKKKK   KKKKK   ]"
        "[        KKKKKK      KKK    KKK  KKKKK   KKKKK          KKKKKKKK     KKKKKKKK        KKKKK    KKKKK   KKKKK  KKKKK   ]"
        "[        KKKKKK      KKK    KKK  KKKKK   KKKKK           KKKKKK       KKKKKK         KKKKK    KKKKK    KKKKK KKKKK   ]"
        "[        KKKKKK      KKKKKKKKKK  KKKKKKKKKKKKK            KKKK         KKKK          KKKKK    KKKKK     KKKKKKKKKK   ]"
        "[        KKKKKK        KKKKKK    KKKKKKKKKKKKK             KK           KK           KKKKK    KKKKK      KKKKKKKKK   ]";

    string Tie =

        "[  KKKKKKKKKKKKKK     KKKKKKKK     KKKKKKKKKKKKKK  ]"
        "[  KKKKKKKKKKKKKK     KKKKKKKK     KKKKKKKKKKKKKK  ]"
        "[  KKKKKKKKKKKKKK     KKKKKKKK     KKKKKKKK        ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKK        ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKKKKKKK   ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKKKKKKK   ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKK        ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKK        ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKKKKKKKK  ]"
        "[      KKKKKK         KKKKKKKK     KKKKKKKKKKKKKK  ]";

    string Roi =
        "[  K  KKKKKKK  K  ]"
        "[ KOKKRORRRORKKOK ]"
        "[ KOOROOOROOOROOK ]"
        "[ KOOOOOOOOOOOOOK ]"
        "[ KWAWAAWAWAAWAWK ]"
        "[ KOOOOOOOOOOOOOK ]"
        "[ KJTWRTTTTTRWTJK ]"
        "[ KJTWKTTTTTKWTJK ]"
        "[KJTTWWTTTTTWWTTJK]"
        "[KJTTTTJJJJJTTTTJK]"
        "[KJJJTJTTTTTJTJJJK]"
        "[ KJJTJTTJTTJTJJK ]"
        "[  KJJJJJJJJJJJK  ]"
        "[  KKJJJJJJJJJSK  ]"
        "[ Y KSSSSCSSSSKK  ]"
        "[YAY KKKSCSKKKWK  ]"
        "[ YKPWWWSCSWWWPK  ]"
        "[ GKPPPWSCSWPPPK  ]"
        "[ YPPPPWBCBWPPPK  ]"
        "[ G KPPWMMMWPPKK  ]"
        "[ G KPPWBCBWPPTK  ]"
        "[ G KPPWBCBWPPK   ]"
        "[ G KPPWBCBWPPK   ]"
        "[ G KPPWBCBWPPK   ]"
        "[ G KKKWBCBWKKK   ]"
        "[      KKKKK      ]";



    float Zoom;
    int IdTex;
    V2 Size;
    string Texture;

    _Titre(int numIm)
    {
        if (numIm == 1)
        {
            Zoom = 5;
            Texture = titre;
        }
        else if (numIm == 2)
        {
            Zoom = 300;
            Texture = BG;
        }

        else if (numIm == 3)
        {
            Zoom = 3;
            Texture = pionBlanc;
        }

        else if (numIm == 4)
        {
            Zoom = 3;
            Texture = pionNoire;
        }

        else if (numIm == 5)
        {
            Zoom = 5;
            Texture = WinN;
        }

        else if (numIm == 6)
        {
            Zoom = 300;
            Texture = BG2;
        }

        else if (numIm == 7)
        {
            Zoom = 6;
            Texture = Tie;
        }

        else if (numIm == 8)
        {
            Zoom = 6;
            Texture = Roi;
        }

        else if (numIm == 9)
        {
            Zoom = 5;
            Texture = WinB;
        }
    }
};

struct deplacement {
    V2 start;
    V2 Fin;
    int indexP;
    int couleur;
    bool aChanger = false;
    deplacement(V2 pS, V2 pF)
    {
        start = pS;
        Fin = pF;

    }
    deplacement(V2 pS, V2 pF, int pP)
    {
        start = pS;
        Fin = pF;
        indexP = pP;
    }
    deplacement(V2 pS, V2 pF, int pP, int pcouleur)
    {
        start = pS;
        Fin = pF;

        couleur = pcouleur;
    }
    void setChanger(bool chang)
    {
        aChanger = chang;
    }
}; 
struct GameData {

    int ecran = 0;
    int joueur;
    int joueurIa;
    _plateau Plateau;
    bool Mur(int x, int y) { return Plateau.Map1[(8- y - 1) * 8 + x] == 'M'; }
    int xMouse;
    int yMouse;
    int Lpix = 80;
    V2 Size;
    int TimerEnd;
    void setTimerEnd(int _TimerEnd) { TimerEnd = _TimerEnd; }
    int IdTexMur;
    int IdTexSol;
    int IdTexPossible;
    deplacement test = deplacement(V2(), V2());
    vector<V2> zonesJouables = {};
    
    bool mouseIsActive = false;
    int getJoueur() { return joueur; }
    void setJoueur() {
        if (joueur == 1) 
        { 
            joueur = 2; 
        }
        else { joueur = 1; }
    }
    void setMouseIsActive(bool _mouseIsActive) { mouseIsActive = _mouseIsActive; }
    vector<_Piece> pieces = {};
    int pieceEncours=-1;
    void setPieces() {
        pieces.clear();

        pieces.push_back(_Pion(V2(0, 6), 2));
        pieces.push_back(_Pion(V2(1, 6), 2));
        pieces.push_back(_Pion(V2(2, 6), 2));
        pieces.push_back(_Pion(V2(3, 6), 2));
        pieces.push_back(_Pion(V2(4, 6), 2));
        pieces.push_back(_Pion(V2(5, 6), 2));
        pieces.push_back(_Pion(V2(6, 6), 2));
        pieces.push_back(_Pion(V2(7, 6), 2));



        pieces.push_back(_Tour(V2(0, 7), 2));
        pieces.push_back(_Tour(V2(7, 7), 2));
        pieces.push_back(_Cavalier(V2(1, 7), 2));
        pieces.push_back(_Cavalier(V2(6, 7), 2));
        pieces.push_back(_Fou(V2(2, 7), 2));
        pieces.push_back(_Fou(V2(5, 7), 2));
        pieces.push_back(_Dame(V2(3, 7), 2));
        pieces.push_back(_Roi(V2(4, 7), 2));

        pieces.push_back(_Pion(V2(0, 1), 1));
        pieces.push_back(_Pion(V2(1, 1), 1));
        pieces.push_back(_Pion(V2(2, 1), 1));
        pieces.push_back(_Pion(V2(3, 1), 1));
        pieces.push_back(_Pion(V2(4, 1), 1));
        pieces.push_back(_Pion(V2(5, 1), 1));
        pieces.push_back(_Pion(V2(6, 1), 1));
        pieces.push_back(_Pion(V2(7, 1), 1));


        pieces.push_back(_Tour(V2(0, 0), 1));
        pieces.push_back(_Tour(V2(7, 0), 1));
        pieces.push_back(_Cavalier(V2(1, 0), 1));
        pieces.push_back(_Cavalier(V2(6, 0), 1));
        pieces.push_back(_Fou(V2(2, 0), 1));
        pieces.push_back(_Fou(V2(5, 0), 1));
        pieces.push_back(_Dame(V2(3, 0), 1));
        pieces.push_back(_Roi(V2(4, 0), 1));


        for (_Piece& piece : pieces) {
            piece.IdTex = G2D::InitTextureFromString(piece.Size, piece.Texture); 
            piece.Size = piece.Size * piece.Zoom;
        }
    }
    GameData() {}
};
GameData G;

   

bool DeplacementPiece(_Piece Piece, V2 pNewPos){
    //0 = pion, 1 = tour, 2 = cavalier, 3 = fou, 4 =dame , 5 = roi, 6 = roi pour test
    V2 vCoord = Piece.getCoord();
    if (vCoord == pNewPos)
        return false;
    if (Piece.getTypePiece() == 0)//pion
    {
        if (((((vCoord + V2(0, 1)==pNewPos )|| (vCoord + V2(0, 2) == pNewPos && vCoord.y == 1 && G.Plateau.getPositionPiece(vCoord + V2(0, 1))==0)) && Piece.getCouleur() == 1 )|| (((vCoord + V2(0,-1) == pNewPos) || (vCoord + V2(0, -2) == pNewPos && vCoord.y == 6) && G.Plateau.getPositionPiece(vCoord + V2(0, -1)) == 0) && Piece.getCouleur() == 2) || (((vCoord + V2(1,1) == pNewPos) || vCoord + V2(-1, 1) == pNewPos) && Piece.getCouleur() == 1) || (((vCoord + V2(1, -1) == pNewPos) || vCoord + V2(-1, -1) == pNewPos) && Piece.getCouleur() == 2)) && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8) {
            if (G.Plateau.getPositionPiece(pNewPos) == 0 && vCoord.x == pNewPos.x) {
                return true;
            }
            else if(G.Plateau.getPositionPiece(pNewPos) != 0 && G.Plateau.getPositionPiece(pNewPos) != Piece.getCouleur() && vCoord.x != pNewPos.x){
                return true;
            }
        }
        return false;
    }
    if (Piece.getTypePiece() == 1)//tour
    {
        //Si horizontal
        if (vCoord.x != pNewPos.x && vCoord.y == pNewPos.y && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8) {
            //Test droite
            if (vCoord.x < pNewPos.x) {
                for (int i = vCoord.x + 1; i <= pNewPos.x; i++)
                {
                    if (G.Plateau.getPositionPiece(V2(i, pNewPos.y)) == 0 || G.Plateau.getPositionPiece(V2(i, pNewPos.y))!= Piece.getCouleur()) {
                        if (i == pNewPos.x)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(i, pNewPos.y)) != 0)
                            return false;
                    }
                    else
                        return false;
                }
            }
            //Test gauche
            else if (vCoord.x > pNewPos.x) {
                for (int i = vCoord.x - 1; i >= pNewPos.x; i--)
                {
                    if (G.Plateau.getPositionPiece(V2(i, pNewPos.y)) == 0 || G.Plateau.getPositionPiece(V2(i, pNewPos.y)) != Piece.getCouleur()) {
                        if (i == pNewPos.x)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(i, pNewPos.y)) != 0)
                            return false;
                    }
                    else
                        return false;
                }
            }
        }

        //Si vertical
        if (vCoord.y != pNewPos.y && vCoord.x == pNewPos.x && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8) {

            //Teste bas
            if (vCoord.y < pNewPos.y) {
                for (int i = vCoord.y + 1; i <= pNewPos.y; i++)
                {
                    if (G.Plateau.getPositionPiece(V2(pNewPos.x, i)) == 0 || G.Plateau.getPositionPiece(V2(pNewPos.x, i)) != Piece.getCouleur()) {
                        if (i == pNewPos.y)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(pNewPos.x, i)) != 0)
                            return false;
                    }
                    else
                        return false;                    
                }
            }

            //Teste haut
            else if (vCoord.y > pNewPos.y) {
                for (int i = vCoord.y - 1; i >= pNewPos.y; i--)
                {
                    if (G.Plateau.getPositionPiece(V2(pNewPos.x, i)) == 0 || G.Plateau.getPositionPiece(V2(pNewPos.x, i)) != Piece.getCouleur()) {
                        if (i == pNewPos.y)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(pNewPos.x, i)) != 0)
                            return false;
                    }
                    else
                        return false;
                }
            }
        }
        return false;
    }
    if (Piece.getTypePiece() == 2)//cavalier
    {
        if ((vCoord + V2(2, 1) == pNewPos || vCoord + V2(1, 2) == pNewPos || vCoord + V2(-2, -1) == pNewPos || vCoord + V2(-1, -2) == pNewPos || vCoord + V2(2, -1) == pNewPos || vCoord + V2(-2, 1) == pNewPos || vCoord + V2(1, -2) == pNewPos || vCoord + V2(-1, 2) == pNewPos) && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8)
            if (G.Plateau.getPositionPiece(pNewPos) != Piece.getCouleur())
                return true;
        return false;
    }
    if (Piece.getTypePiece() == 3)//fou
    {
        //Initialisation des positions actuelles de la pièce et de la distance entre départ et arrivée.
        int pos_x = 0;
        int pos_y = 0;
        int nb_move = 0;

        //Verifie si le mouvement est une diagonale
        if (abs(pNewPos.x - vCoord.x) == abs(pNewPos.y - vCoord.y) && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8) {
            pos_x = vCoord.x;
            pos_y = vCoord.y;

            if (vCoord.x < pNewPos.x && vCoord.y < pNewPos.y) {
                pos_x = vCoord.x + 1;
                pos_y = vCoord.y + 1;

                // Vérification si le mouvement est valide case par case (diagonale vers haut et droite).
                nb_move = abs(pNewPos.x - vCoord.x);
                for (int i = 0; i <= nb_move; i++) {
                    if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) == 0 || G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != Piece.getCouleur()) {
                        if (pos_x == pNewPos.x && pos_y == pNewPos.y)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != 0)
                            return false;
                    }
                    else
                        return false;
                    pos_x++;
                    pos_y++;
                }
            }

            if (vCoord.x > pNewPos.x && vCoord.y > pNewPos.y) {
                pos_x = vCoord.x - 1;
                pos_y = vCoord.y - 1;

                // Vérification si le mouvement est valide case par case (diagonale vers bas et gauche).
                nb_move = abs(pNewPos.x - vCoord.x);
                for (int i = 0; i <= nb_move; i++) {
                    if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) == 0 || G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != Piece.getCouleur()) {
                        if (pos_x == pNewPos.x && pos_y == pNewPos.y)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != 0)
                            return false;
                    }
                    else
                        return false;
                    pos_x--;
                    pos_y--;
                }
            }

            if (vCoord.x < pNewPos.x && vCoord.y > pNewPos.y) {
                pos_x = vCoord.x + 1;
                pos_y = vCoord.y - 1;

                // Vérification si le mouvement est valide case par case (diagonale vers bas et droite).
                nb_move = abs(pNewPos.x - vCoord.x);
                for (int i = 0; i <= nb_move; i++) {
                    if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) == 0 || G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != Piece.getCouleur()) {
                        if (pos_x == pNewPos.x && pos_y == pNewPos.y)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != 0)
                            return false;
                    }
                    else
                        return false;
                    pos_x++;
                    pos_y--;
                }
            }

            if (vCoord.x > pNewPos.x && vCoord.y < pNewPos.y) {
                pos_x = vCoord.x - 1;
                pos_y = vCoord.y + 1;

                // Vérification si le mouvement est valide case par case (diagonale vers haut et gauche).
                nb_move = abs(pNewPos.x - vCoord.x);
                for (int i = 0; i <= nb_move; i++) {
                    if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) == 0 || G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != Piece.getCouleur()) {
                        if (pos_x == pNewPos.x && pos_y == pNewPos.y)
                            return true;
                        else if (G.Plateau.getPositionPiece(V2(pos_x, pos_y)) != 0)
                            return false;
                    }
                    else
                        return false;
                    pos_x--;
                    pos_y++;
                }
            }
        }
        return false;
    }
    if (Piece.getTypePiece() == 4)//dame
    {
        
        return DeplacementPiece(_Tour(Piece.getCoord(),Piece.getCouleur()),pNewPos)|| DeplacementPiece(_Fou(Piece.getCoord(), Piece.getCouleur()), pNewPos);
    }
    if (Piece.getTypePiece() == 5)//roi
    {
        if ((pNewPos.x == vCoord.x + 1 || pNewPos.x == vCoord.x - 1 || pNewPos.x == vCoord.x) && (pNewPos.y == vCoord.y + 1 || pNewPos.y == vCoord.y - 1 || pNewPos.y == vCoord.y) && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8){
            if (G.Plateau.getPositionPiece(pNewPos) != Piece.getCouleur()) {   
                return true;
            }
        }
        /*else if (Piece.getNoMove())//TEst pour le roque
        {
            if ((vCoord.y == pNewPos.y && vCoord.x + 2 == pNewPos.x)) {
                if (Piece.getCouleur() == 1 && G.pieces[25].getNoMove() && G.pieces[25].getEstVivant()) {
                    //cout << "maybe" << endl;
                    //cout<< "dernier" << DeplacementPiece(Piece, V2(6, 0));

                    if (DeplacementPiece(G.pieces[25], V2(5, 0)) && DeplacementPiece(Piece, V2(5, 0)))
                    {
                        Piece.setCoord(V2(5, 0));
                        G.Plateau.setPositionPiece(4, 0, "0");
                        G.Plateau.setPositionPiece(5, 0, "1");
                        if (DeplacementPiece(Piece, V2(6, 0)))
                        {
                            G.Plateau.setPositionPiece(4, 0, "1");
                            G.Plateau.setPositionPiece(5, 0, "0");
                            Piece.setCoord(V2(4, 0));
                            return true;
                        }
                        G.Plateau.setPositionPiece(4, 0, "1");
                        G.Plateau.setPositionPiece(5, 0, "0");
                        Piece.setCoord(V2(4, 0));
                        return false;
                    }
                }
                else if (Piece.getCouleur() == 2 && G.pieces[9].getNoMove() && G.pieces[9].getEstVivant()) {
                    //cout << "maybe" << endl;
                    //cout<< "dernier" << DeplacementPiece(Piece, V2(6, 0));

                    if (DeplacementPiece(G.pieces[9], V2(5, 7)) && DeplacementPiece(Piece, V2(5, 7)))
                    {
                        
                        Piece.setCoord(V2(5, 7));
                        G.Plateau.setPositionPiece(4, 7, "0");
                        G.Plateau.setPositionPiece(5, 7, "2");
                        if (DeplacementPiece(Piece, V2(6, 7)))
                        {
                            G.Plateau.setPositionPiece(4, 7, "2");
                            G.Plateau.setPositionPiece(5, 7, "0");
                            Piece.setCoord(V2(4, 7));
                            return true;
                        }
                        G.Plateau.setPositionPiece(4, 7, "2");
                        G.Plateau.setPositionPiece(5, 7, "0");
                        Piece.setCoord(V2(4, 7));
                        return false;
                    }
                }
            }
            else if (vCoord.y == pNewPos.y && vCoord.x - 2 == pNewPos.x) {
                if (Piece.getCouleur() == 1 && G.pieces[24].getNoMove() && G.pieces[24].getEstVivant()) {
                    if (DeplacementPiece(G.pieces[24], V2(3, 0)) && DeplacementPiece(Piece, V2(3, 0)))
                    {
                        
                        Piece.setCoord(V2(3, 0));
                        G.Plateau.setPositionPiece(4, 0, "0");
                        G.Plateau.setPositionPiece(3, 0, "1");
                        if (DeplacementPiece(Piece, V2(2, 0)))
                        {
                            G.Plateau.setPositionPiece(4, 0, "1");
                            G.Plateau.setPositionPiece(3, 0, "0");
                            Piece.setCoord(V2(4, 0));
                            return true;
                        }
                        G.Plateau.setPositionPiece(4, 0, "1");
                        G.Plateau.setPositionPiece(3, 0, "0");
                        Piece.setCoord(V2(4, 0));
                        return false;
                    }
                }
                else if (Piece.getCouleur() == 2 && G.pieces[8].getNoMove() && G.pieces[8].getEstVivant()) {
                    //cout << "maybe" << endl;
                    //cout<< "dernier" << DeplacementPiece(Piece, V2(6, 0));

                    if (DeplacementPiece(G.pieces[8], V2(3, 7)) && DeplacementPiece(Piece, V2(3, 7)))
                    {
                        
                        Piece.setCoord(V2(3, 7));
                        G.Plateau.setPositionPiece(4, 7, "0");
                        G.Plateau.setPositionPiece(3, 7, "2");                        
                        if (DeplacementPiece(Piece, V2(2, 7)))
                        {
                            G.Plateau.setPositionPiece(4, 7, "2");
                            G.Plateau.setPositionPiece(3, 7, "0");
                            Piece.setCoord(V2(3, 7));
                            return true;
                        }
                        G.Plateau.setPositionPiece(4, 7, "2");
                        G.Plateau.setPositionPiece(3, 7, "0");
                        Piece.setCoord(V2(3, 7));
                        return false;
                    }
                }
            }
            
        }
        */
        return false;
    }
    if (Piece.getTypePiece() == 6) {
        if ((pNewPos.x == vCoord.x + 1 || pNewPos.x == vCoord.x - 1 || pNewPos.x == vCoord.x) && (pNewPos.y == vCoord.y + 1 || pNewPos.y == vCoord.y - 1 || pNewPos.y == vCoord.y) && pNewPos.x >= 0 && pNewPos.x < 8 && pNewPos.y >= 0 && pNewPos.y < 8) {
            return true;
        }
        return false;
    }
    return false;
}
bool NoSuicideMove(_Piece Piece, V2 pNewPos) {
    char pastPlateau = G.Plateau.getPositionPiece(pNewPos);
    V2 vCoord = Piece.getCoord();
    int leMort = -1; // la piece qui meurt si on joue notre coup
    G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(Piece.getCouleur()));
    G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(0));
    if (Piece.getCouleur() == 1) 
    {
        if (!(Piece.getTypePiece()==5)) 
        {
            for (int i = 0; i < 15; i++) 
            {
                if (G.pieces[i].getCoord() == pNewPos && G.pieces[i].getEstVivant())
                {
                    leMort = i;
                    G.pieces[i].setEstVivant(false);
                }
                else if (G.pieces[i].getEstVivant()) 
                {
                    
                    if (DeplacementPiece(G.pieces[i], G.pieces[31].getCoord())) 
                    {
                        G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                        G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                        if (leMort != -1)
                        {
                            G.pieces[leMort].setEstVivant(true);

                        }
                        return false;
                    }
                }
            }
            
            G.pieces[15].setTypePiece(6);

            if (DeplacementPiece(G.pieces[15], G.pieces[31].getCoord()))
            {
                G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                G.pieces[15].setTypePiece(5);
                if (leMort != -1)
                {
                    G.pieces[leMort].setEstVivant(true);

                }
                return false;
            }
            G.pieces[15].setTypePiece(5);
            if (leMort != -1)
            {
                G.pieces[leMort].setEstVivant(true);

            }
        }
        else
        {
            for (int i = 0; i < 15; i++)
            {
                if (G.pieces[i].getCoord() == pNewPos && G.pieces[i].getEstVivant())
                {
                    leMort = i;
                    G.pieces[i].setEstVivant(false);
                }
                else if (G.pieces[i].getEstVivant())
                {

                    if (DeplacementPiece(G.pieces[i], pNewPos))
                    {
                        G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                        G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                        if (leMort != -1)
                        {
                            G.pieces[leMort].setEstVivant(true);

                        }
                        return false;
                    }
                }
            }

            G.pieces[15].setTypePiece(6);

            if (DeplacementPiece(G.pieces[15], pNewPos))
            {
                G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                G.pieces[15].setTypePiece(5);
                if (leMort != -1)
                {
                    G.pieces[leMort].setEstVivant(true);

                }
                return false;
            }
            G.pieces[15].setTypePiece(5);
            if (leMort != -1)
            {
                G.pieces[leMort].setEstVivant(true);

            }
        }
        
    }
    else if (Piece.getCouleur() == 2) {
        if (!(Piece.getTypePiece() == 5))
        {
            for (int i = 16; i < 31; i++) {
                if (G.pieces[i].getCoord() == pNewPos && G.pieces[i].getEstVivant())
                {
                    leMort = i;
                    G.pieces[i].setEstVivant(false);
                }
                else if (G.pieces[i].getEstVivant()) {

                    if (DeplacementPiece(G.pieces[i], G.pieces[15].getCoord())) {
                        G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                        G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                        if (leMort != -1)
                        {
                            G.pieces[leMort].setEstVivant(true);

                        }
                        return false;
                    }
                }
            }
            
            G.pieces[31].setTypePiece(6);
            if (DeplacementPiece(G.pieces[31], G.pieces[15].getCoord())) {
                G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                G.pieces[31].setTypePiece(5);
                if (leMort != -1)
                {
                    G.pieces[leMort].setEstVivant(true);

                }
                return false;
            }
            G.pieces[31].setTypePiece(5);
            if (leMort != -1)
            {
                G.pieces[leMort].setEstVivant(true);

            }
        }
        else 
        {
            for (int i = 16; i < 31; i++) {
                if (G.pieces[i].getCoord() == pNewPos && G.pieces[i].getEstVivant())
                {
                    leMort = i;
                    G.pieces[i].setEstVivant(false);
                }
                else if (G.pieces[i].getEstVivant()) {

                    if (DeplacementPiece(G.pieces[i], pNewPos)) {
                        G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                        G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                        if (leMort != -1)
                        {
                            G.pieces[leMort].setEstVivant(true);

                        }
                        return false;
                    }
                }
            }

            G.pieces[31].setTypePiece(6);
            if (DeplacementPiece(G.pieces[31], pNewPos)) {
                G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
                G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
                G.pieces[31].setTypePiece(5);
                if (leMort != -1)
                {
                    G.pieces[leMort].setEstVivant(true);

                }
                return false;
            }
            G.pieces[31].setTypePiece(5);
            if (leMort != -1)
            {
                G.pieces[leMort].setEstVivant(true);

            }
        }

        

    }
    G.Plateau.setPositionPiece(pNewPos.x, pNewPos.y, to_string(pastPlateau));
    G.Plateau.setPositionPiece(vCoord.x, vCoord.y, to_string(Piece.getCouleur()));
    return true;

}
void setZonesJouables(_Piece pieceActuelle) {
    G.zonesJouables.clear();
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (DeplacementPiece(pieceActuelle, V2(x, y)))
            {
                if (NoSuicideMove(pieceActuelle, V2(x, y))) 
                {
                    G.zonesJouables.push_back(V2(x, y));
                }
            }
        }
    }
}
//IA 
vector<deplacement> DePossible(int joueur)
{
    vector < deplacement > DP = {};
    if (joueur == 1)
    {
        for (int i = 16; i < 32; i++)
        {
            _Piece vPiece = G.pieces[i];
            for (int k = 0; k < 8; k++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (i == 31 && (abs(vPiece.pos.x - k) < 2))
                    {
                        if (DeplacementPiece(vPiece, V2(k, j)))
                        {
                            if (NoSuicideMove(vPiece, V2(k, j))) {
                                DP.push_back(deplacement(vPiece.pos, V2(k, j), i));
                                // std::cout << "(" << vPiece.pos.x << vPiece.pos.y << ";" << k << j << ")" << endl;
                            }
                        }
                    }
                    else if (i != 31 && DeplacementPiece(vPiece, V2(k, j)) && vPiece.getEstVivant())
                    {
                        if (NoSuicideMove(vPiece, V2(k, j))) {
                            DP.push_back(deplacement(vPiece.pos, V2(k, j), i));
                            //std::cout << "(" << vPiece.pos.x << vPiece.pos.y << ";" << k << j << ")" << endl;
                        }
                    }

                }
            }
        }
        return DP;
    }
    else
    {
        for (int i = 0; i < 16; i++)
        {
            _Piece vPiece = G.pieces[i];
            for (int k = 0; k < 8; k++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (i == 15 && (abs(vPiece.pos.x - k) < 2))
                    {
                        if (DeplacementPiece(vPiece, V2(k, j)))
                        {
                            if (NoSuicideMove(vPiece, V2(k, j))) {
                                DP.push_back(deplacement(vPiece.pos, V2(k, j), i));
                                //std::cout << "(" << vPiece.pos.x << vPiece.pos.y << ";" << k << j << ")" << endl;
                                int p = 0;
                            }
                        }
                    }
                    else if (i != 15 && DeplacementPiece(vPiece, V2(k, j)) && vPiece.getEstVivant())
                    {
                        if (NoSuicideMove(vPiece, V2(k, j))) {
                            DP.push_back(deplacement(vPiece.pos, V2(k, j), i));
                            //std::cout << "(" << vPiece.pos.x << vPiece.pos.y << ";" << k << j << ")" << endl;
                        }
                    }
                }
            }
        }
        return DP;
    }
}

int point(int joueur)
{
    int point = 0;

    for (int i = 0; i < 32; i++)
    {

        _Piece P = G.pieces[i];
        if (i < 16)
        {
            if (P.estVivant)
            {
                if (P.typePiece == 0) { point += 10; }
                if (P.typePiece == 2) { point += 30; }
                if (P.typePiece == 1) { point += 50; }
                if (P.typePiece == 3) { point += 30; }
                if (P.typePiece == 4) { point += 80; }
                if (P.typePiece == 5) { point += 1000; }
                if (P.pos.x >= 3 && P.pos.y <= 4 && P.pos.y >= 3 && P.pos.x <= 4 && joueur == 2)
                {
                    point += 9;
                }
                if ((P.pos.x < 3 || P.pos.x > 4) && P.pos.y <= 4 && P.pos.y >= 3 && joueur == 2)
                {
                    point += 2;
                }

            }

        }
        else
        {
            if (P.estVivant)
            {
                if (P.typePiece == 0) { point -= 10; }
                if (P.typePiece == 2) { point -= 30; }
                if (P.typePiece == 1) { point -= 50; }
                if (P.typePiece == 3) { point -= 30; }
                if (P.typePiece == 4) { point -= 80; }
                if (P.typePiece == 5) { point -= 1000; }
                if (P.pos.x >= 3 && P.pos.y <= 4 && P.pos.y >= 3 && P.pos.x <= 4 && joueur == 1)
                {
                    point -= 9;
                }
                if ((P.pos.x < 3 || P.pos.x > 4) && P.pos.y <= 4 && P.pos.y >= 3 && joueur == 1)
                {
                    point -= 2;
                }

            }
        }
    }
    if (joueur == 1)
    {
        point = -point;
        vector<deplacement> M = DePossible(1);
        point += M.size() * (1 / 3);
    }
    else
    {
        vector<deplacement> M = DePossible(2);
        point += M.size() * (1 / 3);

    }
    int score = point;
    return score;
}
//IA
void Timer(_Piece* piece, int multiplier)
{
    
    piece->TimeDead += multiplier;
}

deplacement changePos(int index, V2 pos)
{
    G.Plateau.setPositionPiece(G.pieces[index].getCoord().x, G.pieces[index].getCoord().y, "0");
    deplacement D = deplacement(G.pieces[index].getCoord(), pos, 0, G.Plateau.getPositionPiece(pos));

    for (_Piece& P : G.pieces)
    {
        if (!P.getEstVivant() && P.TimeDead >-1)
        {
            Timer(&P, 1);
        }
        if (P.pos == pos && P.getEstVivant())
        {
            P.setEstVivant(!P.getEstVivant());
            P.TimeDead = 0;
            G.Plateau.setPositionPiece(P.pos.x, P.pos.y, "0");
        }

    }

    G.pieces[index].pos = pos;
    G.Plateau.setPositionPiece(G.pieces[index].getCoord().x, G.pieces[index].getCoord().y, std::to_string(G.pieces[index].getCouleur()));
    return D;
}
void changeBack(deplacement D)
{
    for (_Piece& piece : G.pieces)
    {


        if (piece.pos == D.Fin)
        {
            if (piece.estVivant)
            {
                if (G.Plateau.getPositionPiece(piece.pos))
                {
                    G.Plateau.setPositionPiece(piece.pos.x, piece.pos.y, to_string(D.couleur));
                }
                piece.pos = D.start;
                G.Plateau.setPositionPiece(piece.pos.x, piece.pos.y, to_string(piece.getCouleur()));

            }

        }
        if (!piece.getEstVivant())
        {
            if (piece.TimeDead == 0)
            {
                piece.setEstVivant(!piece.getEstVivant());
                piece.TimeDead = -1;
                G.Plateau.setPositionPiece(piece.pos.x, piece.pos.y, to_string(piece.couleur));

            }
            else if(piece.TimeDead >0)
            {
                Timer(&piece, -1);
            }
        }
        /* if (!G.pieces[17].getEstVivant())
         {
             cout << G.Plateau.getPlateau() << endl;
         }*/
    }
}
void fin()
{
    for (int i = 0; i < 32; i++)
    {
        if (!G.pieces[i].getEstVivant())
        {
            G.pieces[i].TimeDead = -1;
        }
    }
}
void actualisePlateau()
{
    for (int i = 0; i < 32; i++)
    {
        if (G.pieces[i].getEstVivant())
        {
            if (G.pieces[i].couleur == 1)
                G.Plateau.setPositionPiece(G.pieces[i].pos.x, G.pieces[i].pos.y, "3");
            else
                G.Plateau.setPositionPiece(G.pieces[i].pos.x, G.pieces[i].pos.y, "4");
        }
    }
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            //cout << G.Plateau.getPositionPiece(V2(x, y)) << endl;
            if (G.Plateau.getPositionPiece(V2(x, y)) == 3)
            {
                G.Plateau.setPositionPiece(x, y, "1");
            }
            else if (G.Plateau.getPositionPiece(V2(x, y)) == 4)
            {
                G.Plateau.setPositionPiece(x, y, "2");
            }
            else
            {
                G.Plateau.setPositionPiece(x, y, "0");
            }
        }

    }
    //cout << G.Plateau.getPlateau() << endl;
}
int IaN(int joueur, int alpha, int beta, bool EMin, bool fils, int depth)
{
    int v;
    deplacement coup = deplacement(V2(9, 9), V2(9, 9));
    if (depth == 0)
    {

        return point(joueur);
    }
    if (abs(point(joueur) > 500))
    {
        return point(joueur);
    }
    else if (EMin)
    {
        v = 2000;
        vector<deplacement> DP = DePossible(3 - joueur);
        int size = DP.size();

        for (int i = 0; i < size; i++)
        {

            deplacement y = changePos(DP[i].indexP, DP[i].Fin);
            if ((G.pieces[DP[i].indexP].getTypePiece() == 0 && G.pieces[DP[i].indexP].getCoord().y == 7 && G.pieces[DP[i].indexP].getCouleur() == 1) || (G.pieces[DP[i].indexP].getTypePiece() == 0 && G.pieces[DP[i].indexP].getCoord().y == 0 && G.pieces[DP[i].indexP].getCouleur() == 2))
            {
                DP[i].setChanger(true);
                G.pieces[DP[i].indexP] = _Dame(G.pieces[DP[i].indexP].getCoord(), G.pieces[DP[i].indexP].getCouleur());
            }
            v = min(v, IaN(joueur, alpha, beta, false, true, depth - 1));

            if (alpha > v)
            {
                if (fils)
                {
                    if (DP[i].aChanger)
                    {
                        G.pieces[DP[i].indexP] = _Pion(G.pieces[DP[i].indexP].getCoord(), G.pieces[DP[i].indexP].getCouleur());
                    }
                    changeBack(y);
                    actualisePlateau();
                    return v;
                }
            }
            beta = min(beta, v);
            if (DP[i].aChanger)
            {
                G.pieces[DP[i].indexP] = _Pion(G.pieces[DP[i].indexP].getCoord(), G.pieces[DP[i].indexP].getCouleur());
            }
            changeBack(y);
            actualisePlateau();
        }
    }
    else
    {
        v = -2000;
        vector<deplacement> DP = DePossible(joueur);
        int size = DP.size();
        for (int i = 0; i < size; i++)
        {
            if (i == 0)
            {
                coup = DP[0];
            }

            deplacement x = changePos(DP[i].indexP, DP[i].Fin);
            if ((G.pieces[DP[i].indexP].getTypePiece() == 0 && G.pieces[DP[i].indexP].getCoord().y == 7 && G.pieces[DP[i].indexP].getCouleur() == 1) || (G.pieces[DP[i].indexP].getTypePiece() == 0 && G.pieces[DP[i].indexP].getCoord().y == 0 && G.pieces[DP[i].indexP].getCouleur() == 2))
            {
                DP[i].setChanger(true);
                G.pieces[DP[i].indexP] = _Dame(G.pieces[DP[i].indexP].getCoord(), G.pieces[DP[i].indexP].getCouleur());
            }
            int m = v;
            int t = IaN(joueur, alpha, beta, true, true, depth - 1);
            //cout << t<<endl;

            v = max(v, t);
            /*if (!fils)
            {
                cout << DP[i].Fin.x << DP[i].Fin.y << endl;
                cout << "score: " << t << endl;
                cout << "v=: " << v << endl;
                cout << "m=: " << m << endl;
                cout <<"coup:" << coup.Fin.x << coup.Fin.y << endl;
            }*/
            if (v > m)

                coup = DP[i];
            if (beta < v)
            {

                if (fils)
                {
                    if (DP[i].aChanger)
                    {
                        G.pieces[DP[i].indexP] = _Pion(G.pieces[DP[i].indexP].getCoord(), G.pieces[DP[i].indexP].getCouleur());
                    }
                    changeBack(x);
                    actualisePlateau();
                    return v;
                }
            }
            alpha = max(alpha, v);
            if (DP[i].aChanger)
            {
                G.pieces[DP[i].indexP] = _Pion(G.pieces[DP[i].indexP].getCoord(), G.pieces[DP[i].indexP].getCouleur());
            }
            changeBack(x);
            actualisePlateau();
        }
    }
    if (fils)
    {
        return v;
    }
    else
    {
        changePos(coup.indexP, coup.Fin);
        if ((G.pieces[coup.indexP].getTypePiece() == 0 && G.pieces[coup.indexP].getCoord().y == 7 && G.pieces[coup.indexP].getCouleur() == 1) || (G.pieces[coup.indexP].getTypePiece() == 0 && G.pieces[coup.indexP].getCoord().y == 0 && G.pieces[coup.indexP].getCouleur() == 2))
        {

            G.pieces[coup.indexP] = _Dame(G.pieces[coup.indexP].getCoord(), G.pieces[coup.indexP].getCouleur());
        }
        actualisePlateau();
        fin();
        return v;
    }
}
int finDePartie() {
    if (DePossible(G.getJoueur()).empty()) {
        if (G.getJoueur() == 1) {
            for (int i = 0; i < 15; i++) {
                if (DeplacementPiece(G.pieces[i], G.pieces[31].getCoord()))
                    return 2;
            }
        }
        else if (G.getJoueur() == 2) {
            for (int i = 16; i < 31; i++) {
                if (DeplacementPiece(G.pieces[i], G.pieces[15].getCoord()))
                    return 1;
            }
        }
        return 0;
    }
    return -1;
}
void affichage_ecran_accueil() {
    //G2D::DrawRectangle(V2(0, 0), V2(640, 640), Color::Green, true);

    _Titre BG = _Titre(2);
    BG.IdTex = G2D::InitTextureFromString(BG.Size, BG.Texture);
    BG.Size = BG.Size * BG.Zoom;
    G2D::DrawRectWithTexture(BG.IdTex, V2(-400, 0), BG.Size);

    _Titre Titre = _Titre(1);
    Titre.IdTex = G2D::InitTextureFromString(Titre.Size, Titre.Texture);
    Titre.Size = Titre.Size * Titre.Zoom;
    G2D::DrawRectWithTexture(Titre.IdTex, V2(100, 550), Titre.Size);

    _Titre PionB = _Titre(3);
    PionB.IdTex = G2D::InitTextureFromString(PionB.Size, PionB.Texture);
    PionB.Size = PionB.Size * PionB.Zoom;
    G2D::DrawRectWithTexture(PionB.IdTex, V2(120, 250), PionB.Size);

    _Titre PionN = _Titre(4);
    PionN.IdTex = G2D::InitTextureFromString(PionN.Size, PionN.Texture);
    PionN.Size = PionN.Size * PionN.Zoom;
    G2D::DrawRectWithTexture(PionN.IdTex, V2(390, 250), PionN.Size);

    G2D::DrawStringFontMono(V2(100, 100), "Appuyez sur ENTER pour continuer.", 20, 3, Color::White);
}//end

void affichage_ecran_options() {
    _Titre BG = _Titre(2);
    BG.IdTex = G2D::InitTextureFromString(BG.Size, BG.Texture);
    BG.Size = BG.Size * BG.Zoom;
    G2D::DrawRectWithTexture(BG.IdTex, V2(-400, 0), BG.Size);

    G2D::DrawStringFontMono(V2(100, 500), "Choisissez votre difficulte !", 23, 3,
        Color::White);
    G2D::DrawStringFontMono(V2(50, 300),
        "Appuyez sur A pour jouer les blancs contre l'IA", 16, 3,
        Color::Green);
    G2D::DrawStringFontMono(V2(50, 250),
        "Appuyez sur B pour jouer les noirs contre l'IA", 16, 3,
        Color::Yellow);
    G2D::DrawStringFontMono(V2(50, 200),
        "Appuyez sur C pour jouer en PvP", 16, 3,
        Color::Blue);
}
//END

void affichage_init_partie() {
    _Titre BG = _Titre(2);
    BG.IdTex = G2D::InitTextureFromString(BG.Size, BG.Texture);
    BG.Size = BG.Size * BG.Zoom;
    G2D::DrawRectWithTexture(BG.IdTex, V2(-400, 0), BG.Size);

    _Titre roi = _Titre(8);
    roi.IdTex = G2D::InitTextureFromString(roi.Size, roi.Texture);
    roi.Size = roi.Size * roi.Zoom;
    G2D::DrawRectWithTexture(roi.IdTex, V2(250, 280), roi.Size);


    G2D::DrawStringFontMono(V2(10, 150), "CONSEIL : N'hesitez pas à utiliser le rocque pour mettre ", 16, 3,
        Color::White);
    G2D::DrawStringFontMono(V2(60, 130), "a l'abri votre roi et developper une de vos pieces", 16, 3, Color::White);

    G2D::DrawStringFontMono(V2(220, 80), "Appuyez sur ENTER", 16, 3, Color::White);

    G2D::DrawStringFontMono(V2(190, 590), "LOADING...", 40, 3, Color::White);

}
//ecran chargement
void affichage_ecran_jeu() {
    //TOUS LES AFFICHAGES VISUELS
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            int xx = x * G.Lpix -12;
            int yy = y * G.Lpix;
            if (G.Mur(x, y))
                G2D::DrawRectWithTexture(G.IdTexMur, V2(xx, yy),
                    G.Size);
            else {
                G2D::DrawRectWithTexture(G.IdTexSol, V2(xx, yy),
                    G.Size);
            }
        }
    
    

    //affichage pieces
    for (int i = 0; i<32;i++) {
        if (G.pieces[i].getEstVivant() && i!=G.pieceEncours) 
        {
            G.pieces[i].IdTex = G2D::InitTextureFromString(G.pieces[i].Size, G.pieces[i].Texture);
            G.pieces[i].Size = G.pieces[i].Size * G.pieces[i].Zoom;
            G2D::DrawRectWithTexture(G.pieces[i].IdTex, V2(G.pieces[i].getCoord().x * G.Lpix + 8, G.pieces[i].getCoord().y * G.Lpix + 2), G.pieces[i].Size);
        }
    }
    if (G.pieceEncours != -1) {
        for (V2 position : G.zonesJouables) {
            int xx = position.x * G.Lpix - 12;
            int yy = position.y * G.Lpix;
            G2D::DrawRectWithTexture(G.IdTexPossible, V2(xx, yy),
                G.Size);
        }
    }
    if (G2D::IsMouseLeftButtonPressed())
    {
        if (G.mouseIsActive)
        {
            G.pieces[G.pieceEncours].IdTex = G2D::InitTextureFromString(G.pieces[G.pieceEncours].Size, G.pieces[G.pieceEncours].Texture);
            G.pieces[G.pieceEncours].Size = G.pieces[G.pieceEncours].Size * G.pieces[G.pieceEncours].Zoom * 1.5;
            G2D::DrawRectWithTexture(G.pieces[G.pieceEncours].IdTex, V2((G.xMouse - G.pieces[G.pieceEncours].Size.x / 2), G.yMouse - G.pieces[G.pieceEncours].Size.y / 2), G.pieces[G.pieceEncours].Size);
        }
    }
    if (G.TimerEnd > 0 && G.TimerEnd < 80)
    {
        G2D::DrawStringFontMono(V2(50, 300), "CHECKMATE!!", 80, 20,
            Color::Black);
    }
}
//end
void affichage_ecran_victoire_blanc() 
{
    _Titre BG = _Titre(6);
    BG.IdTex = G2D::InitTextureFromString(BG.Size, BG.Texture);
    BG.Size = BG.Size * BG.Zoom;
    G2D::DrawRectWithTexture(BG.IdTex, V2(-400, 0), BG.Size);

    _Titre Win = _Titre(9);
    Win.IdTex = G2D::InitTextureFromString(Win.Size, Win.Texture);
    Win.Size = Win.Size * Win.Zoom;
    G2D::DrawRectWithTexture(Win.IdTex, V2(30, 300), Win.Size);

    //G2D::DrawStringFontMono(V2(70, 500), "You WIN !!!!", 80, 10, Color::Green);
    G2D::DrawStringFontMono(V2(50, 200),
        "Appuyez sur ENTER pour faire une autre partie.", 16,
        3, Color::Black);
}
//end

void affichage_ecran_victoire_noir() {
    _Titre Win = _Titre(5);
    Win.IdTex = G2D::InitTextureFromString(Win.Size, Win.Texture);
    Win.Size = Win.Size * Win.Zoom;
    G2D::DrawRectWithTexture(Win.IdTex, V2(30, 300), Win.Size);

    G2D::DrawStringFontMono(V2(50, 200),
        "Appuyez sur ENTER pour faire une autre partie.", 16,
        3, Color::White);
}
void affichage_ecran_pat() {
    _Titre BG = _Titre(6);
    BG.IdTex = G2D::InitTextureFromString(BG.Size, BG.Texture);
    BG.Size = BG.Size * BG.Zoom;
    G2D::DrawRectWithTexture(BG.IdTex, V2(-400, 0), BG.Size);

    _Titre Tie = _Titre(7);
    Tie.IdTex = G2D::InitTextureFromString(Tie.Size, Tie.Texture);
    Tie.Size = Tie.Size * Tie.Zoom;
    G2D::DrawRectWithTexture(Tie.IdTex, V2(160, 300), Tie.Size);

    G2D::DrawStringFontMono(V2(100, 100), "Appuyez sur ENTER pour continuer.", 20, 3, Color::Black);

}
//end
void render() {
    G2D::ClearScreen(Color::Black);
    if (G.ecran == ECRAN_ACCUEIL) {
        affichage_ecran_accueil();
    }
    if (G.ecran == ECRAN_OPTIONS) {
        affichage_ecran_options();
    }
    if (G.ecran == INIT_PARTIE) {
        affichage_init_partie();
    }
    if (G.ecran == ECRAN_JEU) {
        affichage_ecran_jeu();
    }
    if (G.ecran == ECRAN_Victoire_Blanc) {
        affichage_ecran_victoire_blanc();
    }
    if (G.ecran == ECRAN_Victoire_Noir) {
        affichage_ecran_victoire_noir();
    }
    if (G.ecran == ECRAN_Pat) {
        affichage_ecran_pat();
    }
    G2D::Show();
}


int gestion_ecran_accueil() {
    if (G2D::IsKeyPressed(Key::ENTER)) {
        return 1;
    }
    return 0;
}
//end
int gestion_ecran_options() {
    // blanc contre ia
    if (G2D::IsKeyPressed(Key::A)) {
        G.joueurIa = 2;
        return 2;
    }
    // noir contre ia
    if (G2D::IsKeyPressed(Key::B)) {
        G.joueurIa = 1;
        return 2;
    }
    // jCJ
    if (G2D::IsKeyPressed(Key::C)) {

        G.joueurIa = 0;
        return 2;
    }
    return 1;
}
//end

int InitPartie() {
    if (G2D::IsKeyPressed(Key::ENTER)) {
        G.setPieces();
        G.Plateau.resetPlateau();
        G.joueur = 1;
        G.setTimerEnd(0);
        //réinitialise la game
        return 3;
    }
    return 2;
}
//end
int gestion_ecran_jeu() {
    //l'integralité des fonctionnements gameplay / imput

    //cout << DeplacementPiece(_Pion(V2(6, 1), 1, 0), V2(6, 3)) << endl;
    if (G.TimerEnd > 0 && G.TimerEnd < 80)
    {
        cout << G.TimerEnd<<endl;
        G.setTimerEnd(G.TimerEnd + 1);
        return 3;
    }
    if (G.getJoueur()==G.joueurIa)
    {
       actualisePlateau();
       IaN(G.joueurIa, -2000, 2000, false, false, 3);
       G.setJoueur();
    }
    else
    { 
        if (G2D::IsMouseLeftButtonPressed())
        {
            G2D::GetMousePos(&G.xMouse, &G.yMouse);
            if (!G.mouseIsActive)
            {
                if (G.getJoueur()==1)
                {
                    for (int i = 16; i < 32; i++) {
                        if (G.pieces[i].getEstVivant() && G.pieces[i].getCoord() == V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)))
                        {
                            G.pieceEncours = i;
                            G.setMouseIsActive(true);
                            setZonesJouables(G.pieces[G.pieceEncours]);
                            break;
                        }
                    }
                }
                else if(G.getJoueur() == 2)
                {
                    for (int i = 0; i < 16; i++) {
                        if (G.pieces[i].getEstVivant() && G.pieces[i].getCoord() == V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)))
                        {
                            G.pieceEncours = i;
                            G.setMouseIsActive(true);
                            setZonesJouables(G.pieces[G.pieceEncours]);
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if (G.mouseIsActive)
            {
                G.setMouseIsActive(false);
                if (DeplacementPiece(G.pieces[G.pieceEncours], V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)))) {
                    if (NoSuicideMove(G.pieces[G.pieceEncours], V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)))) {
                        if (G.Plateau.getPositionPiece(V2((int)(G.xMouse / 80), (int)(G.yMouse / 80))) == 0) {
                            /*if (G.pieces[G.pieceEncours].getTypePiece() == 5) {//verification si roque
                                if ((G.pieces[G.pieceEncours].getCoord().x + 2 == (int)(G.xMouse / 80))) {
                                    if (G.pieces[G.pieceEncours].getCouleur() == 1) {
                                        G.Plateau.setPositionPiece(5, 0, "1");
                                        G.Plateau.setPositionPiece(7, 0, "0");
                                        G.pieces[25].setCoord(V2(5, 0));
                                    }
                                    else {
                                        G.Plateau.setPositionPiece(5, 7, "2");
                                        G.Plateau.setPositionPiece(7, 7, "0");
                                        G.pieces[9].setCoord(V2(5, 7));
                                    }
                                }
                                else if ((G.pieces[G.pieceEncours].getCoord().x - 2 == (int)(G.xMouse / 80))) {
                                    if (G.pieces[G.pieceEncours].getCouleur() == 1) {
                                        G.Plateau.setPositionPiece(3, 0, "1");
                                        G.Plateau.setPositionPiece(0, 0, "0");
                                        G.pieces[24].setCoord(V2(3, 0));
                                    }
                                    else {
                                        G.Plateau.setPositionPiece(3, 7, "2");
                                        G.Plateau.setPositionPiece(0, 7, "0");
                                        G.pieces[8].setCoord(V2(3, 7));
                                    }
                                }
                            }
                            */
                            G.Plateau.setPositionPiece((int)(G.xMouse / 80), (int)(G.yMouse / 80), to_string(G.pieces[G.pieceEncours].getCouleur()));
                            G.Plateau.setPositionPiece(G.pieces[G.pieceEncours].getCoord().x, G.pieces[G.pieceEncours].getCoord().y, "0");
                            G.pieces[G.pieceEncours].setCoord(V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)));
                            if (G.pieces[G.pieceEncours].getNoMove()) {
                                G.pieces[G.pieceEncours].setNoMove(false);
                            }
                            if ((G.pieces[G.pieceEncours].getTypePiece() == 0 && G.pieces[G.pieceEncours].getCoord().y == 7 && G.pieces[G.pieceEncours].getCouleur() == 1) || (G.pieces[G.pieceEncours].getTypePiece() == 0 && G.pieces[G.pieceEncours].getCoord().y == 0 && G.pieces[G.pieceEncours].getCouleur() == 2)) {
                                G.pieces[G.pieceEncours] = _Dame(G.pieces[G.pieceEncours].getCoord(), G.pieces[G.pieceEncours].getCouleur());
                            }
                        }
                        else if (G.Plateau.getPositionPiece(V2((int)(G.xMouse / 80), (int)(G.yMouse / 80))) != G.pieces[G.pieceEncours].getCouleur()) {
                            for (_Piece& piece : G.pieces) {
                                if (piece.getCoord() == V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)) && piece.getEstVivant()) {
                                    piece.setEstVivant(false);
                                }
                            }
                            G.Plateau.setPositionPiece((int)(G.xMouse / 80), (int)(G.yMouse / 80), to_string(G.pieces[G.pieceEncours].getCouleur()));
                            G.Plateau.setPositionPiece(G.pieces[G.pieceEncours].getCoord().x, G.pieces[G.pieceEncours].getCoord().y, "0");
                            G.pieces[G.pieceEncours].setCoord(V2((int)(G.xMouse / 80), (int)(G.yMouse / 80)));
                            if (G.pieces[G.pieceEncours].getNoMove()) {
                                G.pieces[G.pieceEncours].setNoMove(false);
                            }
                            if ((G.pieces[G.pieceEncours].getTypePiece() == 0 && G.pieces[G.pieceEncours].getCoord().y == 7 && G.pieces[G.pieceEncours].getCouleur() == 1) || (G.pieces[G.pieceEncours].getTypePiece() == 0 && G.pieces[G.pieceEncours].getCoord().y == 0 && G.pieces[G.pieceEncours].getCouleur() == 2)) {
                                G.pieces[G.pieceEncours] = _Dame(G.pieces[G.pieceEncours].getCoord(), G.pieces[G.pieceEncours].getCouleur());
                            }
                            
                        }
                        

                        G.setJoueur();
                    }
                }
                G.pieceEncours = -1;
            }
        }

    }
    int finpartie = finDePartie();
    if (finpartie != -1) {
        if (G.TimerEnd <= 0)
        {
            G.setTimerEnd(1);
            return 3;
        }

        if (finpartie == 1) {
            return 4;
        }
        else if (finpartie == 2) {
            return 5;
        }
        else {
            return 6;
        }
    }
    return 3;
}
//end
int gestion_ecran_victoire_blanc() {
    if (G2D::IsKeyPressed(Key::ENTER)) {
        return 1;
    }
    return 4;
}
int gestion_ecran_victoire_noir() {
    if (G2D::IsKeyPressed(Key::ENTER)) {
        return 1;
    }
    return 5;
}
int gestion_ecran_pat() {
    if (G2D::IsKeyPressed(Key::ENTER)) {
        return 1;
    }
    return 6;
}
void Logic() {
    if (G.ecran == ECRAN_ACCUEIL) {
        G.ecran = gestion_ecran_accueil();
    }

    if (G.ecran == ECRAN_OPTIONS) {
        G.ecran = gestion_ecran_options();
    }
    if (G.ecran == INIT_PARTIE) {
        G.ecran = InitPartie();
    }
    if (G.ecran == ECRAN_JEU) {
        G.ecran = gestion_ecran_jeu();
    }

    if (G.ecran == ECRAN_Victoire_Blanc) {
        G.ecran = gestion_ecran_victoire_blanc();
    }
    if (G.ecran == ECRAN_Victoire_Noir) {
        G.ecran = gestion_ecran_victoire_noir();
    }
    if (G.ecran == ECRAN_Pat) {
        G.ecran = gestion_ecran_pat();
    }
}

void AssetsInit() {
    // Size passé en ref et texture en param
    G.IdTexMur =
        G2D::InitTextureFromString(G.Size, G.Plateau.textureMur);
    G.IdTexSol =
        G2D::InitTextureFromString(G.Size, G.Plateau.textureSol);
    G.IdTexPossible =
        G2D::InitTextureFromString(G.Size, G.Plateau.texturePossible);
    G.Size =
        G.Size * 10; // on peut zoomer la taille du sprite
}
int main(int argc, char* argv[]) {
    G2D::InitWindow(argc, argv, V2(G.Lpix * 8, G.Lpix * 8), V2(200, 200),
        string("Echecs"));

    AssetsInit();

    G2D::Run(Logic, render);
}