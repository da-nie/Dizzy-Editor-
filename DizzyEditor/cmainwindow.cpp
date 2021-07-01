//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include <QtWidgets>
#include <stdint.h>
#include <memory>
#include "cpart.h"
#include "cpartunion.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::CMainWindow)
{
 ui->setupUi(this);
 SelectedTileIndexX=0;
 SelectedTileIndexY=0;

 qAction_ModeSetPart=new QAction(QPixmap(":/image/img_set.png"),tr("Установка блоков"),this);
 qAction_ModeSetPart->setStatusTip(tr("Установка блоков"));
 qAction_ModeSetPart->setCheckable(true);
 connect(qAction_ModeSetPart,SIGNAL(triggered()),this,SLOT(On_ToolBar_Main_SetPart()));

 qAction_ModeSelectPart=new QAction(QPixmap(":/image/img_select.png"),tr("Выбор блоков"),this);
 qAction_ModeSelectPart->setStatusTip(tr("Выбор блоков"));
 qAction_ModeSelectPart->setCheckable(true);
 connect(qAction_ModeSelectPart,SIGNAL(triggered()),this,SLOT(On_ToolBar_Main_SelectPart()));

 qAction_ModeMoveMap=new QAction(QPixmap(":/image/img_move.png"),tr("Перемещение по карте"),this);
 qAction_ModeMoveMap->setStatusTip(tr("Перемещение по карте"));
 qAction_ModeMoveMap->setCheckable(true);
 connect(qAction_ModeMoveMap,SIGNAL(triggered()),this,SLOT(On_ToolBar_Main_MoveMap()));

 ui->cToolBar_Main->addAction(qAction_ModeSetPart);
 ui->cToolBar_Main->addAction(qAction_ModeSelectPart);
 ui->cToolBar_Main->addAction(qAction_ModeMoveMap);

 UpdateTilesImage();

 On_ToolBar_Main_MoveMap();
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CMainWindow::~CMainWindow()
{
 delete(ui);
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//обновить картинку списка тайлов
//----------------------------------------------------------------------------------------------------
void CMainWindow::UpdateTilesImage(void)
{
 QPainter qPainter;
 QPixmap qPixmap_Local=CImageStorage::GetPtr()->GetTiles();
 qPainter.begin(&qPixmap_Local);
 qPainter.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
 qPainter.drawRect(QRect(SelectedTileIndexX*CImageStorage::TILE_WITH_BORDER_WIDTH,SelectedTileIndexY*CImageStorage::TILE_WITH_BORDER_HEIGHT,CImageStorage::TILE_WITH_BORDER_WIDTH-1,CImageStorage::TILE_WITH_BORDER_HEIGHT-1));
 qPainter.end();

 QPalette qPalette;
 qPalette.setBrush(backgroundRole(),QBrush(qPixmap_Local));
 ui->cScrollAreaWidgetContents_Tiles->setPalette(qPalette);
 ui->cScrollAreaWidgetContents_Tiles->setAutoFillBackground(true);
 ui->cScrollAreaWidgetContents_Tiles->setFixedSize(qPixmap_Local.width(),qPixmap_Local.height());  
}
//----------------------------------------------------------------------------------------------------
//обработчик нажатия на кнопку мышки
//----------------------------------------------------------------------------------------------------
void CMainWindow::mousePressEvent(QMouseEvent *qMouseEvent_Ptr)
{
 if (qMouseEvent_Ptr->button()&Qt::LeftButton)
 {
  QPoint mpos=qMouseEvent_Ptr->globalPos();
  QPoint mpoint=ui->cScrollAreaWidgetContents_Tiles->mapFromGlobal(mpos);

  int32_t width=ui->cScrollAreaWidgetContents_Tiles->width();
  int32_t height=ui->cScrollAreaWidgetContents_Tiles->height();

  if (mpoint.x()>=width) return;
  if (mpoint.y()>=height) return;

  int32_t tx=mpoint.x()/CImageStorage::TILE_WITH_BORDER_WIDTH;
  int32_t ty=mpoint.y()/CImageStorage::TILE_WITH_BORDER_HEIGHT;

  SelectedTileIndexX=tx;
  SelectedTileIndexY=ty;

  CTilesSequence cTilesSequence(CTile(SelectedTileIndexX,SelectedTileIndexY));
  bool barrier=ui->cCheckBox_Matherial_Barrier->isChecked();
  std::shared_ptr<IPart> iPart_Ptr(new CPartUnion());
  iPart_Ptr->GetItemPtr()->push_back(std::shared_ptr<IPart>(new CPart(0,0,cTilesSequence,barrier)));
  ui->cMapEditor->SetSelectedPart(iPart_Ptr);
  UpdateTilesImage();
 }
}
//----------------------------------------------------------------------------------------------------
//обработчик отпускания кнопки мышки
//----------------------------------------------------------------------------------------------------
void CMainWindow::mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr)
{
}
//----------------------------------------------------------------------------------------------------
//обработчик нажатия клавиши
//----------------------------------------------------------------------------------------------------
void CMainWindow::keyPressEvent(QKeyEvent *pe)
{
 ui->cMapEditor->PressKey(pe);
}
//----------------------------------------------------------------------------------------------------
//обработчик отпускание клавиши
//----------------------------------------------------------------------------------------------------
void CMainWindow::keyReleaseEvent(QKeyEvent *pe)
{
 ui->cMapEditor->ReleaseKey(pe);
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку проницаемости материала
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cCheckBox_Matherial_Barrier_clicked(void)
{
 bool barrier=ui->cCheckBox_Matherial_Barrier->isChecked();
 ui->cMapEditor->SetSelectedBarrier(barrier);
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "сохранить карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_SaveMap_triggered(void)
{
 ui->cMapEditor->SaveMap("map.bin");
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "загрузить карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_LoadMap_triggered(void)
{
 ui->cMapEditor->LoadMap("map.bin");
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "экспортировать карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_ExportMap_triggered()
{
 ui->cMapEditor->ExportMap("map.gam");
}
//----------------------------------------------------------------------------------------------------
//слот выбора в панеле инструментов режима установки блоков
//----------------------------------------------------------------------------------------------------
void CMainWindow::On_ToolBar_Main_SetPart(void)
{     
 ui->cMapEditor->SetModeSetPart();
 qAction_ModeSetPart->setChecked(true);
 qAction_ModeSelectPart->setChecked(false);
 qAction_ModeMoveMap->setChecked(false);
}
//----------------------------------------------------------------------------------------------------
//слот выбора в панеле инструментов режима выбора блоков
//----------------------------------------------------------------------------------------------------
void CMainWindow::On_ToolBar_Main_SelectPart(void)
{
 ui->cMapEditor->SetModeSelectPart();
 qAction_ModeSetPart->setChecked(false);
 qAction_ModeSelectPart->setChecked(true);
 qAction_ModeMoveMap->setChecked(false);
}
//----------------------------------------------------------------------------------------------------
//слот выбора в панеле инструментов режима перемещения по карте
//----------------------------------------------------------------------------------------------------
void CMainWindow::On_ToolBar_Main_MoveMap(void)
{
 ui->cMapEditor->SetModeMoveMap();
 qAction_ModeSetPart->setChecked(false);
 qAction_ModeSelectPart->setChecked(false);
 qAction_ModeMoveMap->setChecked(true);
}
//****************************************************************************************************
//открытые функции
//****************************************************************************************************
