#include "gameinstance.h"

GameInstance::GameInstance(QString _white, QString _black,QString _whiteOdds,QString _blackOdds,unsigned int _timePerMove,QTextBrowser* _moveBox,QGraphicsScene* _scene,QMap<QString,QLabel*> _captureMap)
{
    white = _white;
    black = _black;
    whiteOdds = _whiteOdds;
    blackOdds = _blackOdds;
    timePerMove = _timePerMove;
    moveBox = _moveBox;
    scene = _scene;
    captureMap = _captureMap;
}

GameResult GameInstance::Start(){
    insufficentMaterial = false;
    fiftyMoveRule = 0;
    if(timePerMove == 0 || isStopped){
        return stopped;
    }
    if(processList.isEmpty()){
        QString algArray[2] = {white,black};
        for(unsigned int i = 0; i < 2;i++){
            if(algArray[i] == "Stockfish"){
                processList.append(Engine::startEngine(Stockfish));
            }else if(algArray[i] == "Leela Chess Zero"){
                processList.append(Engine::startEngine(Leela));
            }else if(algArray[i] == "Fire"){
                processList.append(Engine::startEngine(Fire));
            }
        }
    }
    allMoves.clear();
    allMovesDisplayed.clear();
    QString currentMove;
    int moveCounter = 1;
    ChessBoard::SetStartingPosition(scene);
    ChessBoard::ResetCapturedPieces(captureMap);
    if(whiteOdds != "None" || blackOdds != "None"){
        ChessBoard::SetOddsPosition(scene,whiteOdds,blackOdds,captureMap);
        Engine::SetOddsPosition(whiteOdds,blackOdds,&FEN);
    }

    while (true) {
        /*Both engines make one move*/
        if(fiftyMoveRule == 50){
            return draw;
        }
        fiftyMoveRule++;
        for(unsigned int i = 0; i < 2;i++){
            if(isStopped){
                return stopped;
            }
            /*Set up position for engine*/
            Engine::Write("position fen "+FEN.toUtf8()+" moves "+allMoves,processList[i]);
            /*Engine starts calculation*/
            currentMove = utils::GetMoveFromEngine(Engine::MakeMove(processList[i],timePerMove));
            if(currentMove == "defeat"){
                return i == 0 ? blackWins : whiteWins;
            }else if(currentMove == "draw"){
                return draw;
            }
            /*Engine gives evaluation and position, show engine move on GUI*/
            allMovesDisplayed.append((i == 0 ? QString::number(moveCounter).toUtf8()+". " : QString().toUtf8()) +ChessBoard::EditMoveForDisplay(currentMove,scene).toUtf8()+(i % 2 != 0 ? "\n" : " "));
            ChessBoard::MakeMove(currentMove,scene,&fiftyMoveRule,&insufficentMaterial,captureMap);
            allMoves.append(currentMove.toUtf8()+" ");
            moveBox->setText(allMovesDisplayed);
            QCoreApplication::processEvents();
            if(Engine::CheckForThreeFoldRepetition(allMoves) || insufficentMaterial){
                return draw;
            }
        }
        moveCounter++;
    }
}
