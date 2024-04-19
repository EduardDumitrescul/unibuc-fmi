#include <iostream>
#include <vector>
#include <cstring>
#include <deque>
#include <algorithm>

class Player {
    static int idCount;
    const int playerId;

    char* name = nullptr;
    int birthYear{};
    float height{};
    int ovr{};
    char* position = nullptr;
    bool injured{};

public:
    Player();
    Player(const char* name);
    Player(const char* name, int birthYear);
    Player(const char* name, int birthYear, float height, int ovr = 50, const char* position = "unknown", bool injured = false);
    Player(const Player& object);

    int getId();
    const char* getName();
    int getBirthYear() const;
    float getHeight() const;
    int getOvr() const;
    const char* getPosition();
    bool getInjured() const;

    void setName(const char* name);
    void setBirthYear(int birthYear);
    void setHeight(float height);
    void setOvr(int ovr);
    void setPosition(const char* position);
    void setInjured(bool injured);

    std::string toString() const;
    explicit operator std::string();
    operator std::string() const;

    Player& operator=(const Player& object);
    Player operator+(const Player& object);   /// returns a new player with average stats
    Player operator*(const Player& object);   /// return a new player with the best stats of the two
    Player& operator++(); /// increases ovr
    Player operator++(int); /// increases ovr
    Player& operator--(); /// decreases ovr
    Player operator--(int); /// decreases ovr
    /** int operator[](int); **/
    bool operator<(const Player& other) const; /// compares players' ovr
    bool operator<=(const Player& other) const;
    bool operator>(const Player& other) const;
    bool operator>=(const Player& other) const;
    bool operator==(const Player& other);

    friend std::ostream& operator <<(std::ostream& out, const Player &object);
    friend std::istream& operator >>(std::istream& in, Player &object);

    ~Player();
};
int Player::idCount = 1000;
Player::Player() : playerId(++idCount) {
    this->setName("unknown");
    this->setBirthYear(0);
    this->setOvr(0);
    this->setHeight(0);
    this->setPosition("unknown");
    this->setInjured(false);
}
Player::Player(const char *name) : playerId(++idCount) {
    this->setName(name);
    this->setBirthYear(0);
    this->setHeight(0);
    this->setOvr(0);
    this->setPosition("unknown");
    this->setInjured(false);
}
Player::Player(const char *name, int birthYear) : playerId(++idCount) {
    this->setName(name);
    this->setBirthYear(birthYear);
    this->setHeight(0);
    this->setOvr(0);
    this->setPosition("unknown");
    this->setInjured(false);
}
Player::Player(const char *name, int birthYear, float height, int ovr, const char *position, bool injured): playerId(++idCount) {
    this->setName(name);
    this->setBirthYear(birthYear);
    this->setHeight(height);
    this->setOvr(ovr);
    this->setPosition(position);
    this->setInjured(injured);
}
Player::Player(const Player &object) : playerId(++idCount) {
    this->setName(object.name);
    this->setBirthYear(object.birthYear);
    this->setHeight(object.height);
    this->setOvr(object.ovr);
    this->setPosition(object.position);
    this->setInjured(object.injured);
}

