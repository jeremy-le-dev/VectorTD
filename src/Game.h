//
// Created by Jérémy Froment on 24/10/2016.
//

#ifndef VECTORTD_GAME_H
#define VECTORTD_GAME_H

#include <stdio.h>
#include <libconfig/libconfig.h>
#include "Button.h"

class TowerAbstract;
class Case;

class Game {
public:
    int width, height, credits, points, level, vie, choosePath, priceTowerR, priceTowerG, priceTowerB, nbMyPath, ticks;
    float nbCases, gameSize, pas, leftPos, beginXPath, beginYPath, endXPath, endYPath;
    bool waitStart, inPause, started, gameover, mypath;
    char selectedTower;
    TowerAbstract *currentTower;
    Case *oldCaseMyPath, *currentCaseMyPath;
    Button *btnStartGame, *btnResumePause, *btnUpgrade, *btnSale, *btnExit, *btnRestart, *btnRestartGO, *btnValidPath;

    Game(int width_, int height_) :
            width(width_),
            height(height_),
            credits(200),
            points(0),
            vie(20),
            level(1),
            nbCases(12),
            gameSize(1.5f),
            leftPos(-0.95f),
            pas(gameSize / nbCases),
            waitStart(true),
            started(false),
            inPause(false),
            selectedTower('R'),
            currentTower(NULL),
            beginXPath(0.0f),
            beginYPath(0.0f),
            endXPath(0.0f),
            endYPath(0.0f),
            choosePath(1),
            priceTowerR(100),
            priceTowerG(75),
            priceTowerB(50),
            mypath(false),
            nbMyPath(0),
            oldCaseMyPath(NULL),
            currentCaseMyPath(NULL),
            ticks(0),
            gameover(false) {

        config_t cfg;
        config_init(&cfg);

        if (config_read_file(&cfg, "../src/config.cfg")) {
            // On récupère le nombre de cases dans la config
            int _nbCases;
            if (config_lookup_int(&cfg, "taille_tableau", &_nbCases)) {
                if (_nbCases >= 4) {
                    nbCases = _nbCases;
                    pas = gameSize / nbCases;
                }
            }
            // On récupère la vie dans la config
            int _vie;
            if (config_lookup_int(&cfg, "vie", &_vie)) {
                if (_vie > 0) {
                    vie = _vie;
                }
            }
            // On récupère les crédits dans la config
            int _credits;
            if (config_lookup_int(&cfg, "credits", &_credits)) {
                if (_credits >= 50) {
                    credits = _credits;
                }
            }
            // On récupère le prix de la tourelle R dans la config
            int _priceTowerR;
            if (config_lookup_int(&cfg, "price_tower_R", &_priceTowerR)) {
                if (_priceTowerR >= 1) {
                    priceTowerR = _priceTowerR;
                }
            }
            // On récupère le prix de la tourelle G dans la config
            int _priceTowerG;
            if (config_lookup_int(&cfg, "price_tower_G", &_priceTowerG)) {
                if (_priceTowerG >= 1) {
                    priceTowerG = _priceTowerG;
                }
            }
            // On récupère le prix de la tourelle B dans la config
            int _priceTowerB;
            if (config_lookup_int(&cfg, "price_tower_B", &_priceTowerB)) {
                if (_priceTowerB >= 1) {
                    priceTowerB = _priceTowerB;
                }
            }
        }

        config_destroy(&cfg);

        btnStartGame    = new Button(new char[11] {'S', 'T', 'A', 'R', 'T', ' ', 'G', 'A', 'M', 'E', '\0'}, -0.2f, -0.5f, 0.5f, 0.1f, 0.106f, 0.282f, 0.282f);
        btnUpgrade      = new Button(new char[2] {}, 0.6f, -0.2f, 0.35f, 0.1f, 0.106f, 0.282f, 0.282f, 1.0f, 0.03f);
        btnSale         = new Button(new char[2] {}, 0.6f, -0.35f, 0.35f, 0.1f, 0.106f, 0.282f, 0.282f);
        btnResumePause  = new Button(new char[2] {}, 0.6f, -0.7f, 0.35f, 0.1f, 0.106f, 0.282f, 0.282f, 1.0f, 0.1f);
        btnValidPath    = new Button(new char[12] {'C', 'R', 'E', 'A', 'T', 'E', ' ', 'P', 'A', 'T', 'H', '\0'}, 0.6f, -0.7f, 0.35f, 0.1f, 0.961f, 0.329f, 0.518f, 1.0f, 0.02f);
        btnRestart      = new Button(new char[8] {'R', 'E', 'S', 'T', 'A', 'R', 'T', '\0' }, 0.6f, -0.83f, 0.35f, 0.1f, 0.961f, 0.329f, 0.518f);
        btnExit         = new Button(new char[5] {'E', 'X', 'I', 'T', '\0' }, 0.6f, -0.96f, 0.35f, 0.1f, 0.961f, 0.329f, 0.518f, 1.0f, 0.11f);
        btnRestartGO    = new Button(new char[9] {'N', 'E', 'W', ' ', 'G', 'A', 'M', 'E', '\0' }, -0.2f, -0.1f, 0.35f, 0.1f, 0.961f, 0.329f, 0.518f, 1.0f, 0.05f);
    };

    ~Game();

    void draw();

    bool touchResumePause(float x, float y);

    bool touchValidPath(float x, float y);

    void touchTower(float x, float y);

    void touchUpgrade(float x, float y);

    void touchSale(float x, float y);

    bool touchStartGame(float x, float y);

    int towerPrice(char tower);

    int isPath(int path, int coordX, int coordY);

    void touchPath(float x, float y);

    bool touchExit(float x_, float y_);

    bool touchRestart(float x_, float y_);

    bool touchRestartGO(float x_, float y_);
};


#endif //VECTORTD_GAME_H
