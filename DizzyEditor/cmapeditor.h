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
#include "cdialog_animations.h"

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
   MODE_SELECT,//режим выбора блоков
   MODE_MOVE_MAP//режим перемещения карты
  };
  //режим работы мышки
  enum MOUSE_MODE
  {
   MOUSE_MODE_STANDARD,//обычное перемещение мышки
   MOUSE_MODE_SELECT_AREA,//задание области выделения
   MOUSE_MODE_PASTE,//установка блоков
   MOUSE_MODE_MOVE_SELECTED,//перемещение выделенных блоков
   MOUSE_MODE_MOVE_MAP//перемещение поля
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

  QPoint qPoint_MouseMoveMapButtonDownPos;//координата нажатия правой кнопки мыши
  QPoint qPoint_MouseMoveSelectedButtonDownPos;//координата нажатия левой кнопки мыши
  QPoint qPoint_MousePos;//текущая координата мышки

  std::shared_ptr<IPart> Map_Ptr;//карта
  std::shared_ptr<IPart> CursorPart_Ptr;//перемещаемые курсором блоки
  std::shared_ptr<IPart> CopyPart_Ptr;//копируемые курсором блоки

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
  void SetSelectedFirstPlane(bool first_plane);//задать является ли выбранная часть передним планом
  void SetSelectedItem(bool item);//задать является ли выбранная часть предметом
  bool SaveMap(const std::string &file_name);//записать карту
  bool LoadMap(const std::string &file_name);//загрузить карту
  bool ExportMap(const std::string &file_name);//экспортировать карту
  void SetModeSetPart(void);//установить режим установки блоков  
  void SetModeSelectPart(void);//установить режим выбора блоков
  void SetName(const std::string &name);//задать имя материалу
  void SetModeMoveMap(void);//установить режим перемещения карты
  void PressKey(QKeyEvent *pe);//нажатие клавиши
  void ReleaseKey(QKeyEvent *pe);//отпускание клавиши  
 private:
  //-закрытые функции-----------------------------------------------------------------------------------  
  void timerEvent(QTimerEvent *qTimerEvent_Ptr);//обработчик таймера
  void mouseMoveEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик перемещения мышки
  void mousePressEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик нажатия на кнопку мышки
  void mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик отпускания кнопки мышки
  void paintEvent(QPaintEvent *qPaintEvent_Ptr);//обработчик события перерисовки

  void TimerEvent_Mode_MoveMap(const QPoint &qPoint);//обработчик таймера в режиме перемещения карты
  void MouseMoveEvent_Mode_Set(const QPoint &qPoint);//обработчик перемщения мышки в режиме установки блоков
  void MouseMoveEvent_Mode_Select(const QPoint &qPoint);//обработчик перемщения мышки в режиме выбора блоков

  void DrawGrid(QPainter &qPainter,int32_t w_width,int32_t w_height);//рисование сетки
  void DrawMap(QPainter &qPainter);//рисование карты
  void DrawFrameSelectedPartAndBarrierAndFirstPlane(QPainter &qPainter);//рисование рамкок вокруг выделенных, частей переднего плана и непроницаемых блоков карты
  void DrawCursor(QPainter &qPainter,std::shared_ptr<IPart> MousePart_Ptr);//рисование курсора
  void DrawSelectedArea(QPainter &qPainter);//рисование области выделения

  void SetTileForMousePos(int32_t mouse_x,int32_t mouse_y,std::shared_ptr<IPart> MousePart_Ptr);//поставить тайл в позицию по координатам мыши
  void SetTileForBlockPos(int32_t block_x,int32_t block_y,std::shared_ptr<IPart> MousePart_Ptr);//поставить тайл в позицию по координатам блоков
  void SetTile(int32_t mouse_x,int32_t mouse_y,std::shared_ptr<IPart> MousePart_Ptr);//поставить тайл в позицию
  void SelectTiles(QRect &qRect_Area);//выбрать область тайлов
  void UnselectTiles(void);//отменить выбор тайлов
  void SelectTile(int32_t mouse_x,int32_t mouse_y);//выбрать тайл
  void DeleteSelectedTiles(void);//удалить выбранные тайлы
  bool IsTileSelected(int32_t mouse_x,int32_t mouse_y);//проверить, что по данным координатам мышки тайл выбран
  void ConnectSelectedTiles(void);//объединить выбранные тайлы и установить результат в качестве курсора
  void MoveMap(int32_t dx,int32_t dy);//переместить поле
  void AnimationTiles(void);//анимировать тайлы
  void ResetTilesFrame(void);//сбросить кадр на исходный для тайлов (нужно для синхронности анимации)
  void MouseToMap(int32_t mouse_x,int32_t mouse_y,int32_t &map_x,int32_t &map_y);//перевести координаты мыши в координаты блоков карты
  void SetMouseMode(MOUSE_MODE mouse_mode);//задать режим работы мышки
  void GetStringImageSize(QPainter &qPainter,const std::string &string,uint32_t &width,uint32_t &height);//получить размер строки в пикселях
 private slots:
  void on_ContextMenu_CopyPart(void);//слот выбора в контекстном меню пункта "скопировать"
  void on_ContextMenu_PastePart(void);//слот выбора в контекстном меню пункта "вставить"
};

#endif
