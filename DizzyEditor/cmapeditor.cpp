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

 CtrlOn=false;

 qPoint_LeftTop=QPoint(0,0); 
 qPoint_MousePos=QPoint(0,0);

 Mode=MODE_SELECT;
 MouseMode=MOUSE_MODE_STANDARD;

 CursorPart_Ptr.reset(new CPartUnion());

 //создаём карту
 Map_Ptr.reset(new CPartUnion());

 //создаём меню
 qMenu_Context=new QMenu(this);
 qMenu_Context->addAction("Сделать копию");
 connect(qMenu_Context,SIGNAL(triggered(QAction*)),SLOT(on_ContextMenu_CopyPart(QAction*)));

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

 if (MouseLButton==true)
 {
  if (Mode==MODE_SET) SetTile(x,y);  
  if (Mode==MODE_SELECT)
  {
   if (MouseMode==MOUSE_MODE_SELECT_AREA)
   {
    int32_t map_x;
    int32_t map_y;
    MouseToMap(x,y,map_x,map_y);

    int x1;
    int y1;
    int x2;
    int y2;
    qRect_SelectedArea.getCoords(&x1,&y1,&x2,&y2);
    qRect_SelectedArea.setCoords(x1,y1,map_x,map_y);
   }
  }
 }
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
  if (Mode==MODE_SET) SetTile(x,y);
  if (Mode==MODE_SELECT)
  {
   if (CtrlOn==true) SelectTile(x,y);
   else
   {
    UnselectTiles();
    MouseMode=MOUSE_MODE_SELECT_AREA;
    int32_t map_x;
    int32_t map_y;
    MouseToMap(x,y,map_x,map_y);
    qRect_SelectedArea.setCoords(map_x,map_y,map_x,map_y);
   }
  }
 }
 if (qMouseEvent_Ptr->button()&Qt::RightButton)
 {
  if (MouseRButton==false) MouseRButton=true;
  qPoint_MouseRightButtonDownPos=QPoint(x,y);
  if (Mode==MODE_SELECT)
  {
   if (IsTileSelected(x,y)==true)//нажатие произошло на выбранном тайле
   {
    MouseRButton=false;
    qMenu_Context->exec(qMouseEvent_Ptr->globalPos());
   }
  }
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

  if (Mode==MODE_SELECT)
  {
   if (MouseMode==MOUSE_MODE_SELECT_AREA)
   {
    //для всей выделенной области вызываем выбор блоков
    SelectTiles(qRect_SelectedArea);
    MouseMode=MOUSE_MODE_STANDARD;
   }
  }
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

 DrawMap(qPainter);
 DrawGrid(qPainter,w_width,w_height);
 if (MouseMode==MOUSE_MODE_SELECT_AREA) DrawSelectedArea(qPainter);
 if (Mode==MODE_SET) DrawCursor(qPainter);
}

