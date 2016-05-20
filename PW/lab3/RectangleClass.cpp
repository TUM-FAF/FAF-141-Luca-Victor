//
// Created by Vitiok on 5/20/2016.
//

#include "RectangleClass.h"

RectangleClass::RectangleClass() {
    this->penWidth = 1;
    this->penStyle = PS_SOLID;
    this->penColor = RGB(0, 0, 0);
    this->isDrawing = FALSE;
}

int RectangleClass::getPenWidth() const {
    return penWidth;
}

void RectangleClass::setIsDrawing(BOOL isDrawing) {
    this->isDrawing = isDrawing;
}

void RectangleClass::setPenWidth(int penWeight) {
    RectangleClass::penWidth = penWeight;
}

HPEN RectangleClass::getPen() const {
    return CreatePen(this->penStyle, this->penWidth, this->penColor);
}

int RectangleClass::getPenStyle() const {
    return penStyle;
}

void RectangleClass::setPenStyle(int penStyle) {
    RectangleClass::penStyle = penStyle;
}

COLORREF RectangleClass::getPenColor() const {
    return penColor;;
}

void RectangleClass::setPenColor(COLORREF penColor) {
    RectangleClass::penColor = penColor;
}

void RectangleClass::setStart(POINT start) {
    this->start.x = start.x;
    this->start.y = start.y;
}

POINT RectangleClass::getStart() {
    return start;
}

void RectangleClass::setEnd(POINT end) {
    this->end = end;
}

POINT RectangleClass::getEnd() {
    return end;
}

void RectangleClass::Draw(HDC hdc) {
    HPEN hNewPen;
    hNewPen = getPen();
    SelectObject(hdc, hNewPen);
    Rectangle(hdc, start.x, start.y, end.x, end.y);
}