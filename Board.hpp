
#ifndef BOARD_HPP
#define BOARD_HPP

// Simple template class for easily
// getting/setting boolean array values
template <int WIDTH, int HEIGHT>
class Board
{
  public:
    const bool *getData() const
    {
        return board;
    }

    void set(const int &x, const int &y, const bool &val)
    {
        const int index = (x % WIDTH) + (y * HEIGHT);
        board[index] = val;
    }

    bool get(const int &x, const int &y) const
    {
        // Return false for values outside of the board
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
            return false;

        return board[(x % WIDTH) + (y * HEIGHT)];
    }

  private:
    // Our board data
    bool board[WIDTH * HEIGHT];
};

#endif