const int NONE = 0;
const int SOURCE_EMPTY = 11;
const int OPPONENT_PIECE = 12;
const int CAPTURE_OWN_PIECE = 13;
const int INVALID_MOVE = 21;
const int CHECK = 41;
const int SUCCESSFUL_MOVE = 42;

static constexpr int BOARD_SIZE = 8;

enum class Color {
    NO_COLOR = -1,
    BLACK = 0,
    WHITE = 1
};