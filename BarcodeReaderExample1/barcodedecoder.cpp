#include "barcodedecoder.h"

BarcodeDecoder::BarcodeDecoder()
{

}

void BarcodeDecoder::setup_map(pattern_map &table)
{
    table.insert(std::make_pair(Ob(0001101), 0));
    table.insert(std::make_pair(Ob(0011001), 1));
    table.insert(std::make_pair(Ob(0010011), 2));
    table.insert(std::make_pair(Ob(0111101), 3));
    table.insert(std::make_pair(Ob(0100011), 4));
    table.insert(std::make_pair(Ob(0110001), 5));
    table.insert(std::make_pair(Ob(0101111), 6));
    table.insert(std::make_pair(Ob(0111011), 7));
    table.insert(std::make_pair(Ob(0110111), 8));
    table.insert(std::make_pair(Ob(0001011), 9));
}

void BarcodeDecoder::align_boundary(const Mat &img, Point &cur, int begin, int end)
{
    if (img(cur) == end)
    {
      while (img(cur) == end)
        ++cur.x;
    }
    else
    {
      while (img(cur.y, cur.x - 1) == begin)
        --cur.x;
    }
}
