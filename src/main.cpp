#include <opencv2/opencv_modules.hpp>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include "pytnashki.h"

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        Pyatnashki *game = reinterpret_cast<Pyatnashki *>(userdata);
        vector<int> key;

        for (auto k : game->GetKeyboard())
        {
            key = k.second;
            if (x > key[0] && x < key[2] && y > key[1] && y < key[3])
            {
                game->Interface(k.first);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите количество строк или столбцов от 2 до 8" << endl;
    int m = 0;
    cin >> m;
    if (m < 2)
    {
        cout << "Введеное значение меньше минимального" << endl;
        return 0;
    }
    if (m > 8)
    {
        cout << "Введеное значение больше максимального" << endl;
        return 0;
    }

    VideoCapture cap(0);
    if (cap.isOpened() == false)
    {
        cout << "Видеокамера с ID 0 не найдена, введите ID видеокамеры" << endl;
        int id = 0;
        cin >> id;
        cap.release();
        VideoCapture cap2(id);
        cap = cap2;
        if (cap.isOpened() == false)
        {
            cout << "Видеокамера не найдена" << endl;
            return 0;
        }
    }
    


    Display *d = XOpenDisplay(NULL);
    Screen *s = DefaultScreenOfDisplay(d);
    double w = s->width;
    double h = s->height;
    XCloseDisplay(d);
 

    Pyatnashki game(w, h, m);
    game.FillingSheet();
    Mat frame;
    string interface_window = "interface";

    while (true)
    {
        if (game.GetExit())
            break;
        bool bSuccess = cap.read(frame);
        if (bSuccess == false)
        {
            cout << "Видеокамера не подключена" << endl;
            break;
        }

  cv::resize(frame, frame, cv::Size(w,h));
        int i = -1;
        int n = game.GetSideSquare();
        for (int r = 0; r < frame.rows; r += n)
            for (int c = game.GetWidthSideField(); c < (game.GetWidthSideField() + m * n); c += n)
            {
                Mat tile = frame(Range(r, min(r + n, frame.rows)),
                                 Range(c, min(c + n, frame.cols)));
                ++i;
                if (i < m * m - 1)
                {
                    string name_window = to_string(i);
                    namedWindow(name_window);
                    moveWindow(name_window, game.GetSheet(i).first, game.GetSheet(i).second);
                    imshow(to_string(i), tile);
                    waitKey(1);
                }
            }
        Mat tile = frame(Range(0, h), Range(0, game.GetWidthSideField()));
        string name_window = to_string(++i);
        namedWindow(name_window);
        moveWindow(name_window, 0, 0);
        imshow(to_string(i), tile);
        waitKey(1);

        tile = frame(Range(0, h), Range(game.GetWidthSideField() + n * m, w));
        namedWindow(interface_window);
        ++i;
        moveWindow(interface_window, game.GetWidthSideField() + n * m, 0);
        if (game.GetStart() == true && game.GetSheetVector() == game.GetSheetControl())
            putText(tile, "victory", {10, 100}, FONT_HERSHEY_DUPLEX, 1.5, Scalar(0, 255, 0));
        else if (game.GetStart() == true)
            putText(tile, "game", {10, 100}, FONT_HERSHEY_DUPLEX, 1.5, Scalar(0, 255, 0));
        for (auto k : game.GetKeyboard())
        {
            vector<int> coordinate = k.second;
            rectangle(tile, Point(coordinate[0], coordinate[1]),
                      Point(coordinate[2], coordinate[3]), Scalar::all(255), -1, 8, 0);
            putText(tile, k.first, {coordinate[0] + 10, coordinate[1] + 40},
                    FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 0, 0));
        }
        imshow(interface_window, tile);
        setMouseCallback(interface_window, onMouse, &game);
        waitKey(1);
    }
    return 0;
}