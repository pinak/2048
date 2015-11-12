#include "gamemodel.h"

GameModel::GameModel(QObject* parent)
    : QAbstractListModel(parent)
{
    connect(&m_game, &Game::boardChanged, this, &GameModel::ondataChanged);
}

int GameModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return boardSize * boardSize;
}

QVariant GameModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() > boardSize * boardSize) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        int i = index.row() / boardSize;
        int j = index.row() % boardSize;
        QString val = QString::number(m_game.get(i, j));
        return val;
    }
    return QVariant();
}

void GameModel::ondataChanged()
{
    emit dataChanged(createIndex(0,0), createIndex( (rowCount() - 1), 0));
    emit scoreChanged();
}

void GameModel::moveUp()
{
    m_game.play(Game::up);
}

void GameModel::moveDown()
{
    m_game.play(Game::down);
}

void GameModel::moveLeft()
{
    m_game.play(Game::left);
}

void GameModel::moveRight()
{
    m_game.play(Game::right);
}



