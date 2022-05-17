#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <QProcess>
#include <QTime>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include "utils.h"

static QString Stockfish= "\""+QDir::currentPath()+"/Resources/stockfish_14.1/stockfish_14.1.exe";
static QString Leela= "\""+QDir::currentPath()+"/Resources/Lc0/Lc0.exe";
static QString Fire= "\""+QDir::currentPath()+"/Resources/Fire/Fire_8.2_x64/Fire_8.2_x64_sse41.exe";

static QString PawnOddsWhite= "rnbqkbnr/pppppppp/8/8/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
static QString PawnOddsBlack= "rnbqkbnr/pppp1ppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
static QString KnightOddsWhite= "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R1BQKBNR w KQkq - 0 1";
static QString KnightOddsBlack= "r1bqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
static QString BishopOddsWhite= "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RN1QKBNR w KQkq - 0 1";
static QString BishopOddsBlack= "rn1qkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
static QString RookOddsWhite= "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR w Kkq - 0 1";
static QString RookOddsBlack= "1nbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQk - 0 1";
static QString QueenOddsWhite= "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNB1KBNR w KQkq - 0 1";
static QString QueenOddsBlack= "rnb1kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Engine
{
public:
    static QProcess* startEngine(QString PathToEngine);
    static QString Write(QByteArray command,QProcess *process);
    static QString MakeMove(QProcess *process,unsigned int timePerMove);
    static void SetOddsPosition(QString whiteOdds,QString blackOdds,QString* FEN);
    static void Quit(QList<QProcess*> processList);
    static void Delay(unsigned int timePerMove);
    static void InitializeLeela(QProcess *process);
    static bool CheckForThreeFoldRepetition(QByteArray allMoves);
private:
    Engine(){};
};

#endif // ENGINE_H
