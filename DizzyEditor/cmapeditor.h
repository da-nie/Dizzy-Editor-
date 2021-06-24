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
 Q_OBJECT
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //режим работы компонента
  enum MODE
  {
   MODE_SET,//режим установки блоков
   MODE_SELECT//режим выбора блоков
  };
  //режим работы мышки
  enum MOUSE_MODE
  {
   MOUSE_MODE_STANDARD,//обычное перемещение мышки
   MOUSE_MODE_SELECT_AREA//задание области выделения
  };
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

  MODE Mode;//режим работы редактора
  MOUSE_MODE MouseMode;//режим работы мышки
  bool CtrlOn;//нажата ли клавиша ctrl

  QRect qRect_SelectedArea;//выбранная область

  QMenu *qMenu_Context;//контекстное меню
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
  bool ExportMap(const std::string &file_name);//экспортировать карту
  void SetModeSetPart(void);//установить режим установки блоков  
  void SetModeSelectPart(void);//установить режим выбора блоков
  void PressKey(QKeyEvent *pe);//нажатие клавиши
  void ReleaseKey(QKeyEvent *pe);//отпускание клавиши  
 private:
  //-закрытые функции-----------------------------------------------------------------------------------  
  void timerEvent(QTimerEvent *qTimerEvent_Ptr);//обработчик таймера
  void mouseMoveEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик перемещения мышки
  void mousePressEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик нажатия на кнопку мышки
  void mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик отпускания кнопки мышки
  void paintEvent(QPaintEvent *qPaintEvent_Ptr);//обработчик события перерисовки

  void DrawGrid(QPainter &qPainter,int32_t w_width,int32_t w_height);//рисование сетки
  void DrawMap(QPainter &qPainter);//рисование карты
  void DrawCursor(QPainter &qPainter);//рисование курсора
  void DrawSelectedArea(QPainter &qPainter);//рисование области выделения

  void SetTile(int32_t mouse_x,int32_t mouse_y);//поставить тайл в позицию
  void SelectTiles(QRect &qRect_Area);//выбрать область тайлов
  void UnselectTiles(void);//отменить выбор тайлов
  void SelectTile(int32_t mouse_x,int32_t mouse_y);//выбрать тайл
  void DeleteSelectedTiles(void);//удалить выбранные тайлы
  bool IsTileSelected(int32_t mouse_x,int32_t mouse_y);//проверить, что по данным координатам мышки тайл выбран
  void ConnectSelectedTiles(void);//объединить выбранные тайлы и установить результат в качестве курсора
  void MoveMap(int32_t dx,int32_t dy);//переместить поле
  void AnimateTiles(void);//анимировать тайлы
  void MouseToMap(int32_t mouse_x,int32_t mouse_y,int32_t &map_x,int32_t &map_y);//перевести координаты мыши в координаты блоков карты
 private slots:
  void on_ContextMenu_CopyPart(QAction *pAction);//слот выбора в контекстном меню пункта "скопировать"
};

#endif
