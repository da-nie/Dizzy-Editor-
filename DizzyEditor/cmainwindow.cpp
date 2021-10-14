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
static std::string CaptionName("Dizzy Map Editor v1.0");

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

 ScaleTable.push_back(std::pair<std::string,double>("1",1));
 ScaleTable.push_back(std::pair<std::string,double>("2",2));
 ScaleTable.push_back(std::pair<std::string,double>("3",3));
 ScaleTable.push_back(std::pair<std::string,double>("4",4));
 ScaleTable.push_back(std::pair<std::string,double>("0.75",0.75));
 ScaleTable.push_back(std::pair<std::string,double>("0.5",0.5));
 size_t size=ScaleTable.size();
 for(size_t n=0;n<size;n++) ui->cComboBox_Scale->addItem(ScaleTable[n].first.c_str());
 ui->cComboBox_Scale->setCurrentIndex(0);

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
  QPoint marea=ui->cScrollArea_Tiles->mapFromGlobal(mpos);

  QRect qRect_image=ui->cScrollAreaWidgetContents_Tiles->geometry();
  QRect qRect=ui->cScrollArea_Tiles->contentsRect();

  if (marea.x()>=qRect.width()) return;
  if (marea.y()>=qRect.height()) return;
  if (marea.x()<qRect.x()) return;
  if (marea.y()<qRect.y()) return;

  if (mpoint.x()>qRect_image.width()) return;
  if (mpoint.y()>qRect_image.height()) return;

  int32_t tx=mpoint.x()/CImageStorage::TILE_WITH_BORDER_WIDTH;
  int32_t ty=mpoint.y()/CImageStorage::TILE_WITH_BORDER_HEIGHT;

  SelectedTileIndexX=tx;
  SelectedTileIndexY=ty;

  CTilesSequence cTilesSequence(CTile(SelectedTileIndexX,SelectedTileIndexY));
  bool barrier=ui->cCheckBox_Matherial_Barrier->isChecked();
  bool first_plane=ui->cCheckBox_Matherial_FirstPlane->isChecked();
  bool before_background=ui->cCheckBox_Matherial_BeforeBackground->isChecked();
  std::string name;
  name=ui->cLineEdit_PartName->text().toStdString();
  std::shared_ptr<IPart> iPart_Ptr(new CPartUnion());

  iPart_Ptr->GetItemPtr()->push_back(std::shared_ptr<IPart>(new CPart(0,0,cTilesSequence,barrier,first_plane,before_background,name)));
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
//слот нажатия на кнопку переднего плана материала
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cCheckBox_Matherial_FirstPlane_clicked()
{
 bool first_plane=ui->cCheckBox_Matherial_FirstPlane->isChecked();
 ui->cMapEditor->SetSelectedFirstPlane(first_plane);
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку задания, что материал является предметом
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cCheckBox_Matherial_BeforeBackground_clicked()
{
 bool before_background=ui->cCheckBox_Matherial_BeforeBackground->isChecked();
 ui->cMapEditor->SetSelectedBeforeBackground(before_background);
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку задания имени материала
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cPushButton_SetPartName_clicked()
{
 std::string name;
 name=ui->cLineEdit_PartName->text().toStdString();
 ui->cMapEditor->SetName(name);
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "сохранить карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_SaveMap_triggered(void)
{
 if (CurrentFileName.empty()==false)
 {
  ui->cMapEditor->SaveMap(CurrentFileName);  
  return;
 }
 on_cAction_SaveMapAs_triggered();
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "сохранить карту как"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_SaveMapAs_triggered()
{
 QString file_name=QFileDialog::getSaveFileName(this,tr("Укажите сохраняемый файл карты"),".","*.bin");
 if (file_name.isEmpty()) return;
 CurrentFileName=file_name.toStdString();
 ui->cMapEditor->SaveMap(CurrentFileName);
 setWindowTitle(tr((CaptionName+" "+CurrentFileName).c_str()));
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "загрузить карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_LoadMap_triggered(void)
{
 QString file_name=QFileDialog::getOpenFileName(this,tr("Укажите загружаемый файл карты"),".","*.bin");
 if (file_name.isEmpty()) return;
 CurrentFileName=file_name.toStdString();
 if (ui->cMapEditor->LoadMap(CurrentFileName)==true)
 {
  setWindowTitle(tr((CaptionName+" "+CurrentFileName).c_str()));
 }
}
//----------------------------------------------------------------------------------------------------
//слот выбора пункта меню "экспортировать карту"
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cAction_ExportMap_triggered()
{
 bool res=ui->cMapEditor->ExportMap("map.gam");
 if (res==true)
 {
  QMessageBox *qMessageBox=new QMessageBox(QMessageBox::Information,"Сообщение","Экспорт карты в файл map.gam выполнен успешно.",QMessageBox::Yes);
  qMessageBox->exec();
  delete(qMessageBox);
 }
 else
 {
  QMessageBox *qMessageBox=new QMessageBox(QMessageBox::Information,"Ошибка!","Не удалось выполнить экспорт карты!",QMessageBox::Yes);
  qMessageBox->exec();
  delete(qMessageBox);
 }
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
//----------------------------------------------------------------------------------------------------
//слот смены выбора масштаба
//----------------------------------------------------------------------------------------------------
void CMainWindow::on_cComboBox_Scale_currentIndexChanged(int index)
{
 double scale=ScaleTable[index].second;
 ui->cMapEditor->SetScale(scale);
}
//****************************************************************************************************
//открытые функции
//****************************************************************************************************


