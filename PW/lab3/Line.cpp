//

//
// Created by Vitiok on 5/8/2016.

#include "Line.h"

Line::Line() {
    this->penWidth = 1;
    this->penStyle = PS_SOLID;
    this->penColor = RGB(0, 0, 0);
    this->isDrawing = FALSE;
}

int Line::getPenWidth() const {
    return penWidth;
}

void Line::setIsDrawing(BOOL isDrawing) {
    this->isDrawing = isDrawing;
}

void Line::setPenWidth(int penWeight) {
    Line::penWidth = penWeight;
}

HPEN Line::getPen() const {
    return CreatePen(this->penStyle, this->penWidth, this->penColor);
}

int Line::getPenStyle() const {
    return penStyle;
}

void Line::setPenStyle(int penStyle) {
    Line::penStyle = penStyle;
}

COLORREF Line::getPenColor() const {
    return penColor;;
}

void Line::setPenColor(COLORREF penColor) {
    Line::penColor = penColor;
}

void Line::setStart(POINT start) {
    this->start.x = start.x;
    this->start.y = start.y;
}

POINT Line::getStart() {
    return start;
}

void Line::setEnd(POINT end) {
    this->end.x = end.x;
    this->end.y = end.y;
}

POINT Line::getEnd() {
    return end;
}

void Line::Draw(HDC hdc) {
    HPEN hNewPen;
    hNewPen = getPen();
    SelectObject(hdc, hNewPen);
    MoveToEx(hdc, start.x, start.y, NULL);
    LineTo(hdc, end.x, end.y);
}

BOOL Line::getIsDrawing() {
    return isDrawing;
}

void Line::modifyWeight(BOOL increase) {
    int weight;
    weight = this->getPenWidth();
    increase == TRUE ? weight++ : weight--;
    this->setPenWidth(weight);
}
