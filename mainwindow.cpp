#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stopButton->setEnabled(false);
    ui->historyButton->setEnabled(std::filesystem::exists(historyFile.toStdString()));
    ui->GameResultLabel->hide();
    ui->AlghoritmNamesLabel->hide();
    scene = ChessBoard::generateBoard();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    currentGame->isStopped = true;
    QCoreApplication::exit();
}

void MainWindow::on_stopButton_clicked()
{
    QCoreApplication::processEvents();
    currentGame->isStopped = true;
}

void MainWindow::on_newButton_clicked()
{
    changeWidgetIndex(1);
}

void MainWindow::on_startPlayingButton_clicked()
{
    ui->stopButton->setEnabled(true);
    ui->newButton->setEnabled(false);
    showAlghoritmNames();
    changeWidgetIndex(0);
    QMap<QString,QLabel*> captureList{
        {"P",ui->whitePawn},{"Pc",ui->whitePawnCount},
        {"N",ui->whiteKnight},{"Nc",ui->whiteKnightCount},
        {"B",ui->whiteBishop},{"Bc",ui->whiteBishopCount},
        {"R",ui->whiteRook},{"Rc",ui->whiteRookCount},
        {"Q",ui->whiteQueen},{"Qc",ui->whiteQueenCount},
        {"p",ui->blackPawn},{"pc",ui->blackPawnCount},
        {"n",ui->blackKnight},{"nc",ui->blackKnightCount},
        {"b",ui->blackBishop},{"bc",ui->blackBishopCount},
        {"r",ui->blackRook},{"rc",ui->blackRookCount},
        {"q",ui->blackQueen},{"qc",ui->blackQueenCount}
    };

    GameInstance* game = new GameInstance(ui->white->currentText(),
                                         ui->black->currentText(),
                                         ui->whiteOdds->currentText(),
                                         ui->blackOdds->currentText(),
                                         ui->TimeForMoveSpinBox->value(),
                                         ui->moveBox,
                                         scene,captureList);

    this->currentGame = game;
    GameResult result;
    int gamesLeft =  ui->NumberOfGamesSpinBox->value();
    for (int i = 0;i < ui->NumberOfGamesSpinBox->value();i++) {
        result = game->Start();
        switch(result) {
          case stopped:
            break;
          case draw:
            announceGameResult("Draw");
            break;
          case whiteWins:
            announceGameResult("White " + ui->white->currentText() + " wins !");
            break;
          case blackWins:
            announceGameResult("Black "+ ui->black->currentText() + " wins !");
            break;
        }
        if(result != stopped){
            utils::WriteGameHistory(game->white,game->black,game->whiteOdds,game->blackOdds,game->timePerMove,game->allMoves,result);
        }
        gamesLeft--;
    }

    Engine::Quit(game->processList);
    ui->historyButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->newButton->setEnabled(true);
}

void MainWindow::on_historyButton_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+historyFile));
}

void MainWindow::changeWidgetIndex(int index){
    ui->stackedWidget->setCurrentIndex(index);
    QCoreApplication::processEvents();
}

void MainWindow::announceGameResult(QString result){
    ui->GameResultLabel->setText(result);
    ui->GameResultLabel->setStyleSheet("font: 20pt;");
    ui->GameResultLabel->show();
    Engine::Delay(3);
    ui->GameResultLabel->setText("");
}

void MainWindow::showAlghoritmNames(){
    ui->AlghoritmNamesLabel->setText(ui->white->currentText()+" vs "+ui->black->currentText());
    ui->AlghoritmNamesLabel->setStyleSheet("font: 20pt;");
    ui->AlghoritmNamesLabel->show();
}

void MainWindow::on_backButton_clicked()
{
    changeWidgetIndex(0);
}

