#pragma once

class baseGame {
protected:

    float accumulatedFixedTime;
    //Called internally when game -specific initilizatio occurs
    void virtual onInit() { }

    // Called internally when game-specifc tick occurs
    void virtual onTick() { }
    void virtual onTickFixed() {}
    // Called internally when game-specifc drawing occurs
    void virtual onDraw() const {}

    // Called internally when game-specifc clean-up occurs
    void virtual onExit() { }
public:
    float targetFixedStep;
    float maxFixedStep;
    // Trivial constructor
    baseGame();

    // Initializes the game window
    void init();

    // Poll for input, update timers, etc.
    void tick();

    //tick objects working on a fixed tick rate
    void tickFixed();
    // Draw the current world state
    void draw() const;

    // Close the game and shutdown
    void exit();

    // Returns true if the game is trying to shut down
    bool shouldClose() const;
   //returns true when enough time has passed for a fixed tick to oocur
    bool shouldTickFixed() const;
};
