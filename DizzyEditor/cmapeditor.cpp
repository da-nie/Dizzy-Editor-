//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cmapeditor.h"
#include "cimagestorage.h"
#include "cpartunion.h"
#include "cpart.h"
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

 CursorPart_Ptr.reset(new CPartUnion());

 //создаём карту
 Map_Ptr.reset(new CPartUnion());

 //подключим таймер обновления экрана
 TimerId=startTimer(TIMER_INTERVAL_MS); 

 LoadMap("last_map.bin");
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CMapEditor::~CMapEditor()
{
 killTimer(TimerId);
 SaveMap("last_map.bin");
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
 auto output_function=[this,&tw,&th,&qPainter,&qPixmap_Tiles](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x*CImageStorage::TILE_WIDTH;
  int32_t screen_y=block_y*CImageStorage::TILE_HEIGHT;
  screen_x-=qPoint_LeftTop.x();
  screen_y-=qPoint_LeftTop.y();

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH;
  int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT;

  qPainter.drawPixmap(screen_x,screen_y,qPixmap_Tiles.copy(tx,ty,tw,th));
 };
 Map_Ptr->Visit(output_function);


 //выводим блоки курсора
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

 auto cursoroutput_function=[this,&screen_x,&screen_y,&tw,&th,&qPainter,&qPixmap_Tiles](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH;
  int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT;

  int32_t ox=iPart_Ptr->BlockPosX*CImageStorage::TILE_WIDTH;
  int32_t oy=iPart_Ptr->BlockPosY*CImageStorage::TILE_HEIGHT;

  qPainter.drawPixmap(screen_x+ox,screen_y+oy,qPixmap_Tiles.copy(tx,ty,tw,th));
 };
 CursorPart_Ptr->Visit(cursoroutput_function);
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

 //выполняем установку тайлов
 //удаляем все тайлы, которые наложились

 std::shared_ptr<IPart> iPart_Map_Ptr=Map_Ptr;
 auto remove_function=[this,iPart_Map_Ptr,&block_x,&block_y](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  iPart_Map_Ptr->RemovePartIfCoord(block_x+iPart_Ptr->BlockPosX,block_y+iPart_Ptr->BlockPosY);
 };
 CursorPart_Ptr->Visit(remove_function);
 //накладываем тайлы
 auto add_function=[this,iPart_Map_Ptr,&block_x,&block_y](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  //смещаем положение на участок карты
  int32_t x=iPart_Ptr->BlockPosX+block_x;
  int32_t y=iPart_Ptr->BlockPosY+block_y;
  std::shared_ptr<IPart> iPart_New(new CPart(x,y,iPart_Ptr->cTilesSequence,iPart_Ptr->Barrier));
  iPart_Map_Ptr->GetItemPtr()->push_back(iPart_New);
 };
 CursorPart_Ptr->Visit(add_function);
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
//анимировать тайлы
//----------------------------------------------------------------------------------------------------
void CMapEditor::AnimateTiles(void)
{
 //анимируем выбранный тайл
 CursorPart_Ptr->AnimateTiles();
 //анимируем карту
 Map_Ptr->AnimateTiles();
}
//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//задать выбранную последовательность блоков
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetSelectedPart(std::shared_ptr<IPart> iPart_Ptr)
{
 CursorPart_Ptr=iPart_Ptr;
}
//----------------------------------------------------------------------------------------------------
//задать является ли выбранная часть барьером
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetSelectedBarrier(bool barrier)
{
 auto setbarrier_function=[&barrier](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  iPart_Ptr->Barrier=barrier;
 };
 CursorPart_Ptr->Visit(setbarrier_function);
}
//----------------------------------------------------------------------------------------------------
//записать карту
//----------------------------------------------------------------------------------------------------
bool CMapEditor::SaveMap(const std::string &file_name)
{
 std::ofstream file;
 file.open(file_name,std::ios_base::out|std::ios_base::binary);
 if (file.is_open()==false) return(false);
 Map_Ptr->Save(file);
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
 Map_Ptr->Release();
 Map_Ptr->Load(file);
 return(true);
}
