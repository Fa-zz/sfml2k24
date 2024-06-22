// #include "Command.hpp"
// class moveRight : public Command {
// private:
//     sf::Keyboard::Key commandsKey_;
// public:
//     void execute(Character& actor) override {
//         actor.addDir(sf::Vector2f{1.0f,0.f});
//     }
//     void setCommandsKey(sf::Keyboard::Key key) override { commandsKey_ = key; }
//     sf::Keyboard::Key getCommandsKey() override { return commandsKey_; }
// };

// class moveLeft : public Command {
// private:
//     sf::Keyboard::Key commandsKey_;
// public:
//     void execute(Character& actor) override {
//         actor.addDir(sf::Vector2f{-1.f,0.f});
//     }
//     void setCommandsKey(sf::Keyboard::Key key) override { commandsKey_ = key; }
//     sf::Keyboard::Key getCommandsKey() override { return commandsKey_; }
// };

// class moveUp : public Command {
// private:
//     sf::Keyboard::Key commandsKey_;
// public:
//     void execute(Character& actor) override {
//         actor.addDir(sf::Vector2f{0.0f,-1.f});
//     }
//     void setCommandsKey(sf::Keyboard::Key key) override { commandsKey_ = key; }
//     sf::Keyboard::Key getCommandsKey() override { return commandsKey_; }
// };

// class moveDown : public Command {
// private:
//     sf::Keyboard::Key commandsKey_;
// public:
//     void execute(Character& actor) override {
//         actor.addDir(sf::Vector2f{0.0f,1.f});
//     }
//     void setCommandsKey(sf::Keyboard::Key key) override { commandsKey_ = key; }
//     sf::Keyboard::Key getCommandsKey() override { return commandsKey_; }
// };