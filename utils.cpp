#include "utils.h"

utils::utils()
{

}

QString utils::GetMoveFromEngine(QString moveString){
    if(moveString.isEmpty()){
        return "Error - move string is empty";
    }
    QStringList move = moveString.split(' ');
    if(moveString.contains("bestmove")){
        return  move[1].trimmed();
    }
    if(moveString == "defeat" || moveString == "draw"){
        return moveString;
    }
    return "Error";
}

void utils::WriteGameHistory(QString whiteName,QString blackName,QString whiteOdds,QString blackOdds,int timePerMove,
                             QByteArray allMoves,GameResult result){
    bool fileExists = std::filesystem::exists(historyFile.toStdString()) ? true : false;
    std::ofstream history(historyFile.toStdString(),std::ios::app);
    QString resultString;
    switch(result) {
      case draw:
        resultString = "Draw";
        break;
      case whiteWins:
        resultString = "White wins";
        break;
      case blackWins:
        resultString = "Black wins";
        break;
      case stopped:
        history.close();
        return;
    }

    if(!fileExists){
        history << "White,Black,White Odds,Black Odds,Time per move,Moves,Result\n";
    }
    history << whiteName.toStdString()+","+
               blackName.toStdString()+","+
               whiteOdds.toStdString()+","+
               blackOdds.toStdString()+","+
               std::to_string(timePerMove)+","+
               allMoves.toStdString()+","+
               resultString.toStdString()+"\n";
    // Close the file
    history.close();
}
