#include "engine.h"

QProcess* Engine::startEngine(QString PathToEngine) {
    QProcess *process = new QProcess();
    process->start(PathToEngine);
    if (!process->waitForStarted()) return NULL;
    Write("uci",process);
    if(Write("isready",process).contains("readyok\r")){
        if(PathToEngine.contains("Lc0")){
            InitializeLeela(process);
            return process;
        }
        Write("ucinewgame",process);
        return process;
    }
    return NULL;
}

QString Engine::Write(QByteArray command,QProcess *process){
    process->setReadChannel(QProcess::StandardOutput);
    process->write(command+"\n");
    if(command.contains("ucinewgame") || command.contains("position")){ //commands that dont return output so we dont need to wait for it
        return "ok";
    }
    process->waitForReadyRead();
    QString line;
    QString lastLine;
    while (process->canReadLine()) {
       line = QString::fromLocal8Bit(process->readLine());
       if(line.contains("bestmove")){
           if(line.contains("none")){
               if(lastLine.contains("mate 0")){
                   return "defeat";
               }else if(lastLine.contains("cp 0")){
                   return "draw";
               }
           }
           return line;
       }
       if(command.contains("go") && !line.contains("bestmove") && line.contains("mate") && !process->canReadLine()){
           process->waitForReadyRead();
       }
       if(line.contains("bestmove (none)")){ //engine is mated or in stalemate
           if(lastLine.contains("mate 0")){
               return "defeat";
           }else if(lastLine.contains("cp 0")){
               return "draw";
           }
       }
       lastLine = line;
    }
    return line;
}
void Engine::SetOddsPosition(QString whiteOdds,QString blackOdds,QString* FEN){

    if(whiteOdds == "e2 Pawn"){
        FEN->replace(30,1,'1');
    }else if(whiteOdds == "b1 Knight"){
        FEN->replace(36,1,'1');
    }else if(whiteOdds == "c1 Bishop"){
        FEN->replace(37,1,'1');
    }else if(whiteOdds == "a1 Rook"){
        FEN->replace(35,1,'1');
    }else if(whiteOdds == "Queen"){
        FEN->replace(38,1,'1');
    }

    if(blackOdds == "e7 Pawn"){
        FEN->replace(13,1,'1');
    }else if(blackOdds == "b8 Knight"){
        FEN->replace(1,1,'1');
    }else if(blackOdds == "c8 Bishop"){
        FEN->replace(2,1,'1');
    }else if(blackOdds == "a8 Rook"){
        FEN->replace(0,1,'1');
    }else if(blackOdds == "Queen"){
        FEN->replace(3,1,'1');
    }
}

void Engine::InitializeLeela(QProcess *process){
    process->setReadChannel(QProcess::StandardOutput);
    process->write("ucinewgame\n");
    process->waitForReadyRead();
    Delay(5);
}

bool Engine::CheckForThreeFoldRepetition(QByteArray allMoves){
    QByteArrayList listOfAllMoves = allMoves.split(' ');
    if(listOfAllMoves.length() < 9){
        return false;
    }
    QByteArray fourthMove = listOfAllMoves[listOfAllMoves.length()-3]+listOfAllMoves[listOfAllMoves.length()-2];
    QByteArray thirdMove = listOfAllMoves[listOfAllMoves.length()-5]+listOfAllMoves[listOfAllMoves.length()-4];
    QByteArray secondMove = listOfAllMoves[listOfAllMoves.length()-7]+listOfAllMoves[listOfAllMoves.length()-6];
    QByteArray firstMove = listOfAllMoves[listOfAllMoves.length()-9]+listOfAllMoves[listOfAllMoves.length()-8];
    if(firstMove == thirdMove && secondMove == fourthMove){
        return true;
    }
    return false;
}

void Engine::Quit(QList<QProcess*> processList){
    if(processList.isEmpty()){
        return;
    }
    for(QProcess* x : processList){
        x->kill();
    }
}

void Engine::Delay(unsigned int timePerMove){
    QTime dieTime= QTime::currentTime().addSecs(timePerMove);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString Engine::MakeMove(QProcess *process,unsigned int timePerMove){
    process->setReadChannel(QProcess::StandardOutput);
    process->write("go\n");
    QTime dieTime= QTime::currentTime().addSecs(timePerMove);
    QString line = "unset";
    QString lastLine = "unset";
    while (QTime::currentTime() < dieTime){
            if(process->canReadLine()){
                line = QString::fromLocal8Bit(process->readLine());
            }

           if(line.contains("bestmove")){
               if(line.contains("none") || line == "bestmove \r\n"
                       || utils::GetMoveFromEngine(line).left(2) == utils::GetMoveFromEngine(line).mid(2,2)){
                   if(lastLine.contains("mate 0") || utils::GetMoveFromEngine(line).left(2) == utils::GetMoveFromEngine(line).mid(2,2)){
                       return "defeat";
                   }else if(lastLine.contains("cp 0")){
                       return "draw";
                   }
               }
               return line;
           }
            lastLine = line;
           QCoreApplication::processEvents();
        }
    process->write("stop\n");
    process->waitForReadyRead();
    while (process->canReadLine()) {
        if(process->canReadLine()){
            line = QString::fromLocal8Bit(process->readLine());
        }

       if(line.contains("bestmove")){
           if(line.contains("none") || line == "bestmove \r\n"
                   || utils::GetMoveFromEngine(line).left(2) == utils::GetMoveFromEngine(line).mid(2,2)){
               if(lastLine.contains("mate 0") || utils::GetMoveFromEngine(line).left(2) == utils::GetMoveFromEngine(line).mid(2,2)){
                   return "defeat";
               }else if(lastLine.contains("cp 0")){
                   return "draw";
               }
           }
           return line;
       }
        lastLine = line;

       while(!line.contains("bestmove") && !process->canReadLine()){
           if(process->canReadLine()){
               break;
           }
           QTime dieTime= QTime::currentTime().addMSecs(100);
           while (QTime::currentTime() < dieTime)
               QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
       }
    }
    return line;
}

