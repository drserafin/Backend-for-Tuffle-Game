#pragma once

#include <string>
#include <vector>

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
 public:
  GameState(const std::string& answer) { answer_ = answer; }

  std::string GetAnswer() const { return answer_; }

  std::vector<std::string> GetBoardColors() const { return board_colors_; }
  void SetBoardColors(std::vector<std::string> board) { board_colors_ = board; }

  std::vector<std::string> GetGuessedWords() const { return guessed_answers_; }
  void SetGuessedWords(std::vector<std::string> words) {
    guessed_answers_ = words;
  }

  std::string GetStatus() const { return status_; }
  void SetStatus(std::string status) { status_ = status; }

  std::string GetErrorMessage() { return error_message_; }
  void SetErrorMessages(std::string error) { error_message_ = error; }

 private:
  std::string answer_;
  std::vector<std::string> board_colors_;
  std::vector<std::string> guessed_answers_;
  std::string status_;
  std::string error_message_;
};

#endif  // GAMESTATE_H
