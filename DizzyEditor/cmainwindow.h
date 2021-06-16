#ifndef C_MAIN_WINDOW_H
#define C_MAIN_WINDOW_H

//****************************************************************************************************
//Класс главного окна программы
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <QMainWindow>
#include "cimagestorage.h"

//****************************************************************************************************
//пространства имён
//****************************************************************************************************

namespace Ui
{
 class CMainWindow;
}

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
//Класс главного окна программы
//****************************************************************************************************
class CMainWindow:public QMainWindow
{
 Q_OBJECT
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
 private:
  //-переменные-----------------------------------------------------------------------------------------
  Ui::CMainWindow *ui;
  QPixmap qPixmap_Screen;//поле редактирования

  int32_t SelectedTileIndexX;//позиция выбранного тайла по X
  int32_t SelectedTileIndexY;//позиция выбранного тайла по Y
 public:
  //-конструктор----------------------------------------------------------------------------------------
  explicit CMainWindow(QWidget *parent=0);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CMainWindow();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
  void UpdateTilesImage(void);//обновить картинку списка тайлов
  void mousePressEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик нажатия на кнопку мышки
  void mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr);//обработчик отпускания кнопки мышки
};

#endif