void Player::setName(const char *name) {
    if(this->name != nullptr) {
        delete[] this->name;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}
void Player::setBirthYear(int birthYear) {
    this->birthYear = birthYear;
}
void Player::setHeight(float height) {
    this->height = height;
}
void Player::setPosition(const char *position) {
    if(this->position != nullptr) {
        delete[] this->position;
    }
    this->position = new char[strlen(position) + 1];
    strcpy(this->position, position);
}
void Player::setInjured(bool injured) {
    this->injured = injured;
}
void Player::setOvr(int ovr) {
    this->ovr = ovr;
}

int Player::getId() {
    return this->playerId;
}
const char *Player::getName() {
    return this->name;
}
int Player::getBirthYear() const {
    return this->birthYear;
}
float Player::getHeight() const {
    return this->height;
}
const char *Player::getPosition() {
    return this->position;
}
bool Player::getInjured() const {
    return this->injured;
}
int Player::getOvr() const {
    return this->ovr;
}

Player::~Player() {
    if(this->name != nullptr) {
        delete[] this->name;
        this->name = nullptr;
    }
    if(this->position != nullptr) {
        delete[] this->position;
        this->position = nullptr;
    }
}

std::string Player::toString() const {
    std::string output = this->name;
    output += " " + std::to_string(this->ovr);
    output += " " + std::to_string(this->birthYear);
    output += " " + std::to_string(this->height);
    output += " " + (std::string)this->position;
    output += " "  + std::to_string(this->injured);
    return output;
}
Player::operator std::string() {
    return this->toString();
}
Player::operator std::string()const {
    return this->toString();
}

Player &Player::operator=(const Player &object) {
    if(this != &object) {
        this->setName(object.name);
        this->setBirthYear(object.birthYear);
        this->ovr = object.ovr;
        this->setHeight(object.height);
        this->setPosition(object.position);
        this->setInjured(object.injured);
    }
    return *this;
}
Player Player::operator+(const Player& object) {
    Player temp;
    if(this->name < object.name) {
        temp = *this;
    }
    else {
        temp = object;
    }
    temp.ovr = (this->ovr + object.ovr) / 2;
    temp.height = (this->height + object.height) / 2;
    return temp;
}
Player Player::operator*(const Player& object) {
    Player temp;
    if(this->name < object.name) {
        temp = *this;
    }
    else {
        temp = object;
    }
    temp.ovr = std::max(this->ovr, object.ovr);
    temp.height = std::max(this->height, object.height);
    return temp;
}
Player& Player::operator++() {
    this->ovr ++;99
    this->ovr = std::min(this->ovr, 100);
    return *this;
}
Player Player::operator++(int) {
    Player temp(*this);
    this->ovr ++;
    return temp;
}
Player &Player::operator--() {
    this->ovr --;
    this->ovr = std::max(this->ovr, 40);
    return *this;
}
Player Player::operator--(int) {
    Player temp(*this);
    this->ovr --;
    return temp;
}

bool Player::operator<(const Player &other) const {
    return this->getOvr() < other.getOvr();
}
bool Player::operator>(const Player &other) const {
    return this->getOvr() > other.getOvr();
}
bool Player::operator<=(const Player &other) const {
    return this->getOvr() <= other.getOvr();
}
bool Player::operator>=(const Player &other) const {
    return this->getOvr() >= other.getOvr();
}
bool Player::operator==(const Player &other) {
    return this->ovr == other.ovr and this->height == other.height and this->position == other.position;
}

std::ostream &operator<<(std::ostream &out, const Player &object) {
    out << "Player Id: " << object.playerId << '\n';
    out << "Player name: " << object.name << '\n';
    out << "Player's overall rating: " << object.ovr << '\n';
    out << "Player birth year: " << object.birthYear << '\n';
    out << "Player height: " << object.height << '\n';
    out << "Player position: " << object.position << '\n';
    out << "Player injured: " << object.injured << '\n';
    return out;
}
std::istream &operator>>(std::istream &in, Player &object) {
    char playerName[200];
    std::cout << "Insert player name: ";
    in.get();
    in.getline(playerName, 200);
    object.setName(playerName);
    std::cout << "Insert player's ovr: ";
    int ovr;
    in >> ovr;
    object.setOvr(ovr);
    int birthYear;
    std::cout << "Insert player birth year: ";
    in >> birthYear;
    object.setBirthYear(birthYear);
    float height;
    std::cout << "Insert player height: ";
    in >> height;
    object.setHeight(height);
    char position[20];
    std::cout << "Insert player position: ";
    in.get();
    in.getline(position, 20);
    object.setPosition(position);
    bool injured;
    std::cout << "Is player injured? [0/1]: ";
    in >> injured;
    object.setInjured(injured);

    return in;
}

class Team {
    static int idCount;
    const int teamId;

    char* name = nullptr;
    int gamesPlayed{};
    int* gamesRecord = nullptr;
    std::vector <Player*> playerList;

public:
    Team();
    Team(const char* name);
    Team(const char* name, int gamesPlayed, const int* gamesRecord);
    Team(const char* name, int gamesPlayed, const int* gamesRecord, const std::vector <Player*>& players);
    Team(const Team& object);

    bool removePlayer(int playerId);
    void addPlayer(Player* player);
    int teamRating() const;

    int getId();
    const char* getName();
    int getGamesPlayed() const;
    const int* getGamesRecord();
    std::vector <Player*> getPlayers();

    void setName(const char* name);
    void setGamesRecord(int gamesPlayed, const int* gamesRecord);
    void setPlayerList(std::vector <Player*> players);

    std::string toString() const;
    explicit operator std::string();
    operator std::string() const;

    Team& operator=(const Team& object);
    Team operator+(const Team& object);
    int operator*(const Team& object) const;
    bool operator==(const Team& object) const;
    bool operator<(const Team& object) const;
    bool operator>(const Team& object) const;
    bool operator<=(const Team& object) const;
    bool operator>=(const Team& object) const;
    const Player* operator[](int);

    friend std::ostream& operator <<(std::ostream& out, const Team &object);
    friend std::istream& operator >>(std::istream& in, Team &object);

    ~Team();
};

int Team::idCount = 1000;

bool Team::removePlayer(int playerId) {
    for(int i = 0; i < this->playerList.size(); i ++) {
        if(this->playerList[i]->getId() == playerId) {
            this->playerList.erase(this->playerList.begin() + i);
            return true;
        }
    }
    return false;
}
void Team::addPlayer(Player* player) {
    this->playerList.push_back(player);
}
int Team::teamRating() const {
    int sum = 0, count = 0;
    for(auto p: this->playerList) {
        sum += p->getOvr();
        count ++;
    }
    if(count == 0)
        return -1;
    return sum / count;
}

int Team::getId() {
    return this->teamId;
}
const char *Team::getName() {
    return this->name;
}
int Team::getGamesPlayed() const {
    return this->gamesPlayed;
}
const int *Team::getGamesRecord() {
    return this->gamesRecord;
}
std::vector<Player*> Team::getPlayers() {
    return this->playerList;
}

void Team::setName(const char *name) {
    if(this->name != nullptr) {
        delete[] this->name;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}
void Team::setGamesRecord(int gamesPlayed, const int *gamesRecord) {
    this->gamesPlayed = gamesPlayed;
    if(this->gamesRecord != nullptr) {
        delete[] this->gamesRecord;
    }
    this->gamesRecord = new int[this->gamesPlayed];
    for(int i = 0; i < this->gamesPlayed; i ++) {
        this->gamesRecord[i] = gamesRecord[i];
    }
}
void Team::setPlayerList(std::vector<Player*> players) {
    this->playerList = players;
}

Team::Team() : teamId(idCount++) {
    this->setName("unkown");
    this->setGamesRecord(0, {});
    this->setPlayerList({});
}
Team::Team(const char *name) : teamId(idCount++) {
    this->setName(name);
    this->setGamesRecord(0, {});
    this->setPlayerList({});
}
Team::Team(const char *name, int gamesPlayed, const int *gamesRecord) : teamId(idCount++) {
    this->setName(name);
    this->setGamesRecord(gamesPlayed, gamesRecord);
    this->setPlayerList({});
}
Team::Team(const char *name, int gamesPlayed, const int *gamesRecord, const std::vector<Player*>& players) : teamId(idCount++) {
    this->setName(name);
    this->setGamesRecord(gamesPlayed, gamesRecord);
    this->setPlayerList(players);
}
Team::Team(const Team &object) : teamId(idCount++) {
    this->setName(object.name);
    this->setGamesRecord(object.gamesPlayed, object.gamesRecord);
    this->setPlayerList(object.playerList);
}

std::string Team::toString() const {
    if(this == nullptr) {
        return "NULL";
    }
    std::string output = (this->name == nullptr) ? "null" : this->name;
    output += " ; gamesPlayed: " + std::to_string(this->gamesPlayed);
    output += " ; playerCount: " + std::to_string(this->playerList.size());
    return output;
}
Team::operator std::string() {
    return this->toString();
}
Team::operator std::string() const {
    return this->toString();
}

Team &Team::operator=(const Team &object) {
    if(this != &object) {
        this->setName(object.name);
        this->setGamesRecord(object.gamesPlayed, object.gamesRecord);
        this->setPlayerList(object.playerList);
    }
    return *this;
}
Team Team::operator+(const Team& object) {
    Team temp;
    if(this->name <= object.name) {
        temp = *this;
    }
    else {
        temp = object;
    }
    int count = this->gamesPlayed + object.gamesPlayed;
    int games[count];
    for(int i = 0; i < this->gamesPlayed; i ++)
        games[i]  = this->gamesRecord[i];
    for(int i = 0; i < object.gamesPlayed; i ++)
        games[i + this->gamesPlayed]  = object.gamesRecord[i];
    temp.setGamesRecord(count, games);
    std::vector <Player*> v = this->playerList;
    for(auto i : object.playerList) {
        v.push_back(i);
    }
    temp.setPlayerList(v);
    return temp;
}
int Team::operator*(const Team& object) const {
    return std::abs(this->teamRating() - object.teamRating());
}
bool Team::operator==(const Team& object) const {
    return this->teamRating() == object.teamRating();
}
bool Team::operator<(const Team& object) const {
    return this->teamRating() < object.teamRating();
}
bool Team::operator>(const Team& object) const {
    return this->teamRating() > object.teamRating();
}
bool Team::operator<=(const Team& object) const {
    return this->teamRating() <= object.teamRating();
}
bool Team::operator>=(const Team& object) const {
    return this->teamRating() >= object.teamRating();
}
const Player* Team::operator[](int index) {
    if(index >= this->playerList.size()) {
        return nullptr;
    }
    return this->playerList[index];
}

std::ostream &operator<<(std::ostream &out, const Team &object) {
    out << "Team name: " << object.name << '\n';
    out << "Games Played: " << object.gamesPlayed << '\n';
    out << "Games Record: " << (object.gamesPlayed == 0 ? "no games played" : "");
    for(int i = 0; i < object.gamesPlayed; i ++)
        out << object.gamesRecord[i] << ' ';
    out << '\n';
    out << "Number of Players: " << object.playerList.size() << '\n';
    for(auto player: object.playerList) {
        out << player->getName() << ' ';
    }
    out << '\n';
    return out;
}
std::istream &operator>>(std::istream &in, Team &object) {
    std::cout << "Insert team name: ";
    char name[200];
    in.get();
    in.getline(name, 200);
    object.setName(name);

//    std::cout << "Games Played: ";
//    in >> object.gamesPlayed;
//
//    int record[object.gamesPlayed];
//
//    for(int i = 0; i < object.gamesPlayed; i ++) {
//        std::cout << "Record for game " << i + 1 << ": ";
//        in >> record[i];
//    }
//    object.setGamesRecord(object.gamesPlayed, record);

    return in;
}

Team::~Team() {
    if(this->name != nullptr) {
        delete[] this->name;
        this->name = nullptr;
    }
    if(this->gamesRecord != nullptr) {
        delete[] this->gamesRecord;
        this->gamesRecord;
    }
}

class Game {
    static int idCount;
    const int gameId;

    Team* homeTeam{};
    Team* awayTeam{};
    Player* mvp{};

    int homeScore{};
    int awayScore{};

public:
    Game();
    Game(Team* homeTeam, Team* awayTeam);
    Game(Team* homeTeam, Team* awayTeam, int homeScore, int awayScore);
    Game(Team* homeTeam, Team* awayTeam, int homeScore, int awayScore, Player* mvp);
    Game(const Game& object);

    void selectMvp();
    Team* getWinningTeam();

    const Team* getHomeTeam();
    const Team* getAwayTeam();
    int getHomeScore() const;
    int getAwayScore() const;
    const Player* getMvp();
    int getId();

    void setHomeTeam(Team* homeTeam);
    void setAwayTeam(Team* awayTeam);
    void setMvp(Player* mvp);
    void setHomeScore(int homeScore);
    void setAwayScore(int awayScore);

    Game& operator=(const Game& object);

    bool operator==(const Game& object) const; /// checks if the same two teams played
    bool operator<(const Game& object) const; /// compares score difference
    bool operator<=(const Game& object) const;
    bool operator>(const Game& object) const;
    bool operator>=(const Game& object) const;
//    Game operator+(const Game& object) const; /// merges games and averages score
    Game operator*(const Game& object) const; /// merges teams with max scores

    Game& operator++();
    Game operator++(int);
    Team* operator[](int);

    friend std::ostream& operator<<(std::ostream& out, const Game& object);
    friend std::istream& operator>>(std::istream& in, Game& object);

    std::string toString() const;
    explicit operator std::string();
    operator std::string() const;

    ~Game();
};

int Game::idCount = 1000;

Game::Game(): gameId(idCount++) {
    this->setHomeTeam(nullptr);
    this->setAwayTeam(nullptr);
    this->setHomeScore(0);
    this->setAwayScore(0);
    this->setMvp(nullptr);
}
Game::Game(Team *homeTeam, Team *awayTeam): gameId(idCount++) {
    this->setHomeTeam(homeTeam);
    this->setAwayTeam(awayTeam);
    this->setHomeScore(0);
    this->setAwayScore(0);
    this->setMvp(nullptr);
}
Game::Game(Team* homeTeam, Team* awayTeam, int homeScore, int awayScore): gameId(idCount++) {
    this->setHomeTeam(homeTeam);
    this->setAwayTeam(awayTeam);
    this->setHomeScore(homeScore);
    this->setAwayScore(awayScore);
    this->setMvp(nullptr);
}
Game::Game(Team* homeTeam, Team* awayTeam, int homeScore, int awayScore, Player* mvp): gameId(idCount++) {
    this->setHomeTeam(homeTeam);
    this->setAwayTeam(awayTeam);
    this->setHomeScore(homeScore);
    this->setAwayScore(awayScore);
    this->setMvp(mvp);
}
Game::Game(const Game &object): gameId(idCount++) {
    this->setHomeTeam(object.homeTeam);
    this->setAwayTeam(object.awayTeam);
    this->setHomeScore(object.homeScore);
    this->setAwayScore(object.awayScore);
    this->setMvp(object.mvp);
}

void Game::selectMvp() {
    if(this->homeScore > this->awayScore) {
        Player* p = nullptr;
        for(auto it: this->homeTeam->getPlayers()) {
            if(p == nullptr) {
                p = it;
            }
            else if (p < it) {
                p = it;
            }
        }
        this->setMvp(p);
    }
    else {
        Player* p = nullptr;
        for(auto it: this->awayTeam->getPlayers()) {
            if(p == nullptr) {
                p = it;
            }
            else if (p < it) {
                p = it;
            }
        }
        this->setMvp(p);
    }

}
Team* Game::getWinningTeam() {
    if(this->homeScore > this->awayScore) {
        return this->homeTeam;
    }
    return this->awayTeam;
}

const Team* Game::getHomeTeam() {
    return this->homeTeam;
}
const Team* Game::getAwayTeam() {
    return this->awayTeam;
}
int Game::getHomeScore() const {
    return this->homeScore;
}
int Game::getAwayScore() const {
    return this->awayScore;
}
const Player* Game::getMvp() {
    return this->mvp;
}
int Game::getId() {
    return this->gameId;
}

void Game::setHomeTeam(Team* homeTeam) {
    this->homeTeam = homeTeam;
}
void Game::setAwayTeam(Team* awayTeam) {
    this->awayTeam = awayTeam;
}
void Game::setMvp(Player* mvp) {
    this->mvp = mvp;
}
void Game::setHomeScore(int homeScore) {
    this->homeScore = homeScore;
}
void Game::setAwayScore(int awayScore) {
    this->awayScore = awayScore;
}

Game &Game::operator=(const Game &object) {
    if(this != &object) {
        this->setHomeTeam(object.homeTeam);
        this->setAwayTeam(object.awayTeam);
        this->setHomeScore(object.homeScore);
        this->setAwayScore(object.awayScore);
        this->setMvp(object.mvp);
    }
    return *this;
}

bool Game::operator==(const Game& object) const {
    return (this->homeScore > this->awayScore) == (this->homeScore > this->awayScore);
}
bool Game::operator<(const Game& object) const {
    return (this->homeScore - this->awayScore) < (object.homeScore - object.awayScore);
}
bool Game::operator<=(const Game& object) const {
    return (this->homeScore - this->awayScore) <= (object.homeScore - object.awayScore);
}
bool Game::operator>(const Game& object) const {
    return (this->homeScore - this->awayScore) > (object.homeScore - object.awayScore);
}
bool Game::operator>=(const Game& object) const {
    return (this->homeScore - this->awayScore) >= (object.homeScore - object.awayScore);
}
//Game Game::operator+(const Game& object) const {
//    Game temp;
//    if(*this < object) {
//        temp = *this;
//    }
//    else {
//        temp = object;
//    }
//    temp.homeScore = (this->homeScore + object.homeScore) / 2;
//    temp.awayScore = (this->awayScore + object.awayScore) / 2;
//    return temp;
//}
Game Game::operator*(const Game& object) const {
    Game temp;
    if(*this < object) {
        temp = *this;
    }
    else {
        temp = object;
    }
    temp.homeScore = std::max(this->homeScore, object.homeScore);
    temp.awayScore = std::max(this->awayScore, object.awayScore);
    return temp;
}
Game& Game::operator++() {
    this->homeScore++;
    this->awayScore++;
    return *this;
}
Game Game::operator++(int) {
    Game temp(*this);
    this->homeScore++;
    this->awayScore++;
    return temp;
}
Team* Game::operator[](int index) {
    if(index == 0) {
        return this->homeTeam;
    }
    else if (index == 1) {
        return this->awayTeam;
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &out, const Game &object) {
    out << "ID: " << object.gameId << '\n';
    out << "Home Team: " << (object.homeTeam == nullptr ? "null" : object.homeTeam->toString()) << '\n';
    out << "Away Team: " << (object.awayTeam == nullptr ? "null" : object.awayTeam->toString()) << '\n';
    out << "Home Score: " << object.homeScore << '\n';
    out << "Away Score: " << object.awayScore << '\n';
    out << "MVP: " << (object.mvp == nullptr ? "null" : object.mvp->toString()) << '\n';
    return out;
}
std::istream &operator>>(std::istream &in, Game &object) {
    Team *home = new Team();
    Team *away = new Team();
    Player *player = new Player();
    std::cout << "Insert Home Team Information..." << '\n';
    in >> *home;
    std::cout << "Insert Away Team Information..." << '\n';
    in >> *away;
    std::cout << "Insert Home Score: ";
    in >> object.homeScore;
    std::cout << "Insert Away Score: ";
    in >> object.awayScore;
    std::cout << "Insert MVP information..." << '\n';
    in >> *player;
    object.setMvp(player);
    object.setHomeTeam(home);
    object.setAwayTeam(away);

    if(home != nullptr) {
        delete home;
        home = nullptr;
    }
    if(away != nullptr) {
        delete away;
        away = nullptr;
    }
    if(player != nullptr) {
        delete player;
        player = nullptr;
    }

    return in;
}

std::string Game::toString() const {
    std::string output = std::to_string(this->gameId) + ": " + this->homeTeam->toString() + " " + std::to_string(this->homeScore)  + " - " + std::to_string(this->awayScore) + " " + this->awayTeam->toString();
    return output;
}
Game::operator std::string() {
    return this->toString();
}
Game::operator std::string() const {
    return this->toString();
}

Game::~Game() {
    this->homeTeam = nullptr;
    this->awayTeam = nullptr;
    this->mvp = nullptr;
}

class Season {
    static int idCount;
    const int seasonId;

    int year;
    std::vector <Game*> games;
    std::vector <Team*> teams;

public:
    Season();
    Season(int year);
    Season(int year, const std::vector <Game*> &games, const std::vector <Team*> &teams);
    Season(const Season& object);

    void addGame(Game* game);
    void addTeam(Team* team);
    std::vector <std::pair<Team*, int>> getLeaderboard() const;

    int getYear() const;
    const std::vector<Game*> & getGames() const;
    const std::vector<Team*>& getTeams() const;

    void setYear(int year);
    void setGames(const std::vector <Game*> &games);
    void setTeams(const std::vector <Team*> &teams);

    Season &operator =(const Season& object);
    const Game* operator[](int index);
    Season operator + (const Game& game);
    friend Season operator + (const Game& game, const Season& season);
    friend Season operator + (const Game& g1, const Game& g2);
    Season operator + (const Season& season) const; /// merges two seasons
    Season operator * (const Season& season) const; /// creates a new season with the top half teams from each season
    Season& operator++();
    Season operator++(int); /// increases year
    explicit operator int() const;
    bool operator ==(const Season& object) const; ///compares year
    bool operator <(const Season& object) const;
    bool operator <=(const Season& object) const;
    bool operator >(const Season& object) const;
    bool operator >=(const Season& object) const;

    friend std::ostream &operator<<(std::ostream &out, const Season& object);
    friend std::istream &operator>>(std::istream &in, Season& object);

    ~Season();
};
int Season::idCount = 1000;

Season::Season(): seasonId(idCount++)  {
    this->setYear(0);
    this->setGames({});
    this->setTeams({});
}
Season::Season(int year): seasonId(idCount++) {
    this->setYear(year);
    this->setGames({});

    this->setTeams({});
}
Season::Season(int year, const std::vector<Game*> &games, const std::vector <Team*> &teams): seasonId(idCount++)  {
    this->setYear(year);
    this->setGames(games);
    this->setTeams(teams);
}
Season::Season(const Season &object): seasonId(idCount++)  {
    this->setYear(object.year);
    this->setGames(object.games);
    this->setTeams(object.teams);
}

void Season::addGame(Game* game) {
    this->games.emplace_back(game);
}
void Season::addTeam(Team* const team) {
    this->teams.push_back(team);
}
std::vector <std::pair<Team*, int>> Season::getLeaderboard() const {
    std::vector <std::pair <Team*, int>> v;
    for(auto team: this->teams) {
        int wins = 0;
        if(team == nullptr) {
            continue;
        }
        for(auto game: this->games) {
            if(team->getId() == game->getWinningTeam()->getId()) {
                wins ++;
            }
        }
        v.emplace_back(team, wins);
    }
    std::sort(v.begin(), v.end(), [](auto a, auto b){ return a.second > b.second;});
    return v;
}

int Season::getYear() const {
    return this->year;
}
const std::vector<Game*> & Season::getGames() const {
    return this->games;
}
const std::vector<Team*>& Season::getTeams() const {
    return this->teams;
}

void Season::setYear(int year) {
    this->year = year;
}
void Season::setGames(const std::vector<Game*> &games) {
    this->games = games;
}
void Season::setTeams(const std::vector <Team*> &teams) {
    this->teams = teams;
}

Season &Season::operator=(const Season &object) {
    if(this != &object) {
        this->setYear(object.year);
        this->setGames(object.games);
        this->setTeams(object.teams);
    }
    return *this;
}
const Game* Season::operator[](int index) {
    if(index >= this->games.size())
        return nullptr;
    return this->games[index];
}

Season Season::operator + (const Game& game) {
    Season temp(*this);
    temp.addGame(const_cast<Game *>(&game));
    return temp;
}
Season operator + (const Game& game, const Season& season) {
    Season temp(season);
    temp.addGame(const_cast<Game *>(&game));
    return temp;
}
Season operator + (const Game& g1, const Game& g2) {
    Season temp;
    temp.addGame(const_cast<Game *>(&g1));
    temp.addGame(const_cast<Game *>(&g2));
    return temp;
}
Season Season::operator + (const Season& season) const {
    Season temp(*this);
    for(auto g: season.games) {
        temp.addGame(g);
    }
    return temp;
}
Season Season::operator * (const Season& season) const {
    auto l1 = this->getLeaderboard();
    auto l2 = this->getLeaderboard();
    Season temp;
    for(int i = 0; i < l1.size()/2; i++) {
        temp.addTeam(l1[i].first);
    }
    for(int i = 0; i < l2.size()/2; i++) {
        temp.addTeam(l2[i].first);
    }
    return temp;
}
Season& Season::operator++() {
    this->year ++;
    return *this;
}
Season Season::operator++(int) {
    Season temp(*this);
    this->year ++;
    return temp;
}
Season::operator int() const {
    return this->year;
}
bool Season::operator ==(const Season& object) const {
    return this->year == object.year;
}
bool Season::operator <(const Season& object) const {
    return this->year < object.year;
}
bool Season::operator <=(const Season& object) const {
    return this->year <= object.year;
}
bool Season::operator >(const Season& object) const {
    return this->year > object.year;
}
bool Season::operator >=(const Season& object) const{
    return this->year >= object.year;
}

std::ostream &operator<<(std::ostream &out, const Season &object) {
    out << "Season Year: " << object.year << '\n';
    out << "Season Games Count: " << object.games.size() << '\n';
    for(auto game: object.games) {
        out << game->toString() << '\n';
    }
    out << "Season Teams count:" << object.teams.size() << '\n';
    for(auto team: object.teams) {
        out << team->toString() << '\n';
    }
    return out;
}
std::istream &operator>>(std::istream &in, Season &object) {
    std::cout << "Insert Season Year: ";
    in >> object.year;
//    std::cout << "Insert Games Count: ";
//    int gamesCount;
//    in >> gamesCount;
//    while(gamesCount--) {
//        Game game;
//        in >> game;
//        object.addGame(game);
//    }
    return in;
}



Season::~Season() = default;

void testPlayerClass() {
    Player a;
    Player b("player b");
    Player c("player c", 2003);
    Player d("player d", 2003, 1.97, 95, "PG", true);
    Player e(d);
    e.setOvr(40);
    Player f = e;

    e.setName("player e");
    f.setName("player f");

    std::cout << a.toString() << '\n';
    std::cout << b.toString() << '\n';
    std::cout << c.toString() << '\n';
    std::cout << d.toString() << '\n';
    std::cout << e.toString() << '\n';
    std::cout << f.toString() << '\n';

    std::cout << (d + e).toString() << '\n';
    std::cout << (e + d).toString() << '\n';
    std::cout << (d * e).toString() << '\n';
    std::cout << (e * d).toString() << '\n';

    std::cout << e++.toString() << '\n';
    std::cout << (++e).toString() << '\n';

    Player player;
    std::cin >> player;
    std::cout << player << '\n';
}
void testTeamClass() {
    Team a;
    int record[2];
    record[0] = -25, record[1] = 36;
    Team b("team b");
    Player player("player d", 2003, 1.97, 95, "PG", true);
    Team c("team c", 2, record, {&player});

    Team d(c);
    Team e = d;

    d.setName("team d");
    e.setName("teams e");

    std::cout << a.toString() << '\n';
    std::cout << b.toString() << '\n';
    std::cout << c.toString() << '\n';
    std::cout << d.toString() << '\n';
    std::cout << e.toString() << '\n';

    std::cout << (d + e).toString() << '\n';
    std::cout << (e + d).toString() << '\n';
    std::cout << (d * e) << '\n';
    std::cout << (e * d) << '\n';

    Team team;
    std::cin >> team;
    std::cout << team << '\n';
}
void testGameClass() {
    Game a;
    Team home("home");
    Team away("away");
    Player mvp("mvp");

    Game b(&home, &away);
    Game c(&home, &away, 123, 321);
    Game d(&home, &away, 123, 321, &mvp);
    Game e(d);
    Game f = e;

    e.setAwayTeam(&home);
    e.setHomeTeam(&away);

    std::cout << a << b << c << d << e << f;

    std::cout << (c * d).toString() << '\n';
    std::cout << (d * c).toString() << '\n';
    std::cout << (++d).toString() << '\n';
    std::cout << (d++).toString() << '\n';
    std::cout << (d++).toString() << '\n';


    std::cin >> a;
    std::cout << a;
}

void testSeasonClass() {
    Season a;
    Season b(2003);
    Season c(2023, {}, {});
    Season d(c);
    d.setYear(201241);

    std::cout << a << b << c << d;

    Season s;
    std::cin >> s;
    std::cout << s;
}

void testSeasonGameAddition() {
    Game g1;
    Game g2;
    Season s1(2003);
    Season s2(102);

    std::cout << s1 + g1 << '\n';
    std::cout << g1 + s1 << '\n';
    std::cout << s1 + s2 << '\n';
    std::cout << g1 + g2 << '\n';


}

class Demo {
    std::deque <Player> players;
    std::deque <Team> teams;
    std::deque <Game> games;
    Season season;
    bool seasonPlayed = false;
    bool defaultDataLoaded = false;

public:
    void run();
    void seeAllPlayers();
    void addPlayer();
    int addPlayer(const Player &player);
    void editPLayer();
    void seeAllTeams();
    void addTeam();
    void addTeam(const Team &team);
    void editTeam();

    int addGame(const Game& game);
    Game* getGame(int id);

    void editSeason();
    void seeSeasonLeaderboard();
    void playSeason();
    void loadDefaultData();

    Player* getPlayer(int id);
    bool removePlayer(int id);
    Team* getTeam(int id);
    bool removeTeam(int id);
};

void Demo::run() {
    bool running = true;
    while(running) {
        std::cout << "[0] -> exit\n";

        std::cout << "[11] -> see all players\n";
        std::cout << "[12] -> add player\n";
        std::cout << "[13] -> edit player\n";

        std::cout << "[21] -> see all teams\n";
        std::cout << "[22] -> add team\n";
        std::cout << "[23] -> edit team\n";

        std::cout << "[31] -> season\n";

        std::cout << "[99] -> load default data\n";

        int command;
        std::cin >> command;
        switch (command) {
            case 0: {
                running = false;
                break;
            }
            case 11: {
                this->seeAllPlayers();
                break;
            }
            case 12: {
                this->addPlayer();
                break;
            }
            case 13: {
                this->editPLayer();
                break;
            }
            case 21: {
                this->seeAllTeams();
                break;
            }
            case 22: {
                this->addTeam();
                break;
            }
            case 23: {
                this->editTeam();
                break;
            }
            case 31: {
                this->editSeason();
                break;
            }
            case 99: {
                this->loadDefaultData();
                break;
            }
            default: {
                std::cout << "UNRECOGNIZED COMMAND\n";
                break;
            }
        }
        std::cout << "----------------------------|\n";
    }
}
void Demo::loadDefaultData() {
    if(this->defaultDataLoaded) {
        return;
    }
    this->defaultDataLoaded = true;
    srand(time(nullptr));
    for(int i = 0; i < 4; i ++) {
        std::string name = "Team #" + std::to_string(i);
        this->addTeam(Team(name.c_str()));
    }
    for(auto &team: this->teams) {
        this->season.addTeam(this->getTeam(team.getId()));
    }
    for(int i = 0; i < 20; i ++) {
        std::string name = "Player #" + std::to_string(i);
        Player player(name.c_str(), 1980 + rand() % 30, (180 + rand() % 40) / 100.0 ,rand() % 60 + 40, "pos", false);
        int id = this->addPlayer(player);
        this->teams[i/5].addPlayer(this->getPlayer(id));
    }
}

Player* Demo::getPlayer(int id) {
    Player* player = nullptr;
    for(int i = 0; i < this->players.size(); i ++) {
        if(this->players[i].getId() == id) {
            player = &this->players[i];
            break;
        }
    }
    return player;
}
bool Demo::removePlayer(int id) {
    for(int i = 0; i < this->players.size(); i ++) {
        if(this->players[i].getId() == id) {
            this->players.erase(this->players.begin() + i);
            return true;
        }
    }
    return false;
}
Team* Demo::getTeam(int id) {
    Team* team = nullptr;
    for(auto & i : this->teams) {
        if(i.getId() == id) {
            team = &i;
            break;
        }
    }
    return team;
}
bool Demo::removeTeam(int id) {
    for(int i = 0; i < this->teams.size(); i ++) {
        if(this->teams[i].getId() == id) {
            this->teams.erase(this->teams.begin() + i);
            return true;
        }
    }
    return false;
}

void Demo::seeAllPlayers() {
    for(const auto& player: this->players) {
        std::cout << player;
    }
}
void Demo::addPlayer() {
    Player player;
    std::cin >> player;
    this->players.push_back(player);
    std::cout << "Player added successfully!\n";
}
int Demo::addPlayer(const Player &player) {
    this->players.push_back(player);
    return this->players.back().getId();

}
void Demo::editPLayer() {
    std::cout << "Insert the ID of the player: ";
    int id;
    std::cin >> id;
    Player* player = this->getPlayer(id);
    if(player == nullptr) {
        std::cout << "Invalid ID!\n";
        return;
    }

    bool running = true;
    while(running) {
        std::cout << "[0] -> back\n";
        std::cout << "[1] -> change name\n";
        std::cout << "[2] -> change ovr\n";
        std::cout << "[3] -> change position\n";
        std::cout << "[4] -> change injured status\n";
        std::cout << "[5] -> change birth year\n";
        std::cout << "[6] -> change height\n";
        std::cout << "[7] -> delete\n";

        int command;
        std::cin >> command;
        switch(command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                char name[200];
                std::cout << "Insert name (char*, max 200 characters): ";
                std::cin.get();
                std::cin.getline(name, 200);
                player->setName(name);
                break;
            }
            case 2: {
                int ovr;
                std::cout << "Insert ovr (int 40-100): ";
                std::cin >> ovr;
                player->setOvr(ovr);
                break;
            }
            case 3: {
                char position[20];
                std::cout << "Insert position (char*, max 20 characters): ";
                std::cin.get();
                std::cin.getline(position, 20);
                player->setPosition(position);
                break;
            }
            case 4: {
                bool injured;
                std::cout << "Insert injured status (bool): ";
                std::cin >> injured;
                player->setInjured(injured);
                break;
            }
            case 5: {
                int birthYear;
                std::cout << "Insert birth year (int): ";
                std::cin >> birthYear;
                player->setBirthYear(birthYear);
                break;
            }
            case 6: {
                float height;
                std::cout << "Insert height(float): ";
                std::cin >> height;
                player->setHeight(height);
                break;
            }
            case 7: {
                this->removePlayer(id);
                running = false;
                break;
            }
            default: {
                std::cout << "UNRECOGNIZED COMMAND!\n";
                break;
            }
        }
    }
}

void Demo::seeAllTeams() {
    for(const auto& team: this->teams) {
        std::cout << team;
    }
}
void Demo::addTeam() {
    Team team;
    std::cin >> team;
    this->teams.push_back(team);
    std::cout << "Team added successfully!\n";
}
void Demo::addTeam(const Team& team) {
    this->teams.push_back(team);
}
void Demo::editTeam() {
    std::cout << "Insert the ID of the team: ";
    int id;
    std::cin >> id;
    Team* team = Demo::getTeam(id);
    if(team == nullptr) {
        std::cout << "Invalid ID!\n";
        return;
    }

    bool running = true;
    while(running) {
        std::cout << "[0] -> back\n";
        std::cout << "[1] -> change name\n";
        std::cout << "[2] -> add player\n";
        std::cout << "[3] -> remove player\n";
        std::cout << "[4] -> delete\n";

        int command;
        std::cin >> command;
        switch(command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                char name[200];
                std::cout << "Insert name (char*, max 200 characters): ";
                std::cin >> name;
                team->setName(name);
                break;
            }
            case 2: {
                int playerId;
                std::cout << "Insert player ID: ";
                std::cin >> playerId;
                Player* player = Demo::getPlayer(playerId);
                if(player == nullptr) {
                    std::cout << "Invalid ID!\n";
                }
                else {
                    team->addPlayer(player);
                    std::cout << "Player added successfully!\n";
                }
                break;
            }
            case 3: {
                int playerId;
                std::cout << "Insert player ID to remove from team: ";
                std::cin >> playerId;
                    team->removePlayer(playerId);
                break;
            }
            case 4: {
                this->removeTeam(id);
                break;
            }
            default: {
                std::cout << "UNRECOGNIZED COMMAND!\n";
                break;
            }
        }
    }
}

int Demo::addGame(const Game& game) {
    this->games.push_back(game);
    return this->games.back().getId();
}
Game* Demo::getGame(int id) {
    for(auto & game : this->games){
        if(game.getId() == id)
            return &game;
    }
}

void Demo::editSeason() {
    bool running = true;
    while(running) {
        int command;
        std::cout << "[0] -> back\n";
        std::cout << "[1] -> addTeam\n";
        std::cout << "[2] -> play Season\n";
        std::cout << "[3] -> see leaderboard\n";

        std::cin >> command;
        switch (command) {
            case 0: {
                running = false;
                break;
            }
            case 1: {
                std::cout << "Insert Team ID:\n";
                int id;
                std::cin >> id;
                if(this->getTeam(id) == nullptr) {
                    std::cout << "Invalid ID\n";
                    break;
                }
                this->season.addTeam(this->getTeam(id));
                break;
            }
            case 2: {
                if(this->seasonPlayed) {
                    std::cout << "Season has already been simulated";
                    break;
                }
                this->seasonPlayed = true;
                for(int i = 0; i < this->teams.size(); i ++) {
                    for(int j = i+1; j < this->teams.size(); j ++) {
                        int r1 = rand() % 40 - 20;
                        int r2 = rand() % 40 - 20;
                        Game game(&this->teams[i], &this->teams[j], this->teams[i].teamRating() + r1, this->teams[j].teamRating() + r2,
                                  nullptr);
                        game.selectMvp();
                        int id = this->addGame(game);
                        this->season.addGame(this->getGame(id));
                    }
                }

                for(int i = 0; i < this->teams.size(); i ++) {
                    for(int j = i+1; j < this->teams.size(); j ++) {
                        int r1 = rand() % 40 - 20;
                        int r2 = rand() % 40 - 20;
                        Game game(&this->teams[j], &this->teams[i], this->teams[j].teamRating() + r1, this->teams[i].teamRating() + r2,
                                  nullptr);
                        game.selectMvp();
                        int id = this->addGame(game);
                        this->season.addGame(this->getGame(id));
                    }
                }
                break;
            }
            case 3: {
                auto leaderboard = this->season.getLeaderboard();
                for(auto it: leaderboard) {
                    std::cout << *it.first << "-> wins: " << it.second << '\n';
                }
                break;
            }
            default: {
                std::cout << "Invalid Command!\n";
                break;
            }
        }
    }
}
void Demo::seeSeasonLeaderboard() {

}
void Demo::playSeason() {

}

int main() {
    Demo demo;
    demo.run();

    return 0;
}
