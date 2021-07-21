//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cdialog_animations.h"
#include "ui_cdialog_animations.h"

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
CDialog_Animations::CDialog_Animations(QWidget *parent,const CTilesSequence &cTilesSequence_set):QDialog(parent),ui(new Ui::CDialog_Animations)
{ 
 ui->setupUi(this);

 cTilesSequence=cTilesSequence_set;

 SelectedTileIndexX=0;
 SelectedTileIndexY=0;

 SelectedTileSequenceIndexX=0;
 SelectedTileSequenceIndexY=0;

 std::vector<CTile> *cTile_Sequence_Ptr=cTilesSequence.GetItemPtr();
 size_t size=cTile_Sequence_Ptr->size();
 if (size>0)
 {
  CTile &cTile=(*cTile_Sequence_Ptr)[size-1];
  SelectedTileIndexX=cTile.X;
  SelectedTileIndexY=cTile.Y;
 }
 UpdateTilesImage();

 ui->cComboBox_AnimationMode->addItem("Циклическая анимация");
 ui->cComboBox_AnimationMode->addItem("Анимация остановлена");
 ui->cComboBox_AnimationMode->addItem("Однократная анимация");
 CTilesSequence::ANIMATION_MODE animation_mode=cTilesSequence.GetAnimationMode();
 if (animation_mode==CTilesSequence::ANIMATION_MODE_CYCLIC) ui->cComboBox_AnimationMode->setCurrentIndex(0);
 if (animation_mode==CTilesSequence::ANIMATION_MODE_SET_STEP) ui->cComboBox_AnimationMode->setCurrentIndex(1);
 if (animation_mode==CTilesSequence::ANIMATION_MODE_ONE_SHOT) ui->cComboBox_AnimationMode->setCurrentIndex(2);
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CDialog_Animations::~CDialog_Animations()
{     
 delete(ui);
}
//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//обновить картинку списка тайлов
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::UpdateTilesImage(void)
{
 //обновляем список тайлов
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

 //обновляем последовательность анимации тайлов

 std::vector<CTile> *cTile_Sequence_Ptr=cTilesSequence.GetItemPtr();
 size_t size=cTile_Sequence_Ptr->size();

 QPixmap &qPixmap_Tiles=CImageStorage::GetPtr()->GetTiles();

 QImage qImage_Sequence(CImageStorage::TILE_WITH_BORDER_WIDTH,CImageStorage::TILE_WITH_BORDER_HEIGHT*size,QImage::Format_RGB32);

 QPainter qPainter_Sequence;

 qPainter_Sequence.begin(&qImage_Sequence);

 static const uint32_t clear=(0xff<<24)|(0<<16)|(0<<8)|(0<<0);
 qPainter_Sequence.fillRect(QRect(0,0,qImage_Sequence.width(),qImage_Sequence.height()),QBrush(QColor(clear)));

 int32_t tw=CImageStorage::TILE_WIDTH;
 int32_t th=CImageStorage::TILE_HEIGHT;

 for(size_t n=0;n<size;n++)
 {
  CTile &cTile=(*cTile_Sequence_Ptr)[n];

  int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH+CImageStorage::TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT+CImageStorage::TILE_BORDER_HEIGHT;

  int32_t screen_x=CImageStorage::TILE_BORDER_WIDTH;
  int32_t screen_y=CImageStorage::TILE_BORDER_HEIGHT+n*CImageStorage::TILE_WITH_BORDER_HEIGHT;
  qPainter_Sequence.drawPixmap(screen_x,screen_y,qPixmap_Tiles.copy(tx,ty,tw,th));

  if (SelectedTileSequenceIndexX==0 && SelectedTileSequenceIndexY==n)
  {
   qPainter_Sequence.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
   qPainter_Sequence.drawRect(screen_x-1,screen_y-1,tw+1,th+1);
  }
 }
 qPainter_Sequence.end();

 QPalette qPalette_Sequence;
 qPalette_Sequence.setBrush(backgroundRole(),QBrush(qImage_Sequence));
 ui->cScrollAreaWidgetContents_TilesSequence->setPalette(qPalette_Sequence);
 ui->cScrollAreaWidgetContents_TilesSequence->setAutoFillBackground(true);
 ui->cScrollAreaWidgetContents_TilesSequence->setFixedSize(qImage_Sequence.width(),qImage_Sequence.height());

}
//----------------------------------------------------------------------------------------------------
//выбрать тайл в наборе
//----------------------------------------------------------------------------------------------------
bool CDialog_Animations::SelectedTile(QPoint &mpos)
{
 QPoint mpoint=ui->cScrollAreaWidgetContents_Tiles->mapFromGlobal(mpos);
 QPoint marea=ui->cScrollArea_Tiles->mapFromGlobal(mpos);

 QRect qRect_image=ui->cScrollAreaWidgetContents_Tiles->geometry();
 QRect qRect=ui->cScrollArea_Tiles->contentsRect();

 if (marea.x()>=qRect.width()) return(false);
 if (marea.y()>=qRect.height()) return(false);
 if (marea.x()<qRect.x()) return(false);
 if (marea.y()<qRect.y()) return(false);

 if (mpoint.x()>qRect_image.width()) return(false);
 if (mpoint.y()>qRect_image.height()) return(false);

 int32_t tx=mpoint.x()/CImageStorage::TILE_WITH_BORDER_WIDTH;
 int32_t ty=mpoint.y()/CImageStorage::TILE_WITH_BORDER_HEIGHT;

 SelectedTileIndexX=tx;
 SelectedTileIndexY=ty;

 return(true);
}
//----------------------------------------------------------------------------------------------------
//выбрать тайл в последовательности
//----------------------------------------------------------------------------------------------------
bool CDialog_Animations::SelectedTileSequence(QPoint &mpos)
{
 QPoint mpoint=ui->cScrollAreaWidgetContents_TilesSequence->mapFromGlobal(mpos);
 QPoint marea=ui->cScrollArea_TilesSequence->mapFromGlobal(mpos);

 QRect qRect_image=ui->cScrollAreaWidgetContents_TilesSequence->geometry();
 QRect qRect=ui->cScrollArea_TilesSequence->contentsRect();

 if (marea.x()>=qRect.width()) return(false);
 if (marea.y()>=qRect.height()) return(false);
 if (marea.x()<qRect.x()) return(false);
 if (marea.y()<qRect.y()) return(false);

 if (mpoint.x()>qRect_image.width()) return(false);
 if (mpoint.y()>qRect_image.height()) return(false);

 int32_t tx=mpoint.x()/CImageStorage::TILE_WITH_BORDER_WIDTH;
 int32_t ty=mpoint.y()/CImageStorage::TILE_WITH_BORDER_HEIGHT;

 SelectedTileSequenceIndexX=tx;
 SelectedTileSequenceIndexY=ty;

 return(true);
}

//----------------------------------------------------------------------------------------------------
//обработчик нажатия на кнопку мышки
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::mousePressEvent(QMouseEvent *qMouseEvent_Ptr)
{
 if (qMouseEvent_Ptr->button()&Qt::LeftButton)
 {
  QPoint mpos=qMouseEvent_Ptr->globalPos();
  if (SelectedTile(mpos)==true || SelectedTileSequence(mpos)==true) UpdateTilesImage();
 }
}
//----------------------------------------------------------------------------------------------------
//обработчик отпускания кнопки мышки
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr)
{
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку добавление тайла в последовательность
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::on_cPushButton_Add_clicked(void)
{
 CTile cTile(SelectedTileIndexX,SelectedTileIndexY);
 cTilesSequence.AddNewTile(cTile);
 UpdateTilesImage();
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку удаления всех тайлов кроме первого из последовательности
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::on_cPushButton_Clear_clicked(void)
{
 std::vector<CTile> *cTile_Sequence_Ptr=cTilesSequence.GetItemPtr();
 size_t size=cTile_Sequence_Ptr->size();
 if (size>0)
 {
  CTile cTile=(*cTile_Sequence_Ptr)[0];
  cTile_Sequence_Ptr->clear();
  cTile_Sequence_Ptr->push_back(cTile);
  SelectedTileSequenceIndexX=0;
  SelectedTileSequenceIndexY=0;
  UpdateTilesImage();
 }
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку удаления выбранного тайла из последовательности
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::on_cPushButton_Delete_clicked()
{
 std::vector<CTile> *cTile_Sequence_Ptr=cTilesSequence.GetItemPtr();
 size_t size=cTile_Sequence_Ptr->size();
 if (size>1 && SelectedTileSequenceIndexX==0 && SelectedTileSequenceIndexY<size)
 {
  cTile_Sequence_Ptr->erase(cTile_Sequence_Ptr->begin()+SelectedTileSequenceIndexY);
  SelectedTileSequenceIndexY=0;
  UpdateTilesImage();
 }
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку отмена
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::on_cPushButton_Cancel_clicked()
{
 reject();
}
//----------------------------------------------------------------------------------------------------
//слот нажатия на кнопку применить
//----------------------------------------------------------------------------------------------------
void CDialog_Animations::on_cPushButton_Apply_clicked()
{
 int32_t index=ui->cComboBox_AnimationMode->currentIndex();
 if (index==CYCLYC_ANIMATION_INDEX) cTilesSequence.SetAnimationMode(CTilesSequence::ANIMATION_MODE_CYCLIC);
 if (index==SET_STEP_ANIMATION_INDEX) cTilesSequence.SetAnimationMode(CTilesSequence::ANIMATION_MODE_SET_STEP);
 if (index==ONE_SHOT_ANIMATION_INDEX) cTilesSequence.SetAnimationMode(CTilesSequence::ANIMATION_MODE_ONE_SHOT);
 accept();
}
//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//получить последовательность анимации
//----------------------------------------------------------------------------------------------------
CTilesSequence& CDialog_Animations::GetTilesSequence(void)
{
 return(cTilesSequence);
}



