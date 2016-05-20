//

//
// Created by Vitiok on 5/8/2016.

#include "LineClass.h"

LineClass::LineClass() {
    this->penWidth = 1;
    this->penStyle = PS_SOLID;
    this->penColor = RGB(0, 0, 0);
    this->isDrawing = FALSE;
}

int LineClass::getPenWidth() const {
    return penWidth;
}

void LineClass::setIsDrawing(BOOL isDrawing) {
    this->isDrawing = isDrawing;
}

void LineClass::setPenWidth(int penWeight) {
    LineClass::penWidth = penWeight;
}

HPEN LineClass::getPen() const {
    return CreatePen(this->penStyle, this->penWidth, this->penColor);
}

int LineClass::getPenStyle() const {
    return penStyle;
}

void LineClass::setPenStyle(int penStyle) {
    LineClass::penStyle = penStyle;
}

COLORREF LineClass::getPenColor() const {
    return penColor;;
}

void LineClass::setPenColor(COLORREF penColor) {
    LineClass::penColor = penColor;
}

void LineClass::setStart(POINT start) {
    this->start.x = start.x;
    this->start.y = start.y;
}

POINT LineClass::getStart() {
    return start;
}

void LineClass::setEnd(POINT end) {
    this->end = end;
}

POINT LineClass::getEnd() {
    return end;
}

void LineClass::Draw(HDC hdc) {
    HPEN hNewPen;
    hNewPen = getPen();
    SelectObject(hdc, hNewPen);
    MoveToEx(hdc, start.x, start.y, NULL);
    LineTo(hdc, end.x, end.y);
}

BOOL LineClass::getIsDrawing() {
    return isDrawing;
}

void LineClass::modifyWidth(BOOL increase) {
    int weight;
    weight = this->getPenWidth();
    increase == TRUE ? weight++ : weight--;
    this->setPenWidth(weight);
}

void LineClass::setPen(HDC hdc) {
    HPEN hNewPen;
    hNewPen = getPen();
    SelectObject(hdc, hNewPen);
}
