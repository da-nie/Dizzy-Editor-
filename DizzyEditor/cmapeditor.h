#ifndef C_MAP_EDITOR_H
#define C_MAP_EDITOR_H

//****************************************************************************************************
//класс поля редактирования
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <QtWidgets>
#include <list>
#include <stdint.h>
#include <string>
#include "ipart.h"
#include "ctilessequence.h"

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//предварительные объявления
//****************************************************************************************************

//****************************************************************************************************
//класс поля редактирования
//****************************************************************************************************
class CMapEditor:public QWidget
{
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
  static const uint32_t TIMER_INTERVAL_MS=50;//интервал срабатывания таймера, мс
  static const uint32_t TIMER_CHANGE_TILE_DIVIDER=10;//делитель для анимации тайлов
 private:
  //-переменные-----------------------------------------------------------------------------------------
  int32_t TimerId;//идентификатор таймера
  QImage qImage_Map;//изображение поля

  size_t ChangeTileCounter;//счётчик для анимации тайлов

  bool MouseLButton;//состояние левой кнопки мышки
  bool MouseRButton;//состояние правой кнопки мышки
  bool MouseCButton;//состояние центральной кнопки мышки

  QPoint qPoint_LeftTop;//координата левой верхней точки

  QPoint qPoint_MouseRightButtonDownPos;//координата нажатия правой кнопки мыши
  QPoint qPoint_MousePos;//текущая координата мышки

  std::shared_ptr<IPart> Map_Ptr;//карта
  std::shared_ptr<IPart> CursorPart_Ptr;//перемещаемые курсором блоки
 public:
  //-конструктор----------------------------------------------------------------------------------------
  explicit CMapEditor(QWidget *parent=0);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CMapEditor();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void SetSelectedPart(std::shared_ptr<IPart> iPart_Ptr);//задать выбранную последовательность блоков
  void SetSelectedBarrier(bool barrier);//задать является ли выбранная часть барьером
  bool SaveMap(const std::string &file_name);//записать карту
  bool LoadMap(const std::string &file_name);//загрузить карту
 private:
  //-закрытые функции-----------------------------------------------------------------------------------  
  void timerEvent(QTimerEvent *qTimerEvent_Ptr);//обработчик таймера
  void mouseMoveEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик перемещения мышки
  void mousePressEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик нажатия на кнопку мышки
  void mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик отпускания кнопки мышки
  void paintEvent(QPaintEvent *qPaintEvent_Ptr);//обработчик события перерисовки

  void SetTile(int32_t mouse_x,int32_t mouse_y);//поставить тайл в позицию
  void MoveMap(int32_t dx,int32_t dy);//переместить поле
  void AnimateTiles(void);//анимировать тайлы
};

#endif
