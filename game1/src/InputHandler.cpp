// #include "InputHandler.hpp"

// InputHandler::~InputHandler() {
//     for (Command* command : commands_) {
//         delete command;
//     }
// }

// InputHandler::InputHandler() {
//     freeRoamBind();
// }

// Command* InputHandler::handleInput() {
//     if (sf::Keyboard::isKeyPressed(right_->getCommandsKey())) {
//         return right_;
//     }
//     if (sf::Keyboard::isKeyPressed(left_->getCommandsKey())) {
//         return left_;
//     }
//     if (sf::Keyboard::isKeyPressed(up_->getCommandsKey())) {
//         return up_;
//     }
//     if (sf::Keyboard::isKeyPressed(down_->getCommandsKey())) {
//         return down_;
//     }
//     return nullptr;
// }

// // Command* InputHandler::specifiedOutput(int code) {
// //     if (code == 0){
// //         return right_;
// //     }
// //     if (code == 1) {
// //         return left_;
// //     }
// //     if (code == 2) {
// //         return up_;
// //     }
// //     if (code == 3) {
// //         return down_;
// //     }
// //     return nullptr;
// // }

// void InputHandler::freeRoamBind() {
//     right_ = new moveRight();
//     right_->setCommandsKey(sf::Keyboard::Right);
//     left_ = new moveLeft();
//     left_->setCommandsKey(sf::Keyboard::Left);
//     up_ = new moveUp();
//     up_->setCommandsKey(sf::Keyboard::Up);
//     down_ = new moveDown();
//     down_->setCommandsKey(sf::Keyboard::Down);

//     commands_.push_back(right_);
//     commands_.push_back(left_);
//     commands_.push_back(up_);
//     commands_.push_back(down_);
// }