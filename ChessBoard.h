#ifndef GENERATECHESSBOARD_H
#define GENERATECHESSBOARD_H
#include <QMainWindow>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QCoreApplication>
#include <QLabel>

struct squarePos {
  unsigned int x;
  unsigned int y;
  QPointF pos = QPointF(x,y);
};

static const QMap<QString,squarePos> squareMap{
    {"a8", {0,0}},{"b8", {50,0}},{"c8", {100,0}},{"d8", {150,0}},{"e8", {200,0}},{"f8", {250,0}},{"g8", {300,0}},{"h8", {350,0}},
    {"a7", {0,50}},{"b7", {50,50}},{"c7", {100,50}},{"d7", {150,50}},{"e7", {200,50}},{"f7", {250,50}},{"g7", {300,50}},{"h7", {350,50}},
    {"a6", {0,100}},{"b6", {50,100}},{"c6", {100,100}},{"d6", {150,100}},{"e6", {200,100}},{"f6", {250,100}},{"g6", {300,100}},{"h6", {350,100}},
    {"a5", {0,150}},{"b5", {50,150}},{"c5", {100,150}},{"d5", {150,150}},{"e5", {200,150}},{"f5", {250,150}},{"g5", {300,150}},{"h5", {350,150}},
    {"a4", {0,200}},{"b4", {50,200}},{"c4", {100,200}},{"d4", {150,200}},{"e4", {200,200}},{"f4", {250,200}},{"g4", {300,200}},{"h4", {350,200}},
    {"a3", {0,250}},{"b3", {50,250}},{"c3", {100,250}},{"d3", {150,250}},{"e3", {200,250}},{"f3", {250,250}},{"g3", {300,250}},{"h3", {350,250}},
    {"a2", {0,300}},{"b2", {50,300}},{"c2", {100,300}},{"d2", {150,300}},{"e2", {200,300}},{"f2", {250,300}},{"g2", {300,300}},{"h2", {350,300}},
    {"a1", {0,350}},{"b1", {50,350}},{"c1", {100,350}},{"d1", {150,350}},{"e1", {200,350}},{"f1", {250,350}},{"g1", {300,350}},{"h1", {350,350}},
};

static qint16 whitePawnCounter = 0;
static qint16 whiteKnightCounter = 0;
static qint16 whiteBishopCounter = 0;
static qint16 whiteRookCounter = 0;
static qint16 whiteQueenCounter = 0;
static qint16 blackPawnCounter = 0;
static qint16 blackKnightCounter = 0;
static qint16 blackBishopCounter = 0;
static qint16 blackRookCounter = 0;
static qint16 blackQueenCounter = 0;

class ChessBoard
{
public:
    ChessBoard();
    static QGraphicsScene* generateBoard();
    static bool MakeMove(QString move,QGraphicsScene* scene,unsigned int* fiftyMoveRule,bool* isThreeFoldRepetition,QMap<QString,QLabel*> captureList);
    static void applyCastlingRule(QString move, QGraphicsItem* king, QList<QGraphicsItem*> pieceList);
    static bool handlePromotion(QString moveTo, QString promoteTo,QGraphicsScene*);
    static void showCapturedPiece(QGraphicsItem* toPiece,QMap<QString,QLabel*> captureMap);
    static void SetStartingPosition(QGraphicsScene* scene);
    static void SetOddsPosition(QGraphicsScene* scene, QString whiteOdds, QString blackOdds, QMap<QString,QLabel*> capturedPieces);
    static void RemovePiece(QGraphicsScene* scene,QString pieceSquare,QMap<QString,QLabel*> capturedPieces);
    static void ResetCapturedPieces(QMap<QString,QLabel*> capturedPieces);
    static QString EditMoveForDisplay(QString move, QGraphicsScene* scene);
};

#endif // GENERATECHESSBOARD_H
