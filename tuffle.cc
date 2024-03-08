#include "tuffle.h"

// ========================= YOUR CODE HERE =========================
// This implementation file is where you should implement the member
// functions declared in the header, only if you didn't implement
// them inline in the header.
//
// Remember to specify the name of the class with :: in this format:
//     <return type> MyClassName::MyFunction() {
//        ...
//     }
// to tell the compiler that each function belongs to the TuffleGame class.
// ===================================================================
std::string BoardColors(std::string guess, std::string answer) {
  std::string color = "BBBBB";
  for (int i = 0; i < answer.size(); i++) {
    if (answer[i] == guess[i]) {
      color[i] = 'G';
      answer[i] = '&';
    }
  }
  for (int i = 0; i < answer.size(); i++) {
    int index = answer.find(guess[i]);
    if (answer.find(guess[i]) != std::string::npos) {
      if (color[i] != 'G') {
        color[i] = 'Y';
        answer[index] = '&';
      }
    }
  }
  return color;
}
void TuffleGame::NewGame() {
  game_state_ = GameState(dictionary_.GetRandomTuffle());
  game_state_.SetStatus("active");
}
void TuffleGame::LetterKeyPressed(char key) {
  if (game_state_.GetStatus() != "active") {
    return;
  }
  ClearGameState();
  std::vector<std::string> guesses = game_state_.GetGuessedWords();
  if (guesses.size() == 0) {
    guesses.push_back("");
  }
  int index = guesses.size() - 1;
  std::string current_guess = guesses[index];
  if (current_guess.size() != 5) {
    guesses[index] = current_guess + key;
    game_state_.SetGuessedWords(guesses);
  }
}
void TuffleGame::EnterKeyPressed() {
  if (game_state_.GetStatus() != "active") {
    return;
  }
  ClearGameState();
  std::vector<std::string> guesses = game_state_.GetGuessedWords();
  int index = guesses.size() - 1;
  std::string current_guess = guesses[index];
  bool word = dictionary_.IsValidGuess(current_guess);
  if (not word) {
    game_state_.SetErrorMessages("not valid");
    return;
  }
  if (current_guess.size() != 5) {
    game_state_.SetErrorMessages("not long enough word");
    return;
  }
  std::vector<std::string> board = game_state_.GetBoardColors();
  std::string color = BoardColors(current_guess, game_state_.GetAnswer());
  board.push_back(color);
  game_state_.SetBoardColors(board);
  if (color == "GGGGG") {
    game_state_.SetStatus("win");
    return;
  } else if (guesses.size() == 6) {
    game_state_.SetStatus("lose");
    return;
  } else {
    guesses.push_back("");
    game_state_.SetGuessedWords(guesses);
  }
}
void TuffleGame::DeleteKeyPressed() {
  if (game_state_.GetStatus() != "active") {
    return;
  }
  ClearGameState();
  std::vector<std::string> guesses = game_state_.GetGuessedWords();
  int index = guesses.size() - 1;
  std::string current_guess = guesses[index];
  if (current_guess.size() == 0) {
    return;
  }
  current_guess.pop_back();
  guesses[index] = current_guess;
  game_state_.SetGuessedWords(guesses);
}
void TuffleGame::ClearGameState() { game_state_.SetErrorMessages(""); }
crow::json::wvalue TuffleGame::GameStateInJson() {
  // The JSON object to return to the Tuffle Frontend.
  crow::json::wvalue game_state_json({});

  // ===================== YOUR CODE HERE =====================
  // Fill the game_state_json with the data expected by the
  // Tuffle frontend. The frontend expects the following keys:
  //   1. "answer"
  //   2. "boardColors"
  //   3. "guessedWords"
  //   4. "gameStatus"
  //   5. "errorMessage"
  //   6. [OPTIONAL] "letterColors"
  // See the "JSON Response" section of tinyurl.com/cpsc121-f22-tuffle
  //
  // You can set the key in the JSON to a value like so:
  //             game_state_json[<key>] = <value>
  //
  // See below for an example to set the "answer" key:
  game_state_json["answer"] = game_state_.GetAnswer();
  game_state_json["boardColors"] = game_state_.GetBoardColors();
  game_state_json["guessedWords"] = game_state_.GetGuessedWords();
  game_state_json["gameStatus"] = game_state_.GetStatus();
  game_state_json["errorMessage"] = game_state_.GetErrorMessage();
  // ==========================================================
  return game_state_json;
}