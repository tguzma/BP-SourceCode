#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
}

QGraphicsScene* ChessBoard::generateBoard(){

    QGraphicsScene* scene = new QGraphicsScene();

    int x = 0;
    int y = 0;
    QGraphicsRectItem* array[64];
    int iterator = 0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            array[iterator] = new QGraphicsRectItem(x,y,50,50);

            iterator++;
            x+=50;
        }
        x=0;
        y+=50;
    }
    int odd = 0;
    int even = 1;
    int tmp;
    for(int i = 0;i<63;i+=2){
        if(i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || i == 48 || i == 56){
            tmp = odd;
            odd = even;
            even = tmp;
        }
        array[i+odd]->setBrush(QBrush(QColor(245,245,220)));
        array[i+even]->setBrush(QBrush(QColor(125,135,150)));
    }
    for(int i = 0;i<64;i++){
        scene->addItem(array[i]);
    }

    SetStartingPosition(scene);

    return scene;
}

void ChessBoard::SetStartingPosition(QGraphicsScene* scene){
    //FEN STARTING POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    //delete items from previous game
    QList<QGraphicsItem *> list = scene->items();
    for(QGraphicsItem* x : list){
        if(x->data(0) == "piece"){
            delete x;
        }
    }

    const QPixmap wQ = QPixmap(":Chess_pieces/Chess_white_queen.png");
    const QPixmap wK = QPixmap(":Chess_pieces/Chess_white_king.png");
    const QPixmap wN = QPixmap(":Chess_pieces/Chess_white_knight.png");
    const QPixmap wP = QPixmap(":Chess_pieces/Chess_white_pawn.png");
    const QPixmap wR = QPixmap(":Chess_pieces/Chess_white_rook.png");
    const QPixmap wB = QPixmap(":Chess_pieces/Chess_white_bishop.png");

    const QPixmap bQ = QPixmap(":Chess_pieces/Chess_black_queen.png");
    const QPixmap bK = QPixmap(":Chess_pieces/Chess_black_king.png");
    const QPixmap bN = QPixmap(":Chess_pieces/Chess_black_knight.png");
    const QPixmap bP = QPixmap(":Chess_pieces/Chess_black_pawn.png");
    const QPixmap bR = QPixmap(":Chess_pieces/Chess_black_rook.png");
    const QPixmap bB = QPixmap(":Chess_pieces/Chess_black_bishop.png");

    QGraphicsPixmapItem* whiteQueen = scene->addPixmap(wQ);
    QGraphicsPixmapItem* whiteKing = scene->addPixmap(wK);

    QGraphicsPixmapItem* whiteRook1 = scene->addPixmap(wR);
    QGraphicsPixmapItem* whiteRook2 = scene->addPixmap(wR);

    QGraphicsPixmapItem* whiteKnight1 = scene->addPixmap(wN);
    QGraphicsPixmapItem* whiteKnight2 = scene->addPixmap(wN);

    QGraphicsPixmapItem* whiteBishop1 = scene->addPixmap(wB);
    QGraphicsPixmapItem* whiteBishop2 = scene->addPixmap(wB);

    QGraphicsPixmapItem* whitePawn1 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn2 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn3 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn4 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn5 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn6 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn7 = scene->addPixmap(wP);
    QGraphicsPixmapItem* whitePawn8 = scene->addPixmap(wP);
    //create black pieces
    QGraphicsPixmapItem* blackQueen = scene->addPixmap(bQ);
    QGraphicsPixmapItem* blackKing = scene->addPixmap(bK);

    QGraphicsPixmapItem* blackRook1 = scene->addPixmap(bR);
    QGraphicsPixmapItem* blackRook2 = scene->addPixmap(bR);

    QGraphicsPixmapItem* blackKnight1 = scene->addPixmap(bN);
    QGraphicsPixmapItem* blackKnight2 = scene->addPixmap(bN);

    QGraphicsPixmapItem* blackBishop1 = scene->addPixmap(bB);
    QGraphicsPixmapItem* blackBishop2 = scene->addPixmap(bB);

    QGraphicsPixmapItem* blackPawn1 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn2 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn3 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn4 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn5 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn6 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn7 = scene->addPixmap(bP);
    QGraphicsPixmapItem* blackPawn8 = scene->addPixmap(bP);

    QList<QGraphicsPixmapItem*> pieceList = {
        whiteQueen,whiteKing,whiteRook1,whiteRook2,whiteKnight1,whiteKnight2,whiteBishop1,whiteBishop2,
        whitePawn1,whitePawn2,whitePawn3,whitePawn4, whitePawn5,whitePawn6, whitePawn7,whitePawn8,
        blackQueen,blackKing,blackRook1,blackRook2,blackKnight1,blackKnight2,blackBishop1,blackBishop2,
        blackPawn1,blackPawn2,blackPawn3,blackPawn4,blackPawn5,blackPawn6,blackPawn7,blackPawn8
    };
    for(QGraphicsPixmapItem* piece: pieceList){
        piece->setScale(0.8);
        piece->setData(0,"piece");
    }
    //position white pieces
    whiteQueen->setPos(QPointF(squareMap.value("d1").pos));
    whiteQueen->setData(1,"Q");
    whiteKing->setPos(QPointF(squareMap.value("e1").pos));
    whiteKing->setData(1,"K");

    whiteRook1->setPos(squareMap.value("a1").pos);
    whiteRook1->setData(1,"R");
    whiteRook2->setPos(squareMap.value("h1").pos);
    whiteRook2->setData(1,"R");

    whiteKnight1->setPos(squareMap.value("b1").pos);
    whiteKnight1->setData(1,"N");
    whiteKnight2->setPos(squareMap.value("g1").pos);
    whiteKnight2->setData(1,"N");

    whiteBishop1->setPos(squareMap.value("c1").pos);
    whiteBishop1->setData(1,"B");
    whiteBishop2->setPos(squareMap.value("f1").pos);
    whiteBishop2->setData(1,"B");

    whitePawn1->setPos(squareMap.value("a2").pos);
    whitePawn2->setPos(squareMap.value("b2").pos);
    whitePawn3->setPos(squareMap.value("c2").pos);
    whitePawn4->setPos(squareMap.value("d2").pos);
    whitePawn5->setPos(squareMap.value("e2").pos);
    whitePawn6->setPos(squareMap.value("f2").pos);
    whitePawn7->setPos(squareMap.value("g2").pos);
    whitePawn8->setPos(squareMap.value("h2").pos);
    whitePawn1->setData(1,"P");
    whitePawn2->setData(1,"P");
    whitePawn3->setData(1,"P");
    whitePawn4->setData(1,"P");
    whitePawn5->setData(1,"P");
    whitePawn6->setData(1,"P");
    whitePawn7->setData(1,"P");
    whitePawn8->setData(1,"P");

    //position black pieces

    blackQueen->setPos(squareMap.value("d8").pos);
    blackQueen->setData(1,"q");
    blackKing->setPos(squareMap.value("e8").pos);
    blackKing->setData(1,"k");

    blackRook1->setPos(squareMap.value("a8").pos);
    blackRook1->setData(1,"r");
    blackRook2->setPos(squareMap.value("h8").pos);
    blackRook2->setData(1,"r");

    blackKnight1->setPos(squareMap.value("b8").pos);
    blackKnight1->setData(1,"n");
    blackKnight2->setPos(squareMap.value("g8").pos);
    blackKnight2->setData(1,"n");

    blackBishop1->setPos(squareMap.value("c8").pos);
    blackBishop1->setData(1,"b");
    blackBishop2->setPos(squareMap.value("f8").pos);
    blackBishop2->setData(1,"b");

    blackPawn1->setPos(squareMap.value("a7").pos);
    blackPawn2->setPos(squareMap.value("b7").pos);
    blackPawn3->setPos(squareMap.value("c7").pos);
    blackPawn4->setPos(squareMap.value("d7").pos);
    blackPawn5->setPos(squareMap.value("e7").pos);
    blackPawn6->setPos(squareMap.value("f7").pos);
    blackPawn7->setPos(squareMap.value("g7").pos);
    blackPawn8->setPos(squareMap.value("h7").pos);
    blackPawn1->setData(1,"p");
    blackPawn2->setData(1,"p");
    blackPawn3->setData(1,"p");
    blackPawn4->setData(1,"p");
    blackPawn5->setData(1,"p");
    blackPawn6->setData(1,"p");
    blackPawn7->setData(1,"p");
    blackPawn8->setData(1,"p");
}