//----------------------------------------------------------------------------------------------------
//рисование сетки
//----------------------------------------------------------------------------------------------------
void CMapEditor::DrawGrid(QPainter &qPainter,int32_t w_width,int32_t w_height)
{
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
}
//----------------------------------------------------------------------------------------------------
//рисование карты
//----------------------------------------------------------------------------------------------------
void CMapEditor::DrawMap(QPainter &qPainter)
{
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

  int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH+CImageStorage::TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT+CImageStorage::TILE_BORDER_HEIGHT;

  if (iPart_Ptr->Selected==false)
  {
   qPainter.drawPixmap(screen_x,screen_y,qPixmap_Tiles.copy(tx,ty,tw,th));
   return;
  }
  //выводим выбранный блок
  qPainter.drawPixmap(screen_x,screen_y,qPixmap_Tiles.copy(tx,ty,tw,th));

  qPainter.setPen(QPen(Qt::yellow,1,Qt::SolidLine));
  qPainter.drawRect(screen_x+1,screen_y+1,tw-2,th-2);
  qPainter.setPen(QPen(Qt::green,1,Qt::SolidLine));
  qPainter.drawRect(screen_x+2,screen_y+2,tw-4,th-4);
 };
 Map_Ptr->Visit(output_function);
}
//----------------------------------------------------------------------------------------------------
//рисование курсора
//----------------------------------------------------------------------------------------------------
void CMapEditor::DrawCursor(QPainter &qPainter)
{
 QPixmap &qPixmap_Tiles=CImageStorage::GetPtr()->GetTiles();

 int32_t tw=CImageStorage::TILE_WIDTH;
 int32_t th=CImageStorage::TILE_HEIGHT;

 //координаты в общем пространстве
 int32_t block_x;
 int32_t block_y;
 MouseToMap(qPoint_MousePos.x(),qPoint_MousePos.y(),block_x,block_y);

 int32_t screen_x=block_x*CImageStorage::TILE_WIDTH;
 int32_t screen_y=block_y*CImageStorage::TILE_HEIGHT;

 screen_x-=qPoint_LeftTop.x();
 screen_y-=qPoint_LeftTop.y();

 auto cursoroutput_function=[this,&screen_x,&screen_y,&tw,&th,&qPainter,&qPixmap_Tiles](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*CImageStorage::TILE_WITH_BORDER_WIDTH+CImageStorage::TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*CImageStorage::TILE_WITH_BORDER_HEIGHT+CImageStorage::TILE_BORDER_HEIGHT;

  int32_t ox=iPart_Ptr->BlockPosX*CImageStorage::TILE_WIDTH;
  int32_t oy=iPart_Ptr->BlockPosY*CImageStorage::TILE_HEIGHT;

  qPainter.drawPixmap(screen_x+ox,screen_y+oy,qPixmap_Tiles.copy(tx,ty,tw,th));
 };
 CursorPart_Ptr->Visit(cursoroutput_function);
}
//----------------------------------------------------------------------------------------------------
//рисование области выделения
//----------------------------------------------------------------------------------------------------
void CMapEditor::DrawSelectedArea(QPainter &qPainter)
{
 //выводим выделенную область
 int x1;
 int y1;
 int x2;
 int y2;
 qRect_SelectedArea.getCoords(&x1,&y1,&x2,&y2);

 if (x2<x1)
 {
  int x=x2;
  x2=x1;
  x1=x;
 }
 if (y2<y1)
 {
  int y=y2;
  y2=y1;
  y1=y;
 }

 x2++;
 y2++;
 int32_t ox1=x1*CImageStorage::TILE_WIDTH-qPoint_LeftTop.x();
 int32_t oy1=y1*CImageStorage::TILE_HEIGHT-qPoint_LeftTop.y();
 int32_t ox2=x2*CImageStorage::TILE_WIDTH-qPoint_LeftTop.x();
 int32_t oy2=y2*CImageStorage::TILE_HEIGHT-qPoint_LeftTop.y();

 qPainter.setPen(QPen(Qt::white,1,Qt::DashDotLine));
 qPainter.drawRect(ox1,oy1,(ox2-ox1),(oy2-oy1));
}
//----------------------------------------------------------------------------------------------------
//поставить тайл в позицию
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetTile(int32_t mouse_x,int32_t mouse_y)
{
 int32_t block_x;
 int32_t block_y;
 MouseToMap(mouse_x,mouse_y,block_x,block_y);

 //выполняем установку тайлов
 //удаляем все тайлы, которые наложились
 std::shared_ptr<IPart> iPart_Map_Ptr=Map_Ptr;
 auto remove_function=[this,iPart_Map_Ptr,&block_x,&block_y](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент  
  void RemovePart(std::function<bool(std::shared_ptr<IPart>)> callback_function);//удалить часть
  auto if_function=[this,&block_x,&block_y,&iPart_Ptr](std::shared_ptr<IPart> iPart_Local_Ptr)->bool
  {
   return(iPart_Local_Ptr->IsCoord(block_x+iPart_Ptr->BlockPosX,block_y+iPart_Ptr->BlockPosY));
  };
  iPart_Map_Ptr->RemovePart(if_function);
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
//выбрать тайл
//----------------------------------------------------------------------------------------------------
void CMapEditor::SelectTile(int32_t mouse_x,int32_t mouse_y)
{
 int32_t block_x;
 int32_t block_y;
 MouseToMap(mouse_x,mouse_y,block_x,block_y);
 //выбираем или отменяем выделение блоков
 auto select_function=[this,&block_x,&block_y](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  if (iPart_Ptr->IsCoord(block_x,block_y)==true)
  {
   if (iPart_Ptr->Selected==true) iPart_Ptr->Selected=false;
                             else iPart_Ptr->Selected=true;
  }
 };
 Map_Ptr->Visit(select_function);
}
//----------------------------------------------------------------------------------------------------
//выбрать область тайлов
//----------------------------------------------------------------------------------------------------
void CMapEditor::SelectTiles(QRect &qRect_Area)
{
 //выбираем выделение блоков
 auto select_function=[this,&qRect_Area](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  int x1;
  int y1;
  int x2;
  int y2;
  qRect_Area.getCoords(&x1,&y1,&x2,&y2);
  if (x1>x2)
  {
   int x=x1;
   x1=x2;
   x2=x;
  }
  if (y1>y2)
  {
   int y=y1;
   y1=y2;
   y2=y;
  }
  for(int x=x1;x<=x2;x++)
  {
   for(int y=y1;y<=y2;y++)
   {
    if (iPart_Ptr->IsCoord(x,y)==true) iPart_Ptr->Selected=true;
   }
  }
 };
 Map_Ptr->Visit(select_function);
}
//----------------------------------------------------------------------------------------------------
//отменить выбор тайлов
//----------------------------------------------------------------------------------------------------
void CMapEditor::UnselectTiles(void)
{
 //отменяем выделение блоков
 auto select_function=[this](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  iPart_Ptr->Selected=false;
 };
 Map_Ptr->Visit(select_function);
}
//----------------------------------------------------------------------------------------------------
//удалить выбранные тайлы
//----------------------------------------------------------------------------------------------------
void CMapEditor::DeleteSelectedTiles(void)
{
 //удаляем все выделенные тайлы
 auto if_function=[](std::shared_ptr<IPart> iPart_Ptr)->bool
 {
  return(iPart_Ptr->Selected);
 };
 Map_Ptr->RemovePart(if_function);
}
//----------------------------------------------------------------------------------------------------
//проверить, что по данным координатам мышки тайл выбран
//----------------------------------------------------------------------------------------------------
bool CMapEditor::IsTileSelected(int32_t mouse_x,int32_t mouse_y)
{
 bool selected=false;
 int32_t block_x;
 int32_t block_y;
 MouseToMap(mouse_x,mouse_y,block_x,block_y);
 auto isselect_function=[this,&block_x,&block_y,&selected](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  if (iPart_Ptr->IsCoord(block_x,block_y)==true)
  {
  if (iPart_Ptr->Selected==true) selected=true;
  }
 };
 Map_Ptr->Visit(isselect_function);
 return(selected);
}
//----------------------------------------------------------------------------------------------------
//объединить выбранные тайлы и установить результат в качестве курсора
//----------------------------------------------------------------------------------------------------
void CMapEditor::ConnectSelectedTiles(void)
{
 int32_t min_x=0;
 int32_t min_y=0;
 bool first=true;
 std::shared_ptr<IPart> iPart_Set_Ptr(new CPartUnion());
 auto select_function=[this,&iPart_Set_Ptr,&min_x,&min_y,&first](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  if (iPart_Ptr->Selected==true)
  {
   IPart* iPart_Local_Ptr=new CPart();
   *iPart_Local_Ptr=*iPart_Ptr;
   iPart_Local_Ptr->Selected=false;
   iPart_Set_Ptr->GetItemPtr()->push_back(std::shared_ptr<IPart>(iPart_Local_Ptr));
   if (iPart_Ptr->BlockPosX<min_x || first==true) min_x=iPart_Ptr->BlockPosX;
   if (iPart_Ptr->BlockPosY<min_y || first==true) min_y=iPart_Ptr->BlockPosY;
   first=false;
  }
 };
 Map_Ptr->Visit(select_function);
 //вычитаем минимальную координату
 auto subcoord_function=[this,&min_x,&min_y](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  iPart_Ptr->BlockPosX-=min_x;
  iPart_Ptr->BlockPosY-=min_y;
 };
 iPart_Set_Ptr->Visit(subcoord_function);

 SetSelectedPart(iPart_Set_Ptr);
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
//----------------------------------------------------------------------------------------------------
//перевести координаты мыши в координаты блоков карты
//----------------------------------------------------------------------------------------------------
void CMapEditor::MouseToMap(int32_t mouse_x,int32_t mouse_y,int32_t &map_x,int32_t &map_y)
{
 //координаты в общем пространстве
 QPoint qPoint(mouse_x,mouse_y);
 map_x=(qPoint+qPoint_LeftTop).x();
 map_y=(qPoint+qPoint_LeftTop).y();
 //координаты в индексах блоков
 map_x=map_x/CImageStorage::TILE_WIDTH;
 map_y=map_y/CImageStorage::TILE_HEIGHT;
}

//----------------------------------------------------------------------------------------------------
//слот выбора в контекстном меню пункта "скопировать"
//----------------------------------------------------------------------------------------------------
void CMapEditor::on_ContextMenu_CopyPart(QAction *pAction)
{
 ConnectSelectedTiles();//объединяем выбранные тайлы и устанавливаем их в качестве курсора
 //переключаемся принудительно в режим установки блоков
 SetModeSetPart();
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
//----------------------------------------------------------------------------------------------------
//экспортировать карту
//----------------------------------------------------------------------------------------------------
bool CMapEditor::ExportMap(const std::string &file_name)
{
 std::ofstream file;
 file.open(file_name,std::ios_base::out|std::ios_base::binary);
 if (file.is_open()==false) return(false);
 //считаем количество блоков
 int32_t counter=0;
 auto counter_function=[this,&counter](std::shared_ptr<IPart> iPart_Ptr)
 {
  if (iPart_Ptr->GetItemPtr()!=NULL) return;//это объединение элементов, а не один элемент
  counter++;
 };
 Map_Ptr->Visit(counter_function);

 if (file.write(reinterpret_cast<char*>(&counter),sizeof(counter)).fail()==true) return(false);
 Map_Ptr->Export(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//установить режим установки блоков
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetModeSetPart(void)
{
 MouseMode=MOUSE_MODE_STANDARD;
 Mode=MODE_SET;
 UnselectTiles();
}
//----------------------------------------------------------------------------------------------------
//установить режим выбора блоков
//----------------------------------------------------------------------------------------------------
void CMapEditor::SetModeSelectPart(void)
{ 
 MouseMode=MOUSE_MODE_STANDARD;
 Mode=MODE_SELECT;
}
//----------------------------------------------------------------------------------------------------
//нажатие клавиши
//----------------------------------------------------------------------------------------------------
void CMapEditor::PressKey(QKeyEvent *pe)
{
 if (pe->key()==Qt::Key_Delete) DeleteSelectedTiles();
 if (pe->key()==Qt::Key_Control) CtrlOn=true;
}
//----------------------------------------------------------------------------------------------------
//отпускание клавиши
//----------------------------------------------------------------------------------------------------
void CMapEditor::ReleaseKey(QKeyEvent *pe)
{
 if (pe->key()==Qt::Key_Control) CtrlOn=false;
}
