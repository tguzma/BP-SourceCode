#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QList>
#include <QDebug>
#include <QDir>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

enum GameResult { stopped,draw,whiteWins,blackWins};
static const QString historyFile = QDir::currentPath()+"/History.csv";

class utils
{
public:
    utils();
    static QString GetMoveFromEngine(QString moveString);
    static void WriteGameHistory(QString whiteName,QString blackName,QString whiteOdds,QString blackOdds,int timePerMove,
                                 QByteArray allMoves,GameResult result);
};

#endif // UTILS_H