bool ChessBoard::MakeMove(QString move,QGraphicsScene* scene,unsigned int* fiftyMoveRule,bool* isThreeFoldRepetition, QMap<QString,QLabel*> captureMap){

    QString from = move.left(2);
    QString to = move.mid(2,2);
    QString promoteTo = NULL;
    if(move.length() == 5){
        promoteTo = move.right(1);
    }
    QList<QGraphicsItem *> list = scene->items();
    QList<QGraphicsItem *> pieceList;
    QGraphicsItem* fromPiece = NULL;
    QGraphicsItem* toPiece = NULL;
    bool noPawns = true; //for insufficient material
    for(QGraphicsItem* x : list){
        if(x->data(0) == "piece"){
            pieceList.append(x);
            if(x->pos() == squareMap.value(from).pos){
                fromPiece = x;
            }
            if(x->pos() == squareMap.value(to).pos){
                toPiece = x;
            }
            if(x->data(1) == "p" || x->data(1) == "P"){ //for insufficient material
                noPawns = false;
            }
        }
    }
    if(noPawns && pieceList.length() <= 4){
        if(pieceList.length() == 2){
            *isThreeFoldRepetition = true; //only kings left
            return true;
        }
        bool containsRookOrQueen = false;
        unsigned int whitePiecesCount = 0;
        unsigned int blackPiecesCount = 0;
        for(QGraphicsItem* x : pieceList){
            if(x->data(1) == "r" || x->data(1) == "R" || x->data(1) == "q" || x->data(1) == "Q" ){
                containsRookOrQueen = true;
            }
            x->data(1).toString().isUpper() ? whitePiecesCount++ : blackPiecesCount++;
        }
        if(!containsRookOrQueen && whitePiecesCount < 3 && blackPiecesCount < 3){
             *isThreeFoldRepetition = true;
            return true;
        }
    }
    if(toPiece != NULL){
        *fiftyMoveRule = 0;
        showCapturedPiece(toPiece,captureMap);
        delete toPiece;
    }
    if(fromPiece != NULL && (fromPiece->data(1)=="p" || fromPiece->data(1)=="P") && toPiece == NULL && from[0] != to[0]){
        if(fromPiece->data(1)=="P"){
            to[1] = '5';
            for(QGraphicsItem* x : pieceList){
                if(x->pos() == squareMap.value(to).pos){
                    toPiece = x;
                }
            }
            *fiftyMoveRule = 0;
            showCapturedPiece(toPiece,captureMap);
            delete toPiece;
        }else{
            to[1] = '4';
            for(QGraphicsItem* x : pieceList){
                if(x->pos() == squareMap.value(to).pos){
                    toPiece = x;
                }
            }
            *fiftyMoveRule = 0;
            showCapturedPiece(toPiece,captureMap);
            delete toPiece;
        }
    }
    if(move.length() == 5 && fromPiece != NULL && (fromPiece->data(1) == "p" || fromPiece->data(1) == "P")){
        //promotion
        delete fromPiece;
        if(handlePromotion(to,promoteTo,scene)){
            return true;
        }
    }
    if(fromPiece != NULL){
        applyCastlingRule(move,fromPiece,pieceList); //if castling occured
        fromPiece->setPos(squareMap.value(to).pos);
        QCoreApplication::processEvents();
        return true;
    }
    return false;
}

