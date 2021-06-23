//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cpartunion.h"
#include "cpart.h"
#include <algorithm>

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
CPartUnion::CPartUnion(void)
{
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CPartUnion::~CPartUnion()
{
 Release();
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//записать
//----------------------------------------------------------------------------------------------------
bool CPartUnion::Save(std::ofstream &file)
{
 size_t part=Item.size();
 if (file.write(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);

 auto save_function=[&file](std::shared_ptr<IPart> iPart_Ptr)
 {
  bool part_union=true;
  if (iPart_Ptr->GetItemPtr()==NULL) part_union=false;
  if (file.write(reinterpret_cast<char*>(&part_union),sizeof(part_union)).fail()==true) return;
  iPart_Ptr->Save(file);
 };
 std::for_each(Item.begin(),Item.end(),save_function);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CPartUnion::Load(std::ifstream &file)
{
 size_t part;
 if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);

 for(size_t n=0;n<part;n++)
 {
  //загружаем, какого типа объект нам нужно создавать
  bool part_union;
  if (file.read(reinterpret_cast<char*>(&part_union),sizeof(part_union)).fail()==true) return(false);
  IPart *iPart_Ptr=NULL;
  if (part_union==true) iPart_Ptr=new CPartUnion();
                   else iPart_Ptr=new CPart();
  iPart_Ptr->Load(file);
  Item.push_back(std::shared_ptr<IPart>(iPart_Ptr));
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//получить указатель на список элементов
//----------------------------------------------------------------------------------------------------
std::list<std::shared_ptr<IPart>>* CPartUnion::GetItemPtr(void)
{
 return(&Item);
}
//----------------------------------------------------------------------------------------------------
//удалить все элементы
//----------------------------------------------------------------------------------------------------
void CPartUnion::Release(void)
{
 auto release_function=[](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->Release();
 };
 std::for_each(Item.begin(),Item.end(),release_function);
 Item.clear();
}
//----------------------------------------------------------------------------------------------------
//обойти все элементы
//----------------------------------------------------------------------------------------------------
void CPartUnion::Visit(std::function<void(std::shared_ptr<IPart>)> callback_function)
{
 callback_function(shared_from_this());//вызываем для самого себя
 auto visit_function=[&callback_function](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->Visit(callback_function);
 };
 std::for_each(Item.begin(),Item.end(),visit_function);
}
//----------------------------------------------------------------------------------------------------
//удалить часть
//----------------------------------------------------------------------------------------------------
void CPartUnion::RemovePart(std::function<bool(std::shared_ptr<IPart>)> callback_function)
{
 auto compare_function=[&callback_function](std::shared_ptr<IPart> iPart_Ptr)->bool
 {
  if (iPart_Ptr->GetItemPtr()!=NULL)
  {
   iPart_Ptr->RemovePart(callback_function);
   if (iPart_Ptr->GetItemPtr()->size()!=0) return(false);//ветка ещё не пустая
   return(true);//требуется удаление
  }
  if (callback_function(iPart_Ptr)==true) return(true);//требуется удаление
  return(false);
 };
 Item.erase(std::remove_if(Item.begin(),Item.end(),compare_function),Item.end());
}
//----------------------------------------------------------------------------------------------------
//выполнить анимацию тайлов
//----------------------------------------------------------------------------------------------------
void CPartUnion::AnimateTiles(void)
{
 auto animatetiles_function=[](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->AnimateTiles();
 };
 std::for_each(Item.begin(),Item.end(),animatetiles_function);
}