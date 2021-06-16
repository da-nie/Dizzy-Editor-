//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cmapeditor.h"
#include "cimagestorage.h"
#include <fstream>

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
CMapEditor::CMapEditor(QWidget *parent):QWidget(parent)
{ 
 //настраиваем исходные состояния кнопок мышки
 MouseLButton=false;
 MouseRButton=false;
 MouseCButton=false;

 qPoint_LeftTop=QPoint(0,0); 
 qPoint_MousePos=QPoint(0,0);

 ChangeTileCounter=0;
 SelectedBarrier=false;

 //подключим таймер обновления экрана
 TimerId=startTimer(TIMER_INTERVAL_MS);

 LoadMap("map.bin");
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CMapEditor::~CMapEditor()
{
 killTimer(TimerId);
 SaveMap("map.bin");
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************


//----------------------------------------------------------------------------------------------------
//обработчик таймера
//----------------------------------------------------------------------------------------------------
void CMapEditor::timerEvent(QTimerEvent *qTimerEvent_Ptr)
{
 if (qTimerEvent_Ptr->timerId()!=TimerId) return;
 //переводим координаты курсора в систему координат виджета
 QPoint qPoint=mapFromGlobal(cursor().pos());

 if (MouseRButton==true)
 {
  int32_t dx=qPoint.x()-qPoint_MouseRightButtonDownPos.x();
  int32_t dy=qPoint.y()-qPoint_MouseRightButtonDownPos.y();
  qPoint_MouseRightButtonDownPos=qPoint;
  MoveMap(dx,dy);
 }
 qPoint_MousePos=qPoint;

 ChangeTileCounter++;
 ChangeTileCounter%=TIMER_CHANGE_TILE_DIVIDER;
 if (ChangeTileCounter==0) AnimateTiles();

 update();
}

//----------------------------------------------------------------------------------------------------
//обработчик перемещения мышки
//----------------------------------------------------------------------------------------------------
void CMapEditor::mouseMoveEvent(QMouseEvent *qMouseEvent_Ptr)
{
 int32_t x=qMouseEvent_Ptr->localPos().x();
 int32_t y=qMouseEvent_Ptr->localPos().y(); 

 if (MouseLButton==true) SetTile(x,y);
}
//----------------------------------------------------------------------------------------------------
//обработчик нажатия на кнопку мышки
//----------------------------------------------------------------------------------------------------
void CMapEditor::mousePressEvent(QMouseEvent *qMouseEvent_Ptr)
{
 int32_t x=qMouseEvent_Ptr->localPos().x();
 int32_t y=qMouseEvent_Ptr->localPos().y();

 if (qMouseEvent_Ptr->button()&Qt::LeftButton)
 {
  if (MouseLButton==false) MouseLButton=true;
  SetTile(x,y);
 }
 if (qMouseEvent_Ptr->button()&Qt::RightButton)
 {
  if (MouseRButton==false) MouseRButton=true;
  qPoint_MouseRightButtonDownPos=QPoint(x,y);
 }
 if (qMouseEvent_Ptr->button()&Qt::MidButton)
 {
  if (MouseCButton==false) MouseCButton=true;
 }
}
//----------------------------------------------------------------------------------------------------
//обработчик отпускания кнопки мышки
//----------------------------------------------------------------------------------------------------
void CMapEditor::mouseReleaseEvent(QMouseEvent *qMouseEvent_Ptr)
{
 int32_t x=qMouseEvent_Ptr->localPos().x();
 int32_t y=qMouseEvent_Ptr->localPos().y();

 if (qMouseEvent_Ptr->button()&Qt::LeftButton)
 {
  if (MouseLButton==true) MouseLButton=false;
 }
 if (qMouseEvent_Ptr->button()&Qt::RightButton)
 {
  if (MouseRButton==true) MouseRButton=false;
 }
 if (qMouseEvent_Ptr->button()&Qt::MidButton)
 {
  if (MouseCButton==true) MouseCButton=false;
 }
}

//----------------------------------------------------------------------------------------------------
//обработчик события перерисовки
//----------------------------------------------------------------------------------------------------
void CMapEditor::paintEvent(QPaintEvent *qPaintEvent_Ptr)
{
 int32_t w_width=width();
 int32_t w_height=height();

 QPainter qPainter(this);
 qPainter.fillRect(QRect(0,0,w_width,w_height),QBrush(Qt::black));

 qPainter.setPen(QPen(Qt::gray,1,Qt::SolidLine));

 int32_t py=qPoint_LeftTop.y()/CImageStorage::TILE_HEIGHT;
 for(int32_t y_pos=CImageStorage::TILE_HEIGHT-qPoint_LeftTop.y()%CImageStorage::TILE_HEIGHT;y_pos<w_height;y_pos+=CImageStorage::TILE_HEIGHT,py++)
 {
  if (py%15==0) qPainter.setPen(QPen(Qt::white,1,Qt::SolidLine));
           else qPainter.setPen(QPen(Qt::gray,1,Qt::SolidLine));
  qPainter.drawLine(0,y_pos,w_width,y_pos);
 }
 int32_t px=qPoint_LeftTop.x()/CImageStorage::TILE_HEIGHT;
 for(int32_t x_pos=CImageStorage::TILE_WIDTH-qPoint_LeftTop.x()%CImageStorage::TILE_WIDTH;x_pos<w_width;x_pos+=CImageStorage::TILE_WIDTH,px++)
 {
  if (px%20==0) qPainter.setPen(QPen(Qt::white,1,Qt::SolidLine));
           else qPainter.setPen(QPen(Qt::gray,1,Qt::SolidLine));
  qPainter.drawLine(x_pos,0,x_pos,w_height);
 }

 QPixmap &qPixmap_Tiles=CImageStorage::GetPtr()->GetTiles();

 int32_t tw=CImageStorage::TILE_WIDTH;
 int32_t th=CImageStorage::TILE_HEIGHT;

 //выводим карту
 auto OutputFunc=[this,&tw,&th,&qPainter,&qPixmap_Tiles](CPart &cPart)
 {
  int32_t block_x=cPart.BlockPosX;
  int32_t block_y=cPart.BlockPosY;

  int32_t screen_x=block_x*CImageStorage::TILE_WIDTH;
  int32_t screen_y=block_y*CImageStorage::TILE_HEIGHT;
  screen_x-=qPoint_LeftTop.x();
  screen_y-=qPoint_LeftTop.y();

  size_t tile_index=cPart.cTilesSequence.GetCurrentIndex();
  CTile &cTile=cPart.cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH;
  int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT;

  qPainter.drawPixmap(screen_x,screen_y,qPixmap_Tiles.copy(tx,ty,tw,th));
 };
 std::for_each(Map.begin(),Map.end(),OutputFunc);


 size_t tile_index=cTilesSequence_Selected.GetCurrentIndex();
 CTile &cTile=cTilesSequence_Selected.GetTile(tile_index);

 int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH;
 int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT;

 //координаты в общем пространстве
 int32_t map_x=(qPoint_MousePos+qPoint_LeftTop).x();
 int32_t map_y=(qPoint_MousePos+qPoint_LeftTop).y();
 //координаты в индексах блоков
 int32_t block_x=map_x/CImageStorage::TILE_WIDTH;
 int32_t block_y=map_y/CImageStorage::TILE_HEIGHT;

 int32_t screen_x=block_x*CImageStorage::TILE_WIDTH;
 int32_t screen_y=block_y*CImageStorage::TILE_HEIGHT;

 screen_x-=qPoint_LeftTop.x();
 screen_y-=qPoint_LeftTop.y();

 qPainter.drawPixmap(screen_x,screen_y,qPixmap_Tiles.copy(tx,ty,tw,th));
}

//----------------------------------------------------------------------------------------------------
//поставить тайл в позицию
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetTile(int32_t mouse_x,int32_t mouse_y)
{
 //координаты в общем пространстве
 QPoint qPoint(mouse_x,mouse_y);
 int32_t map_x=(qPoint+qPoint_LeftTop).x();
 int32_t map_y=(qPoint+qPoint_LeftTop).y();
 //координаты в индексах блоков
 int32_t block_x=map_x/CImageStorage::TILE_WIDTH;
 int32_t block_y=map_y/CImageStorage::TILE_HEIGHT;
 //ищем по данным координатам блок
 auto compare_func=[block_x,block_y](CPart &cPart)->bool
 {
  if (block_x==cPart.BlockPosX && block_y==cPart.BlockPosY) return(true);
  return(false);
 };
 Map.erase(std::remove_if(Map.begin(),Map.end(),compare_func),Map.end());
 Map.push_back(CPart(block_x,block_y,cTilesSequence_Selected,SelectedBarrier));
}
//----------------------------------------------------------------------------------------------------
//переместить поле
//----------------------------------------------------------------------------------------------------
void CMapEditor::MoveMap(int32_t dx,int32_t dy)
{
 int32_t nx=qPoint_LeftTop.x()+dx;
 int32_t ny=qPoint_LeftTop.y()+dy;
 if (nx<0) nx=0;
 if (ny<0) ny=0; 
 qPoint_LeftTop=QPoint(nx,ny);
}
//----------------------------------------------------------------------------------------------------
//записать карту
//----------------------------------------------------------------------------------------------------
bool CMapEditor::SaveMap(const std::string &file_name)
{
 std::ofstream file;
 file.open(file_name,std::ios_base::out|std::ios_base::binary);
 if (file.is_open()==false) return(false);
 size_t part=Map.size();
 if (file.write(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);

 auto save_function=[&file](CPart &cPart)
 {
  cPart.Save(file);
 };
 std::for_each(Map.begin(),Map.end(),save_function);
 return(true);
}

//----------------------------------------------------------------------------------------------------
//загрузить карту
//----------------------------------------------------------------------------------------------------
bool CMapEditor::LoadMap(const std::string &file_name)
{
 std::ifstream file;
 file.open(file_name,std::ios_base::in|std::ios_base::binary);
 if (file.is_open()==false) return(false);

 size_t part;
 if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);
 Map.clear();

 for(size_t n=0;n<part;n++)
 {
  CPart cPart;
  cPart.Load(file);
  Map.push_back(cPart);
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//анимировать тайлы
//----------------------------------------------------------------------------------------------------
void CMapEditor::AnimateTiles(void)
{
 //анимируем выбранный тайл
 cTilesSequence_Selected.ToNextTile();
 //анимируем карту
 auto OutputFunc=[](CPart &cPart)
 {
  cPart.cTilesSequence.ToNextTile();
 };
 std::for_each(Map.begin(),Map.end(),OutputFunc);
}
//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//задать выбранную последовательность тайлов
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetSelectedTiles(const CTilesSequence &cTilesSequence)
{
 cTilesSequence_Selected=cTilesSequence;
}
//----------------------------------------------------------------------------------------------------
//задать является ли выбранная часть барьером
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetSelectedBarrier(bool barrier)
{
 SelectedBarrier=barrier;
}
