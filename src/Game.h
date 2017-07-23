#ifndef __GAME_H
#define __GAME_H

class Engine;

class Game {
  public:
    virtual void init() = 0;
    virtual void render() = 0;
    virtual void step() = 0;
    void setEngine(Engine *engine);
  protected:
    Engine *engine;
};

#endif
