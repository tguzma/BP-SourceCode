#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H
#include "engine.h"
#include "utils.h"
#include "ChessBoard.h"
#include <iostream>
#include <chrono>
#include <QThread>
#include <QTextBrowser>
#include <QLabel>

class GameInstance
{
public:
    QString white;
    QString whiteOdds;
    QString black;
    QString blackOdds;
    QString FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    QByteArray allMoves;
    QByteArray allMovesDisplayed;
    QList<QByteArray> allMovesList;
    unsigned int timePerMove;
    QTextBrowser* moveBox;
    QGraphicsScene* scene;
    bool isStopped = false;
    unsigned int fiftyMoveRule;
    bool insufficentMaterial;
    QList<QProcess*> processList;
    QMap<QString,QLabel*> captureMap;
    GameInstance(QString _white, QString _black,QString _whiteOdds,QString _blackOdds,unsigned int _timePerMove,QTextBrowser* moveBox,QGraphicsScene* _scene,QMap<QString,QLabel*> _captureList);
    GameResult Start();
};

#endif // GAMEINSTANCE_H
