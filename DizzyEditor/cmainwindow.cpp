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

 UpdateTilesImage();

 //ui->cToolBar_Main->addAction();

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
  /*iPart_Ptr->GetItemPtr()->push_back(std::shared_ptr<IPart>(new CPart(0,1,cTilesSequence,barrier)));
  iPart_Ptr->GetItemPtr()->push_back(std::shared_ptr<IPart>(new CPart(1,0,cTilesSequence,barrier)));
  iPart_Ptr->GetItemPtr()->push_back(std::shared_ptr<IPart>(new CPart(1,1,cTilesSequence,barrier)));
  */
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
//слот нажатия на кнопку проницаемости материала
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cCheckBox_Matherial_Barrier_clicked()
{
 bool barrier=ui->cCheckBox_Matherial_Barrier->isChecked();
 ui->cMapEditor->SetSelectedBarrier(barrier);
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "сохранить карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_SaveMap_triggered()
{
 ui->cMapEditor->SaveMap("map.bin");
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "загрузить карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_LoadMap_triggered()
{
 ui->cMapEditor->LoadMap("map.bin");
}


//****************************************************************************************************
//открытые функции
//****************************************************************************************************