void ChessBoard::applyCastlingRule(QString move, QGraphicsItem* piece, QList<QGraphicsItem*> pieceList){
    if(piece->data(1)=="K" && (move == "e1g1" || move == "e1c1")){
        if(move == "e1g1"){
            for(QGraphicsItem* x : pieceList){
                if(x->data(0) == "piece" && x->pos() == squareMap.value("h1").pos){
                    x->setPos(squareMap.value("f1").pos);
                }
            }
        }else{
            for(QGraphicsItem* x : pieceList){
                if(x->data(0) == "piece" && x->pos() == squareMap.value("a1").pos){
                    x->setPos(squareMap.value("d1").pos);
                }
            }
        }
    }
    if(piece->data(1)=="k" && (move == "e8g8" || move == "e8c8")){
        if(move == "e8g8"){
            for(QGraphicsItem* x : pieceList){
                if(x->data(0) == "piece" && x->pos() == squareMap.value("h8").pos){
                    x->setPos(squareMap.value("f8").pos);
                }
            }
        }else{
            for(QGraphicsItem* x : pieceList){
                if(x->data(0) == "piece" && x->pos() == squareMap.value("a8").pos){
                    x->setPos(squareMap.value("d8").pos);
                }
            }
        }
    }
}

bool ChessBoard::handlePromotion(QString moveTo, QString promoteTo, QGraphicsScene* scene){
    QGraphicsPixmapItem* piece = NULL;
    if(promoteTo == "q"){
        if(moveTo.contains("8")){ //white promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_white_queen.png"));
            piece->setData(1,"Q");
        }else{ //black promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_black_queen.png"));
            piece->setData(1,"q");
        }
    }
    if(promoteTo == "n"){
        if(moveTo.contains("8")){ //white promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_white_knight.png"));
            piece->setData(1,"N");
        }else{ //black promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_black_knight.png"));
            piece->setData(1,"n");
        }
    }
    if(promoteTo == "b"){
        if(moveTo.contains("8")){ //white promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_white_bishop.png"));
            piece->setData(1,"B");
        }else{ //black promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_black_bishop.png"));
            piece->setData(1,"b");
        }
    }
    if(promoteTo == "r"){
        if(moveTo.contains("8")){ //white promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_white_rook.png"));
            piece->setData(1,"R");
        }else{ //black promotes
            piece = scene->addPixmap(QPixmap(":Chess_pieces/Chess_black_rook.png"));
            piece->setData(1,"r");
        }
    }
    if(piece != NULL){
        piece->setScale(0.8);
        piece->setData(0,"piece");
        QCoreApplication::processEvents();
        piece->setPos(squareMap.value(moveTo).pos);
        QCoreApplication::processEvents();
        return true;
    }
    return false;
}

