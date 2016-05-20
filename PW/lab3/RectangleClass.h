//
// Created by Vitiok on 5/20/2016.
//

#ifndef LAB3_RECTANGLE_H
#define LAB3_RECTANGLE_H

#include <windows.h>

class RectangleClass {
private:
    POINT start;
    POINT end;
    int penWidth;
    int penStyle;
    BOOL isDrawing;
    COLORREF penColor;
public:
    RectangleClass();

    void setStart(POINT start);
    POINT getStart();

    void setEnd(POINT end);
    POINT getEnd();

    int getPenWidth() const ;
    void setPenWidth(int penWeight) ;

    int getPenStyle() const ;
    void setPenStyle(int penStyle) ;

    COLORREF getPenColor() const ;
    void setPenColor(COLORREF penColor) ;

    void setPen(HDC hdc);
    HPEN getPen() const;

    void Draw(HDC hdc);

    void setIsDrawing(BOOL isDrawing);
    BOOL getIsDrawing();

    void modifyWidth(BOOL increase);
};


#endif //LAB3_RECTANGLE_H
