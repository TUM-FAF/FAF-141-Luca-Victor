//
// Created by Vitiok on 5/8/2016.
//

#ifndef LAB3_DRAWING_H
#define LAB3_DRAWING_H

#include <windows.h>

class LineClass {
protected:
    POINT start;
    POINT end;
    int penWidth;
    int penStyle;
    BOOL isDrawing;
    COLORREF penColor;
public:
    LineClass();

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


#endif //LAB3_DRAWING_H