void ChessBoard::showCapturedPiece(QGraphicsItem* toPiece,QMap<QString,QLabel*> captureMap){
    if(toPiece == NULL){
        return;
    }
    if(toPiece->data(1)=="P"){
        if(whitePawnCounter == 0){
            captureMap.value("P")->setPixmap(QPixmap(":Chess_pieces/Chess_white_pawn.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        whitePawnCounter++;
        captureMap.value("Pc")->setText(QString::number(whitePawnCounter));
        return;
    }else if(toPiece->data(1)=="N"){
        if(whiteKnightCounter == 0){
            captureMap.value("N")->setPixmap(QPixmap(":Chess_pieces/Chess_white_knight.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        whiteKnightCounter++;
        captureMap.value("Nc")->setText(QString::number(whiteKnightCounter));
        return;
    }else if(toPiece->data(1)=="B"){
        if(whiteBishopCounter == 0){
            captureMap.value("B")->setPixmap(QPixmap(":Chess_pieces/Chess_white_bishop.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        whiteBishopCounter++;
        captureMap.value("Bc")->setText(QString::number(whiteBishopCounter));
        return;
    }else if(toPiece->data(1)=="R"){
        if(whiteRookCounter == 0){
            captureMap.value("R")->setPixmap(QPixmap(":Chess_pieces/Chess_white_rook.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        whiteRookCounter++;
        captureMap.value("Rc")->setText(QString::number(whiteRookCounter));
        return;
    }else if(toPiece->data(1)=="Q"){
        if(whiteQueenCounter == 0){
            captureMap.value("Q")->setPixmap(QPixmap(":Chess_pieces/Chess_white_queen.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        whiteQueenCounter++;
        captureMap.value("Qc")->setText(QString::number(whiteQueenCounter));
        return;
    }

    if(toPiece->data(1)=="p"){
        if(blackPawnCounter == 0){
            captureMap.value("p")->setPixmap(QPixmap(":Chess_pieces/Chess_black_pawn.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        blackPawnCounter++;
        captureMap.value("pc")->setText(QString::number(blackPawnCounter));
        return;
    }else if(toPiece->data(1)=="n"){
        if(blackKnightCounter == 0){
            captureMap.value("n")->setPixmap(QPixmap(":Chess_pieces/Chess_black_knight.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        blackKnightCounter++;
        captureMap.value("nc")->setText(QString::number(blackKnightCounter));
        return;
    }else if(toPiece->data(1)=="b"){
        if(blackBishopCounter == 0){
            captureMap.value("b")->setPixmap(QPixmap(":Chess_pieces/Chess_black_bishop.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        blackBishopCounter++;
        captureMap.value("bc")->setText(QString::number(blackBishopCounter));
    }else if(toPiece->data(1)=="r"){
        if(blackRookCounter == 0){
            captureMap.value("r")->setPixmap(QPixmap(":Chess_pieces/Chess_black_rook.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        blackRookCounter++;
        captureMap.value("rc")->setText(QString::number(blackRookCounter));
        return;
    }else if(toPiece->data(1)=="q"){
        if(blackQueenCounter == 0){
            captureMap.value("q")->setPixmap(QPixmap(":Chess_pieces/Chess_black_queen.png").scaled(30,30,Qt::KeepAspectRatio));
        }
        blackQueenCounter++;
        captureMap.value("qc")->setText(QString::number(blackQueenCounter));
        return;
    }
}

void ChessBoard::ResetCapturedPieces(QMap<QString,QLabel*> capturedPieces){
    for(QLabel* piece : capturedPieces){
        piece->setText("");
        piece->setPixmap(QPixmap());
    }
    whitePawnCounter = 0;
    whiteKnightCounter = 0;
    whiteBishopCounter = 0;
    whiteRookCounter = 0;
    whiteQueenCounter = 0;
    blackPawnCounter = 0;
    blackKnightCounter = 0;
    blackBishopCounter = 0;
    blackRookCounter = 0;
    blackQueenCounter = 0;
}

void ChessBoard::SetOddsPosition(QGraphicsScene* scene, QString whiteOdds, QString blackOdds,QMap<QString,QLabel*> capturedPieces){

    if(whiteOdds == "e2 Pawn"){
        RemovePiece(scene,"e2",capturedPieces);
    }else if(whiteOdds == "b1 Knight"){
        RemovePiece(scene,"b1",capturedPieces);
    }else if(whiteOdds == "c1 Bishop"){
        RemovePiece(scene,"c1",capturedPieces);
    }else if(whiteOdds == "a1 Rook"){
        RemovePiece(scene,"a1",capturedPieces);
    }else if(whiteOdds == "Queen"){
        RemovePiece(scene,"d1",capturedPieces);
    }

    if(blackOdds == "e7 Pawn"){
        RemovePiece(scene,"e7",capturedPieces);
    }else if(blackOdds == "b8 Knight"){
        RemovePiece(scene,"b8",capturedPieces);
    }else if(blackOdds == "c8 Bishop"){
        RemovePiece(scene,"c8",capturedPieces);
    }else if(blackOdds == "a8 Rook"){
        RemovePiece(scene,"a8",capturedPieces);
    }else if(blackOdds == "Queen"){
        RemovePiece(scene,"d8",capturedPieces);
    }
}

void ChessBoard::RemovePiece(QGraphicsScene* scene,QString pieceSquare,QMap<QString,QLabel*> capturedPieces){
    QList<QGraphicsItem *> list = scene->items();
    for(QGraphicsItem* x:list){
        if(x->data(0) == "piece" && x->pos() == squareMap.value(pieceSquare).pos){
            showCapturedPiece(x,capturedPieces);
            delete x;
            QCoreApplication::processEvents();
        }
    }
}

QString ChessBoard::EditMoveForDisplay(QString move, QGraphicsScene* scene){
    QString from = move.left(2);
    QString promoteTo = NULL;
    if(move.length() == 5){
        promoteTo = move.right(1);
    }
    QList<QGraphicsItem *> list = scene->items();
    QGraphicsItem* fromPiece = NULL;

    for(QGraphicsItem* x : list){
        if(x->data(0) == "piece"){
            if(x->pos() == squareMap.value(from).pos){
                fromPiece = x;
            }
        }
    }
    if(fromPiece == NULL){
        return "error";
    }
    if(fromPiece->data(1) == "P"){
        return QChar(0x2659)+move;
    }else if(fromPiece->data(1) == "N"){
        return QChar(0x2658)+move;
    }else if(fromPiece->data(1) == "B"){
        return QChar(0x2657)+move;
    }else if(fromPiece->data(1) == "R"){
        return QChar(0x2656)+move;
    }else if(fromPiece->data(1) == "Q"){
        return QChar(0x2655)+move;
    }else if(fromPiece->data(1) == "K"){
        return QChar(0x2654)+move;
    }

    if(fromPiece->data(1) == "p"){
        return QChar(0x265F)+move;
    }else if(fromPiece->data(1) == "n"){
        return QChar(0x265E)+move;
    }else if(fromPiece->data(1) == "b"){
        return QChar(0x265D)+move;
    }else if(fromPiece->data(1) == "r"){
        return QChar(0x265C)+move;
    }else if(fromPiece->data(1) == "q"){
        return QChar(0x265B)+move;
    }else if(fromPiece->data(1) == "k"){
        return QChar(0x265A)+move;
    }
    return "error";
}
